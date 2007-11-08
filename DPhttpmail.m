//
//  httpmail.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPhttpmail.h"
#import "httpmail_constants.h"
#import "DPhttpmailMessage.h"

@implementation DPhttpmail

- (id)init {
    self = [super init];
    
    if(self) {
#ifdef USE_ASYNC_HTTP
        fHttp = [[DPAsyncHttp newWithURL: [NSURL URLWithString: HTTPMAIL_URL]] retain];
#else	
        fHttp = [[DPhttp newWithURL: [NSURL URLWithString: HTTPMAIL_URL]] retain];
#endif		
        fUsername = NULL;
        fPassword = NULL;
        fFolders = [[NSMutableDictionary dictionary] retain];
        fProviderURL = HTTPMAIL_URL;
        fOtherFolders = [[NSMutableArray array] retain];
        fEncoding = NSWindowsCP1252StringEncoding;
        stopped = NO;
        fUserAgent = NULL;
        fActiveDate = NULL;
        fFolderDate = NULL;
    }
    
    return self;
}

- (void) dealloc {
    [fHttp release];
	
    [fUsername release];
    [fPassword release];
    [fFolders release];
    [fOtherFolders release];
    [fUserAgent release];
    [fActiveDate release];
    [fFolderDate release];
    
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

- (BOOL)login {
    NSData* response;
    NSScanner* scanner;
    NSString* data;
    
    fConnected = NO;
    [fFolders removeAllObjects];    
    [fHttp setURL: [NSURL URLWithString: fProviderURL]];
    [fHttp clearCookies];
    [fHttp clearHeaders];
    [fHttp setUsername: fUsername];
    [fHttp setPassword: fPassword];
    [fHttp setMethod: @"PROPFIND"];
    
    if(fActiveDate && fFolderDate) {
        NSString* timestamp = [NSString stringWithFormat: @"folders=%d, ACTIVE=%d", [fFolderDate timeIntervalSince1970],
                                                                                    [fActiveDate timeIntervalSince1970]];
        [fHttp setHeaderValue: timestamp forKey: @"X-Timestamp"];
    }
    
    [fHttp get];
    
    if(fActiveDate && fFolderDate) {
        [fHttp removeHeaderForKey: @"X-Timestamp"];
    }
    
    if(![fHttp stopped] ) {
        fCode = [fHttp responseCode]; 
            
        if((fCode<200)&&(fCode>=300)) {
            return NO;
        }
    } else {
        return NO;
    }
    
    [fHttp setRequestContentAsString: HTTPMAIL_FIND_FOLDERS];
    [fHttp setRequestContentType: @"text/xml"];
    [fHttp setMethod: @"PROPFIND"];

    if(fUserAgent) {
        [fHttp setHeaderValue: fUserAgent forKey: @"User-Agent"];
    } else {
        [fHttp setHeaderValue: @"Entourage/10.0 (Mac_PowerPC; DigExt; TmstmpExt)" forKey: @"User-Agent"];
    }
//    [fHttp setHeaderValue: @"Security/Remote-Passphrase" forKey: @"Extension"];
//    [fHttp setHeaderValue: @"t" forKey: @"Brief"];
    [fHttp setHeaderValue: @"0" forKey: @"Depth"];
//    [fHttp setHeaderValue: @"MacOS" forKey: @"UA-OS"];
//    [fHttp setHeaderValue: @"PPC" forKey: @"UA-CPU"];
//    [fHttp setHeaderValue: @"en" forKey: @"Accept-Language"];
//    [fHttp setHeaderValue: @"folders=1096148656, ACTIVE=1096148405" forKey: @"X-Timestamp"];

//    [fHttp setHeaderValue: @"Keep-Alive" forKey: @"Connection"];
    
/*    
    [fHttp setHeaderOrder: [NSArray arrayWithObjects: @"Host", @"Accept-Language", @"Connection", @"Referer", @"User-Agent", @"UA-OS", @"UA-CPU",
                                                      @"Cookie", @"Depth", @"Content-Type", @"Brief", @"X-Timestamp", @"Extension", @"Authorization",
                                                      @"Content-Length", nil]];
*/

    response = [fHttp get];
    
    if(![fHttp stopped] ) {
        fCode = [fHttp responseCode]; 
            
        if((fCode>=200)&&(fCode<300)) {
            data = [NSString stringWithCString: [response bytes] length: [response length]];
            
            scanner = [NSScanner scannerWithString: data];
            while([scanner scanUpToString: @"<hm:" intoString: nil] && ![scanner isAtEnd]) {
                NSString* name;
                [scanner setScanLocation: [scanner scanLocation] + 4];
                
                if([scanner scanUpToString: @">" intoString: &name]) {
                    NSString* folder;
                    
                    [scanner setScanLocation: [scanner scanLocation] + 1];
                    if([scanner scanUpToString: @"</hm:" intoString: &folder]) {
                        [fFolders setObject: [NSURL URLWithString: folder] forKey: [name decomposedStringWithCanonicalMapping]];
                    }
                }
            }

            // now find the other folders
            [fHttp setRequestContentAsString: HTTPMAIL_FIND_SUBFOLDERS];
            [fHttp setURL: [self URLForFolder: @"msgfolderroot"]];
            response = [fHttp get];

            data = [NSString stringWithCString: [response bytes] length: [response length]];

    //        NSLog(@"data = \n%@", data);
            
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
      
    //                    NSLog(@"encodedName = '%@'", encodedName);
                        
                        int L = [encodedName length];
                        
                        if(L>0) {
							const char* buf = [encodedName cStringUsingEncoding: [NSString defaultCStringEncoding]];
                            NSData* nameData = [NSData dataWithBytes: buf length: strlen(buf)];
                            NSString* name = [[[NSString alloc] initWithData: nameData encoding: fEncoding] stringByTrimmingCharactersInSet: [NSCharacterSet whitespaceCharacterSet]];
                            name = [name decomposedStringWithCanonicalMapping];
                            
                            NSURL* folderUrl = [NSURL URLWithString: folder];
                            
                            if(folderUrl && name) {
                                [fFolders setObject: folderUrl forKey: name];
                            
                                [(NSMutableArray*)fOtherFolders addObject: name];
                            } else {
        /*                    
                                NSLog(@"responseString = '%@'", [fHttp responseString]);
                                NSLog(@"headers = %@", [fHttp responseHeaders]);
                                NSLog(@"bad part: %@", part);
                                NSLog(@"data: %@", data);
        */                        
        //                        [response writeToFile: @"/tmp/badresponse.xml" atomically: YES];
                            }
                        } else {
                            NSLog(@"responseString = '%@'", [fHttp responseString]);
                            NSLog(@"headers = %@", [fHttp responseHeaders]);
                            NSLog(@"bad part: %@", part);
                            NSLog(@"data: %@", data);
                        }
                    }
                }
            }
            
            fConnected = YES;
            return YES;
        } else {
            return NO;
        }
    } else {
        return NO;
    }
}

- (BOOL)isConnected {
    return fConnected;
}

- (void)stop {
    if(fHttp) {
        [fHttp stop];
    }
    
    stopped = YES;
}

- (BOOL)stopped {
    return stopped;
}

- (NSURL*)URLForFolder:(NSString*)folder {
    return (NSURL*)[fFolders objectForKey: folder];
}

- (NSArray*)messagesForFolder:(NSString*)folder {
    NSURL* url = [self URLForFolder: folder];
    
    if(url) {
        NSData* response;
        NSString* data;
        NSMutableArray* result = [NSMutableArray array];
        
        [fHttp setURL: url];
        [fHttp setRequestContentAsString: HTTPMAIL_FIND_MESSAGES];
        [fHttp setRequestContentType: @"text/xml"];
        [fHttp setMethod: @"PROPFIND"];
        [fHttp setHeaderValue: @"1" forKey: @"Depth"];
     
        response = [fHttp get];

        if(![fHttp stopped]) {
            data = [NSString stringWithCString: [response bytes] length: [response length]];        
            
    //        NSLog(@"data = \n%@", data);
            
            NSScanner* scanner = [NSScanner scannerWithString: data];
            
            while([scanner scanUpToString: @"<D:response>" intoString: NULL]) {
                NSString* response = NULL;
                
                if([scanner scanUpToString: @"</D:response>" intoString: &response]) {
                    DPhttpmailMessage* msg = [[[DPhttpmailMessage alloc] initWithString: response andFolder: folder] autorelease];
                    if(msg) {
                        [result addObject: msg];
                    }
                }
            }

            return result;
        }
    }
    
    return NULL;
}

- (int)responseCode {
    return [fHttp responseCode];
}

- (NSString*)responseString {
    return [fHttp responseString];
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

- (NSURL*)sentItemsFolder {
    return [self URLForFolder: @"sentitems"];
}

- (NSData*)get:(NSURL*)url {
#ifdef USE_ASYNC_HTTP
    // make sure we get a new socket
    [fHttp close];
#endif

    [fHttp setRequestContent: NULL];
    [fHttp setURL: url];
    [fHttp setMethod: @"GET"];
    return [fHttp get];
}

- (NSData*)moveMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from toFolder: (NSURL*)to {
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
    [fHttp setHeaderValue: @"1" forKey: @"Depth"];
    
    NSData* result = [fHttp get];
    
    [fHttp removeHeaderForKey: @"Destination"];
    
    return result;
}

- (NSData*)removeMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from {
    return [self moveMessageIDs: msgs fromFolder: from toFolder: [self trashFolder]];
}

- (NSData*)moveMessages: (NSArray*)msgs fromFolder: (NSURL*)from toFolder:(NSURL*)url {
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
    [fHttp setHeaderValue: @"1" forKey: @"Depth"];
    
    NSData* result = [fHttp get];
    
    [fHttp removeHeaderForKey: @"Destination"];
    
    return result;
}

- (NSData*)remove:(NSArray*)msgs fromFolder: (NSURL*)from {
    return [self moveMessages: msgs fromFolder: from toFolder: [self trashFolder]];
}

- (NSData*)sendMessage:(NSString*)body to: (NSArray*)recipients{
    return [self sendMessage: body to: recipients savingInSent: NO];
}

- (NSData*)sendMessage:(NSString*)body to: (NSArray*)recipients savingInSent:(BOOL)save {
    [fHttp setMethod: @"POST"];
    
    if(save) {
        [fHttp setHeaderValue: @"t" forKey: @"SAVEINSENT"];
    } else {
        [fHttp setHeaderValue: @"f" forKey: @"SAVEINSENT"];
    }
    
    [fHttp setRequestContentType: @"message/rfc821"];
    [fHttp setURL: [self sendFolder]];
    
    int i, C;
    NSMutableString* who = [NSMutableString string];
    C = [recipients count];
    for(i=0; i<C; i++) {
        [who appendFormat: HTTPMAIL_RECIPIENT, [recipients objectAtIndex: i]];
    }
    
    NSString* buf = [NSString stringWithFormat: HTTPMAIL_SEND_MESSAGE, fUsername, who, body];
    
    [fHttp setRequestContentAsString: buf];
    
    return [fHttp get];

// POST to sendmsg fold
// Content type = message/rfc821

// content is as follows

// MAIL FROM: <danielparnell@hotmail.com>\r\n
// RCPT TO: <daniel@technofetishist.com>\r\n
// \r\n
// message body
    
}

- (NSData*)markAsRead:(DPhttpmailMessage*)msg {
    
    [fHttp setMethod: @"PROPPATCH"];
    [fHttp setRequestContentAsString: HTTPMAIL_MARK_READ];
    [fHttp setURL: [msg url]];
    [fHttp setRequestContentType: @"text/xml"];
    
    return [fHttp get];
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

- (NSStringEncoding) encoding {
    return fEncoding;
}

- (void)setEncoding:(NSStringEncoding)aEncoding {
    fEncoding = aEncoding;
}

- (void)setSocketTimeout:(int)timeout {
    [fHttp setSocketTimeout: timeout];
}

- (int)socketTimeout {
    return [fHttp socketTimeout];
}

- (void)setUserAgent:(NSString*)aAgent {
    [aAgent retain];
    [fUserAgent release];
    fUserAgent = aAgent;
}

- (NSString*)userAgent {
    return fUserAgent;
}

- (void)setActiveDate:(NSDate*)aDate {
    [aDate retain];
    [fActiveDate release];
    fActiveDate = aDate;
}

- (NSDate*)activeDate {
    return fActiveDate;
}

- (void)setFolderDate:(NSDate*)aDate {
    [aDate retain];
    [fFolderDate release];
    fFolderDate = aDate;
}

- (NSDate*)folderDate {
    return fFolderDate;
}

@end
