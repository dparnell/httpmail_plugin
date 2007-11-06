//
//  SetupMailPrefs.m
//  httpmail
//
//  Created by Daniel Parnell on 11/04/05.
//  Copyright 2005 Daniel Parnell. All rights reserved.
//

#import "SetupMailPrefs.h"


int main(int argc, const char *argv[])
{
    NSAutoreleasePool* pool = [NSAutoreleasePool new];
    
    NSString* mailPrefsPath = [@"~/Library/Preferences/com.apple.mail.plist" stringByExpandingTildeInPath];
    NSData* data;
    NSMutableDictionary* prefs;
    NSPropertyListFormat format;
    NSString* failed = nil;
    
    data = [NSData dataWithContentsOfFile: mailPrefsPath]; 
    if(data) {
        NSLog(@"Loading %@", mailPrefsPath);
        prefs = [NSPropertyListSerialization propertyListFromData: data mutabilityOption: NSPropertyListMutableContainersAndLeaves format: &format errorDescription: &failed];
    } else {
        prefs = [NSMutableDictionary dictionary];
    }


    if(prefs) {
        [prefs setObject: @"1" forKey: @"EnableBundles"];
        [prefs setObject: @"1" forKey: @"BundleCompatibilityVersion"];

        data = [NSPropertyListSerialization dataFromPropertyList: prefs format: format errorDescription: &failed];
        
        if(data) {
            NSLog(@"Writing %@", mailPrefsPath);
            
            [data writeToFile: mailPrefsPath atomically: NO];
        }
    }
    
    NSLog(@"Done");
    
    [pool release];
    
    return 0;
}
