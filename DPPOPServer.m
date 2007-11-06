//
//  DPPOPServer.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 10 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPPOPServer.h"
#import "DPPOPHandler.h"

@implementation DPPOPServer

- (id) init {
    self = [super init];
    if(self) {
        socket = [DPSocket new];
    }
    return self;
}

- (void) run {
    
    terminated = NO;
    [socket setPort: 9001];
    [socket listen];
    NSLog(@"Listening on port %d", [socket port]);
    while(!terminated) {
        DPSocket* client = [socket accept];
        DPPOPHandler* handler = [[DPPOPHandler alloc] initWithSocket: client];
        
        [NSThread detachNewThreadSelector:@selector(run:) toTarget: handler withObject: self];
    }
}

- (void)stop {
    terminated = YES;
    [socket close];
}

@end
