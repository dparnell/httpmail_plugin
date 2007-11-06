//
//  HTTPMailDelivery.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Feb 11 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "HTTPMailDelivery.h"
#import "DPProxy.h"

@implementation HTTPMailDelivery

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    NSLog(@"HTTPMailDelivery doesNotRecognizeSelector: %s", aSelector);
}

- (void)setDelegate:(id)delegate {
    NSLog(@"setDelegate: %@", delegate);
    
    [super setDelegate: [DPProxy newWithTarget: delegate]];
}


- (Class)deliveryClass {
    NSLog(@"deliveryClass");
    return [self class];
}


- (int)deliverSynchronouslySpecifyingReasonForFailure:(id *)err {
    int result = [super deliverSynchronouslySpecifyingReasonForFailure: err];
    
    NSLog(@"deliverSynchronouslySpecifyingReasonForFailure returned %d", result);
    if(err) {
        NSLog(@"err = %@", *err);
    }
    
    return result;
}

- (void)deliverMessageData:(NSData*)message toRecipients: (NSArray*) who {    
    NSLog(@"deliver:\n%@\n to: %@", [NSString stringWithCString: [message bytes] length: [message length]] , who);

    [_message setMessageFlags: 0xfc81];
//    MessageStore* outbox = [MailAccount outboxMessageStore: YES];
//    [outbox deleteMessages: [NSArray arrayWithObject: [self message]] moveToTrash: NO];

//    NSLog(@"outbox = %@", outbox);
//    NSLog(@"messages = %@", [outbox copyOfAllMessages]);
    
//    NSLog(@"archiveAccount = %@", [self archiveAccount]);
//    NSLog(@"delegate = %@", [self delegate]);
}

- (int) deliveryStatus {
    int result = [super deliveryStatus];
    
    NSLog(@"deliveryStatus = %@", result);
    
    return result;
}

@end
