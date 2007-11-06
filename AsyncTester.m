#import "AsyncTester.h"

@implementation AsyncTester


- (IBAction)performTests2:(id)sender {
    mode = 2;
    [NSThread detachNewThreadSelector:@selector(startMyThread:) toTarget: self withObject: nil];
}

- (IBAction)performTests:(id)sender
{
    mode = 1;
    [NSThread detachNewThreadSelector:@selector(startMyThread:) toTarget: self withObject: nil];
}

- (IBAction)testMail:(id)sender {
    NSLog(@"Connecting to httpmail server");
    fMail = [[DPAsyncHttpMail new] retain];
    [fMail setUsername: @"danielparnell"];
    [fMail setPassword: @"yellow11"];

//    [fMail setProxy: [NSURL URLWithString: @"http://proxy.oz.quest.com:8080/"]];
//    [fMail setProxyUsername: @"prod\\dparnell"];
//    [fMail setProxyPassword: @"yellow22"];

    
    [fMail setDelegate: self];
    [fMail login];
}

- (void)startMyThread:(id)dummy
{
    NSAutoreleasePool* pool = [NSAutoreleasePool new];
    
    NSLog(@"starting tests");

    finished = NO;
    
    DPAsyncHttp* http = [[DPAsyncHttp new] retain];
    [http setURL: [NSURL URLWithString: @"http://localhost/~daniel"]];

	if(mode==1) {
		[http setDelegate: self];
		[http asyncGet];
		
		while(!finished && [NSApp isRunning]) {
			[[NSRunLoop currentRunLoop] runUntilDate: [NSDate dateWithTimeIntervalSinceNow: 0.1]];
		}
	} else {	
		NSData* data = [http get];
    
		NSLog(@"data = %@", data);
	}
    
    [pool release];
}


- (void)downloadFinished:(DPAsyncHttp*)sender {
    NSLog(@"DOWNLOAD FINISHED: %d %@", [sender responseCode], [sender responseString]);
    NSData* data = [sender responseData];
    NSLog(@"data:\n%@", [NSString stringWithCString: [data bytes] length: [data length]]);
    
	finished = YES;
}

- (void)downloadFailed:(DPAsyncHttp*)sender dueToError:(CFSocketError)error {
    NSLog(@"DOWNLOAD FAILED DUE TO ERROR %d", error);
    
    finished = YES;
}

- (void) loginSuccessful: (DPAsyncHttpMail*)mail {
    NSLog(@"login successful");
    
    [mail messagesForFolder: @"inbox"];
}

- (void) loginFailed: (DPAsyncHttpMail*)mail {
    NSLog(@"login failed: %@", [mail responseString]);
    
    finished = YES;
}

- (void) messagesFetched: (NSArray*)messages forMail: (DPAsyncHttpMail*)mail {
    NSLog(@"got messages:\n%@", messages);

    finished = YES;
}

- (void) operationSuccessful: (DPAsyncHttpMail*)mail {
    NSLog(@"operationSuccessful");
}

- (void) operationFailed: (DPAsyncHttpMail*)mail withMessage: (NSString*)aMessage {
    NSLog(@"operationFailed: %@", aMessage);
    finished = YES;
}

@end
