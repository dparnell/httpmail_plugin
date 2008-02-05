//
//  DPProxy.m
//  httpmail
//
//  Created by Daniel Parnell on Wed Feb 12 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPProxy.h"


@implementation DPProxy

+ newWithTarget:(id)aTarget {
    DPProxy* result = [[DPProxy alloc] autorelease];
    if(result) {
        result->target = [aTarget retain];
    }
    
    NSLog(@"created proxy for %@", aTarget);
    
    return result;
}

- (void) dealloc {
    [target release];
    
    [super dealloc];
} 

+ (BOOL)respondsToSelector:(SEL)aSelector {
    NSLog(@"respondsToSelector: %s", aSelector);
    return YES;
} 

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    NSLog(@"%@ %p - %@", [target class], target, NSStringFromSelector([anInvocation selector]));
    
    [anInvocation setTarget: target];
    [anInvocation invoke];
    return;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    return [target methodSignatureForSelector:aSelector];
}

@end
