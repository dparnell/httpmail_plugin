//
//  DPAsyncHttpHelper.m
//  httpmail
//
//  Created by Daniel Parnell on 5/06/05.
//  Copyright 2005 Automagic Software. All rights reserved.
//

#import "DPAsyncHttpHelper.h"
#import "DPAsyncSocket.h"

@implementation DPAsyncHttpHelper

+ (DPAsyncHttpHelper*)newHelper: (DPAsyncHttp*)aHttp {
	return [[[DPAsyncHttpHelper alloc] initWithHttp: aHttp] autorelease];
}

- (id) initWithHttp: (DPAsyncHttp*)aHttp {
	self = [super init];
	
	if(self) {
//            NSLog(@"DPAsyncHttpHelper init - %p", self);
		errorMessage = nil;
                exception = nil;
		http = aHttp;
		lock = [[NSLock new] retain];
		[lock lock];
	}
	
	return self;
}

- (void) dealloc {
//            NSLog(@"DPAsyncHttpHelper dealloc - %p", self);
	[lock release];
	[errorMessage release];
        [exception release];
        
	[super dealloc];
}

- (void) startDownload: (id)dummy {
	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	int timeout = [http socketTimeout];
	double diff;
    
//        NSLog(@"timeout = %d", timeout);
        
	NS_DURING
		lastDataSeen = [NSDate timeIntervalSinceReferenceDate];
		failed = NO;
		timedOut = NO;
		done = NO;
		[http asyncGet];
		
		while(!done) {
				NSAutoreleasePool* pool2 = [NSAutoreleasePool new];
				[[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow: 0.1]];
				
				diff = ([NSDate timeIntervalSinceReferenceDate]-lastDataSeen);
				
//                NSLog(@"diff = %f", diff);
				if(diff>timeout) {
//                    NSLog(@"timed out");
					timedOut = YES;
					failed = YES;
					done = YES;
					[http close];
				}
				
				[pool2 release];
		}
	NS_HANDLER
		failed = YES;
//		errorMessage = [[localException reason] retain];
            exception = [localException retain];
	NS_ENDHANDLER
	[lock unlock];
        
	[pool release];
}

- (void) waitUntilDone {
    [http setDelegate: self];
    
    [NSThread detachNewThreadSelector: @selector(startDownload:) toTarget: self withObject: nil];

    // the lock has alredy been locked so we stop here until the download finishes
    [lock lock];
    
    // the download has finished so unlock the lock
    [lock unlock];

    if(failed) {
        if(timedOut) {
            [NSException raise: SOCKET_ERROR format: @"Socket timed out"];
        }

        if(exception) {
            [exception raise];
        }
        
        if(errorMessage) {
            [NSException raise: SOCKET_ERROR format: errorMessage];
        } 
        [NSException raise: SOCKET_ERROR format: @"Unknown socket error"];
    }
}

- (void)downloadFinished:(DPAsyncHttp*)sender {
//	NSLog(@"downloadFinished so unlock lock");
	done = YES;
}

- (void)downloadFailed:(DPAsyncHttp*)sender dueToError:(CFSocketError)error {
//	NSLog(@"downloadFailed so unlock lock");
	errorMessage = [[DPAsyncSocket niceError: error] retain];
	failed = YES;
	done = YES;
}

- (void)downloadProgress:(int)bytes of:(int)total forAsyncHttp: (DPAsyncHttp*)sender {
    lastDataSeen = [NSDate timeIntervalSinceReferenceDate];
}

- (void)downloadStopped:(DPAsyncHttp*)sender {
    done = YES;
}

@end
