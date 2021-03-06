/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSTextView.h"

@class NSImage, NSMutableArray;

@interface MessageHeaderView : NSTextView
{
    NSMutableArray *trackingRectTags;
    BOOL isTrackingMouse;
    NSImage *_backgroundImageCap;
    NSImage *_tilingBackgroundImage;
}

- (void)awakeFromNib;
- (void)dealloc;
- (void)_certificateSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)_securityButtonClicked:(id)fp8;
- (void)keyDown:(id)fp8;
- (void)mouseDown:(id)fp8;
- (void)trackHeaderAddresses:(id)fp8 replacingPreviousAddresses:(BOOL)fp12;
- (void)addressAtomsWereUpdated:(id)fp8;
- (void)addressAttachmentSizeChanged:(id)fp8;
- (void)addressAppearanceChanged:(id)fp8;
- (void)setSelectedRange:(struct _NSRange)fp8 affinity:(unsigned int)fp16 stillSelecting:(BOOL)fp20;
- (void)setSelectedRange:(struct _NSRange)fp8;
- (struct _NSRange)selectionRangeForProposedRange:(struct _NSRange)fp8 granularity:(unsigned int)fp16;
- (void)setTilingBackgroundImage:(id)fp8;
- (id)tilingBackgroundImage;
- (void)setBackgroundImageCap:(id)fp8;
- (id)backgroundImageCap;
- (struct _NSRect)_cellFrameForAttachment:(id)fp8 atCharIndex:(int)fp12;
- (void)_removeCursorRects;
- (void)resetCursorRects;
- (void)viewWillMoveToWindow:(id)fp8;
- (void)viewDidMoveToWindow;
- (void)didChangeText;
- (id)writablePasteboardTypes;
- (BOOL)writeSelectionToPasteboard:(id)fp8 type:(id)fp12;
- (id)menuForEvent:(id)fp8;
- (id)attachmentForPoint:(struct _NSPoint)fp8;
- (id)attachmentForEvent:(id)fp8;
- (id)undoManager;
- (BOOL)accessibilityIsIgnored;
- (id)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(id)fp8;
- (BOOL)accessibilityIsAttributeSettable:(id)fp8;

@end

