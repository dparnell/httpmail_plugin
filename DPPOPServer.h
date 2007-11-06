//
//  DPPOPServer.h
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 10 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPSocket.h"

@interface DPPOPServer : NSObject {
    BOOL	terminated;
    DPSocket*	socket;
}

- (void)run;
- (void)stop;

@end
