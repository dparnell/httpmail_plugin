//
//  DPProxy.h
//  httpmail
//
//  Created by Daniel Parnell on Wed Feb 12 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface DPProxy : NSProxy {
    id target;
}

+ newWithTarget:(id)aTarget;

@end
