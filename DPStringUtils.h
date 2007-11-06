//
//  DPStringUtils.h
//  httpmail
//
//  Created by Daniel Parnell on Thu Sep 26 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface DPStringUtils : NSObject {

}

+ (NSDictionary*)dictionaryFromString:(NSString*)string separatedBy:(char)sep;
+ (NSString*)base64Encode:(NSString*)string;
+ (NSString*)base64Encode:(NSString*)string withLineLength:(unsigned int)lineLength;
+ (unsigned int)hexValue:(NSString*)string;

@end
