//
//  ictest.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Dec 17 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>
#import <SystemConfiguration/SystemConfiguration.h>

NSData *OWKCGetItemAttribute(KCItemRef item, KCItemAttr attrTag)
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


int main(int argc, const char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    NSDictionary* settings;
    settings = (NSDictionary*)SCDynamicStoreCopyProxies(NULL);
    NSLog(@"%@", settings);


  KCSearchRef grepstate; 
  KCItemRef item;
  NSData* data;
  int length;
  void* itemData;
  
  if(KCFindFirstItem(NULL, NULL, &grepstate, &item)==noErr) {  
  
    do {
        NSString* str;
        NSString* str2;
        NSString* password = NULL;
        
        data = OWKCGetItemAttribute(item, kSecLabelItemAttr);
        
        if(data) {
            str = [NSString stringWithCString: [data bytes] length: [data length]];
        } else {
            str = NULL;
        }
        data = OWKCGetItemAttribute(item, kSecAccountItemAttr);
        if(data) {
            str2 = [NSString stringWithCString: [data bytes] length: [data length]];
        } else {
            str2 = NULL;
        }
/*        
        if(SecKeychainItemCopyContent(item, NULL, NULL, &length, &itemData)==noErr) {
            password = [NSString stringWithCString: itemData length: length];
            SecKeychainItemFreeContent(NULL, itemData);
        } else {
            password = NULL;
        } 
*/
        
        NSLog(@"%@\n%@\n%@\n%@", item, str, str2, password); 
                        
        KCReleaseItem(&item);
    } while( KCFindNextItem(grepstate, &item)==noErr);
    
    KCReleaseSearch(&grepstate);
  }

    
/*
    NSString* error;
    
    NSData* data = [NSData dataWithContentsOfFile: @"/private/var/db/SystemConfiguration/preferences.xml"];
    NSDictionary* dict = [NSPropertyListSerialization propertyListFromData: data 
                                                      mutabilityOption: NSPropertyListImmutable 
                                                      format: nil 
                                                      errorDescription: &error];
                                                      
    NSString* currentSet = [dict objectForKey: @"CurrentSet"];
    NSString* key = [currentSet lastPathComponent];
    NSDictionary* services = [dict objectForKey: @"Sets"];
    NSDictionary* service = [services objectForKey: key];
    
    NSString* location = [service objectForKey: @"UserDefinedName"];
    
    NSLog(@"Current location: %@", location);
*/
    

    [pool release];
    
    return 0;
}

