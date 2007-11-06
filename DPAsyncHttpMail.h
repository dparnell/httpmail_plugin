//
//  DPAsyncHttpMail.h
//  httpmail
//
//  Created by Daniel Parnell on Thu May 08 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPHttpmailMessage.h"
#import "DPAsyncHttp.h"

@class DPAsyncHttpMail;

@interface NSObject (DPAsyncHttpMailDelegate)

- (void) loginSuccessful: (DPAsyncHttpMail*)mail;
- (void) loginFailed: (DPAsyncHttpMail*)mail;
- (void) messagesFetched: (NSArray*)messages forMail: (DPAsyncHttpMail*)mail; 

- (void) operationSuccessful: (DPAsyncHttpMail*)mail;
- (void) operationFailed: (DPAsyncHttpMail*)mail withMessage: (NSString*)aMessage;

@end

@interface DPAsyncHttpMail : NSObject {
@private
@protected
    id				delegate;
    
    DPAsyncHttp*		fHttp;
    NSString*			fUsername;
    NSString*			fPassword;
    NSMutableDictionary*	fFolders;
    BOOL			fConnected;
    int				fCode;
    NSString*			fProviderURL;
    NSArray*			fOtherFolders;
    int				state;
    id				fetchObject;
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

- (void)login;
- (BOOL)isConnected;
- (void)close;

- (NSURL*)URLForFolder:(NSString*)folder;
- (void)messagesForFolder:(NSString*)folder;

- (void)get:(NSURL*)url;

- (int)responseCode;
- (NSString*)responseString;
- (NSData*)responseData;

- (NSURL*)trashFolder;
- (NSURL*)inboxFolder;
- (NSURL*)sendFolder;

- (void)moveMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from toFolder: (NSURL*)to;
- (void)removeMessageIDs: (NSArray*)msgs fromFolder: (NSURL*) from;
- (void)moveMessages: (NSArray*)msgs fromFolder: (NSURL*)from toFolder:(NSURL*)url;
- (void)remove:(NSArray*)msgs fromFolder: (NSURL*)from;
- (void)sendMessage:(NSString*)body to: (NSString*)reciptient;

- (void)markAsRead:(DPhttpmailMessage*)msg;

- (NSString*)providerURL;
- (void)setProviderURL:(NSString*)url;

- (NSArray*)otherFolders;

- (void) setDelegate: (id)aDelegate;
- (id) delegate;

@end
