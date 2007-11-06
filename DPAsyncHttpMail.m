//
//  DPAsyncHttpMail.m
//  httpmail
//
//  Created by Daniel Parnell on Thu May 08 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPAsyncHttpMail.h"
#import "httpmail_constants.h"
#import "DPhttpmailMessage.h"

#define STATE_NONE		0
#define STATE_LOGIN		1
#define STATE_LOGIN2		2
#define STATE_MESSAGES		3
#define STATE_SIMPLE_REQUEST	4

@interface DPAsyncHttpMail (Private)

- (void)loginStage2;
- (void)loginStage3;
- (void)messageForFolder2;
- (void)requestFinished;

@end

@implementation DPAsyncHttpMail
- (id)init {
    NSLog(@"DPAsyncHttpMail init");
    
    self = [super init];
    
    if(self) {
        fHttp = [[DPAsyncHttp newWithURL: [NSURL URLWithString: HTTPMAIL_URL]] retain];
        [fHttp setDelegate: self];
        
        fUsername = NULL;
        fPassword = NULL;
        fFolders = [[NSMutableDictionary dictionary] retain];
        fProviderURL = HTTPMAIL_URL;
        fOtherFolders = [[NSMutableArray array] retain];
    }
    
    return self;
}

- (void) dealloc {
    NSLog(@"DPAsyncHttpmail dealloc");
    [fHttp setDelegate: nil];
    [fHttp close];
    [fHttp release];
    [fUsername release];
    [fPassword release];
    [fFolders release];
    [fOtherFolders release];
    
    [super dealloc];
}

- (void) setUsername:(NSString*)username {
    [username retain];
    [fUsername release];
    fUsername = username;
}

- (NSString*) username {
    return fUsername;
}

- (void) setPassword:(NSString*)password {
    [password retain];
    [fPassword release];
    fPassword = password;
}

- (NSString*) password {
    return fPassword;
}

- (void)setProxy:(NSURL*)url {
    [fHttp setProxy: url];
}

- (NSURL*)proxy {
    return [fHttp proxy];
}

- (void)setProxyUsername:(NSString*)username {
    [fHttp setProxyUsername: username];
}

- (NSString*)proxyUsername {
    return [fHttp proxyUsername];
}

- (void)setProxyPassword:(NSString*)password {
    [fHttp setProxyPassword: password];
}

- (NSString*)proxyPassword {
    return [fHttp proxyPassword];
}

- (void)login {    
    fConnected = NO;
    [fFolders removeAllObjects];    
    [fHttp setURL: [NSURL URLWithString: fProviderURL]];
    [fHttp clearCookies];
    [fHttp clearHeaders];
    [fHttp setUsername: fUsername];
    [fHttp setPassword: fPassword];
    [fHttp setRequestContentAsString: HTTPMAIL_FIND_FOLDERS];
    [fHttp setRequestContentType: @"text/xml"];
    [fHttp setMethod: @"PROPFIND"];
//    [fHttp setHeaderValue: @"Mozilla/1.0" forKey: @"User-Agent"];
    [fHttp setHeaderValue: @"Entourage/10.0 (Mac_PowerPC; DigExt; TmstmpExt)" forKey: @"User-Agent"];
        
    fConnected = NO;
    state = STATE_LOGIN;
    [fHttp asyncGet];
}

- (void)loginStage2 {
    NSData* response;
    NSScanner* scanner;
    NSString* data;
    
    if((fCode>=200)&&(fCode<300)) {
        response = [fHttp responseData];
        
        data = [NSString stringWithCString: [response bytes] length: [response length]];
        
        scanner = [NSScanner scannerWithString: data];
        while([scanner scanUpToString: @"<hm:" intoString: nil] && ![scanner isAtEnd]) {
            NSString* name;
            [scanner setScanLocation: [scanner scanLocation] + 4];
            
            if([scanner scanUpToString: @">" intoString: &name]) {
                NSString* folder;
                
                [scanner setScanLocation: [scanner scanLocation] + 1];
                if([scanner scanUpToString: @"</hm:" intoString: &folder]) {                    
                    [fFolders setObject: [NSURL URLWithString: folder] forKey: name];
                }
            }
        }

        // now find the other folders
        [fHttp setRequestContentAsString: HTTPMAIL_FIND_SUBFOLDERS];
        [fHttp setURL: [self URLForFolder: @"msgfolderroot"]];
        
        state = STATE_LOGIN2;
        [fHttp asyncGet];
    } else {
        if(delegate && [delegate respondsToSelector: @selector(loginFailed:)]) {
            [delegate loginFailed: self];
        }
    }
}

- (void)loginStage3 {
    NSData* response = [fHttp responseData];
    NSString* data = [NSString stringWithCString: [response bytes] length: [response length]];

    NSScanner* parts = [NSScanner scannerWithString: data];
    while([parts scanUpToString: @"<D:response>" intoString: nil] && ![parts isAtEnd]) {
        NSString* part;
        [parts setScanLocation: [parts scanLocation] + 12];
        [parts scanUpToString: @"</D:response>" intoString: &part];

        NSRange r1, r2, r3;
        
        r1 = [part rangeOfString: @"<D:href>"];
        r2 = [part rangeOfString: @"</D:href>"];
        
        if(r1.location!=NSNotFound && r2.location!=NSNotFound) {
            r3.location = r1.location+r1.length;
            r3.length = r2.location-r3.location;
            
            NSString* folder = [part substringWithRange: r3];
            
            r1 = [part rangeOfString: @"<D:displayname>"];
            r2 = [part rangeOfString: @"</D:displayname>"];
            
            if(r1.location!=NSNotFound && r2.location!=NSNotFound) {
                r3.location = r1.location+r1.length;
                r3.length = r2.location-r3.location;
                
                NSString* encodedName = [part substringWithRange: r3];
                
                NSData* nameData = [NSData dataWithBytes: [encodedName cString] length: [encodedName length]];
            
                NSString* name = [[NSString alloc] initWithData: nameData encoding: NSWindowsCP1250StringEncoding];
                [fFolders setObject: [NSURL URLWithString: folder] forKey: name];
                
                [(NSMutableArray*)fOtherFolders addObject: name];
            }
        }
    }
    
    NSLog(@"logged in");
    fConnected = YES;
    state = STATE_NONE;
    
    if(delegate && [delegate respondsToSelector: @selector(loginSuccessful:)]) {
        [delegate loginSuccessful: self];
    }
    
}

- (BOOL)isConnected {
    return fConnected;
}

- (NSURL*)URLForFolder:(NSString*)folder {
    return (NSURL*)[fFolders objectForKey: folder];
}

- (void)messagesForFolder:(NSString*)folder {
    NSURL* url = [self URLForFolder: folder];
    
    if(url) {        
        [fHttp setURL: url];
        [fHttp setRequestContentAsString: HTTPMAIL_FIND_MESSAGES];
        [fHttp setRequestContentType: @"text/xml"];
        [fHttp setMethod: @"PROPFIND"];
     
        state = STATE_MESSAGES;
        fetchObject = [folder retain];
        [fHttp asyncGet];
    }
    
}

- (void)messagesForFolder2 {
    NSData* response = [fHttp responseData];
    NSString* data;
    NSMutableArray* result = [NSMutableArray array];

    data = [NSString stringWithCString: [response bytes] length: [response length]];        
        
    NSScanner* scanner = [NSScanner scannerWithString: data];
    
    while([scanner scanUpToString: @"<D:response>" intoString: NULL]) {
        NSString* response = NULL;
        
        if([scanner scanUpToString: @"</D:response>" intoString: &response]) {
            DPhttpmailMessage* msg = [[[DPhttpmailMessage alloc] initWithString: response andFolder: fetchObject] autorelease];
            if(msg) {
                [result addObject: msg];
            }
        }
    }
    
    [fetchObject release];
    fetchObject = nil;

    NSLog(@"got messages");
    state = STATE_NONE;
    
    if(delegate && [delegate respondsToSelector: @selector(messagesFetched:forMail:)]) {
        [delegate messagesFetched: result forMail: self];
    }
}

- (int)responseCode {
    return [fHttp responseCode];
}

- (NSString*)responseString {
    return [fHttp responseString];
}

- (NSData*)responseData {
    return [fHttp responseData];
}

- (NSURL*)trashFolder {
    return [self URLForFolder: @"deleteditems"];
}

- (NSURL*)inboxFolder {
    return [self URLForFolder: @"inbox"];
}

- (NSURL*)sendFolder {
    return [self URLForFolder: @"sendmsg"];
}


- (void)get:(NSURL*)url {
    NSLog(@"downloading %@", url);
    
    [fHttp setRequestContent: NULL];
    [fHttp setURL: url];
    [fHttp setMethod: @"GET"];
    
    state = STATE_SIMPLE_REQUEST;
    [fHttp asyncGet];
}

- (void)moveMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from toFolder: (NSURL*)to {
    NSMutableString* buf = [NSMutableString string];
    int i, C;
    C = [msgs count];
    
    for(i=0; i<C; i++) {        
        [buf appendString: [NSString stringWithFormat: @"<D:href>%@</D:href>\n", [msgs objectAtIndex: i]]];
    }
    
    NSString* request = [NSString stringWithFormat: HTTPMAIL_MOVE_MAIL, buf];
    
    [fHttp setRequestContentAsString: request];
    [fHttp setURL: from];
    [fHttp setRequestContentType: @"text/xml"];
    
    [fHttp setHeaderValue: [to absoluteString] forKey: @"Destination"];
    [fHttp setMethod: @"BMOVE"];
    
    state = STATE_SIMPLE_REQUEST;
    [fHttp asyncGet];
}

- (void)removeMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from {
    [self moveMessageIDs: msgs fromFolder: from toFolder: [self trashFolder]];
}

- (void)moveMessages: (NSArray*)msgs fromFolder: (NSURL*)from toFolder:(NSURL*)url {
    NSMutableString* buf = [NSMutableString string];
    int i, C;
    C = [msgs count];
    
    for(i=0; i<C; i++) {
        NSString* n = [[[[msgs objectAtIndex: i] url] path] lastPathComponent];
        
        [buf appendString: [NSString stringWithFormat: @"<D:href>%@</D:href>\n", n]];
    }
    
    NSString* request = [NSString stringWithFormat: HTTPMAIL_MOVE_MAIL, buf];
    
    [fHttp setRequestContentAsString: request];
    [fHttp setURL: from];
    [fHttp setRequestContentType: @"text/xml"];
    
    [fHttp setHeaderValue: [url absoluteString] forKey: @"Destination"];
    [fHttp setMethod: @"BMOVE"];
    
    state = STATE_SIMPLE_REQUEST;
    [fHttp asyncGet];
    
    [fHttp removeHeaderForKey: @"Destination"];
}

- (void)remove:(NSArray*)msgs fromFolder: (NSURL*)from {
    [self moveMessages: msgs fromFolder: from toFolder: [self trashFolder]];
}

- (void)sendMessage:(NSString*)body to: (NSString*)reciptient{
    [fHttp setMethod: @"POST"];
    [fHttp setHeaderValue: @"f" forKey: @"SAVEINSENT"];
    [fHttp setRequestContentType: @"message/rfc821"];
    [fHttp setURL: [self sendFolder]];
    
    NSString* buf = [NSString stringWithFormat: HTTPMAIL_SEND_MESSAGE, fUsername, reciptient, body];
    
    [fHttp setRequestContentAsString: buf];
    
    state = STATE_SIMPLE_REQUEST;
    [fHttp asyncGet];

// POST to sendmsg fold
// Content type = message/rfc821

// content is as follows

// MAIL FROM: <danielparnell@hotmail.com>\r\n
// RCPT TO: <daniel@technofetishist.com>\r\n
// \r\n
// message body
    
}

- (void)markAsRead:(DPhttpmailMessage*)msg {
    
    [fHttp setMethod: @"PROPPATCH"];
    [fHttp setRequestContentAsString: HTTPMAIL_MARK_READ];
    [fHttp setURL: [msg url]];
    [fHttp setRequestContentType: @"text/xml"];
    
    state = STATE_SIMPLE_REQUEST;
    [fHttp asyncGet];
}

- (NSString*)providerURL {
    return fProviderURL;
}

- (void)setProviderURL:(NSString*)url {
    [url retain];
    [fProviderURL release];
    fProviderURL = url;
}

- (NSArray*)otherFolders {
    return fOtherFolders;
}

- (void) requestFinished {
    NSLog(@"request finished");
    
    state = STATE_NONE;
    
    if(delegate) {
        if((fCode>=200)&&(fCode<300)) {
            if([delegate respondsToSelector: @selector(operationSuccessful:)]) {
                [delegate operationSuccessful: self];
            }
        } else {
            if([delegate respondsToSelector: @selector(operationFailed:withMessage:)]) {
                [delegate operationFailed: self withMessage: [fHttp responseString]];
            }
        }
    }
}

- (void) setDelegate: (id)aDelegate {
    [aDelegate retain];
    [delegate release];
    
    delegate = aDelegate;
}

- (id) delegate {
    return delegate;
}

- (void)downloadFinished:(DPAsyncHttp*)sender {
    fCode = [sender responseCode];
    
    NSLog(@"downloadFinished: %d", state);
    
    switch(state) {
        case STATE_LOGIN:
            [self loginStage2];
            break;
        
        case STATE_LOGIN2:
            [self loginStage3];
            break;

        case STATE_MESSAGES:
            [self messagesForFolder2];
            break;
            
        case STATE_SIMPLE_REQUEST:
            [self requestFinished];
            break;
    }
}

- (void)close {
    [fHttp setDelegate: nil];
    [fHttp close];
}

@end
