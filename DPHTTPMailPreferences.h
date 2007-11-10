//
//  DPHTTPMailPreferences.h
//  httpmail
//
//  Created by Daniel Parnell on Thu Feb 19 2004.
//  Copyright (c) 2004 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-app.h"

@interface DPHTTPMailPreferences : NSPreferencesModule {
    IBOutlet NSButton *foldersUnderInbox;
    IBOutlet NSButton *getSentItems;
    IBOutlet NSBox *preferencesView;
    IBOutlet NSTextField *versionLabel;
    IBOutlet NSSlider *timeout;
    IBOutlet NSButton *failureMessages;
    IBOutlet NSButton *ignoreNetworkState;
    IBOutlet NSComboBox *userAgent;
    IBOutlet NSButton *updates;
	IBOutlet NSButton *createDetailedErrors;
}

- (void)startDebugger:(id)sender;
- (void)checkForUpdates:(id)sender;
- (void)donate:(id)sender;

@end
