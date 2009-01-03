//
//  DPHTTPMailBundle.m
//  httpmail
//
//  Created by Daniel Parnell on Sat Sep 21 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPHTTPMailBundle.h"
#import "HTTPMailAccount.h"
#import "DPAsyncHttpMailAccount.h"
#import "HTTPMailDeliveryAccount.h"
#import "DPProxy.h"
#import "Localization.h"
#import "DPHTTPMailPreferences.h"
#import "NSPreferences.h"
#import "HTTPMailUpdateChecker.h"
#import "Version.h"

#ifdef WATCH_NOTIFICATIONS
#import "DPNotificationWatcher.h"
#endif

#ifdef BUNDLE_LOCK
#import "NSObject-LockingAdditions.h"
#endif

#define STACK_TRACE

#ifndef TARGET_JAGUAR

#import "HTTPMailAuthScheme.h"

static BOOL finished = NO;

#endif

static BOOL foldersUnderInbox = NO;
static BOOL downloadSentItems = NO;
static BOOL detailedErrors = NO;

#ifdef STACK_TRACE
#import <ExceptionHandling/NSExceptionHandler.h>

static NSUncaughtExceptionHandler* oldExceptionHandler = NULL;
static id oldExceptionHandlerDelegate = NULL;

void CB_exceptionHandler( NSException *exception )
{
    NSString *stackTrace = [[exception userInfo] objectForKey:NSStackTraceKey];
    if(stackTrace) {
        NSLog(@"stackTrace = %@", stackTrace);
        
        NSString *str = [NSString stringWithFormat:@"/usr/bin/atos -p %d %@ | tail -n +3 | head -n +%d | c++filt | cat -n",
            [[NSProcessInfo processInfo] processIdentifier],
            stackTrace,
            ([[stackTrace componentsSeparatedByString:@"  "] count] - 4)];
        FILE *file = popen( [str UTF8String], "r" );

        if( file )
        {
            char buffer[512];
            size_t length;

            fprintf( stderr, "An exception of type %s occured.\n%s\n", [[exception name] cStringUsingEncoding: NSUTF8StringEncoding], [[exception reason] cStringUsingEncoding: NSUTF8StringEncoding] );
            fprintf( stderr, "Stack trace:\n" );

            while( length = fread( buffer, 1, sizeof( buffer ), file ) )
            {
                fwrite( buffer, 1, length, stderr );
            }

            pclose( file );
        }
    }
    
    if(oldExceptionHandler) {
        oldExceptionHandler(exception);
    }
}
#endif

static UInt32 getOSVersion() {
	SInt32 result;
	Gestalt(gestaltSystemVersion, &result);
	
	return result;
}

@implementation DPHTTPMailBundle

#ifdef BUNDLE_LOCK
static NSLock* lock = nil;
#endif

+ (void) initialize
{
	int osVersion = getOSVersion() & 0x0FFF0;

#ifdef BUNDLE_LOCK
	lock = [[NSLock new] retain];
#endif

#ifdef WATCH_NOTIFICATIONS
    NSLog(@"Installing notification watcher");
    [[DPNotificationWatcher new] retain];
#endif

    [super initialize];
    [self registerBundle];
 
#ifdef STACK_TRACE
    oldExceptionHandler = NSGetUncaughtExceptionHandler();
    
    // use our exception hander for stack trace printout
    NSSetUncaughtExceptionHandler( *CB_exceptionHandler );

    // this will give us some better exception handling capabilities
    NSLog(@"enabling global exception handler");
    [[NSExceptionHandler defaultExceptionHandler] setExceptionHandlingMask:( NSHandleUncaughtExceptionMask | NSHandleUncaughtSystemExceptionMask | NSHandleUncaughtRuntimeErrorMask | NSHandleTopLevelExceptionMask | NSHandleOtherExceptionMask | 64 | 128 | 256 | 512 )];
    oldExceptionHandlerDelegate = [[NSExceptionHandler defaultExceptionHandler] delegate];
    [[NSExceptionHandler defaultExceptionHandler] setDelegate: self];
#endif

    NSLog(@"Daniels httpmail plugin loaded");    
    NSLog(@"Checking OS version");

#ifdef TARGET_LEOPARD
    // are we trying to run on something other than Leopard?
    if(osVersion!=0x1050) {
        NSString* message = LocalizedString(@"The version of the HTTPMail plugin installed requires MacOS X 10.5", @"");
        NSString* title = LocalizedString(@"HTTPMail Plugin", @"");
        NSLog(@"Failed OS version check");		
		NSRunCriticalAlertPanel(title, message, @"Ok", nil, nil);
        return;
    }
#endif

#ifdef TARGET_TIGER
    // are we trying to run on something other than Tiger?
    if(osVersion!=0x1040) {
        NSString* message = LocalizedString(@"The version of the HTTPMail plugin installed requires MacOS X 10.4", @"");
        NSString* title = LocalizedString(@"HTTPMail Plugin", @"");
        NSLog(@"Failed OS version check");		
		NSRunCriticalAlertPanel(title, message, @"Ok", nil, nil);
        return;
    }
#endif
        
#ifdef TARGET_PANTHER
    // are we trying to run on something other than Panther?
    if(osVersion!=0x1030) {
        NSString* message = LocalizedString(@"The version of the HTTPMail plugin installed requires MacOS X 10.3", @"");
        NSString* title = LocalizedString(@"HTTPMail Plugin", @"");
        NSLog(@"Failed OS version check");		
		NSRunCriticalAlertPanel(title, message, @"Ok", nil, nil);
        return;
    }
#endif

#ifdef TARGET_JAGUAR
    // are we trying to run on something other than Jaguar?
    if(osVersion!=0x1020) {
        NSString* message = LocalizedString(@"The version of the HTTPMail plugin installed requires MacOS X 10.2", @"");
        NSString* title = LocalizedString(@"HTTPMail Plugin", @"");
        NSLog(@"Failed OS version check");
		NSRunCriticalAlertPanel(title, message, @"Ok", nil, nil);
        return;
    }
#endif

#ifdef TARGET_PANTHER
    NSLog(@"registering auth scheme");
    [AuthScheme registerSchemeClass: [HTTPMailAuthScheme class]];
#endif

    NSLog(@"registering account type");
#ifdef TARGET_JAGUAR
    [AccountPreferences addAccountType: @"httpmail" className: @"HTTPMailAccount"];
#else
#ifdef TARGET_PANTHER
    [AccountPreferences addAccountType: @"httpmail" className: @"HTTPMailAccount"];
#else
#ifdef TARGET_TIGER
	[AccountPreferences addAccountType: @"httpmail" class: [HTTPMailAccount class]];
#else
#ifdef TARGET_LEOPARD
	[AccountPreferences addAccountType: @"httpmail" class: [HTTPMailAccount class]];
#else
#error FIXME
#endif
#endif
#endif
#endif

//    [AccountPreferences addAccountType: @"async httpmail" className: @"DPAsyncHttpMailAccount"];
    NSLog(@"registered account type");
  
//    [HTTPMailDeliveryConnection poseAsClass: [SMTPConnection class]];
    
//    [MessageHack poseAsClass: [Message class]];
//    [HTTPMailDeliveryQueue poseAsClass: [DeliveryQueue class]];
//    NSLog(@"delivery queue = %@", [NSApp deliveryQueue]);    
    

    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(mailWillTerminate:) name: NSApplicationWillTerminateNotification object: NSApp];
    [self loadHTTPMailAccounts];
/*	    
    NSMutableArray* accounts;
    accounts = [MailAccount mailAccounts];
    int i, C;
    C = [accounts count];
    for(i=0; i<C; i++) {
        Account* acc = (MailAccount*)[accounts objectAtIndex: i];
        NSLog(@"%d, %@, %@, %@", i, [acc class], [acc displayName], [acc accountInfo]);
//        NSLog(@"%d, %@, %@, %@", i, [acc class], [acc displayName], [acc deliveryClass]);
//        NSLog(@"%d, %@, %@", i, [acc displayName], [acc storeClass]);
//        NSLog(@"%d, %@, %@, %d", i, [acc displayName], [acc primaryMailboxUid], [[acc primaryMailboxUid] type]);
    }   
*/

#ifndef TARGET_JAGUAR
    [[NSPreferences sharedPreferences] addPreferenceNamed: @"HTTPMail" owner: [DPHTTPMailPreferences sharedInstance]];
    
    finished = YES;
#endif
}

#ifdef TARGET_JAGUAR
+(BOOL) hasPreferencesPanel
{
    return NO;
}
#else

+(BOOL) hasPreferencesPanel
{
    return YES;
}

+ (NSString*) preferencesOwnerClassName {
    return NSStringFromClass([DPHTTPMailPreferences class]);
}

+ (NSString*) preferencesPanelName {
    return @"DPHTTPMailPreferences";
}

#endif

+ (BOOL)hasComposeAccessoryViewOwner
{
    return NO;
}

static NSString* ACCOUNTS = @"Accounts";
static NSString* DOWNLOAD_SENT_ITEMS = @"Download Sent Items";
static NSString* FOLDERS_UNDER_INBOX = @"Folders Under Inbox";
static NSString* TIMEOUT = @"Socket Timeout";
static NSString* GENERATE_FAILURE_MESSAGES = @"Generate Failure Messages";
static NSString* IGNORE_NETWORK_STATE = @"Ignore Network State";
static NSString* USER_AGENT = @"User Agent";
static NSString* CHECK_FOR_UPDATES = @"Check For Updates";
static NSString* DETAILED_ERRORS = @"Create Detailed Errors";

static NSString* httpmailPrefs = @"~/Library/Preferences/person.djlp.mail.plist";
 
+ (void) saveHTTPMailAccounts {
#ifndef TARGET_JAGUAR
    NSArray* accounts = [MailAccount mailAccounts];
    int i, C;
    
    NSMutableArray* list = [NSMutableArray array];
    C = [accounts count];
    for(i=0; i<C; i++) {
        MailAccount* account = [accounts objectAtIndex: i];
        
        if([account isKindOfClass: [HTTPMailAccount class]] /* || [account isKindOfClass: [DPAsyncHttpMailAccount class]]*/ ) {
            NSDictionary* dict = [account defaultsDictionary];
            
            [list addObject: dict];
        }
    }
#endif 
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    
#ifndef TARGET_JAGUAR
    [dict setObject: list forKey: ACCOUNTS];
#endif    
    [dict setObject: [NSNumber numberWithBool: downloadSentItems] forKey: DOWNLOAD_SENT_ITEMS];
    [dict setObject: [NSNumber numberWithBool: foldersUnderInbox] forKey: FOLDERS_UNDER_INBOX];
    [dict setObject: [NSNumber numberWithInt: [DPHTTPMailBundle socketTimeout]] forKey: TIMEOUT];
    [dict setObject: [NSNumber numberWithBool: [DPHTTPMailBundle createFailureMessages]] forKey: GENERATE_FAILURE_MESSAGES];
    [dict setObject: [NSNumber numberWithBool: [DPHTTPMailBundle ignoreNetworkState]] forKey: IGNORE_NETWORK_STATE];
    [dict setObject: [NSNumber numberWithBool: [DPHTTPMailBundle checkForUpdates]] forKey: CHECK_FOR_UPDATES];
    [dict setObject: [NSNumber numberWithBool: [DPHTTPMailBundle detailedErrorReports]] forKey: DETAILED_ERRORS];
	
    if([DPHTTPMailBundle userAgent]) {
        [dict setObject: [DPHTTPMailBundle userAgent] forKey: USER_AGENT];
    } else {
        [dict removeObjectForKey: USER_AGENT];
    }
    
    NSData* data = [NSPropertyListSerialization dataFromPropertyList: dict  format: NSPropertyListXMLFormat_v1_0 errorDescription: nil];
    [data writeToFile: [httpmailPrefs stringByExpandingTildeInPath] atomically: YES];
}

+ (void) loadHTTPMailAccounts { 
    NSFileManager* fm = [NSFileManager defaultManager];
    NSString* file = [httpmailPrefs stringByExpandingTildeInPath];
    
    if([fm fileExistsAtPath: file]) {
#ifdef TARGET_PANTHER
        [MailAccount enableMailboxListingNotifications];
#endif
#ifdef TARGET_TIGER
        [MailAccount enableMailboxListingNotifications: YES];
#endif
        
        NSData* data = [NSData dataWithContentsOfFile: file];
        NSArray* httpmailAccounts;
        id  preferences = [NSPropertyListSerialization propertyListFromData: data mutabilityOption: NSPropertyListImmutable format: nil errorDescription: nil];
        
        if([preferences isKindOfClass: [NSArray class]]) {
            httpmailAccounts = preferences;
        } else {
            httpmailAccounts = [preferences objectForKey: ACCOUNTS];
            downloadSentItems = [[preferences objectForKey: DOWNLOAD_SENT_ITEMS] intValue];
            foldersUnderInbox = [[preferences objectForKey: FOLDERS_UNDER_INBOX] intValue];
            [DPHTTPMailBundle setCreateFailureMessages: [[preferences objectForKey: GENERATE_FAILURE_MESSAGES] intValue]];
            [DPHTTPMailBundle setIgnoreNetworkState: [[preferences objectForKey: IGNORE_NETWORK_STATE] intValue]];
            [DPHTTPMailBundle setUserAgent: [preferences objectForKey: USER_AGENT]];
            
            if([preferences objectForKey: CHECK_FOR_UPDATES]) {
                [DPHTTPMailBundle setCheckForUpdates: [[preferences objectForKey: CHECK_FOR_UPDATES] intValue]];
            }
            
            if([preferences valueForKey: TIMEOUT]) {
                [DPHTTPMailBundle setSocketTimeout: [[preferences objectForKey: TIMEOUT] intValue]];
            }
			
			if([preferences objectForKey: DETAILED_ERRORS]) {
				[DPHTTPMailBundle setDetailedErrorReports: [[preferences objectForKey: DETAILED_ERRORS] intValue]];
			}
        }
    
        if([DPHTTPMailBundle checkForUpdates]) {
			NS_DURING
				[HTTPMailUpdateChecker checkForUpdates: NO];
			NS_HANDLER
				// do nothing
		    NS_ENDHANDLER
        }
        
#ifndef TARGET_JAGUAR
		NSArray* existingAccounts = [MailAccount mailAccounts];
		
		NSEnumerator* e;
		NSDictionary* dict;
		e = [httpmailAccounts objectEnumerator];
        while(dict = [e nextObject]) {
            MailAccount* account;
            NSString* type = [dict objectForKey: @"AccountType"];
            
			NSString* accountName = [dict objectForKey: @"AccountName"];
			if(accountName==nil) {
				accountName = [[dict objectForKey: @"EmailAddresses"] objectAtIndex: 0];
				if(accountName==nil) {
					accountName = @"HTTPMail Account";
				}
				
				NSMutableDictionary* dictCopy = [dict mutableCopy];
				[dictCopy setObject: accountName forKey: @"AccountName"];
				
				dict = dictCopy;
			}
			 
            if([type isEqualToString: @"HTTPMailAccount"]) {
				NSEnumerator* ee = [existingAccounts objectEnumerator];
				MailAccount* existingAccount;
				BOOL found = NO;
				
				while(existingAccount = [ee nextObject]) {
					if([[existingAccount displayName] isEqualToString: accountName]) {
						NSLog(@"Account '%@' already loaded", accountName);
						found = YES;
						break;
					}
				}
				
				if(found) {
					account = nil;
				} else {
					NSLog(@"Recreating account '%@'", accountName);
					account = [HTTPMailAccount createAccountWithDictionary: dict];
				}
            }/* else 
            if([type isEqualToString: @"DPAsyncHttpMailAccount"]) {
                account = [DPAsyncHttpMailAccount createAccountWithDictionary: dict];
            }*/ else {
                account = nil;
            }
            			
            if(account) {
				[account setShouldMoveDeletedMessagesToTrash: YES];
                [NSApp insertInAccounts: account];
#ifdef TARGET_PANTHER				
                [account synchronizeMailboxListAfterImport];
#else
				[account _synchronizeMailboxListWithFileSystem];
#endif
            }
        }
        
        [MailAccount saveAccountInfoToDefaults];
        [MailAccount _postMailAccountsHaveChanged];
#endif
        
    }
}

+ (void) mailWillTerminate:(id)notification {
    [self saveHTTPMailAccounts];
}

+ (NSString *) bundleVersion {
    return @"1.0";
}

#ifndef TARGET_JAGUAR
+ (BOOL) bundleFinishedInitialization {
    return finished;
}
#endif

+ (void) setDownloadSentItems:(BOOL)flag {
    downloadSentItems = flag;
}

+ (BOOL) downloadSentItems {
    return downloadSentItems;
}

+ (void) setFoldersUnderInbox:(BOOL)flag {
    foldersUnderInbox = flag;
}

+ (BOOL) foldersUnderInbox {
    return foldersUnderInbox;
}

static int socketTimeout = 60;
+ (void) setSocketTimeout:(int)timeout {
    socketTimeout = timeout;
}

+ (int) socketTimeout {
    return socketTimeout;
}

static BOOL wantFailureMessges = NO;
+ (BOOL) createFailureMessages {
    return wantFailureMessges;
}

+ (void) setCreateFailureMessages:(BOOL) flag {
    wantFailureMessges = flag;
}

static BOOL ignoreNetworkState = NO;
+ (BOOL) ignoreNetworkState {
    return ignoreNetworkState;
}

+ (void) setIgnoreNetworkState:(BOOL) flag {
    ignoreNetworkState = flag;
}

static NSString* userAgent = nil;
+ (NSString*) userAgent {
    if(userAgent) {
        return userAgent;
    }
    
    return @"Entourage/10.0 (Mac_PowerPC; DigExt; TmstmpExt)";
}

+ (void) setUserAgent:(NSString*)aAgent {
    [aAgent retain];
    [userAgent release];
    
    userAgent = aAgent;
}

static BOOL checkForUpdates = YES;
+ (BOOL) checkForUpdates {
    return checkForUpdates;
}

+ (void) setCheckForUpdates:(BOOL) flag{
    checkForUpdates = flag;
}

#ifdef STACK_TRACE
- (BOOL)exceptionHandler:(NSExceptionHandler *)sender shouldLogException:(NSException *)exception mask:(unsigned int)aMask {
    CB_exceptionHandler(exception);
    
    return [oldExceptionHandlerDelegate exceptionHandler: sender shouldLogException: exception mask: aMask];
}


- (BOOL)exceptionHandler:(NSExceptionHandler *)sender shouldHandleException:(NSException *)exception mask:(unsigned int)aMask {
    CB_exceptionHandler(exception);
    
    return [oldExceptionHandlerDelegate exceptionHandler: sender shouldHandleException: exception mask: aMask];
}
#endif

+ (BOOL) detailedErrorReports {
	return detailedErrors;
}

+ (void) setDetailedErrorReports:(BOOL) flag {
	detailedErrors = flag;
}

#ifdef BUNDLE_LOCK
+ (void) lock {
	[lock lock];
}

+ (void) unlock {
	[lock unlock];
}

+ (BOOL) waitForLock {
    return [lock lockBeforeDate: [NSDate dateWithTimeIntervalSinceNow: 0.1]];
}

#endif

+ (NSString*) bundleVersionString {
	return [NSString stringWithFormat: @"HTTPMail Plugin Version %f for %@ %x", VERSION_NUMBER, VERSION_TARGET, getOSVersion()];
}

@end

#ifdef TARGET_PANTHER
extern int MVBundleCompatibilityVersion() {
    return 1;
}
#endif

