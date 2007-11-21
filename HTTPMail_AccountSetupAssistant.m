//
//  HTTPMail_AccountSetupAssistant.m
//  httpmail tiger
//
//  Created by Daniel Parnell on 27/09/04.
//  Copyright 2004 Daniel Parnell. All rights reserved.
//

#import "HTTPMail_AccountSetupAssistant.h"
#import "HTTPMailAccount.h"

@implementation HTTPMail_AccountSetupAssistant

+ (void) load
{
    NSLog(@"Installing HTTPMail Account Setup Assistant");
    [HTTPMail_AccountSetupAssistant poseAsClass:[AccountSetupAssistant class]];
}

#ifdef TARGET_LEOPARD

- (void) awakeFromNib {
	// Add in the HTTPMail account type
	NSMenu* menu = [_incomingTypePopUp menu];
	NSMenuItem* item = [[NSMenuItem alloc] initWithTitle: @"HTTPMail" action: nil keyEquivalent: @""];
	NSImage* img = [[NSImage alloc] initByReferencingFile: [[NSBundle bundleForClass: [HTTPMailAccount class]] pathForResource: @"httpmail" ofType: @"png"]];
	[img setScalesWhenResized: YES];
	[img setSize: NSMakeSize(16.0, 16.0)];
	[item setImage: img];
	
	[menu addItem: item];
}

- (void) setIncomingAccountClassIndex:(int) index {
	[super setIncomingAccountClassIndex: index];

	if(index==[_incomingTypePopUp indexOfItemWithTitle: @"HTTPMail"]) {
		[self setIncomingMailServer: @"hotmail.com"];
		[self setIncomingUserName: [self emailAddress]];
	}
}

- (void)_validateReceivingAccount {
	if([[_incomingTypePopUp titleOfSelectedItem] isEqualToString: @"HTTPMail"]) {
		HTTPMailAccount* account = [HTTPMailAccount new];
		NSString* path = [HTTPMailAccount defaultPathNameForAccountWithHostname: [self incomingMailServer] username: [self incomingUserName]];
		NSString* description = [self incomingDescription];
		if(description==nil) {
			description = @"Hotmail Account";
		}
		
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys: 
									description,									@"AccountName",
									[self name],									@"FullUserName",
									path,											@"AccountPath",
									@"HTTPMailAccount",								@"AccountType",
									[NSArray arrayWithObject: [self emailAddress]],	@"EmailAddresses",
									[self incomingUserName],						@"Username",
									[self incomingMailServer],						@"Hostname",
									@"NO",											@"StoreDraftsOnServer",
									@"NO",											@"StoreNotesInInbox",
									@"NO",											@"StoreSentMessagesOnServer",
									@"NO",											@"StoreTrashOnServer",
									nil];
											
		[account setAccountInfo: dict];
		[account setPassword: [self password]];
		
		[self setReceivingAccount: account];
		[self setDeliveryAccount: [account deliveryAccount]];
		[self setSelectedTab: 5];
	} else {
		[super _validateReceivingAccount];
	}
}

#else

- (BOOL)_shouldSkipIncomingSecurityTabForSelectedAccountBasedOnISPInfo:(id)fp8 {
	if([[self _account] isKindOfClass: [HTTPMailAccount class]]) {
		return YES;
	}
	
	return [super _shouldSkipIncomingSecurityTabForSelectedAccountBasedOnISPInfo: fp8];
}

- (BOOL)_shouldSkipOutgoingServerTabForSelectedAccount {
	if([[self _account] isKindOfClass: [HTTPMailAccount class]]) {
		return YES;
	}
	
	return [super _shouldSkipOutgoingServerTabForSelectedAccount];
}

- (BOOL)_outgoingServerValid {
    if([[self _account] isKindOfClass: [HTTPMailAccount class]]) {
        return YES;
    }
    
    return [super _outgoingServerValid];
}

- (BOOL)_validateValesInTabAtIndex:(int)index {
    if([[self _account] isKindOfClass: [HTTPMailAccount class]]) {
        return YES;
    }
    
    return [super _validateValesInTabAtIndex: index];
}
#endif

@end

