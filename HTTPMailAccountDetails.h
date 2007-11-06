//
//  HTTPMailAccountDetails.h
//  httpmail
//
//  Created by Daniel Parnell on Wed Oct 09 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-api.h"
#import "mail-app.h"

@interface HTTPMailAccountDetails:AccountDetails
{
    IBOutlet NSPopUpButton*	_downloadOptions;
    IBOutlet NSTextField*	_versionLabel;
    IBOutlet NSTextField*	_providerURL;
    IBOutlet NSButton*		_checkLocalAccounts;
    IBOutlet NSButton*		_downloadExtraFolders;
    IBOutlet NSButton*		_saveSent;
    IBOutlet NSPopUpButton*	_transportEncoding;
}

+ (id)currentAccount;
+ (HTTPMailAccountDetails*)currentAccountDetails;
+ (NSString*) accountDetailsNibName;

- (Class)accountClass;
- (void)setupUIFromValuesInAccount:(id)account;
- (void)setupAccountFromValuesInUI: (id)account forValidation:(BOOL)validate;
- (BOOL)userWantsAccountActive;

- (void)restoreDefaultURL:(id)sender;
@end
