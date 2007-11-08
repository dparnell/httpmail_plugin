//
//  DPKeychain.m
//  httpmail
//
//  Created by Daniel Parnell on Fri Jan 03 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPKeychain.h"

@implementation DPKeychain

+ (DPKeychain*)newWithPath: (NSString*)aPath {
    DPKeychain* result = [DPKeychain new];
    
    SecKeychainOpen([aPath cStringUsingEncoding: NSUTF8StringEncoding], &result->keychain);
    
    return result;
}

- (id) init {
    self = [super init];
    
    if(self) {
        keychain = NULL;
    }
    
    return self;
}

- (void) dealloc {
    if(keychain) {
        // how do we release the kecyhain?
    }
    
    [super dealloc];
}

// stolen from OmniWeb
static NSData *OWKCGetItemAttribute(KCItemRef item, KCItemAttr attrTag)
{
    SecKeychainAttribute attr;
    OSStatus keychainStatus;
    UInt32 actualLength;
    void *freeMe = NULL;
    
    attr.tag = attrTag;
    actualLength = 256;
    attr.length = actualLength;  /* KCGetAttribute() doesn't appear to write this field, at least in Cheetah4K29, but it may read it */
    attr.data = alloca(actualLength);
        
    keychainStatus = KCGetAttribute(item, &attr, &actualLength);
    if (keychainStatus == errKCBufferTooSmall) {
        /* the attribute length will have been placed into actualLength */
        freeMe = NSZoneMalloc(NULL, actualLength);
        attr.length = actualLength;
        attr.data = freeMe;
        keychainStatus = KCGetAttribute(item, &attr, &actualLength);
    }
    if (keychainStatus == noErr) {
        NSData *retval = [NSData dataWithBytes:attr.data length:actualLength];
	if (freeMe != NULL)
            NSZoneFree(NULL, freeMe);
        // NSLog(@"attr '%c%c%c%c' value %@", ((char *)&attrTag)[0], ((char *)&attrTag)[1], ((char *)&attrTag)[2], ((char *)&attrTag)[3], retval);
        return retval;
    }
    
    if (freeMe != NULL)
        NSZoneFree(NULL, freeMe);

    if (keychainStatus == errKCNoSuchAttr) {
        /* An expected error. Return nil for nonexistent attributes. */
        return nil;
    }
    
    /* An unexpected error, probably indicating a real problem. Raise an exception. */
    [NSException raise:@"Keychain error" format:@"Error number %d occurred while trying to fetch an item attribute, and Apple's too stingy to include a strerror() equivalent.", keychainStatus];
    
    return nil;  // appease the dread compiler warning gods
}

- (NSDictionary*) findKeychainItem:(NSString*)aName {
  KCSearchRef grepstate; 
  KCItemRef item;
  NSData* data;
  UInt32 length;
  void* itemData;
  NSMutableDictionary* result = NULL;
  
  if(KCFindFirstItem(keychain, NULL, &grepstate, &item)==noErr) {  
  
    do {
        NSString* server;
        
        data = OWKCGetItemAttribute(item, kSecLabelItemAttr);
        if(data) {
            server = [NSString stringWithCString: [data bytes] length: [data length]];
        } else {
            server = NULL;
        }
        
        if([aName isEqualToString: server]) {
            NSString* username;
            NSString* password;
            
            data = OWKCGetItemAttribute(item, kSecAccountItemAttr);
            if(data) {
                username = [NSString stringWithCString: [data bytes] length: [data length]];
            } else {
                username = @"";
            }

        
            if(SecKeychainItemCopyContent(item, NULL, NULL, &length, &itemData)==noErr) {
                password = [NSString stringWithCString: itemData length: length];
                SecKeychainItemFreeContent(NULL, itemData);
            } else {
                password = @"";
            } 
        
            result = [NSMutableDictionary dictionary];
            [result setObject: username forKey: kcUsername];
            [result setObject: password forKey: kcPassword];
            
            KCReleaseItem(&item);
            
            break;
        }
        
        KCReleaseItem(&item);
    } while( KCFindNextItem(grepstate, &item)==noErr);
    
    KCReleaseSearch(&grepstate);
  }
  
  
  return result;
}

@end
