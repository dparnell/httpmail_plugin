//
//  HTTPMailConnection.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 03 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "HTTPMailConnection.h"


@implementation HTTPMailConnection


- (void)doesNotRecognizeSelector:(SEL)aSelector {
    NSLog(@"HTTPMailConnection doesNotRecognizeSelector: %s", aSelector);
}

#ifdef TARGET_LEOPARD
- (id)initWithPendingGateway:(BOOL)fp8 account:(id)fp12 {
	self = [super init];
	
	if(self) {
	}
	
	return self;
}

- (id)gateway {
	return nil;
}

#endif

- (BOOL)connectUsingAccount:(MailAccount*)account errorMessage:(id *)msg {
    NSLog(@"connectUsingAccount %@", account);
    
    *msg = @"connectUsingAccount not yet implemented";
    
    return NO;
}

- (int)connectionState {
    NSLog(@"connectionState");
    
    return 0;
}

- (void) close {
    NSLog(@"close");
}

- (char)examineMailbox: mailbox errorMessage:(id *)error {
    NSLog(@"examineMailbox: %@", mailbox);
   
    return 0; 
}

- fetchHeadersForUid:(int)fp12 {
    NSLog(@"fetchHeadersForUid: %d", fp12);
  
    return NULL;  
}


@end
