/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSString, NSTimer;

@interface TemporaryItemManager : NSObject
{
    NSString *_path;
    NSTimer *_timer;
}

+ (void)cleanupAllItems;
+ (id)temporaryItemManagerWithRelativePath:(id)fp8 cleanupInterval:(double)fp12;
- (void)_setUpTimer:(id)fp8;
- (void)cleanUpDirectory;
- (void)dealloc;
- (id)expirationDate;
- (BOOL)fileManager:(id)fp8 shouldProceedAfterError:(id)fp12;
- (id)path;
- (void)setExpirationDate:(id)fp8;

@end

