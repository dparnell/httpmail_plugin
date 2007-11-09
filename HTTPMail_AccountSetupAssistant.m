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
//	NSLog(@"items = %@", [_incomingTypePopUp itemArray]);
	NSMenu* menu = [_incomingTypePopUp menu];
	NSMenuItem* item = [[NSMenuItem alloc] initWithTitle: @"HTTPMail" action: nil keyEquivalent: @""];
	NSImage* img = [[NSImage alloc] initByReferencingFile: [[NSBundle bundleForClass: [HTTPMailAccount class]] pathForResource: @"httpmail" ofType: @"png"]];
	[img setScalesWhenResized: YES];
	[img setSize: NSMakeSize(16.0, 16.0)];
	[item setImage: img];
	
	[menu addItem: item];
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

