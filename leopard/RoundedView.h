/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSView.h"

@class NSColor;

@interface RoundedView : NSView
{
    NSColor *_backgroundColor;
    NSColor *_borderColor;
}

- (BOOL)isFlipped;
- (void)dealloc;
- (void)drawRect:(struct _NSRect)fp8;
- (id)backgroundColor;
- (void)setBackgroundColor:(id)fp8;
- (id)borderColor;
- (void)setBorderColor:(id)fp8;

@end

