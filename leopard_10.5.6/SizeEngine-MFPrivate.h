/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/SizeEngine.h>

@interface SizeEngine (MFPrivate)
- (void)_lockedStartWorkerThreadIfNeeded;
- (void)_workerThreadFinished:(id)fp8;
- (void)_runWorkerThread;
- (BOOL)_prepareToRefresh;
- (BOOL)_shouldStartWorkerThread;
- (void)_postChangeNotificationWithUserInfo:(id)fp8;
@end
