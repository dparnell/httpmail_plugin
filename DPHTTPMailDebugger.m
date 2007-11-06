#import "DPHTTPMailDebugger.h"

@implementation DPHTTPMailDebugger

DPHTTPMailDebugger* instance = nil;

+ (DPHTTPMailDebugger*) sharedInstance {
    if(instance==nil) {
        instance = [[DPHTTPMailDebugger new] retain];
        if(instance) {
            instance->enabled = NO;
            
            [NSBundle loadNibNamed: @"HTTPMailDebugWindow" owner: instance];
        }
    }
    
    return instance;
}

+ (BOOL) debugEnabled {
    if(instance) {
        return [instance enabled];
    }
    
    return NO;
}

- (BOOL) enabled {
    return enabled;
}

- (void) setEnabled:(BOOL) flag {
    enabled = flag;
    
    if(enabled) {
        [[debugText window] makeKeyAndOrderFront: self];
    }
}

- (void) add: (NSString*) msg {
    if(enabled) {
//        NSLog(@"%@", msg);
        [[debugText textStorage] appendAttributedString: [[NSAttributedString alloc] initWithString: [msg stringByAppendingString: @"\n"]]]; 
        [debugText scrollPageDown: self];
    }
}

@end
