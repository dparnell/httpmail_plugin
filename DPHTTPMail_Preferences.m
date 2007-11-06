//
//  DPHTTPMail_Preferences.m
//  httpmail
//
//  Created by Daniel Parnell on 9/08/04.
//  Copyright 2004 Daniel Parnell. All rights reserved.
//

#import "DPHTTPMail_Preferences.h"
#import "DPHTTPMailPreferences.h"

@implementation DPHTTPMail_Preferences

+ (void) load
{
    NSLog(@"Installing HTTPMail Preferences panel");
    [DPHTTPMail_Preferences poseAsClass:[NSPreferences class]];
}

+ sharedPreferences
{
    static BOOL	added = NO;
    id			preferences = [super sharedPreferences];

    if(preferences != nil && !added){
        added = YES;
        [preferences addPreferenceNamed: @"HTTPMail" owner: [DPHTTPMailPreferences sharedInstance]];
    }
    
    return preferences;
}

- (id)  toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar {
    id result = [super toolbarDefaultItemIdentifiers: toolbar];
    
    return result;
}

- (id) toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar {
    id result = [super toolbarAllowedItemIdentifiers: toolbar];
    
    return result;
}

- (id) toolbarSelectableItemIdentifiers:(NSToolbar*)toolbar {
    NSMutableArray* result = [super toolbarSelectableItemIdentifiers: toolbar];
    [toolbar setAllowsUserCustomization: YES];
    return result;
}

@end
