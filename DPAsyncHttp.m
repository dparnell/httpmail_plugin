//
//  DPAsyncHttp.m
//  httpmail
//
//  Created by Daniel Parnell on Mon May 05 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPAsyncHttp.h"
#import "DPStringUtils.h"
#import "DPMD5.h"
#import "DPAsyncHttpHelper.h"
#import "DPHTTPMailDebugger.h"

//#define DEBUG_HTTP

#define STATE_CONNECTING	0
#define STATE_SENDING		1
#define STATE_RESPONSE		2
#define STATE_HEADERS		3
#define STATE_DATA		4
#define STATE_CHUNKHEADER	5
#define STATE_CHUNKFOOTER	6
#define STATE_NOMORECHUNKS	7
#define STATE_FINISHED		8

@interface DPAsyncNonceHolder : NSObject {
    int	count;
}
- (NSString*) nextValue;
@end

@implementation DPAsyncNonceHolder

- (id) init {
    self = [super init];
    
    if(self) {
        count = 1;
    }
    
    return self;
}

- (NSString*) nextValue {
    return [NSString stringWithFormat: @"%08X", count++];
}

@end

@interface DPAsyncSocket (StringAdditions) 
- (void)writeString:(NSString*)string;
@end

@implementation DPAsyncSocket (StringAdditions) 

- (void)writeString:(NSString*)string {
    NSData* data = [string dataUsingEncoding: NSUTF8StringEncoding];
    [self writeData: data];
}

@end

@interface DPAsyncHttp (Private)

- (void)internalGet:(DPAsyncSocket*)aSocket;
- (void)sendRequest:(DPAsyncSocket*)socket;
- (void)internalDownloadFinished:(DPAsyncSocket*)aSocket;
- (void)notifyDelegateDownloadFinished;
- (void)notifyDelegateOfSocketError:(CFSocketError)error;

@end

@implementation DPAsyncHttp

+ (id)newWithURL:(NSURL*)url {
   return [[[DPAsyncHttp alloc] initWithURL: url] autorelease];
}

- (void)initvars {
//    NSLog(@"DPAsyncHttp init");
    
    fUrl = NULL;
    fHeaders = [[NSMutableDictionary dictionary] retain];
    fCookies = [[NSMutableDictionary dictionary] retain];
    fResponseHeaders = [[NSMutableDictionary dictionary] retain];
    [self setMethod: @"GET"];
    fFollowRedirections = YES;
    fRequestContent = NULL;
    fRequestContentType = NULL;
    fProxy = NULL;
    fProxyUsername = NULL;
    fProxyPassword = NULL;
    fProxyRealm = NULL;
    fUsername = NULL;
    fPassword = NULL;
    nonce = NULL;
    opaque = NULL;
    realm = NULL;
    authMethod = NULL;
    nonce_counts = [[NSMutableDictionary dictionary] retain]; 
    responseData = NULL;    
    socketTimeout = 30;
    
    [self setHeaderValue: @"DPhttp 1.0" forKey: @"User-Agent"];
    
    delegate = NULL;
}

- (id)init {
    self = [super init];

    if(self) {
        [self initvars];
    }
    
    return self;
}

- (id)initWithURL:(NSURL*)url {
    self = [super init];

    if(self) {
        [self initvars];
        fUrl = [url retain];
    }
    
    return self;
}

- (void)dealloc {
//    NSLog(@"DPAsyncHttp dealloc %@", self);
    
    [self setDelegate: nil];
    [self close];
    
    [fUrl release];
    [fHeaders release];
    [fCookies release];
    [fResponseHeaders release];
    [fProxy release];
    [fProxyUsername release];
    [fProxyPassword release];
    [fProxyRealm release];
    [fUsername release];
    [fPassword release];
    [nonce release];
    [opaque release];
    [realm release];
    [authMethod release];
    [fRequestContent release];
    [fRequestContentType release];
    [nonce_counts release];
    [fResponseString release];
    [responseData release];
    
    [super dealloc];
}

- (void)setURL:(NSURL*)url {
    [url retain];
    [fUrl release];
    fUrl = url;
}

- (NSURL*)URL {
    return fUrl;
}

- (void)setMethod:(NSString*)method {
    [method retain];
    [fMethod release];
    fMethod = method;
}

- (NSString*)method {
    return fMethod;
}

- (void)parseResponse:(NSString*)response {
    NSString* code;
    NSString* message;
    NSRange p;

    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"header = %@", response]];
    }
#ifdef DEBUG_HTTP
    NSLog(@"got response '%@'", response);
#endif

    p = [response rangeOfString: @" "];
    
    if(p.location!=NSNotFound) {
        p.location = p.location + 1;
        p.length = 3;
        code = [response substringWithRange: p];
        message = [response substringFromIndex: p.location+4];
    
        fResponseCode = [code intValue];
        [fResponseString release];
        fResponseString = [message retain];
    } else {
        [fResponseString release];
        fResponseString = [response retain];
        fResponseCode = -1;
    }
}

- (void)parseCookie:(NSString*)cookie {
    NSRange p1;
    NSRange p2;
    NSString* name;
    NSString* value;
        
    p1 = [cookie rangeOfString: @"="];
    p2 = [cookie rangeOfString: @";"];
    
    name = [cookie substringToIndex: p1.location];
    if(p2.location==NSNotFound) {
        value = [cookie substringFromIndex: p1.location+1];
    } else {
        p1.length = p2.location - p1.location-1;
        p1.location = p1.location+1;
        value = [cookie substringWithRange: p1];
    } 

    [self setCookieValue: value forKey: name];
}

- (void)processProxyAuthenticate:(NSString*)proxyAuth {
    if([proxyAuth hasPrefix: @"Basic "]) {
        NSString* therest = [proxyAuth substringFromIndex: 6];
        NSDictionary* dict = [DPStringUtils dictionaryFromString: therest separatedBy: ' '];
        
        [fProxyRealm release];
        fProxyRealm = [[dict objectForKey: @"realm"] retain];
    }
}

- (void)parseResponseHeader:(NSString*)header {
    NSRange p;
    NSString* name;
    NSString* value;

    p = [header rangeOfString: @": "];
    
    if(p.location!=NSNotFound) {
        name = [header substringToIndex: p.location];
        value = [header substringFromIndex: p.location + p.length];

    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"got header = %@", header]];
    }
#ifdef DEBUG_HTTP
    NSLog(@"got header %@='%@'", name, value);
#endif    
        
        if([name isEqualToString: @"Set-Cookie"]) {
            [self parseCookie: value];
        } else {
            if([name isEqualToString: @"Proxy-Authenticate"]) {
                [self processProxyAuthenticate: value];
            }
            
            [fResponseHeaders setObject: value forKey: name];
        }
    }
}

- (void)processDigestAuthRequest:(NSString*)auth {
    NSDictionary* dict;
    
    dict = [DPStringUtils dictionaryFromString: auth separatedBy: ','];
    
    nonce = [[dict objectForKey: @"nonce"] retain];
    opaque = [[dict objectForKey: @"opaque"] retain];
    realm = [[dict objectForKey: @"realm"] retain];
    qop = [[dict objectForKey: @"qop"] retain];
}

- (void)processAuthorizationRequest; {
    NSString* auth;
    NSRange p;
    
    auth = [self responseHeaderForKey: @"WWW-Authenticate"];
    
    p = [auth rangeOfString: @" "];
    [authMethod release];
    authMethod = [[auth substringToIndex: p.location] retain];
    
    if([authMethod isEqualToString: @"Digest"]) {
        [self processDigestAuthRequest: [auth substringFromIndex: p.location+1]];
    } else {
        /** @todo add code to handle the Basic auth scheme */
        
        [NSException raise: @"AUTHORIZATION ERROR" format: @"Unknown authorization method: %@", authMethod];
    }    
}

- (NSString*)nonceCountForNonce: (NSString*)n {
    if(n) {
        DPAsyncNonceHolder* h = [nonce_counts objectForKey: n];
        if(h==NULL) {
            h = [[DPAsyncNonceHolder new] autorelease];
            [nonce_counts setObject: h forKey: n];
        }
    
        return [h nextValue];
    }
    
    return NULL;
}

- (void) addDigestAuthorization {
    NSMutableString* response = [NSMutableString string];
    NSString* uri = [fUrl path];
    NSString* A1;
    NSString* A2;
    NSString* temp;
    NSString* digest;
    NSString* cnonce;
    NSString* nc;
    
    A1 = [NSString stringWithFormat: @"%@:%@:%@", fUsername, realm, fPassword]; 
    A2 = [NSString stringWithFormat: @"%@:%@", fMethod, uri];
    
    nc = [self nonceCountForNonce: nonce];
    
    cnonce = [DPMD5 computeFor: [NSString stringWithFormat: @"%08X", time(NULL)]];
    
    if(qop && [qop isEqualToString: @"auth"]) {
        temp = [NSString stringWithFormat: @"%@:%@:%@:%@:%@:%@", [DPMD5 computeFor: A1], nonce, nc, cnonce, qop, [DPMD5 computeFor: A2]];
    } else {
        temp = [NSString stringWithFormat: @"%@:%@:%@", [DPMD5 computeFor: A1], nonce, [DPMD5 computeFor: A2]];
    }
    
    digest = [DPMD5 computeFor: temp];
    
    [response appendString: @"Digest "];
    
    [response appendString: @"username=\""];
    [response appendString: fUsername];
    [response appendString: @"\", "];
    
    [response appendString: @"realm=\""];
    [response appendString: realm];
    [response appendString: @"\", "];

    if(qop && [qop isEqualToString: @"auth"]) {
        [response appendString: @"qop=\"auth\", "];
    }
    
    [response appendString: @"algorithm=\"MD5\", "];

    if(qop && [qop isEqualToString: @"auth"]) {        
        [response appendString: @"nc="];
        [response appendString: nc];
        [response appendString: @", "];
        
        [response appendString: @"cnonce=\""];
        [response appendString: cnonce];
        [response appendString: @"\", "];
    }

    if(nonce) {
        [response appendString: @"nonce=\""];
        [response appendString: nonce];
        [response appendString: @"\", "];
    }

    [response appendString: @"uri=\""];
    [response appendString: uri];
    [response appendString: @"\", "];
                
    [response appendString: @"response=\""];
    [response appendString: digest];
    [response appendString: @"\""];
    
    if(opaque) {
        [response appendString: @", opaque=\""];
        [response appendString: opaque];
        [response appendString: @"\" "];
    }
        
    [self setHeaderValue: response forKey: @"Authorization"];
}

- (void) addAuthorization {
    if(authMethod) {
        if([authMethod isEqualToString: @"Digest"]) {
            [self addDigestAuthorization];
        } else {
            /** @todo add code to handle the Basic auth scheme */
        
            [NSException raise: @"AUTHORIZATION ERROR" format: @"Unknown authorization method: %@", authMethod];
        }
    }
}

- (void) addProxyAuthorization {
    if(fProxy && fProxyUsername && fProxyPassword && fProxyRealm) {
        NSString* temp = [NSString stringWithFormat: @"%@:%@", fProxyUsername, fProxyPassword];
        NSString* auth = [NSString stringWithFormat: @"Basic %@", [DPStringUtils base64Encode: temp]];
        [self setHeaderValue: auth forKey: @"Proxy-Authorization"];
    }
}

- (void) clearAuthorization {
    [authMethod release];
    authMethod = NULL;
    [nonce release];
    nonce = NULL;
    [opaque release];
    opaque = NULL;
    [realm release];
    realm = NULL;
    [qop release];
    qop = NULL;
    
    [self removeHeaderForKey: @"Authorization"];
}

- (void)setHeaderValue:(NSString*)data forKey:(NSString*)key {
    if(data==nil || key==nil) {
        if([DPHTTPMailDebugger debugEnabled]) {
            [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"bad header value '%@' for key '%@'", data, key]];
        }
        NSLog(@"bad header value '%@' for key '%@'", data, key);
    } else {
        [fHeaders setObject: data forKey: key];
    }
}

- (NSString*)headerValueForKey:(NSString*)key {
    return (NSString*)[fHeaders objectForKey: key];
}

- (void)clearHeaders {
    [fHeaders removeAllObjects];
}

- (NSDictionary*)headers {
    return fHeaders;
}

- (void)removeHeaderForKey:(NSString*)key {
    [fHeaders removeObjectForKey: key];
}

- (void)setCookieValue:(NSString*)data forKey:(NSString*)key {    
    [fCookies setObject: data forKey: key];
}

- (NSString*)cookieValueForKey:(NSString*)key {
    return (NSString*)[fCookies objectForKey: key];
}

- (void)clearCookies {
    [fCookies removeAllObjects];
}

- (NSDictionary*)cookies {
    return fCookies;
}

- (void)setCookies:(NSDictionary*)cookies {
    [fCookies removeAllObjects];
    [fCookies addEntriesFromDictionary: cookies];
}

- (void)removeCookieForKey:(NSString*)key {
    [fCookies removeObjectForKey: key];
}

- (int)responseCode {
    return fResponseCode;
}

- (NSString*)responseString {
    return fResponseString;
}

- (NSString*)responseHeaderForKey:(NSString*)key {
    return (NSString*)[fResponseHeaders objectForKey: key];
}

- (NSDictionary*)responseHeaders {
    return fResponseHeaders;
}

- (void)setFollowRedirections:(bool)follow {
    fFollowRedirections = follow;
}

- (bool)followRedirections {
    return fFollowRedirections;
}

- (NSData*)requestContent {
    return fRequestContent;
}

- (void)setRequestContent:(NSData*)data {
    if(fRequestContent) {
        [fRequestContent release];
    }
    
    fRequestContent = [data retain];
}

- (void)setRequestContentAsString:(NSString*)string {
    NSMutableData* data = [NSMutableData data];
    const char* buf = [string cStringUsingEncoding: NSUTF8StringEncoding];
	
    [data appendBytes: buf length: strlen(buf)];
    
    [self setRequestContent: data];
}

- (NSString*)requestContentType {
    return fRequestContentType;
}

- (void)setRequestContentType:(NSString*)type {
    if(fRequestContentType) {
        [fRequestContentType release];
    }
    
    fRequestContentType = [[NSString stringWithString: type] retain];
}

- (NSURL*)proxy {
    return fProxy;
}

- (void)setProxy:(NSURL*)url {
    [url retain];
    [fProxy release];
    fProxy = url;
}

- (void)setProxyUsername:(NSString*)username {
    [username retain];
    [fProxyUsername release];
    fProxyUsername = username;
}

- (NSString*)proxyUsername {
    return fProxyUsername;
}

- (void)setProxyPassword:(NSString*)password {
    [password retain];
    [fProxyPassword release];
    fProxyPassword = password;
}

- (NSString*)proxyPassword {
    return fProxyPassword;
}

- (void)setUsername:(NSString*)username {
    [username retain];
    [fUsername release];
    fUsername = username;
}

- (NSString*)username {
    return fUsername;
}

- (void)setPassword:(NSString*)password {
    [password retain];
    [fPassword release];
    fPassword = password;
}

- (NSString*)password {
    return fPassword;
}

- (void)setDelegate:(id)ADelegate {
    [ADelegate retain];
    [delegate release];
    delegate = ADelegate;
}

- (void)notifyDelegateDownloadFinished {
    if(delegate && [delegate respondsToSelector: @selector(downloadFinished:)]) {
        [delegate downloadFinished: self];
    }
}

- (void) notifyDelegateOfSocketError:(CFSocketError)error {
    if(delegate && [delegate respondsToSelector: @selector(downloadFailed:dueToError:)]) {
        [delegate downloadFailed: self dueToError: error];
    }
}

- (void)internalDownloadFinished:(DPAsyncSocket*)aSocket {
    BOOL again = YES;
    
    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"data = %@", [[NSString alloc] initWithData: responseData encoding: NSWindowsCP1250StringEncoding] ]];
    }

    if([[self responseHeaderForKey: @"Connection"] isEqualToString: @"close"]) {
        [aSocket close];
    }

    state = STATE_FINISHED;
    
    if((fResponseCode==HTTP_PROXY_AUTH_REQUIRED) && !proxyAuthSent) {
        proxyAuthSent = YES;
    } else 
    if((fResponseCode==HTTP_UNAUTHORIZED) && !passwordSent && fUsername && fPassword) {
        passwordSent = YES;
        [self processAuthorizationRequest];
    } else {
        if(fFollowRedirections) {
            if((fResponseCode==HTTP_MOVED_PERMANENTLY) || 
                (fResponseCode==HTTP_MOVED_TEMPORARILY) || 
                (fResponseCode==HTTP_SEE_OTHER)) {
                NSURL* newUrl;
                                    
                NSString* location = [fResponseHeaders objectForKey: @"Location"];

                if(location==NULL) {
                    location = [fResponseHeaders objectForKey: @"Content-Location"];
                }
                
                if(location==NULL) {
                    NSLog(@"%@", fResponseHeaders);
                }
                
                if([location hasPrefix: @"http://"]) {
                    newUrl = [NSURL URLWithString: location];
                    
                    // close the socket
                    [aSocket close];
//                    shouldClose = YES;
                    passwordSent = NO;
                    [self clearAuthorization];
                } else {
                    newUrl = [[NSURL URLWithString: location relativeToURL: fUrl] absoluteURL];
                    shouldClose = NO;
                }
                
                if([DPHTTPMailDebugger debugEnabled]) {
                    [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"got redirection %d to %@", fResponseCode, location]];
                }
#ifdef DEBUG_HTTP
                NSLog(@"Got redirection %d to %@", fResponseCode, location);
#endif
                [self setHeaderValue: [fUrl absoluteString] forKey: @"Referer"];
                [self setURL: newUrl];
                again = YES;
            } else {
                again = NO;
            }
        } else {
            again = NO;
        }
    }
    
    if(again) {
        [self internalGet: aSocket];
    } else {
        [aSocket close];
        
        [self notifyDelegateDownloadFinished];
    }
}

- (void)internalGet:(DPAsyncSocket*)aSocket {
    NSURL* url;
	
	fStopped = NO;
	
    state = STATE_CONNECTING;
        
    if(fProxy) {
        url = fProxy;
    } else {
        url = fUrl;
    }
    
    NSString* host = [url host];
    int port = [[url port] intValue];
    if(port==0) {
        port = 80;    
    }

    if(host==nil) {
        NSLog(@"host = nil -- url = %@", url);
        host = [self headerValueForKey: @"Host"];
        NSLog(@"           -- set host to '%@'", host);
    }
    
    [fResponseHeaders removeAllObjects];

    [self setHeaderValue: [fUrl host] forKey: @"Host"];
    
    if(shouldClose) {
        [self setHeaderValue: @"close" forKey: @"Connection"];
    }
    
    [self setHeaderValue: @"no-cache" forKey: @"Cache-Control"];

    if(authMethod) {
        [self addAuthorization];
    }
    
    if(fProxy) {
        [self addProxyAuthorization];
    }
    
    if(fRequestContent) {
        [self setHeaderValue: [NSString stringWithFormat: @"%d", [fRequestContent length]] forKey: @"Content-Length"];
    } else {
        [self removeHeaderForKey: @"Content-Length"];
    }
    
    if(fRequestContentType && fRequestContent) {
        [self setHeaderValue: fRequestContentType forKey: @"Content-Type"];
    } else {
        [self removeHeaderForKey: @"Content-Type"];
    }
       
    if(aSocket) {
        if(![aSocket isOpen]) {
            [aSocket setHost: host];
            [aSocket setPort: port];
            [aSocket open];
        }
    } else {
//        NSLog(@"creating socket");
        socket = [[DPAsyncSocket newSocketWithHost: host andPort: port] retain];
        [socket setDelegate: self];
        
        [socket open];
        
        aSocket = socket;
    }

// the request is sent in response to the connection opening
//    [self sendRequest: aSocket];
}

- (void)asyncGet {
    shouldClose = NO;
    passwordSent = NO;
    proxyAuthSent = NO;
    
    [self internalGet: socket];
}

- (void)sendRequest:(DPAsyncSocket*)aSocket {
    NSEnumerator *keys = NULL;
    NSString* key = NULL;
    NSString* uri = NULL;

    [responseData release];
    responseData = [[NSMutableData data] retain];
    
    state = STATE_SENDING;
    
    uri = [fUrl absoluteString];
        
	if(fProxy==nil) {
		NSRange hostRange = [uri rangeOfString: [fUrl host]];
		uri = [uri substringFromIndex: hostRange.location+hostRange.length];
	}
    
    // send the request method and URI
    [aSocket writeString: [NSString stringWithFormat: @"%@ %@ HTTP/1.1\r\n", fMethod, uri]];

    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sent request %@ %@", fMethod, uri]];
    }
#ifdef DEBUG_HTTP
    NSLog(@"%@ %@", fMethod, uri);
#endif
    // send the request headers
    keys = [fHeaders keyEnumerator];
    while ((key = [keys nextObject])) {
        NSString* buf = [NSString stringWithFormat: @"%@: %@\r\n", key, [fHeaders objectForKey: key]];
#ifdef DEBUG_HTTP
        NSLog(@"Sending %@", buf);
#endif
        [aSocket writeString: buf];  
        if([DPHTTPMailDebugger debugEnabled]) {
            [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sent %@", buf]];
        }
    }

    // send the cookies
    keys = [fCookies keyEnumerator];
    NSMutableString* cookies = [NSMutableString string];
    int cc = 0;
    [cookies appendString: @"Cookie:"];
    while ((key = [keys nextObject])) {
        [cookies appendString: [NSString stringWithFormat: @" %@=%@;", key, [fCookies objectForKey: key]]];
        cc++;
    }

    if(cc) {
        [cookies appendString: @"\r\n"];
#ifdef DEBUG_HTTP
        NSLog(@"Sending %@", cookies);
#endif
        [aSocket writeString: cookies];
        if([DPHTTPMailDebugger debugEnabled]) {
            [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sent cookies = %@", cookies]];
        }
    }
    
    // tell the server we are done sending the request
    [aSocket writeString: @"\r\n"];
    
    // send the request content if there is any
    if(fRequestContent) {
        [aSocket writeData: fRequestContent];
    }
    
    state = STATE_RESPONSE;
    linePos = 0;
}

- (NSData*)responseData {
    return responseData;
}

- (void)close {
    [socket setDelegate: nil];
    [socket close];
    [socket release];
    socket = nil;
}

// socket delegate routines
- (void)socketConnected:(DPAsyncSocket*)inSocket {
    [self sendRequest:inSocket];
}

- (void) internalDownloadProgress {
    if(delegate && [delegate respondsToSelector: @selector(downloadProgress: of: forAsyncHttp:)]) {
        [delegate downloadProgress: [responseData length] of: responseSize forAsyncHttp: self];
    }
}

- (void)socket:(DPAsyncSocket*)inSocket hasData: (NSData*)data {
//    NSString* s = [NSString stringWithCString: [data bytes] length: [data length]];
//    NSLog(@"%@", s);
//    printf("%s", [s cString]);
    
    if(state==STATE_DATA) {
        [responseData appendData: data];
        
        if([data length]>0) {
            [self internalDownloadProgress];
        }
        
        if([responseData length]>=responseSize) {
            [self internalDownloadFinished: inSocket];
        }
    } else {
        char* buf = (char*)[data bytes];
        int len = [data length];
        int i=0;
        
        while(i<len) {
            char ch = buf[i];
            
            if (ch=='\n') {
                NSString* line = nil;
                if(linePos) {
                    line = [NSString stringWithCString: &lineBuf[0] length: linePos-1];
                }

                switch(state) {
                    case STATE_RESPONSE: 
                        [self parseResponse: line];
                        
                        state = STATE_HEADERS;
                        break;
                    
                    case STATE_HEADERS:
                        if((line==nil) || [line isEqualToString: @""]) {
                            NSString* encoding = [self responseHeaderForKey: @"Transfer-Encoding"];
                            
                            if([encoding isEqualToString: @"chunked"]) {
                                state = STATE_CHUNKHEADER;
                            } else {
                                NSString* length = [self responseHeaderForKey: @"Content-Length"];
                                responseSize = [length intValue];
                                
                                state = STATE_DATA;

                                int L = len-(i+1);
                                if(L) {
                                    [responseData appendBytes: &buf[i+1] length: L];
                                    i = len;
                                }
                                
                                if([responseData length]>=responseSize) {
                                    [self  internalDownloadFinished: inSocket];
                                }

                            }
                            
                        } else {
                            [self parseResponseHeader: line];
                        }
                        
                        break;
                        
                    case STATE_CHUNKHEADER:
                        responseSize = [DPStringUtils hexValue: line];
                        if(responseSize==0) {
                            state = STATE_NOMORECHUNKS;
                        } else {
                            state = STATE_DATA;
                            
                            unsigned int L = len-(i+1);
                            
                            if(L>responseSize) {
                                L = responseSize;
                            }
                            
                            if(L) {
                                [responseData appendBytes: &buf[i+1] length: L];
                                i = i + L;
                                
                                if([responseData length]>=responseSize) {
                                    state = STATE_CHUNKFOOTER;
                                }
                            }
                        }
                        
                        break;
                        
                    case STATE_CHUNKFOOTER:
                        if([line isEqualToString: @""]) {
                            state = STATE_CHUNKHEADER;
                        }
                        
                        break;
                        
                    case STATE_NOMORECHUNKS:
                        [self  internalDownloadFinished: inSocket];
                    
                        break;
                }
                
                linePos = 0;
            } else {
                lineBuf[linePos++] = ch;
            }
            
            i++;
        }
    }
}

- (void)socket:(DPAsyncSocket*)inSocket hasError: (int)errorCode {
    if(delegate && [delegate respondsToSelector: @selector(downloadFailed: dueToError:)]) {
        [delegate downloadFailed: self dueToError: errorCode];
    }
}

- (void) stop {
	fStopped = YES;
    if(delegate && [delegate respondsToSelector: @selector(downloadStopped:)]) {
        [delegate downloadStopped: self];
    }
    
    [self close];
}

- (BOOL) stopped {
	return fStopped;
}

- (void) setSocketTimeout:(int)timeout {
    socketTimeout = timeout;
}

- (int) socketTimeout {
	return socketTimeout;
}


- (NSData*)get {
    //NSLog(@"Asynch get: %@", fUrl);    
    DPAsyncHttpHelper* helper = [[DPAsyncHttpHelper newHelper: self] retain];
    [helper waitUntilDone];
    [helper release];
    
    return [self responseData];
}

@end
