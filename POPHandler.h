//
//  POPHandler.h
//  httpmail
//
//  Created by Daniel Parnell on Sun Dec 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "io.h"

@interface POPHandler : NSObject {
    IO*	io;
}

- (POPHandler*)initWithIO: (IO*) aIO;
- (void)run;

@end
