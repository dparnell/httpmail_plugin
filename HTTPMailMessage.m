//
//  HTTPMailMessage.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Oct 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "HTTPMailMessage.h"


@implementation HTTPMailMessage

- (id)initWithUrl:(NSURL*)url {
    self = [super init];
    
    if(self) {
        fUrl = [url retain];
        fData = NULL;
    }
    
    return self;
}

- (id)initWithData:(NSData*)data {
    self = [super init];
    
    if(self) {
        fUrl = NULL;
        fData = [data retain];
    }
    
    return self;
}

- (NSData*)messageData {
    if(fData==NULL) {
        /** @todo write code to download the data */
        NSLog(@"data not loaded yet");
    }
    
    return fData;
}

- (id) uid {
    NSLog(@"HTTPMailMessage uid = %d", self);
    return self;
}

- (BOOL) hasTemporaryUid {
    return NO;
}

- (BOOL) isPartial {
    return NO;
}

@end
