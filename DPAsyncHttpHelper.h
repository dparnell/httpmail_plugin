//
//  DPAsyncHttpHelper.h
//  httpmail
//
//  Created by Daniel Parnell on 5/06/05.
//  Copyright 2005 Automagic Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DPAsyncHttp.h"

@interface DPAsyncHttpHelper : NSObject {
	DPAsyncHttp* http;
	NSLock* lock;
	BOOL done;
	double lastDataSeen;
	BOOL failed;
	BOOL timedOut;
	NSString* errorMessage;
        NSException* exception;
}

+ (DPAsyncHttpHelper*)newHelper: (DPAsyncHttp*)aHttp;

- (id) initWithHttp: (DPAsyncHttp*)aHttp;

- (void) waitUntilDone;

- (void)downloadFinished:(DPAsyncHttp*)sender;
- (void)downloadFailed:(DPAsyncHttp*)sender dueToError:(CFSocketError)error;
- (void)downloadProgress:(int)bytes of:(int)total forAsyncHttp: (DPAsyncHttp*)sender;
- (void)downloadStopped:(DPAsyncHttp*)sender;

@end
