//
//  DPAsyncHttpMailAccount.m
//  httpmail
//
//  Created by Daniel Parnell on Sun May 11 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <objc/objc-class.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import "DPAsyncHttpMailAccount.h"
#import "Localization.h"
#import "httpmail_constants.h"
#import "DPKeychain.h"
#import "mail-app.h"
#import "httpmailBundle.h"

//#import "DPProxy.h"

#define STATE_IDLE 		0
#define	STATE_LOGIN		1
#define STATE_MESSAGES		2
#define STATE_MESSAGE		3
#define STATE_MARKING_READ	4
#define STATE_DELETE_MESSAGE	5
#define STATE_DELETE_LOGIN	6
#define STATE_DELETE_MESSAGES	7

@implementation DPAsyncHttpMail(HTTPMailAccountStuff)

+ (DPAsyncHttpMail*)newWithMailAccount: (DPAsyncHttpMailAccount*)account {
    DPAsyncHttpMail* result = [DPAsyncHttpMail alloc];
    if(result) {
        result = [result initWithMailAccount: account];
    }
    
    return [result autorelease];
}

- initWithMailAccount: (DPAsyncHttpMailAccount*)account {
    self = [self init];
    
    if(self) {
        NSString* password;
        
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
    }
    
    return self;
}

@end

@interface DPAsyncHttpMailAccount (Private)

- (void) startDownloadingNextMessage: (DPAsyncHttpMail*)mail;
- (void) handleMessageDownloaded: (DPAsyncHttpMail*)mail;
- (void) downloadNextFolder: (DPAsyncHttpMail*)mail;
- (void) downloadNextMessage: (DPAsyncHttpMail*)mail;
- (void) handleSuccessfulLogin: (DPAsyncHttpMail*)mail;
- (void) deleteMessagesForNextFolder: (DPAsyncHttpMail*)mail;
- (BOOL) isConnectionPossible;

@end

@implementation DPAsyncHttpMailAccount

+ (id) DPAsyncHttpMailAccount {
    return [DPAsyncHttpMailAccount new];
}

+ (NSString*) accountTypeString {
    return @"AsycnHTTPMail";
}

/*
- (BOOL)respondsToSelector:(SEL)aSelector {
    BOOL result = [super respondsToSelector: aSelector];
    
    NSLog(@"%p respondsToSelector: %s -> %d", self, aSelector, result);
    
    return result;
}

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    NSLog(@"DPAsyncHttpMailAccount doesNotRecognizeSelector: %s", aSelector);
}
*/

- (id) init {
    self = [super init];
    
    if(self) {	
        [NSApp addTerminationHandler: self];
        
        delivery = NULL;
        [self setIsActive: YES];
        [self setShouldMoveDeletedMessagesToTrash: YES];
    }
    
//    return [DPProxy newWithTarget: self];
    return self;
}

- (void)dealloc {    
    [NSApp removeTerminationHandler: self];
    
    [delivery release];
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

/*
- (BOOL)canCreateNewMailboxes {
    return NO;
}

- (BOOL)canMailboxBeRenamed:fp12 {
    return NO;
}

- (char)canMailboxBeDeleted:fp12 {
    return NO;
}
*/

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
    return @"asycnhttpmail";
}

- (NSString*)secureServiceName {
    return @"asynchttpmail";
}

- (NSString*)saslProfileName {
    return @"asynchttpmail";
}

- (Class)storeClass {
    return [NeXTMbox class];
}

- (Class)connectionClass {
//    return [HTTPMailConnection class];
    return nil;
}

- (NSString*)mailboxPathExtension {
    return @"mbox";
}

- (BOOL)requiresAuthentication {
    return NO;
}

- (BOOL)canGoOffline {
    return YES;
}

- (MailboxUid*) primaryMailboxUid {
    // get the IMAPAccount implementation of primaryMailboxUid
    Method m = class_getInstanceMethod([IMAPAccount class], @selector(primaryMailboxUid));
    // now call it!
    return m->method_imp(self, @selector(primaryMailboxUid));
}

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

static void showAlert(id object, NSException* exception, NSString* title, NSString* message) {
#ifdef TARGET_JAGUAR
    [NSApp alertUserWithMessage: message title: title];
#endif
#ifdef TARGET_PANTHER
    NSError* error;
    
    if(exception) {
        error = [MFError errorWithException: exception];
    } else {
        error = [MFError errorWithDomain: @"HTTPMailErrors" code: 1 localizedDescription: message title: title helpTag: nil userInfo: nil];
    }
  
    [NSApp informUserOfError: error];
#endif
}

- (void) downloadFromFolder: (NSString*)folder intoStore:(MessageStore*)store using:(DPAsyncHttpMail*)mail {
    destFolder = [folder retain];
    destStore = [store retain];
    state = STATE_MESSAGES;
    [mail messagesForFolder: folder];
}

- (BOOL) isConnectionPossible {
    NSDictionary* settings = (NSDictionary*)SCDynamicStoreCopyProxies(NULL);
    NSNumber* proxyEnabled = [settings objectForKey: @"HTTPEnable"];
    NSString* proxy = [settings objectForKey: @"HTTPProxy"];
    NSString* host;
    if(proxy && [proxyEnabled intValue]) {
        host = proxy;
    } else {
        host = [[NSURL URLWithString: [self providerURL]] host];
    }
     
    NetworkController* nc = [NetworkController sharedInstance];
    if(![nc isNetworkUp] || ![nc isHostReachable: host]) {        
        return NO;
    }

    return YES;
}


- (void) fetchSynchronously {    
    if(![self isConnectionPossible]) {
        NSLog(@"can't get to httpmail server so we won't bother trying");

        // tell the rest of the system we are finished now
        [self _backgroundFetchCompleted];
        
        return;
    }
            
    NS_DURING
        DPAsyncHttpMail* mail = [DPAsyncHttpMail newWithMailAccount: self];
        [mail setDelegate: self];
        
        [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Connecting to '%@'...", @""), [self displayName]]];
        
        finished = NO;
        stop = NO;
        state = STATE_LOGIN;
        [mail login];

        while(!finished && [NSApp isRunning]) {
            [[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow: 0.1]];
            
            if(stop) {
                finished = YES;
            }
        }
        
        [mail setDelegate: nil];
        [mail close];
    NS_HANDLER
        showAlert(self, localException, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while checking for new mail for '%@'\n%@", @""), [self displayName], localException]);
        // tell the rest of the system we are finished now
    NS_ENDHANDLER   
        
    [self _backgroundFetchCompleted];
}

- (void)deleteMessagesFromMailboxUid:(MailboxUid*)mailbox olderThanNumberOfDays:(unsigned int)olderthan compact:(BOOL)shouldCompat {
#ifdef TARGET_PANTHER
    if(![httpmailBundle bundleFinishedInitialization]) {
        return;
    }
#endif

    if(![self isConnectionPossible]) {
        NSLog(@"can't get to httpmail server so we won't bother trying to delete things");
        
        return;
    }

    MailboxUid* trash = [self trashMailboxUidCreateIfNeeded: NO];
    
    if(trash) {
        MessageStore* store = [self storeForMailboxUid: trash];
        
        if(store) {
            if(![store isOpened]) {
                [store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
            }
            
            NSArray* messages = [store copyOfAllMessages];
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
                                
                if([folders count]) {
                    NS_DURING
                        DPAsyncHttpMail* mail = [DPAsyncHttpMail newWithMailAccount: self];
                        [mail setDelegate: self];
                        
                        [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Connecting to '%@'...", @""), [self displayName]]];
                        
                        finished = NO;
                        stop = NO;
                        index = 0;
                        
                        dictionaryToProcess = folders;
                        toProcessEnumerator = [folders keyEnumerator];
                        state = STATE_DELETE_LOGIN;
                        [mail login];
                
                        while(!finished && [NSApp isRunning]) {
                            [[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow: 0.1]];
                            
                            if(stop) {
                                finished = YES;
                            }
                        }
                                                
                        [mail setDelegate: nil];
                        [mail close];
                    NS_HANDLER
                        showAlert(self, localException, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while removing deleted mail for '%@'\n%@", @""), [self displayName], localException]);                
                    NS_ENDHANDLER
                    
                    dictionaryToProcess = nil;
                    toProcessEnumerator = nil;
/*                    
                        DPhttpmail* mail = [[DPAsyncHttpMail newWithMailAccount: self] autorelease];
                        if([mail login]) {
                            [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Removing messages from '%@'...", @""), [self displayName]]];
    
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
                                    
                                    [uids addObject: uid];
                                }
                                
                                NSData* result = [mail removeMessageIDs: uids fromFolder: url];
                        
                                if([mail responseCode]>299) {
                                    [self addFailureMessage: LocalizedString(@"Failure Details", @"") withBody: result intoMessageStore: store];
                                    showAlert(LocalizedString(@"Delete Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while removing a message from the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
                                } else {
                                    [store deleteMessages: toDelete moveToTrash: NO];
                                }
                            }

    
                        } else {
                            showAlert(LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"Could not connect to '%@'\n%@", @""), [self displayName], [mail responseString]]);                    
                        }
*/            
                } else {
                            [store deleteMessages: messages moveToTrash: NO];
                }
            }
        }
    }
}

/*
- (BOOL)_setPath:(NSString*)path {
    BOOL result = [super _setPath: path];
    
    if(path) {    
        [MailAccount enableMailboxListingNotifications];
        
        NSFileManager* fm = [NSFileManager defaultManager];
        if(![fm fileExistsAtPath: path]) {
//            NSLog(@"creating directory '%@'", path);
//            [fm createDirectoryAtPath: path attributes: nil];

//            [MessageStore createEmptyStoreIfNeededForPath: path];
            
//            _rootMailboxUid = [MailAccount mailboxUidForFileSystemPath: path create: YES];
//            NSLog(@"_rootMailboxUid = %@", _rootMailboxUid);
 
//         NSLog(@"allMailboxUids = %@", [MailAccount allMailboxUids]);

//            _rootMailboxUid = [[[MailboxUid alloc] initWithAccount: self] retain];
//            [_rootMailboxUid setType: 7]; // it is a root mailbox
//            [_rootMailboxUid setParent: [[MailboxUid specialMailboxUids] objectAtIndex: 0]];
            
//            NSLog(@"_rootMailboxUid = %@", _rootMailboxUid);
            
//            id x = [MailAccount createAccountWithDictionary: path];
//            NSLog(@"%@", x);
            
//            NSLog(@"%@", [MailAccount mailAccounts]);
//            [self resetSpecialMailboxes];
//            id root = [self _specialMailboxUidWithType:7 create: YES];
//            id root = [self rootMailboxUid];
//            MailboxUid* root = [self mailboxUidForRelativePath: @"" create: YES];
//            [self _synchronizeMailboxListWithFileSystem];
//            MailboxUid* root = [MailAccount mailboxUidForFileSystemPath: path create: YES];
//            MailboxUid* root = [self _specialMailboxUidWithType: 7 create: YES];

//            NSString* failed = NULL;
//            MailboxUid* root = [self createMailboxWithParent: nil name: @"root" reasonForFailure: &failed];

//            NSLog(@"root = %@", root);
//            NSLog(@"failed = %@", failed);

//            NSLog(@"root = %@ %d", [self rootMailboxUid], [(MailboxUid*)[self rootMailboxUid] type]);
        }
  
        NSLog(@"_setPath root = %@", [self rootMailboxUid]);
        // make sure the special mail boxes are created
        [self primaryMailboxUid];
        [self trashMailboxUidCreateIfNeeded: YES];
        [self junkMailboxUidCreateIfNeeded: YES];        

        NSString *file;
        NSDirectoryEnumerator *enumerator = [fm enumeratorAtPath: path];
        while (file = [enumerator nextObject]) {
            BOOL isDir = NO;
            
            file = [path stringByAppendingPathComponent: file];
            [fm fileExistsAtPath: file isDirectory: &isDir];

            // make sure that all the mailboxes are loaded
            if(isDir) {
                NSString* name = [[[file lastPathComponent] pathComponents] objectAtIndex: 0];
                
                [self mailboxUidForRelativePath: name create: YES];
            }
        }        

        
//        [MailAccount disableMailboxListingNotifications];
//        NSLog(@"%@ %@", path, [[self primaryMailboxUid] fullPath]);
    }
  
    return result;
//    return [super _setPath: path];
}
*/

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
    NSMutableDictionary* dict = [self accountInfo];
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
    NSMutableDictionary* dict = [self accountInfo];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"deleteOnDownload"];
    [self setAccountInfo: dict];
}

- (NSString*) providerURL {
//    return @"http://localhost/~daniel/";
    NSDictionary* dict = [self accountInfo];
    NSString* providerURL = [dict objectForKey: @"providerURL"];
    if(providerURL==NULL) {
        providerURL = HTTPMAIL_URL;
    }
    
    return providerURL;
}

- (void) setProviderURL:(NSString*)url {
    NSMutableDictionary* dict = [self accountInfo];
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
    NSMutableDictionary* dict = [self accountInfo];
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
    NSMutableDictionary* dict = [self accountInfo];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"downloadExtraFolders"];
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
    NSMutableDictionary* dict = [self accountInfo];
    [dict setObject: [NSNumber numberWithInt: flag] forKey: @"saveSentMessages"];
    [self setAccountInfo: dict];
}


- (DeliveryAccount*)deliveryAccount {    

/*
    if(delivery==NULL) {
        delivery = [[HTTPMailDeliveryAccount newWithAccount: self] retain];
        [delivery setHostname: @"hotmail.com"];
                
        [self setDeliveryAccount: delivery];        
    }
*/
       
    return delivery;
}

- (void) addFailureMessage:(NSString*)subject withBody:(NSData*) body intoMessageStore: (MessageStore*)store {
    NSMutableData* messageData = [NSMutableData data];
    NSArray* toAdd;
    NSMutableArray* failed = [NSMutableArray array];
    NSString* text = [NSString stringWithFormat: @"From: httpmail plugin<danielparnell@hotmail.com>\nSubject: %@\nContent-Type: text/html\n\n", subject];
    const char* bytes = [text UTF8String];
    
    if(![store isOpened]) {
        [store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
    }
    
    [messageData appendBytes: bytes length: strlen(bytes)];
    [messageData appendData: body];
    
    [messageData convertNetworkLineEndingsToUnix];
    NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: messageData] autorelease];
    Message* msg = [[TOCMessage alloc] initWithMessage: [Message messageWithRFC822Data: messageData]];
    [msg setMessageStore: tmpStore];
        
    [msg setMessageFlags: 0x00000080];  // unread message
    
    toAdd = [NSArray arrayWithObject: msg];
    
    [store appendMessages: toAdd unsuccessfulOnes: failed];

}

- (void) startDownloadingNextMessage:(DPAsyncHttpMail*)mail {
    unsigned int C = [toDownload count];
    if(index<C) {
        DPhttpmailMessage* m = [toDownload objectAtIndex: index];                
//        NSString* uid = [m uniqueID];
            
        [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Fetching message %d of %d", @""), index+1, C]];
/*    
        if(!hasNewMail) {                        
            [self newMailHasBeenReceived];
            hasNewMail = YES;
        }
*/    
        state = STATE_MESSAGE;
        [mail get: [m url]];
    } else {
        [toDownload release];
        toDownload = nil;
        [self downloadNextFolder: mail];
    }
}

- (void) handleMessageDownloaded: (DPAsyncHttpMail*)mail {
    NSMutableArray* toAdd = [NSMutableArray array];
    NSMutableArray* failed = [NSMutableArray array];
    BOOL markAsRead = [self shouldMarkAsReadOnDownload];
    BOOL deleteThem = [self shouldDeleteOnDownload];
    DPhttpmailMessage* m = [toDownload objectAtIndex: index]; 
    NSString* uid = [m uniqueID];

    NSMutableData* data = [NSMutableData dataWithData: [mail responseData]];
    [data convertNetworkLineEndingsToUnix];
    NSMutableData* messageData;

    NSRange bodyRange = [self findBodyForData: data];

    NSString* uidHeader = [NSString stringWithFormat: @"HttpmailUid: %@\nHttpmailFolder: %@\n", uid, [m folder]];

    messageData = [NSMutableData data];
    
    if(bodyRange.location!=NSNotFound) {
        [messageData appendData: [data subdataWithRange:NSMakeRange(0, bodyRange.location)]];
    } else {
        [messageData appendData: data];
    }
    
    [messageData appendBytes: [uidHeader cString] length: [uidHeader length]];
    
    if(bodyRange.location!=NSNotFound) {
        [messageData appendData: [data subdataWithRange: bodyRange]];
    } else {
        NSString* emptyBody = @"\r\n\r\n";
        
        [messageData appendBytes: [emptyBody cString] length: [emptyBody length]];
        [messageData convertNetworkLineEndingsToUnix];
    }
    
    
    NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: messageData] autorelease];
    Message* msg = [[TOCMessage alloc] initWithMessage: [Message messageWithRFC822Data: messageData]];
    [msg setMessageStore: tmpStore];
    
    id messageID = [msg messageID];
    
    if([m read]) {
        [msg setMessageFlags: 0x00000081];  // read message that needs to be processed by the junk mail filter
    } else {
        [msg setMessageFlags: 0x00000080];  // unread message that needs to be processed by the junk mail filter
    }
    
    [toAdd removeAllObjects];
    [toAdd addObject: msg];
    
    [destStore appendMessages: toAdd unsuccessfulOnes: failed];
    
    Message* addedMsg = [destStore messageForMessageID: messageID];
    
    if(addedMsg) {
        NSArray* toRoute = [NSArray arrayWithObject: addedMsg];
        [destStore routeMessages: toRoute];
    }

    if(markAsRead && ![m read]) {
        NSLog(@"markAsRead");
        state = STATE_MARKING_READ;
        
        [mail markAsRead: m];
    } else {
        if(deleteThem) {
            NSLog(@"deleteThem");
            state = STATE_DELETE_MESSAGE;
            [mail remove: [NSArray arrayWithObject: m] fromFolder: [mail URLForFolder: [m folder]]];
        } else {
            [self downloadNextMessage: mail];
        }
    }
}

- (void) downloadNextFolder: (DPAsyncHttpMail*)mail {

    if([foldersToDownload count]) {
        NSString* folderName = [[foldersToDownload objectAtIndex: 0] retain];
        [foldersToDownload removeObjectAtIndex: 0];
        NSLog(@"downloading folder '%@'", folderName);
        
        [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Downloading data for %@...", @""), folderName]];

        [MailAccount enableMailboxListingNotifications];
        MailboxUid* folderUid = [self mailboxUidForRelativePath: folderName create: NO];
        if(folderUid==NULL) {
#ifdef TARGET_JAGUAR            
            NSString* failed = NULL;
            folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName reasonForFailure: &failed];
#else
#ifdef TARGET_PANTHER
            folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName];
#else
#error fix me
#endif
#endif            
        }
        
        [folderName release];
        
        MessageStore* store = [self storeForMailboxUid: folderUid];
        [self downloadFromFolder: folderName intoStore: store using: mail];
    } else {
        finished = YES;
    
        [foldersToDownload release];
    }
}

- (void) downloadNextMessage: (DPAsyncHttpMail*)mail {
    if(index<[toDownload count]) {
        NSLog(@"downloading message: %d", index);
        index++;
        [self startDownloadingNextMessage: mail];
    } else {
        NSLog(@"no more messages");
        [toDownload release];
        toDownload = nil;
        [self downloadNextFolder: mail];        
    }
}

- (void)handleSuccessfulLogin: (DPAsyncHttpMail*)mail {
    downloadedUIDs = [[NSMutableArray array] retain];
    
    NSArray* mailboxUids = [MailAccount allMailboxUids]; 
    int L = [mailboxUids count];
    int i,j;
    BOOL checkOthers = [self shouldCheckLocalAccounts];
    
    for ( i = 0; i<L; i++ )
    {
        MailboxUid* mbox = [mailboxUids objectAtIndex: i];
        MailAccount* account = [mbox account];
        NSArray                *messagesInBox;
        int            messageCount;

        // only look in this account and local accounts
        if((account==self)||(checkOthers && [account isKindOfClass: [LocalAccount class]]))
        {
            NSAutoreleasePool* pool = [NSAutoreleasePool new];
            
            MessageStore* s = [account storeForMailboxUid: mbox];
            if(![s isOpened]) {
                [s openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
            }
            
            messagesInBox = [s copyOfAllMessages];
            messageCount = [messagesInBox count];
            for ( j = 0; j<messageCount; j++ )
            {
                id UIDHeader = [[(Message *)[messagesInBox objectAtIndex:j] headers] firstHeaderForKey:@"HttpmailUid"];
                if ( UIDHeader )
                    [downloadedUIDs addObject:UIDHeader];
            }
            
            [pool release];
        }
    }

    [[ActivityMonitor currentMonitor] setStatusMessage: LocalizedString(@"Downloading data for Inbox...", @"")];

    MailboxUid* mb = [self primaryMailboxUid];
    MessageStore* store = [self storeForMailboxUid: mb];
    
    if(![store isOpened]) {
        [store openSynchronouslyUpdatingIndex:NO andOtherMetadata:NO];
    }

    if([self shouldDownloadExtraFolders]) {
        NSArray* folders = [mail otherFolders];
        
        foldersToDownload = [[NSMutableArray arrayWithArray: folders] retain];
    }

    [self downloadFromFolder: @"inbox" intoStore: store using: mail];
}

- (void) deleteMessagesForNextFolder: (DPAsyncHttpMail*)mail {
    NSString* folder;
    int i, C;
    
    NSLog(@"deleteMessagesForNextFolder");
    
    if ((folder = [toProcessEnumerator nextObject])) {
        NSMutableArray* uids = [NSMutableArray array];
        NSArray* toDelete = [dictionaryToProcess objectForKey: folder];
        NSURL* url;
        
        if([folder isEqualToString: @""]) {
            url = [mail inboxFolder];
        } else {
            url = [mail URLForFolder: folder];
        }
        
        NSLog(@"delete messages from folder '%@'", folder);
        
        C = [toDelete count];
        for(i=0; i<C; i++) {
            Message* msg = [toDelete objectAtIndex: i];
            MessageHeaders* headers = [msg headers];
            NSString* uid = [headers firstHeaderForKey: @"HttpmailUid"];
            
            [uids addObject: uid];
        }
  
        messagesToProcess = [toDelete retain];
        state = STATE_DELETE_MESSAGES;      
        [mail removeMessageIDs: uids fromFolder: url];
    } else {
        NSLog(@"no more folders");
        finished = YES;
    }
}

// DPAsyncHttpMail delegate methods

- (void) loginSuccessful: (DPAsyncHttpMail*)mail {
    NSLog(@"loginSuccessful");
    switch(state) {
        case STATE_LOGIN:
            NSLog(@"normal login");
            [self handleSuccessfulLogin: mail];
            break;
            
        case STATE_DELETE_LOGIN:
            NSLog(@"delete login");
            [self deleteMessagesForNextFolder: mail];        
            break;
    }
    
}

- (void) loginFailed: (DPAsyncHttpMail*)mail {
    NSLog(@"login failed");
    finished = YES;
    showAlert(self, nil, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"Could not connect to '%@'\n%@", @""), [self displayName], [mail responseString]]);
}

- (void) messagesFetched: (NSArray*)messages forMail: (DPAsyncHttpMail*)mail {

    int i, j, C, C2;
    BOOL found;
    
    NSLog(@"messagesFetched: %@", messages);
    
    NSString* uid;
    DPhttpmailMessage* m;                
    toDownload = [[NSMutableArray array] retain];
        
    C2 = [downloadedUIDs count];
    C = [messages count];
    for(i=0; i<C; i++) {
        m = [messages objectAtIndex: i];                
        uid = [m uniqueID];
  
        found = NO;
        for(j=0; j<C2; j++) {
            if([uid isEqualToString: [downloadedUIDs objectAtIndex: j]]) {
                found = TRUE;
                break;
            }
        }

        if(!found) {
            [toDownload addObject: m];
        }
    }
    
    state = STATE_MESSAGE;
    index = 0;
    [self startDownloadingNextMessage: mail];
/*
    C = [toDownload count];
    for(i=0; i<C; i++) {
        m = [toDownload objectAtIndex: i];                
        uid = [m uniqueID];
            
        [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Fetching message %d of %d", @""), i+1, C]];

        if(!hasNewMail) {                        
            [self newMailHasBeenReceived];
            hasNewMail = YES;
        }
    
        NSMutableData* data = [NSMutableData dataWithData: [mail get: [m url]]];
        [data convertNetworkLineEndingsToUnix];
        NSMutableData* messageData;

        NSRange bodyRange = [self findBodyForData: data];

        NSString* uidHeader = [NSString stringWithFormat: @"HttpmailUid: %@\nHttpmailFolder: %@\n", uid, [m folder]];
    
        messageData = [NSMutableData data];
        
        if(bodyRange.location!=NSNotFound) {
            [messageData appendData: [data subdataWithRange:NSMakeRange(0, bodyRange.location)]];
        } else {
            [messageData appendData: data];
        }
        
        [messageData appendBytes: [uidHeader cString] length: [uidHeader length]];
        
        if(bodyRange.location!=NSNotFound) {
            [messageData appendData: [data subdataWithRange: bodyRange]];
        } else {
            NSString* emptyBody = @"\r\n\r\n";
            
            [messageData appendBytes: [emptyBody cString] length: [emptyBody length]];
            [messageData convertNetworkLineEndingsToUnix];
        }
        
        
        NSDataMessageStore* tmpStore = [[[NSDataMessageStore alloc] initWithData: messageData] autorelease];
        Message* msg = [TOCMessage TOCMessageFromMessage: [Message messageWithRFC822Data: messageData]];
        [msg setMessageStore: tmpStore];
        
        id messageID = [msg messageID];
        
        if([m read]) {
            [msg setMessageFlags: 0x00000081];  // read message that needs to be processed by the junk mail filter
        } else {
            [msg setMessageFlags: 0x00000080];  // unread message that needs to be processed by the junk mail filter
        }
        
        [toAdd removeAllObjects];
        [toAdd addObject: msg];
        
        [destStore appendMessages: toAdd unsuccessfulOnes: failed];
        
        Message* addedMsg = [destStore messageForMessageID: messageID];
        
        if(addedMsg) {
            NSArray* toRoute = [NSArray arrayWithObject: addedMsg];
            [destStore routeMessages: toRoute];
        }
        
        if(markAsRead && ![m read]) {
            [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Marking message %@ as read", @""), [NSString stringWithFormat: @"%d", i+1]]];
            result = [mail markAsRead: m];
            
            if([mail responseCode]>299) {
                MessageStore* trash = [self storeForMailboxUid: [self trashMailboxUidCreateIfNeeded: NO]];
            
                [self addFailureMessage: LocalizedString(@"Failure Details", @"") withBody: result intoMessageStore: trash];
                showAlert(LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while marking a message as read on the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
            }
            
        } else if(deleteThem) {
            [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Removing message %@", @""), [NSString stringWithFormat: @"%d", i+1]]];
            NSArray* toDelete = [NSArray arrayWithObject: m];
            
            result = [mail remove: toDelete fromFolder: [mail inboxFolder]];
            
            if([mail responseCode]>299) {
                MessageStore* trash = [self storeForMailboxUid: [self trashMailboxUidCreateIfNeeded: NO]];

                [self addFailureMessage: LocalizedString(@"Failure Details", @"") withBody: result intoMessageStore: trash];
                showAlert(LocalizedString(@"Download Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while removing a message from the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
            }
        }
        if(![NSApp isRunning] || [[ActivityMonitor currentMonitor] shouldCancel]) break;
    }
*/

/*
    if([self shouldDownloadExtraFolders]) {
        int i, C;
        NSArray* folders = [mail otherFolders];
        
        C = [folders count];
        for(i=0; i<C; i++) {
            NSString* folderName = [folders objectAtIndex: i];
            [[ActivityMonitor currentMonitor] setStatusMessage: [NSString stringWithFormat: LocalizedString(@"Downloading data for %@...", @""), folderName]];

            [MailAccount enableMailboxListingNotifications];
            MailboxUid* folderUid = [self mailboxUidForRelativePath: folderName create: NO];
            if(folderUid==NULL) {
                NSString* failed = NULL;
                folderUid = [self createMailboxWithParent: [self rootMailboxUid] name: folderName reasonForFailure: &failed];
            }
            
            store = [self storeForMailboxUid: folderUid];
            [self downloadFromFolder: folderName intoStore: store using: mail excludeUids: downloadedUIDs];
        }
    }
*/
}

- (void) operationSuccessful: (DPAsyncHttpMail*)mail {
    MessageStore* store;
    MailboxUid*	trash;

    NSLog(@"operationSuccessful");
    switch(state) {
    
        case STATE_MESSAGE:
            NSLog(@"downloaded message");
            [self handleMessageDownloaded: mail];
            break;
        
        case STATE_MARKING_READ:
            NSLog(@"marked message read");
            [self downloadNextMessage: mail];
            break;
            
        case STATE_DELETE_MESSAGE:
            NSLog(@"deleted message");
            [self downloadNextMessage: mail];
            break;
        
        case STATE_DELETE_MESSAGES:
            NSLog(@"emptied trash");
            trash = [self trashMailboxUidCreateIfNeeded: NO];
            store = [self storeForMailboxUid: trash];        
            [store deleteMessages: messagesToProcess moveToTrash: NO];
            [messagesToProcess release];
            messagesToProcess = nil;
            
            [self deleteMessagesForNextFolder: mail];
            break;
        
    }
    
}

- (void) operationFailed: (DPAsyncHttpMail*)mail withMessage: (NSString*)aMessage {
    MessageStore* store;
    MailboxUid*	trash;
    
    NSLog(@"operationFailed: %@", aMessage);
    
    switch(state) {
        case STATE_DELETE_MESSAGES:
            [messagesToProcess release];
            messagesToProcess = nil;
            trash = [self trashMailboxUidCreateIfNeeded: NO];
            store = [self storeForMailboxUid: trash];
            NSData* result = [mail responseData];
            [self addFailureMessage: LocalizedString(@"Failure Details", @"") withBody: result intoMessageStore: store];
            showAlert(self, nil, LocalizedString(@"Delete Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error occurred while removing a message from the server: %@\n\nA message has been placed in the Trash with more information.", @""), [mail responseString]]);
        break;
    }
    
    finished = YES;
    NSLog(@"operation failed: %@", aMessage);
}

- (void)nowWouldBeAGoodTimeToTerminate:fp12 {
    NSLog(@"nowWouldBeAGoodTimeToTerminate");
    [NSApp removeTerminationHandler: self];
    stop = YES;
}

@end
