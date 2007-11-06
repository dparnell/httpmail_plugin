//
//  HTTPMailDeliveryQueue.m
//  httpmail
//
//  Created by Daniel Parnell on Fri Feb 14 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "HTTPMailDeliveryQueue.h"
#import "DPProxy.h"
#import "HTTPMailDeliveryAccount.h"

@implementation HTTPMailDeliveryQueue

+ sharedDeliveryQueue {
    NSLog(@"sharedDeliveryQueue");
    return [super sharedDeliveryQueue];    
//    return [DPProxy newWithTarget: [super sharedDeliveryQueue]];
}

/*
- (void)_deliverQueuedMessages:fp12 {
    NSLog(@"_deliverQueuedMessages: %@", [fp12 class]);
    
//    [super _deliverQueuedMessages: fp12];
}
*/

- (int)_performDeliveryOfMessage:(Message*)message reasonForFailure:(id *)error usingAccount:(DeliveryAccount*)account accountUsed:(id *)used {
    NSLog(@"_performDeliveryOfMessage");
    if([account isKindOfClass: [HTTPMailDeliveryAccount class]]) {
        NSLog(@"a HTTPMailDeliveryAccount");
        *used = account;

        return 0;
    } else {
        int result = [super _performDeliveryOfMessage: message reasonForFailure: error usingAccount: account accountUsed: used];
        NSLog(@"super _performDeliveryOfMessage returned %d", result);
        return result;
        
    }
}

@end
