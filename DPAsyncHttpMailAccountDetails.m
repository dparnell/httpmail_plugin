//
//  DPAsyncHttpMailAccountDetails.m
//  httpmail
//
//  Created by Daniel Parnell on Mon Jun 30 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPAsyncHttpMailAccountDetails.h"
#import "DPAsyncHttpMailAccount.h"

@implementation DPAsyncHttpMailAccountDetails

- (Class)accountClass {
    return [DPAsyncHttpMailAccount class];
}

@end
