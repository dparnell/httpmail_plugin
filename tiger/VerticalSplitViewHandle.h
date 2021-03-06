/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSView.h"

#import "SplitHandleProtocolProtocol.h"

@class MailVerticalSplitView, NSImage;

@interface VerticalSplitViewHandle : NSView <SplitHandleProtocol>
{
    MailVerticalSplitView *splitView;
    NSImage *image;
    BOOL drawShadowAtLeft;
    BOOL drawsShadowAtAll;
    NSImage *shadow;
}

- (void)dealloc;
- (void)drawRect:(struct _NSRect)fp8;
- (float)handleWidth;
- (id)initWithFrame:(struct _NSRect)fp8;
- (BOOL)isOpaque;
- (void)mouseDown:(id)fp8;
- (void)resetCursorRects;
- (void)setDrawShadowAtLeft:(BOOL)fp8;
- (void)setDrawsShadow:(BOOL)fp8;
- (void)setSplitView:(id)fp8;

@end

