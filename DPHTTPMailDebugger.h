/* DPHTTPMailDebugger */

#import <Cocoa/Cocoa.h>

@interface DPHTTPMailDebugger : NSObject
{
    IBOutlet NSTextView *debugText;
    BOOL enabled;
}

+ (DPHTTPMailDebugger*) sharedInstance;
+ (BOOL) debugEnabled;

- (BOOL) enabled;
- (void) setEnabled:(BOOL) flag;

- (void) add: (NSString*) msg;

@end
