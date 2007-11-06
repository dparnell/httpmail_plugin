//
//  HTTPMailAccount.h
//  httpmail
//
//  Created by Daniel Parnell on Sat Sep 21 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-api.h"
#import "mail-app.h"
#import "DPhttpmail.h"

#ifdef TARGET_TIGER
#define DESCEND_FROM_IMAP_ACCOUNT
#endif

#ifdef TARGET_LEOPARD
#define DESCEND_FROM_IMAP_ACCOUNT
#endif

#ifdef DESCEND_FROM_IMAP_ACCOUNT
@interface HTTPMailAccount : IMAPAccount {
#else
@interface HTTPMailAccount : MailAccount {
#endif
#ifdef TGARGET_JAGUAR
    DeliveryAccount*    delivery;
#endif
    NSMutableDictionary* _dict;
    NSMutableArray*     connections;
#ifdef TARGET_JAGUAR
    bool foundFolders;
#endif
	ActivityMonitor* monitor;
}

- (NSStringEncoding)transportEncoding;
- (void) setTransportEncoding:(NSStringEncoding)encoding;
- (BOOL) shouldMarkAsReadOnDownload;
- (void) setShouldMarkAsReadOnDownload:(BOOL)flag;
- (BOOL) shouldDeleteOnDownload;
- (void) setShouldDeleteOnDownload:(BOOL)flag;
- (NSString*) providerURL;
- (void) setProviderURL:(NSString*)url;
- (BOOL) shouldCheckLocalAccounts;
- (void) setShouldCheckLocalAccounts: (BOOL)flag;
- (BOOL) shouldDownloadExtraFolders;
- (void) setShouldDownloadExtraFolders: (BOOL)flag;
- (BOOL) shouldSaveSentMessages;
- (void) setShouldSaveSentMessages: (BOOL)flag;
- (BOOL) shouldSynchronize;
- (void) setShouldSynchonize: (BOOL)flag;

- (void) addFailureMessage:(NSString*)subject withBody:(NSData*) body intoMessageStore: (MessageStore*)store;

#ifdef DESCEND_FROM_IMAP_ACCOUNT
- (LibraryMessage*) addMessage:(NSData*)message toMailbox: (MailboxUid*) mailbox withFlags: (int) flags;
- (LibraryMessage*) addMessage:(NSData*)message toStore: (MessageStore*) store withFlags: (int) flags;
#endif

@end

@interface DPhttpmail(HTTPMailAccountStuff)
+ (DPhttpmail*) DPhttpmailWithMailAccount: (HTTPMailAccount*)account;
- initWithMailAccount: (HTTPMailAccount*)account;
@end

@interface DPhttpmailCache : NSObject {
    NSMutableDictionary* cache;
}

+ (DPhttpmailCache*)sharedInstance;

- (DPhttpmail*) httpmailWithAccount: (HTTPMailAccount*) account;
- (void) removeFromCache: (HTTPMailAccount*) account;

@end

void showAlert(id object, NSException* exception, NSString* title, NSString* message);

