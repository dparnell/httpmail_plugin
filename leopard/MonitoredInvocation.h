/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSInvocation.h"

@class ActivityMonitor;

@interface MonitoredInvocation : NSInvocation
{
    ActivityMonitor *_monitor;
}

+ (id)invocationWithSelector:(SEL)fp8 target:(id)fp12 taskName:(id)fp16 priority:(unsigned char)fp20 canBeCancelled:(BOOL)fp24;
+ (id)invocationWithSelector:(SEL)fp8 target:(id)fp12 object:(id)fp16 taskName:(id)fp20 priority:(unsigned char)fp24 canBeCancelled:(BOOL)fp28;
+ (id)invocationWithSelector:(SEL)fp8 target:(id)fp12 object1:(id)fp16 object2:(id)fp20 taskName:(id)fp24 priority:(unsigned char)fp28 canBeCancelled:(BOOL)fp32;
+ (id)invocationWithSelector:(SEL)fp8 target:(id)fp12 object1:(id)fp16 object2:(id)fp20 object3:(id)fp24 taskName:(id)fp28 priority:(unsigned char)fp32 canBeCancelled:(BOOL)fp36;
- (void)dealloc;
- (void)finalize;
- (id)monitor;
- (void)setMonitor:(id)fp8;
- (void)invoke;

@end

