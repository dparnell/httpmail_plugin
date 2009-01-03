//
//  HTTPMailAccount.m
//  httpmail
//
//  Created by Daniel Parnell on Sat Sep 21 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <objc/objc-class.h>
#import "HTTPMailAccount.h"
#import "Localization.h"
#import "httpmail_constants.h"
#import "HTTPMailDeliveryAccount.h"
#import "DPKeychain.h"
#import <SystemConfiguration/SystemConfiguration.h>
#import "mail-app.h"
#import "HTTPMailConnection.h"
#import "DPHTTPMailBundle.h"
#import "DPProxy.h"
#import "HTTPMailAccountDetails.h"
#import <ExceptionHandling/NSExceptionHandler.h>

#ifdef DESCEND_FROM_IMAP_ACCOUNT
#import "Library.h"
#import "LibraryIMAPStore.h"
#import "NSObject-LockingAdditions.h"
#endif

#ifdef TARGET_LEOPARD
#import "MailAccount-Internal.h"
#endif

static BOOL QuittingTime = NO;

@implementation DPhttpmailCache

DPhttpmailCache* httpmailCache = nil;

+ (DPhttpmailCache*)sharedInstance {
    if(httpmailCache==nil) {
        httpmailCache = [[DPhttpmailCache new] retain];
    }
    
    return httpmailCache;
}

- (id) init {
    self = [super init];
    
    if(self) {
        cache = [[NSMutableDictionary dictionary] retain];
    }
    
    return self;
}


- (void) dealloc {
    [cache release];
    [super dealloc];
}

- (DPhttpmail*) httpmailWithAccount: (HTTPMailAccount*) account {
    DPhttpmail* result;
    
    result = [cache objectForKey: [account displayName]];
    
    if(result==nil) {
        result = [[[DPhttpmail alloc] initWithMailAccount: account] autorelease];
        [cache setObject: result forKey: [account displayName]];
    } else {
        NSMutableDictionary* dict = [[account accountInfo] mutableCopy];
        NSDate* activeDate;
        NSDate* folderDate;
        
        activeDate = [dict objectForKey: @"Active Date"];
        folderDate = [dict objectForKey: @"Folder Date"];
        
        [result setActiveDate: activeDate];
        [result setFolderDate: folderDate];
        
        if(activeDate==nil) {
            activeDate = [NSDate date];
        }
        folderDate = [NSDate date];
        
        [dict setObject: activeDate forKey: @"Active Date"];
        [dict setObject: folderDate forKey: @"Folder Date"];
        
        [account setAccountInfo: dict];
    }
    
    
    return result;
}

- (void) removeFromCache: (HTTPMailAccount*) account {
    [cache removeObjectForKey: [account displayName]];
}

@end

@implementation DPhttpmail(HTTPMailAccountStuff)

+ (DPhttpmail*) DPhttpmailWithMailAccount: (HTTPMailAccount*)account {    
    return [[DPhttpmailCache sharedInstance] httpmailWithAccount: account];
}

- initWithMailAccount: (HTTPMailAccount*)account {
    self = [self init];
	
    if(self) {
        NSMutableDictionary* dict = [[account accountInfo] mutableCopy];
        NSDate* activeDate;
        NSDate* folderDate;
        
        NSString* password;

        [self setUserAgent: [DPHTTPMailBundle userAgent]];
        [self setProviderURL: [account providerURL]];

        [self setUsername: [account username]];
        
        password = [account passwordFromStoredUserInfo];
        if(password==NULL || [password isEqualToString: @""]) {
          password = [account promptUserForPasswordWithMessage: [NSString stringWithFormat: LocalizedString(@"Please enter the password for '%@'", @""), [account displayName]]];
        }
        
        [self setPassword: password];
        
        NSDictionary* settings = (NSDictionary*)SCDynamicStoreCopyProxies(NULL);
        NSString* proxy;
        NSNumber* enable = [settings objectForKey: @"HTTPEnable"];
        
//        NSLog(@"settings = %@", settings);
        
        if(enable && [enable intValue]) {
            proxy = [settings objectForKey: @"HTTPProxy"];
        } else {
            proxy = NULL;
        }

        if(proxy) {
            NSNumber* port = [settings objectForKey: @"HTTPPort"];
            [self setProxy: [NSURL URLWithString: [NSString stringWithFormat: @"http://%@:%@/", proxy, port]]];            
        
            DPKeychain* keychain = [DPKeychain new];
            NSDictionary* auth = [keychain findKeychainItem: proxy];
        
            if(auth) {
                [self setProxyUsername: [auth objectForKey: kcUsername]];
                [self setProxyPassword: [auth objectForKey: kcPassword]];
                
//                NSLog(@"proxy username='%@' password='%@'", [self proxyUsername], [self proxyPassword]);
            } else {
                /** @TODO: Add code here to pop up a box asking for the username and password for the proxy */
                // NSLog(@"could not find the username and password for the proxy in the keychain");
            }
        }    
    
        activeDate = [dict objectForKey: @"Active Date"];
        folderDate = [dict objectForKey: @"Folder Date"];
        
        [self setActiveDate: activeDate];
        [self setFolderDate: folderDate];
        
        if(activeDate==nil) {
            activeDate = [NSDate date];
        }
        folderDate = [NSDate date];
        
        [dict setObject: activeDate forKey: @"Active Date"];
        [dict setObject: folderDate forKey: @"Folder Date"];
        
        [account setAccountInfo: dict];
        
#ifndef TARGET_JARGUAR        
        [self setSocketTimeout: [DPHTTPMailBundle socketTimeout]];
#endif
    }
    
    return self;
}

@end


@implementation HTTPMailAccount

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    NSLog(@"HTTPMailAccount doesNotRecognizeSelector: %s", aSelector);
}

/*
- (BOOL)respondsToSelector:(SEL)aSelector {
    NSLog(@"HTTPMailAccount respondsToSelector: %s", aSelector);
    
    return [super respondsToSelector: aSelector];
}
*/

+ (id) httpMailAccount {
    return [HTTPMailAccount new];
}

+ (NSString*) accountTypeString {
    return @"HTTPMail";
}

- (id) init {
//    NSLog(@"%@ init", self);
    self = [super init];
    
    if(self) {	
        [NSApp addTerminationHandler: self];
        
        _dict = NULL;
#ifdef TARGET_JAGUAR
        foundFolders = NO;
#endif
        connections = [[NSMutableArray array] retain];
        
#ifndef DESCEND_FROM_IMAP_ACCOUNT
        [self setIsActive: YES];
        [self setShouldMoveDeletedMessagesToTrash: YES];
#endif
        
#ifdef TARGET_PANTHER        
        [self setPortNumber: 80];
        [self setUsesSSL: NO];
        
//        [self setPreferredAuthScheme: [AuthScheme schemeWithName: @"HTTPMail"]];
#endif
    }
  
//    return [DPProxy newWithTarget: self];
    return self;
}

#ifdef DESCEND_FROM_IMAP_ACCOUNT
- (id) initWithPath:(NSString*)aPath {
//    NSLog(@"%@ initWithPath: %@", self,  aPath);

    if(aPath==NULL) {        
        id result = [HTTPMailAccountDetails currentAccount];
        
        if(!result) {
            id currentAccountDetails = [HTTPMailAccountDetails currentAccountDetails];
            // NSLog(@"currentAccountDetails = %@", currentAccountDetails);
            aPath = [currentAccountDetails accountPath];
            // NSLog(@"aPath = %@", aPath);
            
            self = [super initWithPath: aPath];
            result = self;
			
			[self setIsActive: YES];
			[self setShouldMoveDeletedMessagesToTrash: YES];
			
        } else {
            [self autorelease];
        }
        
        return result;
    }
    
    self = [super initWithPath: aPath];

    if(self) {	
        [self setIsActive: YES];
#ifndef DESCEND_FROM_IMAP_ACCOUNT
        [self setShouldMoveDeletedMessagesToTrash: YES];
#endif		
    }
    
    return self;
//    return [DPProxy newWithTarget: self];
}
#endif

- (void)dealloc {
    [connections release];
    [super dealloc];
}

- (BOOL)canFetch {
    return YES;
}

- (void)resetFetcher {
}

- (BOOL) containsMailboxes {
    return YES;
}

- (MailboxUid*) mailboxUidFromName: (NSString*)name {
    int i, C;
    
    NSArray* mboxes = [self mailboxes];
    C = [mboxes count];
    for(i=0; i<C; i++) {
        MailboxUid* muid = [mboxes objectAtIndex: i];

        if([[muid name] isEqualToString: name]) {
            return muid;
        }
    }

/*
    NSLog(@"could not find uid '%@' = '%s' = %@", name, [name lossycStringUsingEncoding: NSUTF8StringEncoding], [name dataUsingEncoding: NSUTF8StringEncoding]);
    for(i=0; i<C; i++) {
        MailboxUid* muid = [mboxes objectAtIndex: i];
        NSLog(@"  '%@' = '%s' = %@", [muid name], [[muid name] lossycStringUsingEncoding: NSUTF8StringEncoding], [[muid name] dataUsingEncoding: NSUTF8StringEncoding]);
    }
*/    
    return NULL;
}


#ifdef DESCEND_FROM_IMAP_ACCOUNT
- (void) synchronizeMailboxListAfterImport {
    NSString* path = [self path];
    if(path) {
        NSFileManager* fm = [NSFileManager defaultManager];
        NSDirectoryEnumerator* enumerator = [fm enumeratorAtPath: path];
        NSString* file;
		
        while(file=[enumerator nextObject]) {
            if ([[file pathExtension] isEqualToString:@"mbox"]) {
                    NSString* folderName = [file stringByDeletingPathExtension];

#ifdef TARGET_LEOPARD
					folderName = [folderName stringByReplacingOccurrencesOfString: @" " withString: @"%20"];
					NSString* folderUrl = [[[self rootMailboxUid] URLString] stringByAppendingString: [folderName stringByReplacingOccurrencesOfString: @"'" withString: @"''"]];
					MailboxUid* folderUid = [MailAccount mailboxUidForURL: folderUrl forceCreation: YES];
					
					if(folderUid==nil) {
						NSLog(@"could not find folder: %@", folderUrl);
					}
#else
                    MailboxUid* folderUid = [self mailboxUidFromName: folderName];                    
//					NSLog(@"folderName = '%@'  folderUid = %@", folderName, folderUid);
                    if(folderUid==NULL) {
						
                        if(putFoldersUnderInbox) {
                            folderUid = [self createMailboxWithParent: [self primaryMailboxUid] name: folderName];
                        } else {
                            folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName];
                        }

						[LibraryStore createEmptyStoreIfNeededForPath: [folderUid fullPath] notIndexable: NO];						
                    }
#endif                    
                    [enumerator skipDescendents];
            }
        }
	}
}

- (BOOL)canAppendMessages {
	return YES;
}


#ifdef TARGET_LEOPARD
- (BOOL) _deleteMailbox:(id)dummy {
	return YES;
}
#endif

/*
- (id)storeForMailboxUid:(MailboxUid*)uid {
	id result = [super storeForMailboxUid: uid];
	NSLog(@"storeForMailboxUid: %@ = %@", uid, result);
	return [DPProxy newWithTarget: result];
}
*/

/*
- (NSString*) _nameForMailboxUid: (MailboxUid*) uid {
	NSLog(@"_nameForMailboxUid: %@", uid);
	return [uid name];
}
*/

- (NSString*) _URLScheme {
	return @"httpmail";
}

- (NSString*)URLString {
//	NSLog(@"URLString called");
	return [NSString stringWithFormat: @"httpmail://%@/", [self firstEmailAddress]];
}

+ (NSString*)defaultPathNameForAccountWithHostname:(NSString*)hostname username:(NSString*)username {
//	NSLog(@"defaultPathNameForAccountWithHostname: %@ username: %@", hostname, username);
	
	NSRange r = [username rangeOfString: @"@"];
	if(r.location==NSNotFound) {
		return [NSString stringWithFormat: @"HTTPMail-%@@%@", username, hostname];
	} else {
		return [NSString stringWithFormat: @"HTTPMail-%@", username];
	}
}

#endif

- (void)releaseAllConnections {
    [super releaseAllConnections];
}

- (unsigned int)defaultPortNumber {
    return 80;
}

- (unsigned int)defaultSecurePortNumber {
    return 80;
}

- (NSString*)serviceName {
    return @"httpmail";
}

- (NSString*)secureServiceName {
    return @"httpmail";
}

- (NSString*)saslProfileName {
    return @"httpmail";
}

#ifdef TARGET_PANTHER
- (void)setPreferredAuthScheme: scheme {
    [super setPreferredAuthScheme: scheme];
}

- (id)preferredAuthScheme {
    return [AuthScheme schemeWithName: @"HTTPMail"];
}
#endif

- (Class)storeClass {
//	NSLog(@"storeClass called");
#ifdef DESCEND_FROM_IMAP_ACCOUNT
    return [LibraryIMAPStore class];
#else
    return [NeXTMbox class];
#endif
}

#ifndef DESCEND_FROM_IMAP_ACCOUNT
- (Class)connectionClass {
    return [HTTPMailConnection class];
}
#endif

#ifndef TARGET_JAGUAR
- (id)connectionForStore:fp8 delegate:fp12 options:(int)fp16 {
    return NULL;
}
#endif

- (NSString*)mailboxPathExtension {
    return @"mbox";
}

- (BOOL)requiresAuthentication {
    return NO;
}

- (BOOL)canGoOffline {
    return YES;
}

- (void)setIsOffline:(char)flag {
    [super setIsOffline: flag];

    if(flag) {
        // remove this account from the cache since it has gone offline
        [[DPhttpmailCache sharedInstance] removeFromCache: self];
    } else {
#ifdef TARGET_PANTHER
        [self setConnectionError: nil];
#endif
    }
}

/*
- (char)isWillingToGoOnline {
    return YES;
}
*/

// stolen from GPGmail
- (NSRange) findBodyForData:(NSData*) data;
{
#define CR	'\r'
#define LF	'\n'
    const unsigned char	*bytes = [data bytes];
    const int			length = [data length];
    int					i;
    NSRange				result = NSMakeRange(NSNotFound, 0);
    
    // First let's find start of body (skip headers)
    for(i = 0; i < length; i++){
        if(bytes[i] == CR){
            if(i + 1 < length){
                if(bytes[i + 1] == CR){
                    result.location = i + 1;
                    break;
                }
                if(bytes[i + 1] == LF)
                    if(i + 3 < length)
                        if(bytes[i + 2] == CR && bytes[i + 3] == LF){
                            result.location = i + 2;
                            break;
                        }
            }
            if(i == 0){
                result.location = 0;
                break;
            }
        }
        else if(bytes[i] == LF){
            if(i + 1 < length)
                if(bytes[i + 1] == LF){
                    result.location = i + 1;
                    break;
                }
            if(i == 0){
                result.location = 0;
                break;
            }
        }
    }
  
    if(result.location!=NSNotFound) {  
        result.length = [data length] - result.location;
    }
    
    return result;
#undef LF
#undef CR
}

static NSString* exceptionDescription(id object, NSString* message, NSException* exception) {
    NSMutableString* buf = [NSMutableString stringWithFormat: @"%@\n", message];
    NSString *stackTrace = [[exception userInfo] objectForKey:NSStackTraceKey];
    NSString *atosPath = @"/usr/bin/atos";  // use the installed version of atos by default
    
    [buf appendString: [NSString stringWithFormat: @"An exception of type %s occured.\n%s\n", [[exception name] cStringUsingEncoding: NSUTF8StringEncoding], [[exception reason] cStringUsingEncoding: NSUTF8StringEncoding] ]];

    if(![[NSFileManager defaultManager] fileExistsAtPath: atosPath]) {
        atosPath = [[NSBundle bundleForClass: [HTTPMailAccount class]] pathForResource: @"atos" ofType: nil];
    }
    
    if(atosPath!=nil && [[NSFileManager defaultManager] fileExistsAtPath: atosPath]) {
        [buf appendString: @"Stack trace:\n" ];
        
        NSString *str = [NSString stringWithFormat:@"%@ -p %d %@",
                            atosPath,
                            [[NSProcessInfo processInfo] processIdentifier],
                            stackTrace];
        FILE *file = popen( [str UTF8String], "r" );

        if( file )
        {
            char buffer[512];
            size_t length;

            while( length = fread( buffer, 1, sizeof( buffer ), file ) )
            {
                [buf appendString: [NSString stringWithCString: &buffer[0] length: length]];
            }

            pclose( file );
        }
    }
    [buf appendString: @"\nRaw stack trace:\n"];
    [buf appendString: stackTrace];
        
    return buf;
}

void showAlert(id object, NSException* exception, NSString* title, NSString* message) {
#ifdef TARGET_JAGUAR
	if([httpmailBundle detailedErrorReports]) {
		message = exceptionDescription(object, message, exception);
	}
    [NSApp alertUserWithMessage: message title: title];
#endif

#ifndef TARGET_JAGUAR
    MFError* error;
    
    if(exception) {
		if([DPHTTPMailBundle detailedErrorReports]) {
			message = exceptionDescription(object, message, exception);
			error = [MFError errorWithDomain: @"HTTPMailErrors" code: 1 localizedDescription: message title: title helpTag: nil userInfo: nil];
		} else {
			error = [MFError errorWithException: exception];
		}
    } else {
        error = [MFError errorWithDomain: @"HTTPMailErrors" code: 1 localizedDescription: message title: title helpTag: nil userInfo: nil];
    }
  
    if(object && [object isKindOfClass: [HTTPMailAccount class]]) {
        [object setConnectionError: error];
        [object setIsOffline: YES];
    } else {
        [NSApp informUserOfError: error];
    
    }
#endif

	if(object && [object isKindOfClass: [HTTPMailAccount class]]) {
		if([DPHTTPMailBundle createFailureMessages]) {
			NSMutableData* body = [NSMutableData data];
			NSString* html = [NSString stringWithFormat: @"<code><pre>%@</pre></code>", message];
			[body appendBytes: [html UTF8String] length: [html length]];
			[object addFailureMessage: LocalizedString(@"Exception Details", @"") withBody: body intoMessageStore: nil];
		}
	}
}

- (void) downloadFromFolder: (NSString*)folder intoStore:(MessageStore*)store using:(DPhttpmail*)mail excludeUids: (NSArray*)downloadedUIDs {
#ifndef DESCEND_FROM_IMAP_ACCOUNT
    NSMutableArray* toAdd = [NSMutableArray array];
    NSMutableArray* failed = [NSMutableArray array];
#endif	
    NSData* result;
    NSMutableArray* uidsInThisFolder = [NSMutableArray array];
    NSMutableArray* toDelete = [NSMutableArray array];
    NSMutableArray* toMarkAsRead = [NSMutableArray array];
    NSMutableArray* readUidsInThisFoler = [NSMutableArray array];
    
//NSLog(@"here A");
    if([self shouldSynchronize]) {
        NSArray* messagesInStore = [[store copyOfAllMessages] autorelease];
        int messageCount = [messagesInStore count];
        int j;
//NSLog(@"here B");
        
//        NSLog(@"messagesInStore = %@", messagesInStore);
        
        for ( j = 0; j<messageCount; j++ )
        {
//NSLog(@"here C");
            Message* msg = (Message *)[messagesInStore objectAtIndex:j];
            if(([msg messageFlags] & 2)==0) {
#ifdef DESCEND_FROM_IMAP_ACCOUNT
				id UIDHeader = [msg remoteID];
				if(!UIDHeader) { 
					UIDHeader = [[msg headers] firstHeaderForKey:@"HttpmailUid"];
					
					if(UIDHeader) {
						[(LibraryMessage*)msg setRemoteID: UIDHeader];
						[(LibraryMessage*)msg commit];
						[Library commit];
					}
				}
#else			
                id UIDHeader = [[msg headers] firstHeaderForKey:@"HttpmailUid"];
#endif				
                if ( UIDHeader ) {
                    [uidsInThisFolder addObject:UIDHeader];
                    
                    // is the message read
                    if([msg messageFlags] & 1) {
                        [readUidsInThisFoler addObject: UIDHeader];
                    }
                }
            }
        }
    }
//NSLog(@"here D");
    
    NSArray* messages = [mail messagesForFolder: folder];
//NSLog(@"here E");

//    NSLog(@"messages for folder '%@' = \n%@", folder, messages);
    
    int i, j, C, C2, C3, C4;
    BOOL hasNewMail = NO;
    BOOL markAsRead = [self shouldMarkAsReadOnDownload];
    BOOL deleteThem = [self shouldDeleteOnDownload];
    BOOL found;
//NSLog(@"here F");
    
    DPhttpmailMessage* m;                
    NSString* uid;
    NSMutableArray* toDownload = [NSMutableArray array];
//NSLog(@"here G");
        
    C2 = [downloadedUIDs count];
    C3 = [uidsInThisFolder count];
    C4 = [readUidsInThisFoler count];
    
    C = [messages count];
    for(i=0; i<C; i++) {
        m = [messages objectAtIndex: i];                
        uid = [m uniqueID];
          
        found = NO;
        for(j=0; j<C2; j++) {
            if([uid isEqualToString: [downloadedUIDs objectAtIndex: j]]) {
                found = YES;
                break;
            }
        }

//        NSLog(@"'%@' '%@' %d", [m subject], uid, found);

        if(!found) {
            [toDownload addObject: m];
        } else {
            // the message was found, now is it in this folder?
            found = NO;
            
            for(j=0; j<C3; j++) {
                NSString* existingUid = [uidsInThisFolder objectAtIndex: j];
                if([uid isEqualToString: existingUid]) {
                    found = YES;
                    break;
                }
            }
            
            if(!found) {
                // no it isn't, so add it to a list of messages to be deleted from this folder
                [toDelete addObject: m];
            } else {
                // it is found, now do we need to mark it as read?
                
                if(![m read]) {
                    found = NO;
                    for(j=0; j<C4; j++) {
                        NSString* readUID = [readUidsInThisFoler objectAtIndex: j];
                        if([uid isEqualToString: readUID]) {
                            found = YES;
                            break;
                        }
                    }
                    
                    if(found) {
                        [toMarkAsRead addObject: m];
                    }
                }
            }
        }
        
//        if(![downloadedUIDs containsObject: uid]) {
//            [toDownload addObject: m];
//        }
    }
//NSLog(@"here H");
    
    C = [toDownload count];
	[monitor setItemsTotal: C];
    for(i=0; i<C && ![mail stopped] && ![monitor shouldCancel]; i++) {
//NSLog(@"here I");
        m = [toDownload objectAtIndex: i];                
        uid = [m uniqueID];
            
        [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Fetching message %d of %d", @""), i+1, C]];
		[monitor setItemsDone: i];
//NSLog(@"here J");

        if(!hasNewMail) {                        
//NSLog(@"here K");
            [self newMailHasBeenReceived];
//NSLog(@"here L");
            hasNewMail = YES;
        }
//NSLog(@"here M");
    
        NSMutableData* data = [NSMutableData dataWithData: [mail get: [m url]]];
        
        if([data length]==0) {
            NSLog(@"download of message '%@' returned no data for URL: %@", [m subject], [m url]);
            
            continue;
        }
//NSLog(@"here N");
        
        [data convertNetworkLineEndingsToUnix];
        NSMutableData* messageData;
//NSLog(@"here O");

        NSRange bodyRange = [self findBodyForData: data];

        NSString* uidHeader = [NSString stringWithFormat: @"HttpmailUid: %@\nHttpmailFolder: %@\n", uid, [m folder]];
    
        messageData = [NSMutableData data];
        
        if(bodyRange.location!=NSNotFound) {
            [messageData appendData: [data subdataWithRange:NSMakeRange(0, bodyRange.location)]];
        } else {
            [messageData appendData: data];
        }
//NSLog(@"here P");
        
        [messageData appendBytes: [uidHeader cStringUsingEncoding: NSUTF8StringEncoding] length: [uidHeader length]];
//NSLog(@"here Q");
        
        if(bodyRange.location!=NSNotFound) {
            [messageData appendData: [data subdataWithRange: bodyRange]];
        } else {
            NSString* emptyBody = @"\r\n\r\n";
            
            [messageData appendBytes: [emptyBody cStringUsingEncoding: NSUTF8StringEncoding] length: [emptyBody length]];
        }
//NSLog(@"here R");
        
            [messageData convertNetworkLineEndingsToUnix];
//NSLog(@"here S");
        
#ifdef DESCEND_FROM_IMAP_ACCOUNT
		int flags;
        
        if([m read]) {
            flags = 0x00000081;  // read message that needs to be processed by the junk mail filter
        } else {
            flags = 0x00000080;  // unread message that needs to be processed by the junk mail filter
        }
//NSLog(@"here T");
        
		LibraryMessage* msg = [self addMessage: messageData toStore: store withFlags: flags];
		[msg setRemoteID: uid];
		
		[msg commit];
//NSLog(@"here U");
#else		
        NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: messageData] autorelease];
        Message* msg = [[TOCMessage alloc] initWithMessage: [Message messageWithRFC822Data: messageData]];
        [msg setMessageStore: tmpStore];
        
        if([m read]) {
            [msg setMessageFlags: 0x00000081];  // read message that needs to be processed by the junk mail filter
        } else {
            [msg setMessageFlags: 0x00000080];  // unread message that needs to be processed by the junk mail filter
        }
        
        [toAdd removeAllObjects];
        [toAdd addObject: msg];
        
        [store appendMessages: toAdd unsuccessfulOnes: failed];
#endif
//NSLog(@"here V");

        id messageID = [msg messageID];
        
        Message* addedMsg = [store messageForMessageID: messageID];
        
        if(addedMsg) {
            NSArray* toRoute = [NSArray arrayWithObject: addedMsg];
            NSArray* routedMessages = [store routeMessages: toRoute];
  
            if([routedMessages count]) {
                // the message was routed to a different folder so add it to the list of messages to delete from this folder
                [toDelete addObject: m];
            }
        }

//NSLog(@"here W");
        
        if(markAsRead && ![m read]) {
            [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Marking message %@ as read", @""), [NSString stringWithFormat: @"%d", i+1]]];
			[monitor setItemsDone: i];
			
            result = [mail markAsRead: m];
            
            if([mail responseCode]>299) {
                showAlert(self, nil, LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while marking a message as read on the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
            }
            
        } else if(deleteThem) {
            [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Removing message %@", @""), [NSString stringWithFormat: @"%d", i+1]]];
			[monitor setItemsDone: i];
			
            NSArray* messageToDelete = [NSArray arrayWithObject: m];
            
            result = [mail remove: messageToDelete fromFolder: [mail URLForFolder: folder]];
            
            if([mail responseCode]>299) {
                showAlert(self, nil, LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while removing a message from the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
            }
        }
        
//NSLog(@"here X");
        if(![NSApp isRunning] || [monitor shouldCancel]) break;
    }


//    NSLog(@"%@ %@ %@", [self accountName], folder, toDelete);
//NSLog(@"here Y");

    if([self shouldSynchronize]) {
        [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Synchronizing folder %@", @""), folder]];
    
        if([toDelete count]) {
            result = [mail remove: toDelete fromFolder: [mail URLForFolder: folder]];
            
            if([mail responseCode]>299) {
                showAlert(self, nil, LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while synchronizing messages on the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
            }
        }

        C = [toMarkAsRead count];
        if(C) {
            for(i=0; i<C; i++) {
                DPhttpmailMessage* m = [toMarkAsRead objectAtIndex: i];
                
//                [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Marking message %@ of %@ as read", @""), [NSString stringWithFormat: @"%d", i+1], C]];
                result = [mail markAsRead: m];
                
                if([mail responseCode]>299) {
                    showAlert(self, nil, LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while marking a message as read on the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
                    break;
                }
            }
        }
    }
//NSLog(@"here Z");

}

- (void)fetchSynchronouslyIsAuto:(NSNumber*)flag {
	[self fetchSynchronously];
}

//#define TEST_MESSAGE_CODE
- (void) fetchSynchronously {    
	monitor = [ActivityMonitor currentMonitor];

#ifdef DESCEND_FROM_IMAP_ACCOUNT
    [self setConnectionError: nil];
#endif

#ifdef TEST_MESSAGE_CODE
    NSString* body = @"<b>Maybe</b> this time?<br/>";
    NSString* text = [NSString stringWithFormat: @"Message-ID: <%@>\nFrom: httpmail plugin<danielparnell@hotmail.com>\nSubject: %@\nContent-Type: text/html\n\n%@", [NSDate date], @"This is a test message", body];
    const char* bytes = [text UTF8String];
	
    NSData* data = [NSData dataWithBytes: bytes length: [text length]];
	
    MailboxUid* inbox = [self primaryMailboxUid];
    [self addMessage: data toMailbox: inbox withFlags: 0x080];
    // tell the rest of the system we are finished now
    [self _backgroundFetchCompleted];

    return;
#endif

    NSDictionary* settings = (NSDictionary*)SCDynamicStoreCopyProxies(NULL);
    NSNumber* proxyEnabled = [settings objectForKey: @"HTTPEnable"];
    NSString* proxy = [settings objectForKey: @"HTTPProxy"];
    NSString* host;
		
    if(proxy && [proxyEnabled intValue]) {
        host = proxy;
    } else {
        host = [[NSURL URLWithString: [self providerURL]] host];
    }

    if(![DPHTTPMailBundle ignoreNetworkState]) {
        NetworkController* nc = [NetworkController sharedInstance];
        if(![nc isHostReachable: host]) {
//            NSLog(@"can't get to httpmail server so we won't bother trying");

            // tell the rest of the system we are finished now
            [self _backgroundFetchCompleted];
      
#ifdef TARGET_PANTHER
            [self setIsOffline: YES];
#endif

            return;
        }
    }
    
#ifndef TARGET_JAGUAR
    BOOL putFoldersUnderInbox = [DPHTTPMailBundle foldersUnderInbox];
#endif

#ifdef DESCEND_FROM_IMAP_ACCOUNT
    [monitor setStatusMessage: LocalizedString(@"Waiting to connect", @"")];
    while(![DPHTTPMailBundle waitForLock] && !QuittingTime) {
        // wait for the lock
    }
    
    if(QuittingTime) {
        return;
    }
#endif

//NSLog(@"here 1");
    MailboxUid* mb = [self primaryMailboxUid];
//NSLog(@"here 2");
    MessageStore* store = [MessageStore currentlyAvailableStoreForUid: mb];
//NSLog(@"here 3");
    
    if(store==NULL) {
//NSLog(@"here 4");
        store = [self storeForMailboxUid: mb];
    }
//NSLog(@"here 5");
    
    if(![store isOpened]) {
#ifdef DESCEND_FROM_IMAP_ACCOUNT
		[store openAsynchronouslyUpdatingMetadata: NO];
//		[store openSynchronously];
#else		
        [store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
#endif		
    }
//NSLog(@"here 6");
    
    DPhttpmail* mail;
    
    @try {	
//        [NSException raise: @"test exception" format: @"testing the exception handler"];
	
//        mail = [[[DPhttpmail alloc] initWithMailAccount: self] autorelease];
        mail = [DPhttpmail DPhttpmailWithMailAccount: self];
        
        [connections addObject: mail];
        
        [mail setEncoding: [self transportEncoding]];
//NSLog(@"here 7");
        
        if(![mail isConnected]) {
//NSLog(@"here 8");
            [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Connecting to '%@'...", @""), [self displayName]]];
//NSLog(@"here 9");
            [mail login];
        }
//NSLog(@"here 10");
        
        if( [mail isConnected] && ![mail stopped] && ![monitor shouldCancel]) {
//NSLog(@"here 11");
            NSMutableArray *downloadedUIDs = [NSMutableArray array];
            NSArray* mailboxUids = [MailAccount allMailboxUids]; 
            int L = [mailboxUids count];
            int i,j;
            BOOL checkOthers = [self shouldCheckLocalAccounts];
        
//NSLog(@"here 12");
            for ( i = 0; i<L; i++ )
            {
                MailboxUid* mbox = [mailboxUids objectAtIndex: i];
                MailAccount* account = [mbox account];
                NSArray* messagesInBox;
                int messageCount;

//NSLog(@"here 13");
        
                // only look in this account and local accounts
                if((account==self)||(checkOthers && [account isKindOfClass: [LocalAccount class]]))
                {
                    NSAutoreleasePool* pool = [NSAutoreleasePool new];
                    
                    MessageStore* s = [MessageStore currentlyAvailableStoreForUid: mbox];
//NSLog(@"here 14");
                    
                    if(s==NULL) {
                        s = [account storeForMailboxUid: mbox];
                    }
                    
                    if(![s isOpened]) {
//NSLog(@"here 15");
#ifdef DESCEND_FROM_IMAP_ACCOUNT
						[s openSynchronously];
#else		
                        [s openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
#endif		
                    }
//NSLog(@"here 16");
                    
                    messagesInBox = [[s copyOfAllMessages] autorelease];
//NSLog(@"here 17");
                    messageCount = [messagesInBox count];
                    for ( j = 0; j<messageCount; j++ )
                    {
#ifdef DESCEND_FROM_IMAP_ACCOUNT
						LibraryMessage* libMsg = [messagesInBox objectAtIndex:j];
//						NSLog(@"looking for remote ID of: %@", libMsg);
						id UIDHeader = [libMsg remoteID];
						if(!UIDHeader) {
//							NSLog(@"not found so looking for the message header");
							UIDHeader = [[libMsg headers]  firstHeaderForKey:@"HttpmailUid"];
							
							if(UIDHeader) {
								[monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Updating message %d of %d '%@'", @""), j+1, messageCount, [libMsg subject]]];
								[monitor setItemMinValue: 0];
								[monitor setItemMaxValue: messageCount];
								[monitor setItemValue: j];
								[monitor updateDoneValue];
//								NSLog(@"setting remote ID to: %@", UIDHeader);
								[libMsg setRemoteID: UIDHeader];
								[libMsg commit];
								// [Library commit];
							}
						}
//						NSLog(@"message id = %@", UIDHeader);
#else					
                        id UIDHeader = [[(Message *)[messagesInBox objectAtIndex:j] headers] firstHeaderForKey:@"HttpmailUid"];
#endif						
                        if ( UIDHeader )
                            [downloadedUIDs addObject:UIDHeader];
                    }
                    
                    [pool release];
                }
            }
        
//NSLog(@"here 18");
        
            [monitor setStatusMessage: LocalizedString(@"Downloading data for Inbox...", @"")];
//NSLog(@"here 19");
            [self downloadFromFolder: @"inbox" intoStore: store using: mail excludeUids: downloadedUIDs];            
//NSLog(@"here 20");

            if([DPHTTPMailBundle downloadSentItems]) {
                MailboxUid* sentMessagesUid = [self sentMessagesMailboxUidCreateIfNeeded: YES];
                store = [MessageStore currentlyAvailableStoreForUid: sentMessagesUid];
                [monitor setStatusMessage: LocalizedString(@"Downloading data for Sent Items...", @"")];
                [self downloadFromFolder: @"sentitems" intoStore: store using: mail excludeUids: downloadedUIDs];
            }

            if([self shouldDownloadExtraFolders] && ![mail stopped] && ![monitor shouldCancel]) {
                int i, C;
                NSArray* folders = [mail otherFolders];
                
                C = [folders count];
                for(i=0; i<C && ![mail stopped] && ![monitor shouldCancel]; i++) {
                    NSString* folderName = [folders objectAtIndex: i];
                    [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Downloading data for %@...", @""), folderName]];
    
#ifdef TARGET_PANTHER
                    [MailAccount enableMailboxListingNotifications];
#endif
#ifdef TARGET_TIGER
					[MailAccount enableMailboxListingNotifications: YES];
#endif
#ifdef TARGET_LEOPARD
					[MailAccount _enableMailboxListingNotifications: YES];
#endif

#ifdef TARGET_LEOPARD
					NSString* folderUrl;
					if(putFoldersUnderInbox) {
						folderUrl = [NSString stringWithFormat: @"%@/%@", [[self primaryMailboxUid] URLString], [folderName stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding]];
					} else {
						folderUrl = [[[self rootMailboxUid] URLString] stringByAppendingString: [folderName stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding]];
					}
					MailboxUid* folderUid = [MailAccount mailboxUidForURL: folderUrl forceCreation: YES];
					
//					NSLog(@"folderUrl=%@ folderUid=%@", folderUrl, folderUid);
#else                    
                    MailboxUid* folderUid = [self mailboxUidFromName: folderName];
#endif
                    
                    if(folderUid==NULL) {
#ifdef TARGET_JAGUAR            
                        NSString* failed = NULL;
                        folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName reasonForFailure: &failed];
#else
#ifdef TARGET_PANTHER
                        if(putFoldersUnderInbox) {
                            folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName];
                        } else {
                            folderUid = [self createMailboxWithParent: [self primaryMailboxUid] name: folderName];
                        }
#else
#ifdef TARGET_TIGER
                        if(putFoldersUnderInbox) {
                            folderUid = [self createMailboxWithParent: [self primaryMailboxUid] name: folderName];
                        } else {
                            folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName];
                        }

						[LibraryStore createEmptyStoreIfNeededForPath: [folderUid fullPath] notIndexable: NO];
#else
#ifdef TARGET_LEOPARD
	// do nothing
#else
#error fix me
#endif
#endif            
#endif
#endif
                    }
                    
                    store = [MessageStore currentlyAvailableStoreForUid: folderUid];
                    if(store==NULL) {
                        store = [self storeForMailboxUid: folderUid];
                    }
                    [self downloadFromFolder: folderName intoStore: store using: mail excludeUids: downloadedUIDs];
                }
            }
        } else {
            if(![mail stopped]) {
                showAlert(self, nil, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"Could not connect to '%@'\n%@", @""), [self displayName], [mail responseString]]);
            }
        }

//        [NSException raise: @"test exception" format: @"testing the exception handler"];
        
    } @catch (NSException* e) {
		NSLog(@"%@", exceptionDescription(self,  @"oops", e));
		
        if(![mail stopped]) {
            showAlert(self, e, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while checking for new mail for '%@'\n%@", @""), [self displayName], e]);
        }
    }
    
    [connections removeObject: mail];
	
#ifdef DESCEND_FROM_IMAP_ACCOUNT
    [DPHTTPMailBundle unlock];
#endif
	[monitor markCompleted: YES];
    // tell the rest of the system we are finished now
    [self _backgroundFetchCompleted];
}

- (MailboxUid*) primaryMailboxUid {    
#ifdef DESCEND_FROM_IMAP_ACCOUNT
	if(_inboxMailboxUid)
		return _inboxMailboxUid;
#endif
		
#ifndef DESCEND_FROM_IMAP_ACCOUNT		
    // this is very naughty!

    // since I have been unable to figure out what calls to make to get Mail to create my primary MailboxUid object, I have resorted to
    // using the code in the IMAPAccount class since I know that works.  This is VERY nasty!
    
    // get the IMAPAccount implementation of primaryMailboxUid
    Method m = class_getInstanceMethod([IMAPAccount class], @selector(primaryMailboxUid));
    // now call it passing in this account as self!
    MailboxUid* result = m->method_imp(self, @selector(primaryMailboxUid));
#else
	MailboxUid* result = [super primaryMailboxUid];
	if([DPHTTPMailBundle foldersUnderInbox]) {
		[result setAttributes: 4];
	} else {
		[result setAttributes: 1];
	}	
#endif

#ifdef DESCEND_FROM_IMAP_ACCOUNT
	_inboxMailboxUid = result;

/*	
	if([MessageStore currentlyAvailableStoreForUid: result]==nil) {	
		HTTPMailLibraryStore* store;
		NSLog(@"%p - Creating store", self);
		[HTTPMailLibraryStore createEmptyStoreIfNeededForPath: [result fullPath] notIndexable: NO];
		
		store = [self storeForMailboxUid: result];
		[MessageStore registerAvailableStore: store];
		NSLog(@"store = %@", store);
	}
*/

#endif

#ifdef TARGET_JAGUAR
    NSString* path = [self path];
    if(path && !foundFolders) {
        NSFileManager* fm = [NSFileManager defaultManager];
        NSDirectoryEnumerator* enumerator = [fm enumeratorAtPath: path];
        NSString* file;
        
        while(file=[enumerator nextObject]) {
            if ([[file pathExtension] isEqualToString:@"mbox"]) {
                    NSString* folderName = [file stringByDeletingPathExtension];
                    MailboxUid* folderUid = [self mailboxUidFromName: folderName];
                    
                    if(folderUid==NULL) {
                        NSString* failed = NULL;
                        folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName reasonForFailure: &failed];
                    }
                    
                    [enumerator skipDescendents];
            }
        }
        
        foundFolders = YES;
    }
#endif

#ifdef TARGET_LEOPARD
	[self synchronizeMailboxListAfterImport];
#endif
	
    return result;
}

- (void)deleteMessagesFromMailboxUid:(MailboxUid*)mailbox olderThanNumberOfDays:(unsigned int)olderthan compact:(BOOL)shouldCompat {
    if(![DPHTTPMailBundle bundleFinishedInitialization])
        return;

    MailboxUid* trash = [self trashMailboxUidCreateIfNeeded: YES];
    
    if(trash) {
        MessageStore* store = [MessageStore currentlyAvailableStoreForUid: trash];
        if(store==NULL) {
            store = [self storeForMailboxUid: trash];
        }
        
        if(store) {
            if(![store isOpened]) {
#ifdef DESCEND_FROM_IMAP_ACCOUNT
				[store openSynchronously];
#else		
                [store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
#endif		
            }
            
            NSArray* messages = [[store copyOfAllMessages] autorelease];
            NSMutableArray* toDelete;
            NSMutableDictionary* folders = [NSMutableDictionary dictionary];
            int i, C;
            
            C = [messages count];
            if(C) {
                for(i=0; i<C; i++) {
                    Message* msg = [messages objectAtIndex: i];
                    MessageHeaders* headers = [msg headers];
                    NSString* uid = [headers firstHeaderForKey: @"HttpmailUid"];
                    NSString* folder = [headers firstHeaderForKey: @"HttpmailFolder"];
                    if(folder==NULL) {
                        folder= @"";
                    }
                    
                    if(uid) {
                        toDelete = [folders objectForKey: folder];
                        
                        if(toDelete==NULL) {
                            toDelete = [NSMutableArray array];
                            [folders setObject: toDelete forKey: folder];
                        }
                    
                        [toDelete addObject: msg];
                    }
                }
                
                [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Connecting to '%@'...", @""), [self displayName]]];
                
                if([folders count]) {
                    DPhttpmail* mail;
                    @try {
//                        mail = [[[DPhttpmail alloc] initWithMailAccount: self] autorelease];
                        mail = [DPhttpmail DPhttpmailWithMailAccount: self];
                        [connections addObject: mail];
                        
                        if(![mail isConnected]) {
                            [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Connecting to '%@'...", @""), [self displayName]]];
                            [mail login];
                        }
                        
                        if( [mail isConnected] && ![mail stopped] && ![monitor shouldCancel]) {
                            [monitor setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Removing messages from '%@'...", @""), [self displayName]]];
    
                            NSEnumerator *enumerator = [folders keyEnumerator];
                            NSString* folder;
                            
                            while ((folder = [enumerator nextObject])) {
                                NSMutableArray* uids = [NSMutableArray array];
                                toDelete = [folders objectForKey: folder];
                                NSURL* url;
                                
                                if([folder isEqualToString: @""]) {
                                    url = [mail inboxFolder];
                                } else {
                                    url = [mail URLForFolder: folder];
                                }
                                
                                
                                C = [toDelete count];
                                for(i=0; i<C; i++) {
                                    Message* msg = [toDelete objectAtIndex: i];
                                    MessageHeaders* headers = [msg headers];
                                    NSString* uid = [headers firstHeaderForKey: @"HttpmailUid"];
                                    
                                    if(uid) {
                                        [uids addObject: uid];
                                    }
                                }
                                
                                if([uids count]>0) {
                                    NSData* result = [mail removeMessageIDs: uids fromFolder: url];
                            
                                    if([mail responseCode]>299) {
                                        showAlert(self, nil, LocalizedString(@"Delete Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while removing a message from the server: %@\n%@", @""), [mail responseString], result]);
                                    } else {
                                        [store deleteMessages: toDelete moveToTrash: NO];
                                    }
                                }
                            }

    
                        } else {
                            if(![mail stopped]) {
                                showAlert(self, nil, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"Could not connect to '%@'\n%@", @""), [self displayName], [mail responseString]]);                    
                            }
                        }
                    } @catch (NSException* e) {
                        if(![mail stopped]) {
                            showAlert(self, e, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while removing deleted mail for '%@'\n%@", @""), [self displayName], e]);
                        }
                    }
                    [connections removeObject: mail];
                } else {
                            [store deleteMessages: messages moveToTrash: NO];
                }
            }
            
        }
    }
}

- (NSStringEncoding)transportEncoding {
    NSDictionary* dict = [self accountInfo];
    NSNumber* value = [dict objectForKey: @"transportEncoding"];
    if(value) {
        return [value intValue];
    } else {
        return NSWindowsCP1252StringEncoding; 
    }
}

- (void) setTransportEncoding:(NSStringEncoding)encoding {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: encoding] forKey: @"transportEncoding"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldMarkAsReadOnDownload {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"markAsReadOnDownload"];
    if(flag) {
        return [flag intValue];
    } else {
        return NO; 
    }
}

- (void) setShouldMarkAsReadOnDownload:(BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"markAsReadOnDownload"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldDeleteOnDownload {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"deleteOnDownload"];
    if(flag) {
        return [flag intValue];
    } else {
        return NO;
    }
}

- (void) setShouldDeleteOnDownload:(BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"deleteOnDownload"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldSaveSentMessages {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"saveSentMessages"];
    if(flag) {
        return [flag intValue];
    } else {
        return NO;
    }
}

- (void) setShouldSaveSentMessages: (BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"saveSentMessages"];
    [self setAccountInfo: dict];
}

- (NSString*) providerURL {
    NSDictionary* dict = [self accountInfo];
    NSString* providerURL = [dict objectForKey: @"providerURL"];
    
    if(providerURL==NULL) {
        providerURL = HTTPMAIL_URL;
    }
    
    return providerURL;
}

- (void) setProviderURL:(NSString*)url {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: url forKey: @"providerURL"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldCheckLocalAccounts {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"checkLocalAccounts"];
    if(flag) {
        return [flag intValue];
    } else {
        return YES;
    }
}

- (void) setShouldCheckLocalAccounts: (BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"checkLocalAccounts"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldDownloadExtraFolders {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"downloadExtraFolders"];
    if(flag) {
        return [flag intValue];
    } else {
        return YES;
    }
}

- (void) setShouldDownloadExtraFolders: (BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"downloadExtraFolders"];
    [self setAccountInfo: dict];
}

- (BOOL) shouldSynchronize {
    NSDictionary* dict = [self accountInfo];
    NSNumber* flag = [dict objectForKey: @"synchronize"];
    if(flag) {
        return [flag intValue];
    } else {
        return NO;
    }
}

- (void) setShouldSynchonize: (BOOL)flag {
    NSMutableDictionary* dict = [[self accountInfo] mutableCopy];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"synchronize"];
    [self setAccountInfo: dict];
}

- (DeliveryAccount*)deliveryAccount {
//        NSLog(@"deliveryAccounts = %@", [DeliveryAccount deliveryAccounts]);
        
        if([super deliveryAccount]==nil) {
            NSLog(@"Creating new delivery account");
            NSString* user = [self username];
            NSString* provider = [self providerURL];
            NSString* host;
            
            if(provider) {
                host = [[NSURL URLWithString: provider] host];
            } else {
                host = nil;
            }
            
            DeliveryAccount* da = [HTTPMailDeliveryAccount accountWithHostname: host username: user];
            
            if(da==nil) {
                da = [HTTPMailDeliveryAccount newWithAccount: self];
                [DeliveryAccount addDeliveryAccount: da];
            }
            [self setDeliveryAccount: da];
        }
        
        return [super deliveryAccount];
}

- (void) addFailureMessage:(NSString*)subject withBody:(NSData*) body intoMessageStore: (MessageStore*)store {
	NSString* text = [NSString stringWithFormat: @"From: httpmail plugin<danielparnell@hotmail.com>\nSubject: %@\nContent-Type: text/html\n\n<font color=\"red\">This is an automatically generated failure message created by the HTTPMail Plugin</font><p>Plugin Version: %@</p>", subject, [DPHTTPMailBundle bundleVersionString]];
	NSMutableData* messageData = [NSMutableData data];
	const char* data = [text cStringUsingEncoding: NSUTF8StringEncoding];
	
	[messageData appendBytes: data length: strlen(data)];
	[messageData appendData: body];
	
	[messageData convertNetworkLineEndingsToUnix];

	if(store==NULL) {
		MailboxUid* trashUid = [self trashMailboxUidCreateIfNeeded: NO];
		store = [MessageStore currentlyAvailableStoreForUid: trashUid];
		if(store==NULL) {
			store = [self storeForMailboxUid: trashUid];
		}
	}

#ifndef DESCEND_FROM_IMAP_ACCOUNT
	NSArray* toAdd;
	NSMutableArray* failed = [NSMutableArray array];
		
	if(![store isOpened]) {
		[store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
	}
	
	NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: messageData] autorelease];
	Message* msg = [[TOCMessage alloc] initWithMessage: [Message messageWithRFC822Data: messageData]];
	[msg setMessageStore: tmpStore];
		
	[msg setMessageFlags: 0x00000080];  // unread message
	
	toAdd = [NSArray arrayWithObject: msg];
	
	[store appendMessages: toAdd unsuccessfulOnes: failed];
	
	NSLog(@"failed = %@", failed);
#else
	[self addMessage: messageData toStore: store withFlags: 0x080];
#endif
		
//	NSLog(@"Failure Message: %@\n%@", subject, [NSString stringWithCString: [body bytes] length: [body length]]);
}

#ifdef DESCEND_FROM_IMAP_ACCOUNT
- (LibraryMessage*) addMessage:(NSData*)message toMailbox: (MailboxUid*) mailbox withFlags: (int) flags {
//	NSLog(@"Adding message: %@", message);
//	NSLog(@"mailbox url = %@", [mailbox URLString]);
	int i, C;

	LibraryIMAPStore* store = [self storeForMailboxUid: mailbox];
	
	if(store==nil) {
//		NSLog(@"looking for mailbox");
		NSArray* stores = [MessageStore currentlyAvailableStoresForAccount: self];
		NSString* mailboxUrl = [mailbox URLString];
//		NSLog(@"stores = %@", stores);
//		NSLog(@"mailboxUrl = %@", mailboxUrl);
		C = [stores count];
		for(i=0; i<C; i++) {
			LibraryIMAPStore* tmp = [stores objectAtIndex: i];
//			NSLog(@" url = %@", [[tmp mailboxUid] URLString]);
			
			if([[[tmp mailboxUid] URLString] isEqualToString: mailboxUrl]) {
//				NSLog(@"found mailbox: %@", tmp);
				store = tmp;
				break;
			}
		}
		
	//	LibraryIMAPStore* store = [MessageStore currentlyAvailableStoreForUid: mailbox];
		if(store==nil) {	
//			NSLog(@"calling createEmptyStoreIfNeededForPath");
			[LibraryIMAPStore createEmptyStoreIfNeededForPath: [mailbox fullPath] notIndexable: NO];
//			NSLog(@"creating store");
			store = [[[LibraryIMAPStore alloc] initWithMailboxUid: mailbox readOnly: NO] autorelease];
	//		id x = [MessageStore registerAvailableStore: store];
	//		NSLog(@"*** x = %@", x);
	//		store = [LibraryStore storeWithMailbox: mailbox];
		} else {
//			NSLog(@"found existing store");
		}
	} else {
//		NSLog(@"got existing store");
	}
	
	return [self addMessage: message toStore: store withFlags: flags];
}

- (LibraryMessage*) addMessage:(NSData*)message toStore: (MessageStore*) store withFlags: (int) flags {
//	NSLog(@"store = %@", store);
	if(![store isOpened]) {
//		NSLog(@"calling [Library setupLibrary]");
//		[Library setupLibrary];
		
//		NSLog(@"opening store");
		[store openSynchronouslyUpdatingMetadata: NO];
//		NSLog(@"store is open");
	}
	
	NSMutableData* data = [NSMutableData dataWithData: message];
	[data convertNetworkLineEndingsToUnix];
	
	NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: data] autorelease];
	Message* msg = [tmpStore message];
		
//	NSLog(@"msg = %@", msg);
//	NSLog(@"subject = %@", [msg subject]);
	NSString* urlString;
	if([store isKindOfClass: [LibraryIMAPStore class]]) {
		urlString = [(LibraryIMAPStore*)store  URLString];
	} else {
		urlString = [[store mailboxUid] URLString];
	}

//	NSLog(@"urlString = %@", urlString);
	NSArray* added = [Library addMessages: [NSArray arrayWithObject: msg] withMailbox: urlString fetchBodies: NO isInitialImport: NO oldMessagesByNewMessage: nil];
//	NSArray* added = [Library addMessages: [NSArray arrayWithObject: msg] withMailbox: urlString];	
//	NSArray* added = [Library insertOrUpdateMessages: [NSArray arrayWithObject: msg] withMailbox: urlString fetchBodies: NO isInitialImport: NO oldMessagesByNewMessage: nil remoteIDs: nil newDocumentIDs: nil setFlags: 0 clearFlags: 0 messageFlagsForMessages: nil copyFiles: YES progressDelegate: nil updateRowIDs: nil];


//	NSLog(@"added = %@", added);

	int i,C;
	C = [added count];
	for(i=0; i<C; i++) {
		LibraryMessage* libMsg = [added objectAtIndex: i];
		
//		NSLog(@"[%@ commit]", libMsg);
		[libMsg commit];
	}
	
//	NSLog(@"[Library commit]");
	[Library commit];
	
//	NSLog(@"xxxx");
	
	if(C>0) {
		return [added objectAtIndex: 0];
	} else {
		return nil;
	}
}

- (BOOL)_usesMailboxCache {
//	NSLog(@"_usesMailboxCache called");
	return NO;
}

/*
- (id)_URLForInfo:(id)fp8 {
	id result = [super _URLForInfo: fp8];
	NSLog(@"_URLForInfo: %@ = %@", fp8, result);
	
	return result;
}
*/
#endif

- (void)nowWouldBeAGoodTimeToTerminate:fp12 {
    int i;
    int C = [connections count];
    DPhttpmail* mail;
    
    QuittingTime = YES;
    
    for(i=0; i<C; i++) {
        mail = [connections objectAtIndex: i];
        
        [mail stop];
    }
        
/*    
	NSLog(@"getting stores for account: %@", self);
	NSArray* stores = [MessageStore currentlyAvailableStoresForAccount: self];
	C = [stores count];
	for(i=0; i<C; i++) {
		MessageStore* store = [stores objectAtIndex: i];
		NSLog(@"removing store from cache: %@", store);
		[MessageStore removeStoreFromCache: store];
	}
*/	
    [NSApp removeTerminationHandler: self];
}

#ifdef TARGET_LEOPARD

- (BOOL)isValidAccountWithError:(id)fp8 accountBeingEdited:(id)fp12 userCanOverride:(char *)fp16 {
	return YES;
}

- (NSString*) separatorChar {
	return @"/";
}

- (id) _gatewayForMailboxUid:(MailboxUid*)mailbox name:(NSString*)name options:(int) options {
	return nil;
}

- (void)_synchronizeAccountWithServerWithUserInput:(id)fp8 {
	// do nothing
}

#endif

@end

