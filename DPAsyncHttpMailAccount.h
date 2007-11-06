//
//  DPAsyncHttpMailAccount.h
//  httpmail
//
//  Created by Daniel Parnell on Sun May 11 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-api.h"
#import "mail-app.h"
#import "DPAsyncHttpMail.h"

@interface DPAsyncHttpMailAccount : MailAccount {
    DeliveryAccount* 		delivery;
    int				state;
    NSString*			destFolder;
    MessageStore*		destStore;
    NSMutableArray*		foldersToDownload;
    NSMutableArray*		downloadedUIDs;
    NSMutableArray* 		toDownload;
    NSArray*			messagesToProcess;
    NSDictionary*		dictionaryToProcess;
    NSEnumerator*		toProcessEnumerator;
    unsigned int                index;
    BOOL			finished;
    BOOL			stop;
}

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

- (void) addFailureMessage:(NSString*)subject withBody:(NSData*) body intoMessageStore: (MessageStore*)store;

@end

@interface DPAsyncHttpMail(HTTPMailAccountStuff)
+ (DPAsyncHttpMail*)newWithMailAccount: (DPAsyncHttpMailAccount*)account;
- initWithMailAccount: (DPAsyncHttpMailAccount*)account;
@end
