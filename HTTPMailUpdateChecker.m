//
//  HTTPMailUpdateChecker.m
//  httpmail
//
//  Created by Daniel Parnell on 30/03/05.
//  Copyright 2005 Daniel Parnell. All rights reserved.
//

#define USE_ASYNC_HTTP
#import "HTTPMailUpdateChecker.h"
#import "Version.h"

#ifdef USE_ASYNC_HTTP
#import "DPAsyncHttp.h"
#else
#import "DPhttp.h"
#endif
#import "Localization.h"
#import "mail-app.h"

@implementation HTTPMailUpdateChecker

+ (void) checkForUpdates:(BOOL) showOK {
    NSData* data;
    
	NetworkController* nc = [NetworkController sharedInstance];
	if([nc isHostReachable: @"www.automagic-software.com"]) {
#ifdef USE_ASYNC_HTTP
		DPAsyncHttp* http = [DPAsyncHttp new];
#else
		DPhttp* http = [DPhttp new];
#endif	
		[http setURL: [NSURL URLWithString: @"http://www.automagic-software.com/versions/httpmail/version.xml"]];
		
		[http setHeaderValue: [NSString stringWithFormat: @"DPhttp 1.0 (HTTPMail %f %@)", VERSION_NUMBER, VERSION_TARGET] forKey: @"User-Agent"];
		
		data = [http get];
		
		if(data) {
			NSString* error = nil;
			NSDictionary* dict = [NSPropertyListSerialization propertyListFromData: data mutabilityOption: NSPropertyListImmutable format: nil errorDescription: &error];
			
			if(dict) {
				NSDictionary* versions = [dict objectForKey: @"Latest Versions"];
				NSNumber* latest = [versions objectForKey: VERSION_TARGET];
				float ver = [latest floatValue];
				
				// do it this way because the float value returned from the plist is sometimes "bigger" than it should be
				if(floor(VERSION_NUMBER*100)<floor(ver*100)) {
					NSRunInformationalAlertPanel(LocalizedString(@"HttpMail Plugin update available", nil), 
												 [NSString stringWithFormat: LocalizedString(@"Version %0.2f of is now available from\nhttp://www.automagic-software.com/", nil), ver], @"Ok", nil, nil);
				} else {
					if(showOK) {
						NSRunInformationalAlertPanel(@"HttpMail Plugin", LocalizedString(@"The currently installed plugin is up to date", nil), @"Ok", nil, nil);
					}
				}
				
			} else {
				NSRunInformationalAlertPanel(LocalizedString(@"Error checking for HttpMail Plugin updates", nil), error, @"Ok", nil, nil);
			}
		} else {
			NSRunInformationalAlertPanel(LocalizedString(@"Error checking for HttpMail Plugin updates", nil), 
										 [NSString stringWithFormat: LocalizedString(@"Could not download the version information: %d %@", nil), [http responseCode], [http responseString]], @"Ok", nil, nil);
		}
	} else {
		if(showOK) {
			NSRunInformationalAlertPanel(LocalizedString(@"Version check failed", nil), 
										 LocalizedString(@"Could not connect to http://www.automagic-software.com/", nil), @"Ok", nil, nil);
		}
	}
}

@end
