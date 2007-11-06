//
//  DPNotificationWatcher.m
//  httpmail
//
//  Created by Daniel Parnell on 31/08/04.
//  Copyright 2004 Daniel Parnell. All rights reserved.
//

#import "DPNotificationWatcher.h"


@implementation DPNotificationWatcher

- (id) init {
    self = [super init];
    
    if(self) {
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleNotification:) name: nil object: nil];
    }
    
    return self;
}

- (void) handleNotification: (NSNotification*) notification {
    if(![[notification name] hasPrefix: @"NS"]) {
        NSLog(@"%@", notification);
    }
}

@end
