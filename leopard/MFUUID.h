/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@interface MFUUID : NSObject
{
    struct __CFUUID *_uuidRef;
}

+ (id)uuid;
+ (id)uuidWithString:(id)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)init;
- (id)initWithString:(id)fp8;
- (id)initWithBytes:(CDAnonymousStruct8 *)fp8;
- (id)initWithUUIDRef:(struct __CFUUID *)fp8;
- (CDAnonymousStruct8)bytes;
- (unsigned int)length;
- (id)dataValue;
- (id)stringValue;
- (id)description;
- (BOOL)isEqual:(id)fp8;
- (BOOL)isEqualToString:(id)fp8;
- (unsigned int)hash;
- (void)dealloc;

@end

