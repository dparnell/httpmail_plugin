//
//  Localization.m
//  httpmail
//
//  Created by Daniel Parnell on Fri Feb 07 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "Localization.h"
#import "HTTPMailAccount.h"

static NSBundle* bundle = NULL;

NSString* LocalizedString(NSString* string, NSString* comment) {
    if(!bundle) {
        bundle = [NSBundle bundleForClass: [HTTPMailAccount class]];
    }
    
    
    return [bundle localizedStringForKey: string value: nil table: nil];
}
