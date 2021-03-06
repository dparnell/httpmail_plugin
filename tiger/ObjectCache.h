/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@interface ObjectCache : NSObject
{
    unsigned int _arrayCapacity;
    struct __CFArray *_keysAndValues;
    BOOL _useIsEqual;
}

- (void)dealloc;
- (void)finalize;
- (id)initWithCapacity:(unsigned int)fp8;
- (BOOL)isObjectInCache:(id)fp8;
- (id)objectForKey:(id)fp8;
- (void)removeAllObjects;
- (void)removeObjectForKey:(id)fp8;
- (void)setCapacity:(unsigned int)fp8;
- (void)setObject:(id)fp8 forKey:(id)fp12;
- (void)setUsesIsEqualForComparison:(BOOL)fp8;

@end

