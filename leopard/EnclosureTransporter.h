/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSString, NSURL;

@interface EnclosureTransporter : NSObject
{
    NSURL *URL;
    NSString *MIMEType;
    long long length;
}

- (void)dealloc;
- (id)initWithEnclosure:(id)fp8;
- (long long)length;
- (void)setLength:(long long)fp8;
- (id)MIMEType;
- (void)setMIMEType:(id)fp8;
- (id)URL;
- (void)setURL:(id)fp8;

@end

