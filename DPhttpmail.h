//
//  httpmail.h
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

//#define USE_ASYNC_HTTP

#import <Foundation/Foundation.h>
#ifdef USE_ASYNC_HTTP
#import "DPAsyncHttp.h"
#else
#import "DPhttp.h"
#endif
#import "DPhttpmailMessage.h"

@interface DPhttpmail : NSObject {
@private
@protected
#ifdef USE_ASYNC_HTTP
    DPAsyncHttp*                fHttp;
#else
    DPhttp*			fHttp;
#endif	
    NSString*			fUsername;
    NSString*			fPassword;
    NSMutableDictionary*	fFolders;
    BOOL			fConnected;
    int				fCode;
    NSString*			fProviderURL;
    NSArray*			fOtherFolders;
    NSStringEncoding            fEncoding;
    BOOL                        stopped;
    NSString*                   fUserAgent;
    NSDate*                     fActiveDate;
    NSDate*                     fFolderDate;
@public
}

- (void) setUsername:(NSString*)username;
- (NSString*) username;
- (void) setPassword:(NSString*)password;
- (NSString*) password;

- (void)setProxy:(NSURL*)url;
- (NSURL*)proxy;
- (void)setProxyUsername:(NSString*)username;
- (NSString*)proxyUsername;
- (void)setProxyPassword:(NSString*)password;
- (NSString*)proxyPassword;

- (BOOL)login;
- (BOOL)isConnected;

- (void)stop;
- (BOOL)stopped;

- (NSURL*)URLForFolder:(NSString*)folder;
- (NSArray*)messagesForFolder:(NSString*)folder;

- (NSData*)get:(NSURL*)url;

- (int)responseCode;
- (NSString*)responseString;

- (NSURL*)trashFolder;
- (NSURL*)inboxFolder;
- (NSURL*)sendFolder;
- (NSURL*)sentItemsFolder;

- (NSData*)moveMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from toFolder: (NSURL*)to;
- (NSData*)removeMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from;
- (NSData*)moveMessages: (NSArray*)msgs fromFolder: (NSURL*)from toFolder:(NSURL*)url;
- (NSData*)remove:(NSArray*)msgs fromFolder: (NSURL*)from;
- (NSData*)sendMessage:(NSString*)body to: (NSArray*)recipients;
- (NSData*)sendMessage:(NSString*)body to: (NSArray*)recipients savingInSent:(BOOL)save;

- (NSData*)markAsRead:(DPhttpmailMessage*)msg;

- (NSString*)providerURL;
- (void)setProviderURL:(NSString*)url;

- (NSArray*)otherFolders;

- (NSStringEncoding) encoding;
- (void)setEncoding:(NSStringEncoding)aEncoding;

- (void)setSocketTimeout:(int)timeout;
- (int)socketTimeout;

- (void)setUserAgent:(NSString*)aAgent;
- (NSString*)userAgent;

- (void)setActiveDate:(NSDate*)aDate;
- (NSDate*)activeDate;
- (void)setFolderDate:(NSDate*)aDate;
- (NSDate*)folderDate;

@end
