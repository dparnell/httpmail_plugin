//
//  DPHTTPMailPreferences.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Feb 19 2004.
//  Copyright (c) 2004 Daniel Parnell. All rights reserved.
//

#import "DPHTTPMailPreferences.h"
#import "DPHTTPMailBundle.h"
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
    if([DPHTTPMailBundle foldersUnderInbox]) {
        [foldersUnderInbox setState: NSOnState];
    } else {
        [foldersUnderInbox setState: NSOffState];
    }
    
    if([DPHTTPMailBundle downloadSentItems]) {
        [getSentItems setState: NSOnState];
    } else {
        [getSentItems setState: NSOffState];
    }
    
    if([DPHTTPMailBundle createFailureMessages]) {
        [failureMessages setState: NSOnState];
    } else {
        [failureMessages setState: NSOffState];
    }
    
    if([DPHTTPMailBundle ignoreNetworkState]) {
        [ignoreNetworkState setState: NSOnState];
    } else {
        [ignoreNetworkState setState: NSOffState];
    }
    
    if([DPHTTPMailBundle checkForUpdates]) {
        [updates setState: NSOnState];
    } else {
        [updates setState: NSOffState];
    }
    
	if([DPHTTPMailBundle detailedErrorReports]) {
		[createDetailedErrors setState: NSOnState];
	} else {
		[createDetailedErrors setState: NSOffState];
	}
	
    [timeout setIntValue: [DPHTTPMailBundle socketTimeout]];
    
    [userAgent setStringValue: [DPHTTPMailBundle userAgent]];
}

- (void)saveChanges {
    [DPHTTPMailBundle setFoldersUnderInbox: [foldersUnderInbox state]==NSOnState];
    [DPHTTPMailBundle setDownloadSentItems: [getSentItems state]==NSOnState];
    [DPHTTPMailBundle setSocketTimeout: [timeout intValue]];
    [DPHTTPMailBundle setCreateFailureMessages: [failureMessages state]==NSOnState];
    [DPHTTPMailBundle setIgnoreNetworkState: [ignoreNetworkState state]==NSOnState];
    [DPHTTPMailBundle setUserAgent: [userAgent stringValue]];
    [DPHTTPMailBundle setCheckForUpdates: [updates state]==NSOnState];
	[DPHTTPMailBundle setDetailedErrorReports: [createDetailedErrors state]==NSOnState];
}

- (char)hasChangesPending {
    return ([DPHTTPMailBundle foldersUnderInbox]!=([foldersUnderInbox state]==NSOnState)) |
           ([DPHTTPMailBundle downloadSentItems]!=([getSentItems state]==NSOnState)) |
           ([DPHTTPMailBundle socketTimeout]!=[timeout intValue]) |
           ([DPHTTPMailBundle createFailureMessages]!=([failureMessages state]==NSOnState)) |
           ([DPHTTPMailBundle ignoreNetworkState]!=([ignoreNetworkState state]==NSOnState)) |
           (![[DPHTTPMailBundle userAgent] isEqualToString: [userAgent stringValue]] |
           ([DPHTTPMailBundle checkForUpdates]!=([updates state]==NSOnState)) |
		   ([DPHTTPMailBundle detailedErrorReports]!=([createDetailedErrors state]==NSOnState))
           )
           ;
}

- (void)startDebugger:(id)sender {
    [[DPHTTPMailDebugger sharedInstance] setEnabled: YES];
}

- (void)checkForUpdates:(id)sender {
    [HTTPMailUpdateChecker checkForUpdates: YES];
}

- (void)donate:(id)sender {
	[[NSWorkspace sharedWorkspace] openFile: [[NSBundle bundleForClass: [self class]] pathForResource: @"donate" ofType: @"html"]];
}

@end
