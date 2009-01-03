/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "EventDelegateWindow.h"

@interface ChildWindow : EventDelegateWindow
{
    BOOL canBecomeKeyWindow;
    BOOL canBecomeMainWindow;
}

- (id)initWithContentRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(unsigned int)fp28 defer:(BOOL)fp32;
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
- (void)setCanBecomeKeyWindow:(BOOL)fp8;
- (void)setCanBecomeMainWindow:(BOOL)fp8;

@end

