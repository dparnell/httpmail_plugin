/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSView.h"

@class NSMutableSet;

@interface MailVerticalSplitView : NSView
{
    NSMutableSet *collapsedSubviews;
    id delegate;
    BOOL isPaneSplitter;
    BOOL adjustSubviewsBeforeDrawing;
}

- (id)initWithFrame:(struct _NSRect)fp8;
- (void)dealloc;
- (void)setIsPaneSplitter:(BOOL)fp8;
- (BOOL)isPaneSplitter;
- (BOOL)isVertical;
- (void)setDelegate:(id)fp8;
- (id)delegate;
- (float)maximumAllowedWidthForFirstSubview;
- (void)adjustSubviews;
- (void)adjustSubviewsToNewSecondaryWidth:(float)fp8 byAnimating:(BOOL)fp12;
- (float)dividerThickness;
- (BOOL)isSubviewCollapsed:(id)fp8;
- (BOOL)acceptsFirstMouse:(id)fp8;
- (void)didAddSubview:(id)fp8;
- (struct _NSRect)dividerFrame;
- (struct _NSRect)cursorRectFrame;
- (float)dividerPosition;
- (void)drawRect:(struct _NSRect)fp8;
- (BOOL)isFlipped;
- (BOOL)isOpaque;
- (CDAnonymousStruct2)_dividerDragParamsForIndex:(unsigned int)fp8 originalPosition:(float)fp12;
- (CDAnonymousStruct1)_resultOfDividerDragToPosition:(float)fp8 withParams:(const CDAnonymousStruct2 *)fp12;
- (void)_presentDividerDragResult:(const CDAnonymousStruct1 *)fp8 withParams:(const CDAnonymousStruct2 *)fp12;
- (id)hitTest:(struct _NSPoint)fp8;
- (void)mimicDoubleClickOnDivider;
- (void)mouseDown:(id)fp8;
- (CDAnonymousStruct2)beginDividerDragging;
- (void)dragDividerToLocation:(float)fp8 withInfo:(CDAnonymousStruct2)fp12;
- (void)endDividerDragging;
- (BOOL)mouseDownCanMoveWindow;
- (void)resetCursorRects;
- (void)replaceSubview:(id)fp8 with:(id)fp12;
- (void)resizeSubviewsWithOldSize:(struct _NSSize)fp8;
- (void)setAutoresizesSubviews:(BOOL)fp8;
- (BOOL)shouldBeTreatedAsInkEvent:(id)fp8;
- (void)willRemoveSubview:(id)fp8;
- (id)description;

@end

