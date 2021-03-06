/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSTextView.h"

@class NSMutableArray;

@interface MessageHeaderView : NSTextView
{
    NSMutableArray *trackingRectTags;
    BOOL isTrackingMouse;
}

- (struct _NSRect)_cellFrameForAttachment:(id)fp8 atCharIndex:(int)fp12;
- (void)_removeCursorRects;
- (void)addressAppearanceChanged:(id)fp8;
- (void)addressAtomsWereUpdated:(id)fp8;
- (void)addressAttachmentSizeChanged:(id)fp8;
- (id)attachmentForEvent:(id)fp8;
- (id)attachmentForPoint:(struct _NSPoint)fp8;
- (void)awakeFromNib;
- (void)dealloc;
- (void)didChangeText;
- (id)dragImageForSelectionWithEvent:(id)fp8 origin:(struct _NSPoint *)fp12;
- (void)keyDown:(id)fp8;
- (id)menuForEvent:(id)fp8;
- (void)mouseDown:(id)fp8;
- (id)originalDragImageForSelectionWithEvent:(id)fp8 origin:(struct _NSPoint *)fp12;
- (void)originalSelectAll:(id)fp8;
- (void)resetCursorRects;
- (void)selectAll:(id)fp8;
- (struct _NSRange)selectionRangeForProposedRange:(struct _NSRange)fp8 granularity:(int)fp16;
- (void)setSelectedRange:(struct _NSRange)fp8;
- (void)setSelectedRange:(struct _NSRange)fp8 affinity:(int)fp16 stillSelecting:(BOOL)fp20;
- (void)trackHeaderAddresses:(id)fp8 replacingPreviousAddresses:(BOOL)fp12;
- (void)viewDidMoveToWindow;
- (void)viewWillMoveToWindow:(id)fp8;
- (id)writablePasteboardTypes;
- (BOOL)writeSelectionToPasteboard:(id)fp8 type:(id)fp12;

@end

