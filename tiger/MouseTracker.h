/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSView;

@interface MouseTracker : NSObject
{
    NSView *_view;
    struct _NSRect _trackingRect;
    int _trackingRectTag;
    BOOL _mouseOver;
    id _delegate;
}

- (void)_updateMouseIsOver;
- (void)dealloc;
- (id)initWithTrackingRect:(struct _NSRect)fp8 inView:(id)fp24;
- (void)mouseEntered:(id)fp8;
- (void)mouseExited:(id)fp8;
- (void)mouseMoved:(id)fp8;
- (BOOL)mouseOver;
- (void)setDelegate:(id)fp8;
- (struct _NSRect)trackingRect;
- (id)view;

@end

