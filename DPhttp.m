//
//  DPhttp.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPhttp.h"
#import "DPStringUtils.h"
#import "DPMD5.h"
#include "time.h"
#import "DPHTTPMailDebugger.h"

//#define DEBUG_HTTP
//#define DEBUG_HTTP_DATA

#ifndef USE_APPLE_HTTP
@interface DPnonceHolder : NSObject {
    int	count;
}
- (NSString*) nextValue;
- (void) reset;
@end

@implementation DPnonceHolder

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

- (void) reset {
    count = 1;
}

@end
#endif

@implementation DPhttp

+ (id)newWithURL:(NSURL*)url {
   return [[[DPhttp alloc] initWithURL: url] autorelease];
}

- (void)initvars {
#ifdef USE_APPLE_HTTP
    fUrlRequest = [[NSMutableURLRequest new] retain];
    fResponse = nil;
    data = [[NSMutableData data] retain];
#else
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
    nonce = NULL;
    opaque = NULL;
    realm = NULL;
    authMethod = NULL;
    nonce_counts = [[NSMutableDictionary dictionary] retain]; 
    fHeaderOrder = NULL;
        
    [self setHeaderValue: @"DPhttp 1.0" forKey: @"User-Agent"];
#endif
    fUsername = NULL;
    fPassword = NULL;
    socketTimeout = 30;
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
#ifdef USE_APPLE_HTTP
        [fUrlRequest setURL: url];
#else
        fUrl = [url retain];
#endif;
    }
    
    return self;
}

- (void)dealloc {
#ifdef USE_APPLE_HTTP
    [fResponse release];
    [fUrlRequest release];
    [data release];
#else
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
#endif

    [super dealloc];
}

- (void)setURL:(NSURL*)url {
#ifdef USE_APPLE_HTTP
    [fUrlRequest setURL: url];
#else
    [url retain];
    [fUrl release];
    fUrl = url;
#endif
}

- (NSURL*)URL {
#ifdef USE_APPLE_HTTP
    return [fUrlRequest URL];
#else
    return fUrl;
#endif
}

- (void)setMethod:(NSString*)method {
#ifdef USE_APPLE_HTTP
    [fUrlRequest setHTTPMethod: method];
#else
    [method retain];
    [fMethod release];
    fMethod = method;
#endif
}

- (NSString*)method {
#ifdef USE_APPLE_HTTP
    return [fUrlRequest HTTPMethod];
#else
    return fMethod;
#endif
}

#ifndef USE_APPLE_HTTP

- (void)parseResponse:(NSString*)response {
    NSString* code;
    NSString* message;
    NSRange p;

    p = [response rangeOfString: @" "];
    
    p.location = p.location + 1;
    p.length = 3;
    code = [response substringWithRange: p];
    message = [response substringFromIndex: p.location+4];

    fResponseCode = [code intValue];
    [fResponseString release];
    fResponseString = [message retain];
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

    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"header = %@", header]];
    }
#ifdef DEBUG_HTTP
    NSLog(@"header = %@", header);
#endif    
    p = [header rangeOfString: @": "];
    
    if(p.location!=NSNotFound) {
        name = [header substringToIndex: p.location];
        value = [header substringFromIndex: p.location + p.length];
        
        if([name isEqualToString: @"Set-Cookie"]) {
            [self parseCookie: value];
        } else {
            if([name isEqualToString: @"Proxy-Authenticate"]) {
                [self processProxyAuthenticate: value];
            }
            
            
            if(name && value) 
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
    
    if(auth==NULL) {
        NSEnumerator *enumerator = [fResponseHeaders keyEnumerator];
        NSString* key;
         
        while ((key = [enumerator nextObject])) {
            if([[key uppercaseString] hasSuffix: @"AUTHENTICATE"]) {
                auth = [fResponseHeaders objectForKey: key];
                break;
            }
        }

    }    
    
    p = [auth rangeOfString: @" "];
    [authMethod release];
    authMethod = [[auth substringToIndex: p.location] retain];
    
    if([authMethod isEqualToString: @"Digest"]) {
        [self processDigestAuthRequest: [auth substringFromIndex: p.location+1]];
    } else {
        if([authMethod isEqualToString: @"Basic"]) {
            // do nothing
            NSLog(@"got basic auth request");
        } else {
            NSLog(@"response headers = %@", fResponseHeaders);
            [NSException raise: @"AUTHORIZATION ERROR" format: @"Unknown authorization method: %@", authMethod];
        }
    }    
}

- (NSString*)nonceCountForNonce: (NSString*)n {
    if(n) {
        DPnonceHolder* h = [nonce_counts objectForKey: n];
        if(h==NULL) {
            h = [[DPnonceHolder new] autorelease];
            
            [nonce_counts setObject: h forKey: n];
        }
    
        return [h nextValue];
    }
    
    return NULL;
}

- (void) resetNonce: (NSString*) n {
    if(n) {
        DPnonceHolder* h = [nonce_counts objectForKey: n];
        if(h) {
            [h reset];
        }
    }
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
    
    if(realm) {
        [response appendString: @"realm=\""];
        [response appendString: realm];
        [response appendString: @"\", "];
    }
    
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

    if(uri) {
        [response appendString: @"uri=\""];
        [response appendString: uri]; 
        [response appendString: @"\", "];
    }
    
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

- (void) addBasicAuthorization {
    NSString* temp = [NSString stringWithFormat: @"%@:%@", fUsername, fPassword];
    NSString* auth = [NSString stringWithFormat: @"Basic %@", [DPStringUtils base64Encode: temp]];
    [self setHeaderValue: auth forKey: @"Authorization"];
}

- (void) addAuthorization {
    if(authMethod) {
        if([authMethod isEqualToString: @"Digest"]) {
            [self addDigestAuthorization];
        } else {
            if([authMethod isEqualToString: @"Basic"]) {
                [self addBasicAuthorization];
            } else {
                [NSException raise: @"AUTHORIZATION ERROR" format: @"Unknown authorization method: %@", authMethod];
            }
        }
    }
}

- (void) addProxyAuthorization {
    if(fProxy && fProxyUsername && fProxyPassword) {
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
#endif

#ifdef USE_APPLE_HTTP

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    [response retain];
    [fResponse release];
    fResponse = (NSHTTPURLResponse*)response;
 
    NSLog(@"Got response: %d", [fResponse statusCode]);
    [data setLength:0];
}

-(NSURLRequest *)connection:(NSURLConnection *)connection
            willSendRequest:(NSURLRequest *)request
           redirectResponse:(NSURLResponse *)redirectResponse

{
    NSLog(@"got redirection to: %@", [[request URL] absoluteString]);
    return request;
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)theData
{
    // append the new data to the receivedData
    NSLog(@"got data");
    [data appendData:theData];
}

- (void)connection:(NSURLConnection *)theConnection didFailWithError:(NSError *)error
{

    [theConnection release];

    NSLog(@"Connection failed! Error - %@ %@",
          [error localizedDescription],
          [[error userInfo] objectForKey:NSErrorFailingURLStringKey]);

    done = YES;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)theConnection
{
    [theConnection release];

    NSLog(@"finished");
    done = YES;
}

-(void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
        NSLog(@"didReceiveAuthenticationChallenge: %@", challenge);
        NSLog(@"[challenge previousFailureCount] = %d", [challenge previousFailureCount]);
    
        NSURLCredential *newCredential;

        newCredential=[NSURLCredential credentialWithUser: fUsername
                                                 password: fPassword
                                              persistence:NSURLCredentialPersistenceNone];

        [[challenge sender] useCredential:newCredential forAuthenticationChallenge:challenge];

}
#endif

- (NSData*)get {
#ifdef USE_APPLE_HTTP
    int code;

    [data setLength: 0];
    [fResponse release];
    fResponse = nil;
  
    done = false;
    NSURLConnection* connection = [[NSURLConnection connectionWithRequest: fUrlRequest delegate: self] retain];
     
    if(connection==nil) {
        [[NSException exceptionWithName: @"HTTP Error" reason: @"Connection creation failed" userInfo: nil] raise];
    }
      
    while(!done) {
        [[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow:0.1]];
    }
    
    [connection release];
    
//    data = [NSURLConnection sendSynchronousRequest: fUrlRequest returningResponse: &fResponse error: &error];
    
    code = [fResponse statusCode];
    if(code<200 || code>299) {
        [NSException raise: @"HTTP Error" format: [self responseString]];
    }
    
    return data;
#else
    stopped = NO;
    
    DPSocket* fSocket = [[DPSocket new] autorelease];
    NSEnumerator *keys = NULL;
    NSString* key = NULL;
    NSMutableData* result = NULL;
    NSString* response = NULL;
    NSString* line = NULL;
    NSString* uri = NULL;
    
    char buffer[1024];
    int count;
    BOOL again = YES;
    BOOL passwordSent = NO;
    BOOL shouldClose = YES;
    BOOL proxyAuthSent = NO;
    NSString* buf;
    NSMutableString* cookies;
    int cc;
    NSRange hostRange;
    
    do {        
        if(shouldClose ) {            
            if(fProxy) {
                [fSocket setUrl: fProxy];
            } else {
                [fSocket setUrl: fUrl];
            }
            
//            shouldClose = NO;
        }
        
        [fResponseHeaders removeAllObjects];
    
        [self setHeaderValue: [fUrl host] forKey: @"Host"];
        
        if(shouldClose) {
            [self setHeaderValue: @"close" forKey: @"Connection"];
        } else {
            [self setHeaderValue: @"Keep-Alive" forKey: @"Connection"];
        }
                
        if(authMethod) {
            [self addAuthorization];
        }
        
        if(fProxy) {
            [self setHeaderValue: @"no-cache" forKey: @"Cache-Control"];
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
        
        [fSocket setSocketTimeout: socketTimeout];
        [fSocket open];

//        uri = [fUrl absoluteString];
//        NSLog(@"fUrl = %@", fUrl);
        
        uri = [fUrl absoluteString];
        
        if(fProxy==nil) {
            hostRange = [uri rangeOfString: [fUrl host]];
            uri = [uri substringFromIndex: hostRange.location+hostRange.length];
        }
        
        // send the request method and URI
        [fSocket writeString: [NSString stringWithFormat: @"%@ %@ HTTP/1.1\r\n", fMethod, uri]];

    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"%@ %@ HTTP/1.1", fMethod, uri]];
    }
#ifdef DEBUG_HTTP
        NSLog(@"%@ %@ HTTP/1.1", fMethod, uri);
#endif

        if(fHeaderOrder) {
            int i, C;
            NSString* value;
            
//            NSLog(@"fHeaderOrder = %@", fHeaderOrder);
//            NSLog(@"fHeaders = %@", fHeaders);
            
            C = [fHeaderOrder count];
            for(i=0; i<C; i++) {
                key = [fHeaderOrder objectAtIndex: i];
                
                if([key isEqualToString: @"Cookie"]) {
                    cookies = [NSMutableString string];
                    cc = 0;
                    keys = [fCookies keyEnumerator];
                    while ((key = [keys nextObject])) {
                        if(cc) {
                            [cookies appendString: @" "];
                        }
                        
                        [cookies appendString: [NSString stringWithFormat: @"%@=%@;", key, [fCookies objectForKey: key]]];
                        cc++;
                    }
                
                    if(cc==0) {
                        key = NULL;
                        value = NULL;
                    } else {
                        key = @"Cookie";
                        value = cookies;
                    }
                } else {
                    value = [fHeaders objectForKey: key];
                }
                
                if(key && value) {
                    buf = [NSString stringWithFormat: @"%@: %@\r\n", key, value];
                    
    if([DPHTTPMailDebugger debugEnabled]) {
        [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sending %@", buf]];
    }
    
#ifdef DEBUG_HTTP
                    NSLog(@"Sending %@", buf);
#endif
                    [fSocket writeString: buf];  
                }
            }
            
        } else {
            // send the request headers
            keys = [fHeaders keyEnumerator];
            while ((key = [keys nextObject])) {
                buf = [NSString stringWithFormat: @"%@: %@\r\n", key, [fHeaders objectForKey: key]];
                
                if([DPHTTPMailDebugger debugEnabled]) {
                    [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sending %@", buf]];
                }
    
    #ifdef DEBUG_HTTP
                NSLog(@"Sending %@", buf);
    #endif
                [fSocket writeString: buf];  
            }
        
            // send the cookies
            keys = [fCookies keyEnumerator];
            cookies = [NSMutableString string];
            cc = 0;
            [cookies appendString: @"Cookie:"];
            while ((key = [keys nextObject])) {
                [cookies appendString: [NSString stringWithFormat: @" %@=%@;", key, [fCookies objectForKey: key]]];
                cc++;
            }
        
            if(cc) {
                [cookies appendString: @"\r\n"];
                
                if([DPHTTPMailDebugger debugEnabled]) {
                    [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Sending %@", cookies]];
                }
#ifdef DEBUG_HTTP
                NSLog(@"Sending %@", cookies);
#endif
                [fSocket writeString: cookies];
            }
        }
        
        // tell the server we are done sending the request
        [fSocket writeString: @"\r\n"];
        
        // send the request content if there is any
        if(fRequestContent) {
            [fSocket writeData: fRequestContent];
        }
        
        // the server should now respond with data
        result = [NSMutableData data];

        // look for a HTTP response code
        response = [fSocket readLine];
        if([response hasPrefix: @"HTTP"]) {
        
            if([DPHTTPMailDebugger debugEnabled]) {
                [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Got response %@", response]];
            }
            
#ifdef DEBUG_HTTP
            NSLog(@"Got response %@", response);
#endif            
            [self parseResponse: response];
            
            // read in the request headers
            line = [fSocket readLine];
            while(!stopped && line && ![line isEqualToString:@""]) {
                [self parseResponseHeader: line];
                line = [fSocket readLine];
            }
        } else {
            // no response, so it looks like something really bad happened!
            fResponseString = NULL;
            fResponseCode = -1;
            [result appendBytes: (void*)[response cStringUsingEncoding: NSASCIIStringEncoding] length: [response length]];
        }
            
        // get the data for the request
        int size = [[fResponseHeaders objectForKey: @"Content-Length"] intValue];
        while(!stopped && (size>0) && (count=[fSocket read: sizeof(buffer) into: &buffer[0]])>0) {
            [result appendBytes: (void*)&buffer length: count];
            size = size - count;
/*            
#ifdef DEBUG_HTTP            
            if(count) {
                NSLog(@"Read %d bytes", count);
                NSLog([NSString stringWithCString: &buffer[0] length: count]);
            }
#endif
*/
        }
        
        if([DPHTTPMailDebugger debugEnabled]) {
            [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"DATA = %@", [NSString stringWithCString: [result bytes] length: [result length]]]];
        }
        
#ifdef DEBUG_HTTP_DATA
    NSLog(@"DATA = %@", [NSString stringWithCString: [result bytes] length: [result length]]);
#endif
            
        if(!stopped) {
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
                            location = [fResponseHeaders objectForKey: @"location"];
                        }
                        
                        if(location==NULL) {
                            location = [fResponseHeaders objectForKey: @"Content-Location"];
                        }

                        if(location==NULL) {
                            NSEnumerator *enumerator = [fResponseHeaders keyEnumerator];
                            NSString* key;
                             
                            while ((key = [enumerator nextObject])) {
                                if([[key uppercaseString] hasSuffix: @"LOCATION"]) {
                                    location = [fResponseHeaders objectForKey: key];
                                    break;
                                }
                            }

                        }
                        
                        
                        if(location==NULL) {
                            NSLog(@"%@", fResponseHeaders);
                        }
                        
/*                        
                        // chop off the ? at the end if there is one
                        if([location hasSuffix: @"?"]) {
                            location = [location substringToIndex: [location length]-1];
                        }
*/                        
                        if([location hasPrefix: @"http://"]) {
                            newUrl = [NSURL URLWithString: location];
                            shouldClose = YES;
                            passwordSent = NO;
                            [self clearAuthorization];
//                            [self resetNonce: nonce];
                        } else {
                            @try {
                                newUrl = [[NSURL URLWithString: location relativeToURL: fUrl] absoluteURL];
                                shouldClose = NO;
                            } @catch (NSException* e) {
                                if([DPHTTPMailDebugger debugEnabled]) {
                                    [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Got bad redirection:\n %@", fResponseHeaders]];
                                }
                                
                                [[NSException exceptionWithName: @"HTTP Redirection" reason: [NSString stringWithFormat: @"%@\nHeaders=%@", [e reason], fResponseHeaders] userInfo: nil] raise];
                            }
                        }
                        
//                        NSLog(@"location = %@", location);
                        if([DPHTTPMailDebugger debugEnabled]) {
                            [[DPHTTPMailDebugger sharedInstance] add: [NSString stringWithFormat: @"Got redirection %d to %@", fResponseCode, location]];
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
        }
        
        if(shouldClose || stopped) {
            [fSocket close];
        }
#ifdef DEBUG_HTTP
        NSLog(@"");
#endif
     } while(again && !stopped);
    
//    [fSocket release];
    
#ifdef DEBUG_HTTP_DATA
    NSString* data = [NSString stringWithCString: [result bytes] length: [result length]];        
    NSLog(@"%@", data);
#endif
    
    if(stopped) {
        result = nil;
    }
    
    return result;
#endif
}

- (void)setHeaderValue:(NSString*)value forKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
    [fUrlRequest setValue: value forHTTPHeaderField: key];
#else
    if(key && value) 
        [fHeaders setObject: value forKey: key];
#endif
}

- (NSString*)headerValueForKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
    return [fUrlRequest valueForHTTPHeaderField: key];
#else
    if(key) 
        return (NSString*)[fHeaders objectForKey: key];

    return nil;
#endif
}

- (void)stop {
    stopped = YES;
}

- (BOOL)stopped {
    return stopped;
}

- (void)clearHeaders {
#ifdef USE_APPLE_HTTP
    [fUrlRequest setAllHTTPHeaderFields: nil];
#else
    [fHeaders removeAllObjects];
#endif
}

- (NSDictionary*)headers {
#ifdef USE_APPLE_HTTP
    return [fResponse allHeaderFields];
#else
    return fHeaders;
#endif
}

- (void)removeHeaderForKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
#else
    [fHeaders removeObjectForKey: key];
#endif;
}

- (void)setHeaderOrder:(NSArray*)order {
    [order retain];
    [fHeaderOrder release];
    fHeaderOrder = order;
}

- (NSArray*)headerOrder {
    return fHeaderOrder;
}


- (void)setCookieValue:(NSString*)data forKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
#else
    if(key && data)
        [fCookies setObject: data forKey: key];
#endif
}

- (NSString*)cookieValueForKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    if(key)
        return (NSString*)[fCookies objectForKey: key];
        
    return nil;
#endif
}

- (void)clearCookies {
#ifdef USE_APPLE_HTTP
#else
    [fCookies removeAllObjects];
#endif
}

- (NSDictionary*)cookies {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    return fCookies;
#endif
}

- (void)setCookies:(NSDictionary*)cookies {
#ifdef USE_APPLE_HTTP
#else
    [fCookies removeAllObjects];
    [fCookies addEntriesFromDictionary: cookies];
#endif
}

- (void)removeCookieForKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
#else
    [fCookies removeObjectForKey: key];
#endif
}

- (int)responseCode {
#ifdef USE_APPLE_HTTP
    return [fResponse statusCode];
#else
    return fResponseCode;
#endif
}

- (NSString*)responseString {
#ifdef USE_APPLE_HTTP
    return [NSHTTPURLResponse localizedStringForStatusCode: [fResponse statusCode]];
#else
    return fResponseString;
#endif
}

- (NSString*)responseHeaderForKey:(NSString*)key {
#ifdef USE_APPLE_HTTP
    return [[fResponse allHeaderFields] objectForKey: key]; 
#else
    return (NSString*)[fResponseHeaders objectForKey: key];
#endif
}

- (NSDictionary*)responseHeaders {
#ifdef USE_APPLE_HTTP
    return [fResponse allHeaderFields];
#else
    return fResponseHeaders;
#endif
}

- (void)setFollowRedirections:(bool)follow {
#ifdef USE_APPLE_HTTP
#else
    fFollowRedirections = follow;
#endif
}

- (bool)followRedirections {
#ifdef USE_APPLE_HTTP
    return YES;
#else
    return fFollowRedirections;
#endif
}

- (NSData*)requestContent {
#ifdef USE_APPLE_HTTP
    return [fUrlRequest HTTPBody];
#else
    return fRequestContent;
#endif
}

- (void)setRequestContent:(NSData*)body{
#ifdef USE_APPLE_HTTP
    [fUrlRequest setHTTPBody: body];
#else
    if(fRequestContent) {
        [fRequestContent release];
    }
    
    fRequestContent = [body retain];
#endif
}

- (void)setRequestContentAsString:(NSString*)string {
    NSMutableData* body = [NSMutableData data];
    const char* buf = [string cStringUsingEncoding: NSUTF8StringEncoding];
	
    [body appendBytes: buf length: strlen(buf)];
    
    [self setRequestContent: body];
}

- (NSString*)requestContentType {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    return fRequestContentType;
#endif
}

- (void)setRequestContentType:(NSString*)type {
#ifdef USE_APPLE_HTTP
#else
    if(fRequestContentType) {
        [fRequestContentType release];
    }
    
    fRequestContentType = [[NSString stringWithString: type] retain];
#endif
}

- (NSURL*)proxy {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    return fProxy;
#endif
}

- (void)setProxy:(NSURL*)url {
#ifdef USE_APPLE_HTTP
#else
    [url retain];
    [fProxy release];
    fProxy = url;
#endif
}

- (void)setProxyUsername:(NSString*)username {
#ifdef USE_APPLE_HTTP
#else
    [username retain];
    [fProxyUsername release];
    fProxyUsername = username;
#endif
}

- (NSString*)proxyUsername {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    return fProxyUsername;
#endif
}

- (void)setProxyPassword:(NSString*)password {
#ifdef USE_APPLE_HTTP
#else
    [password retain];
    [fProxyPassword release];
    fProxyPassword = password;
#endif
}

- (NSString*)proxyPassword {
#ifdef USE_APPLE_HTTP
    return nil;
#else
    return fProxyPassword;
#endif
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

- (void)setSocketTimeout:(int)timeout {
    socketTimeout = timeout;
}

- (int)socketTimeout {
    return socketTimeout;
}

@end
