//
//  xinetd_pop_main.m
//  httpmail
//
//  Created by Daniel Parnell on Sun Dec 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "io.h"
#import "POPHandler.h"

#import <stdio.h>

int main(int argc, const char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    IO*	io = [IO stdio];
    POPHandler* handler = [[POPHandler alloc] initWithIO: io];
    [handler run];
    
    [pool release];
    
    return 0;
}
