//
//  HTTPMailMessage.h
//  httpmail
//
//  Created by Daniel Parnell on Tue Oct 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "mail-api.h"

@interface HTTPMailMessage : Message {
    NSURL*	fUrl;
    NSData*	fData;
}

- (id)initWithUrl:(NSURL*)url;
- (id)initWithData:(NSData*)data;

- (NSData*)messageData;
@end
