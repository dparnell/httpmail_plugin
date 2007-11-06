//
//  DPHTTPMailPreferences.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Feb 19 2004.
//  Copyright (c) 2004 Daniel Parnell. All rights reserved.
//

#import "DPHTTPMailPreferences.h"
#import "httpmailBundle.h"
#import "Version.h"
#import "DPHTTPMailDebugger.h"
#import "HTTPMailUpdateChecker.h"

@implementation DPHTTPMailPreferences

- (id) init {
    [NSBundle loadNibNamed: @"DPHTTPMailPreferences" owner: self];   
    return [super init];
}

- (void) awakeFromNib {
    [versionLabel setStringValue: [NSString stringWithFormat: [versionLabel stringValue], [NSString stringWithFormat: @"%@ %0.2f", VERSION_TARGET, VERSION_NUMBER] ]];
    
#ifdef TARGET_JAGUAR
    [httpmailBundle setFoldersUnderInbox: YES];
    [foldersUnderInbox setState: NSOnState];
    [foldersUnderInbox setEnabled: NO];
#endif
}

- (NSImage *) imageForPreferenceNamed:(NSString *)aName
{
    NSString* path = [[NSBundle bundleForClass: [self class]] pathForResource: @"httpmail" ofType: @"png"];
    
    return [[NSImage alloc] initWithContentsOfFile: path];
}

- (void)initializeFromDefaults {
    if([httpmailBundle foldersUnderInbox]) {
        [foldersUnderInbox setState: NSOnState];
    } else {
        [foldersUnderInbox setState: NSOffState];
    }
    
    if([httpmailBundle downloadSentItems]) {
        [getSentItems setState: NSOnState];
    } else {
        [getSentItems setState: NSOffState];
    }
    
    if([httpmailBundle createFailureMessages]) {
        [failureMessages setState: NSOnState];
    } else {
        [failureMessages setState: NSOffState];
    }
    
    if([httpmailBundle ignoreNetworkState]) {
        [ignoreNetworkState setState: NSOnState];
    } else {
        [ignoreNetworkState setState: NSOffState];
    }
    
    if([httpmailBundle checkForUpdates]) {
        [updates setState: NSOnState];
    } else {
        [updates setState: NSOffState];
    }
    
	if([httpmailBundle detailedErrorReports]) {
		[createDetailedErrors setState: NSOnState];
	} else {
		[createDetailedErrors setState: NSOffState];
	}
	
    [timeout setIntValue: [httpmailBundle socketTimeout]];
    
    [userAgent setStringValue: [httpmailBundle userAgent]];
}

- (void)saveChanges {
    [httpmailBundle setFoldersUnderInbox: [foldersUnderInbox state]==NSOnState];
    [httpmailBundle setDownloadSentItems: [getSentItems state]==NSOnState];
    [httpmailBundle setSocketTimeout: [timeout intValue]];
    [httpmailBundle setCreateFailureMessages: [failureMessages state]==NSOnState];
    [httpmailBundle setIgnoreNetworkState: [ignoreNetworkState state]==NSOnState];
    [httpmailBundle setUserAgent: [userAgent stringValue]];
    [httpmailBundle setCheckForUpdates: [updates state]==NSOnState];
	[httpmailBundle setDetailedErrorReports: [createDetailedErrors state]==NSOnState];
}

- (char)hasChangesPending {
    return ([httpmailBundle foldersUnderInbox]!=([foldersUnderInbox state]==NSOnState)) |
           ([httpmailBundle downloadSentItems]!=([getSentItems state]==NSOnState)) |
           ([httpmailBundle socketTimeout]!=[timeout intValue]) |
           ([httpmailBundle createFailureMessages]!=([failureMessages state]==NSOnState)) |
           ([httpmailBundle ignoreNetworkState]!=([ignoreNetworkState state]==NSOnState)) |
           (![[httpmailBundle userAgent] isEqualToString: [userAgent stringValue]] |
           ([httpmailBundle checkForUpdates]!=([updates state]==NSOnState)) |
		   ([httpmailBundle detailedErrorReports]!=([createDetailedErrors state]==NSOnState))
           )
           ;
}

- (void)startDebugger:(id)sender {
    [[DPHTTPMailDebugger sharedInstance] setEnabled: YES];
}

- (void)checkForUpdates:(id)sender {
    [HTTPMailUpdateChecker checkForUpdates: YES];
}

@end
