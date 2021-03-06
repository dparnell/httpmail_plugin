/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSTextFieldCell.h"

@class NSCell;

@interface ToDoTitleCell : NSTextFieldCell
{
    NSCell *titleCell;
    NSCell *linkCell;
    BOOL _mouseDownInLinkButton;
    SEL _linkButtonAction;
    BOOL _expanding;
}

+ (BOOL)prefersTrackingUntilMouseUp;
- (id)initTextCell:(id)fp8;
- (void)awakeFromNib;
- (void)_generalInit;
- (void)setLineBreakMode:(unsigned int)fp8;
- (void)setAlignment:(unsigned int)fp8;
- (void)setFont:(id)fp8;
- (void)setBackgroundStyle:(int)fp8;
- (void)setEnabled:(BOOL)fp8;
- (void)dealloc;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (SEL)linkButtonAction;
- (void)setLinkButtonAction:(SEL)fp8;
- (struct _NSRect)linkButtonRectForBounds:(struct _NSRect)fp8;
- (struct _NSRect)titleRectForBounds:(struct _NSRect)fp8;
- (id)attributedTitle;
- (void)drawTitleWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (void)drawLinkButtonWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (void)drawInteriorWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (struct _NSRect)expansionFrameWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (void)drawWithExpansionFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (BOOL)trackMouse:(id)fp8 inRect:(struct _NSRect)fp12 ofView:(id)fp28 untilMouseUp:(BOOL)fp32;
- (unsigned int)hitTestForEvent:(id)fp8 inRect:(struct _NSRect)fp12 ofView:(id)fp28;
- (void)editWithFrame:(struct _NSRect)fp8 inView:(id)fp24 editor:(id)fp28 delegate:(id)fp32 event:(id)fp36;
- (void)selectWithFrame:(struct _NSRect)fp8 inView:(id)fp24 editor:(id)fp28 delegate:(id)fp32 start:(int)fp36 length:(int)fp40;
- (void)addTrackingAreasForView:(id)fp8 inRect:(struct _NSRect)fp12 withUserInfo:(id)fp28 mouseLocation:(struct _NSPoint)fp32;
- (void)mouseEntered:(id)fp8;
- (void)mouseExited:(id)fp8;
- (void)accessibilityPerformAction:(id)fp8;

@end

