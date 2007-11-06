//
//  HTTPMailUpdateChecker.h
//  httpmail
//
//  Created by Daniel Parnell on 30/03/05.
//  Copyright 2005 Daniel Parnell. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface HTTPMailUpdateChecker : NSObject {

}

+ (void) checkForUpdates:(BOOL) showOK;

@end
