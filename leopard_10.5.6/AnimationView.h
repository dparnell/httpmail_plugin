/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSView.h"

@class CIContext, StationeryAnimator;

@interface AnimationView : NSView
{
    CIContext *drawingContext;
    StationeryAnimator *animator;
}

- (void)dealloc;
- (void)reset;
- (void)setAnimator:(id)fp8;
- (void)drawRect:(struct _NSRect)fp8;

@end

