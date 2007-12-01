//
//  DPHTTPMailBundle.h
//  httpmail
//
//  Created by Daniel Parnell on Sat Sep 21 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-api.h"
#import "mail-app.h"

#ifdef TARGET_TIGER
#define BUNDLE_LOCK
#endif
#ifdef TARGET_LEOPARD
#define BUNDLE_LOCK
#endif

@interface DPHTTPMailBundle : MVMailBundle {
}

+ (NSString*) bundleVersionString;

+ (void) saveHTTPMailAccounts;
+ (void) loadHTTPMailAccounts;
#ifndef TARGET_JAGUAR
+ (BOOL) bundleFinishedInitialization;
#endif

+ (void) setDownloadSentItems:(BOOL)flag;
+ (BOOL) downloadSentItems;
+ (void) setFoldersUnderInbox:(BOOL)flag;
+ (BOOL) foldersUnderInbox;
+ (void) setSocketTimeout:(int)timeout;
+ (int) socketTimeout;
+ (BOOL) createFailureMessages;
+ (void) setCreateFailureMessages:(BOOL) flag;
+ (BOOL) ignoreNetworkState;
+ (void) setIgnoreNetworkState:(BOOL) flag;
+ (NSString*) userAgent;
+ (void) setUserAgent:(NSString*)aAgent;
+ (BOOL) checkForUpdates;
+ (void) setCheckForUpdates:(BOOL) flag;
+ (BOOL) detailedErrorReports;
+ (void) setDetailedErrorReports:(BOOL) flag;

#ifdef BUNDLE_LOCK
+ (void) lock;
+ (void) unlock;
+ (BOOL) waitForLock;
#endif
@end
