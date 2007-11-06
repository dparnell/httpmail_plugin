//
//  DPKeychain.h
//  httpmail
//
//  Created by Daniel Parnell on Fri Jan 03 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <Security/SecKey.h>
#include <Security/SecKeychain.h>
#include <Security/SecKeychainItem.h>
#include <Security/SecKeychainSearch.h>

#define kcUsername  @"username"
#define kcPassword  @"password"

@interface DPKeychain : NSObject {
    SecKeychainRef keychain;
}

+ (DPKeychain*)newWithPath: (NSString*)aPath;

- (id) init;

- (NSDictionary*) findKeychainItem:(NSString*)aName;

@end
