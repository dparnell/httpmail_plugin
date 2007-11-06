//
//  HTTPMailAccountDetails.m
//  httpmail
//
//  Created by Daniel Parnell on Wed Oct 09 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "HTTPMailAccountDetails.h"
#import "HTTPMailAccount.h"
#import "Version.h"
#import "httpmail_constants.h"
#import "DPProxy.h"

@implementation HTTPMailAccountDetails

static id currentAccount = NULL;
static HTTPMailAccountDetails* details = NULL;

+ (id)currentAccount {
    return currentAccount;
}

+ (HTTPMailAccountDetails*)currentAccountDetails {
    return details;
}

+ (NSString*) accountDetailsNibName {
//    NSLog(@"accountDetailsNibName");
    return @"HTTPMailAccountDetails";
}


- init {
    self = [super init];
    if(self) {
//        NSLog(@"HTTPMailAccountDetails init - %p", self);
        details = self;
        
        _enableAccountCheckbox = nil;
    }
    
//    return [DPProxy newWithTarget: self];
    return self;
}

- (void)dealloc {
//    NSLog(@"HTTPMailAccountDetails dealloc - %p", self);
    
    currentAccount = NULL;
    details = NULL;
    
    [super dealloc];
}

- (void) awakeFromNib {
//    NSLog(@"HTTPMailAccountDetails awakeFromNib - %p", self);
    
    [_transportEncoding removeAllItems];

    NSMenu* menu = [_transportEncoding menu];
    id item;
    
    const NSStringEncoding* encoding = [NSString availableStringEncodings];
    while(*encoding) {
        NSString* title = [NSString localizedNameOfStringEncoding: *encoding];
        [_transportEncoding addItemWithTitle: title];
        item = [menu itemWithTitle: title];
        
        [item setTag: *encoding];
        
        encoding++;
    }    
}

- (Class)accountClass {
    return [HTTPMailAccount class];
}

- (void)setupUIFromValuesInAccount:(id)account {
//    NSLog(@"HTTPMailAccountDetails setupUIFromValuesInAccount - %p", self);
    
    currentAccount = account;

#ifdef TARGET_JAGUAR    
    if(!_enableAccountCheckbox) {
//        NSLog(@"loading preferences nib");
        [NSBundle loadNibNamed: @"HTTPMailAccountDetails" owner: self];
    }
#else
    [NSBundle loadNibNamed: @"HTTPMailAccountDetails" owner: self];
#endif
        
    [_versionLabel setStringValue: [NSString stringWithFormat: [_versionLabel stringValue], [NSString stringWithFormat: @"%@ %0.2f", VERSION_TARGET, VERSION_NUMBER] ]];
        
    if(account==NULL) {
        [_enableAccountCheckbox setState: NSOnState];
        [_providerURL setStringValue: HTTPMAIL_URL];
        [_checkLocalAccounts setState: NSOnState];
        [_downloadExtraFolders setState: NSOnState];
        [_saveSent setState: NSOffState];
        [_transportEncoding selectItemAtIndex: [_transportEncoding indexOfItemWithTag: [NSString defaultCStringEncoding]]];
    } else {
        [_providerURL setStringValue: [account providerURL]];
        
        if([account shouldSaveSentMessages]) {
            [_saveSent setState: NSOnState];
        } else {
            [_saveSent setState: NSOffState];
        }
        if([account shouldCheckLocalAccounts]) {
            [_checkLocalAccounts setState: NSOnState];
        } else {
            [_checkLocalAccounts setState: NSOffState];
        }
        if([account shouldDownloadExtraFolders]) {
            [_downloadExtraFolders setState: NSOnState];
        } else {
            [_downloadExtraFolders setState: NSOffState];
        }
        
        if([account shouldMarkAsReadOnDownload]) {
            [_downloadOptions selectItemAtIndex: 1];
        } else {
            if([account shouldDeleteOnDownload]) {
                [_downloadOptions selectItemAtIndex: 2];
            } else {
                if([account shouldSynchronize]) {
                    [_downloadOptions selectItemAtIndex: 3];
                } else {
                    [_downloadOptions selectItemAtIndex: 0];
                }
            }
        }
        
        [_transportEncoding selectItemAtIndex: [_transportEncoding indexOfItemWithTag: [account transportEncoding]]];        
    }    
    
    [super setupUIFromValuesInAccount: account];
}

- (void)setupAccountFromValuesInUI: (id)account forValidation:(BOOL)validate {        
//    NSLog(@"setupAccountFromValuesInUI: %@ forValidation: %d", account, validate);
    
    if(!validate) {        
        
        [account setProviderURL: [_providerURL stringValue]];
        [account setShouldCheckLocalAccounts: [_checkLocalAccounts state]==NSOnState];
        [account setShouldDownloadExtraFolders: [_downloadExtraFolders state]==NSOnState];
        [account setShouldSaveSentMessages: [_saveSent state]==NSOnState];
        
        switch([_downloadOptions indexOfSelectedItem]) {
            case 0: 
                [account setShouldMarkAsReadOnDownload: NO];
                [account setShouldDeleteOnDownload: NO];
                [account setShouldSynchonize: NO];
                break;
            case 1: 
                [account setShouldMarkAsReadOnDownload: YES];
                [account setShouldDeleteOnDownload: NO];
                [account setShouldSynchonize: NO];
                break;
            case 2: 
                [account setShouldMarkAsReadOnDownload: NO];
                [account setShouldDeleteOnDownload: YES];
                [account setShouldSynchonize: NO];
                break;
            case 3: 
                [account setShouldMarkAsReadOnDownload: NO];
                [account setShouldDeleteOnDownload: NO];
                [account setShouldSynchonize: YES];
                break;
        }
        
        [account setTransportEncoding: [_transportEncoding selectedTag]];
    }
    
    [super setupAccountFromValuesInUI: account forValidation: validate];

    // remove the httpmail object for this accoun from the cache
    [[DPhttpmailCache sharedInstance] removeFromCache: account];
    
//    NSString* path = [NSString stringWithFormat: @"%@-%@@%@", [[account class] accountTypeString], [account username], [account hostname]];
//    [self setAccountPath: path];
//    NSLog(@"path = %@", path);
}

/*
- (void)setUIElementsEnabled:(BOOL)flag {
    NSLog(@"setUIElementsEnabled: %d", flag);
}
*/

- (void)restoreDefaultURL:(id)sender {
    if([[_account firstEmailAddress] hasSuffix: @"@msn.com"]) {
        [_providerURL setStringValue: HTTPMAIL_MSN_URL];
    } else {
        [_providerURL setStringValue: HTTPMAIL_URL];
    }
}

- (BOOL)userWantsAccountActive {
    if([[_account firstEmailAddress] hasSuffix: @"@msn.com"]) {
        [(id)_account setProviderURL: HTTPMAIL_MSN_URL];
    } 
   
    return [super userWantsAccountActive];
}

#ifndef TARGET_JAGUAR
- (BOOL) isAccountInformationDirty:(MailAccount*)account {
    BOOL result = NO;
    int index = 0;
    
//    NSLog(@"isAccountInformationDirty: %@", account);
    if([super respondsToSelector: @selector(isAccountInformationDirty:)]) {
        // surpress the compiler warning
        result = result | [(id)super isAccountInformationDirty: account];
//        NSLog(@"result = %d", result);
  
    }

    HTTPMailAccount* m = (HTTPMailAccount*)account;
    
    if([m shouldMarkAsReadOnDownload]) {
        index = 1;
    } else if([m shouldDeleteOnDownload]) {
        index = 2;
    } else if([m shouldSynchronize]) { 
        index = 3;
    }
    result = result | ([m providerURL] != [_providerURL stringValue]);
    result = result | ([m shouldCheckLocalAccounts] != ([_checkLocalAccounts state]==NSOnState));
    result = result | ([m shouldDownloadExtraFolders] != ([_downloadExtraFolders state]==NSOnState));
    result = result | ([m shouldSaveSentMessages] != ([_saveSent state]==NSOnState));
    result = result | ([_downloadOptions indexOfSelectedItem] != index);
    result = result | ([m transportEncoding] != [_transportEncoding selectedTag]);
    return result;
}
#endif

@end
