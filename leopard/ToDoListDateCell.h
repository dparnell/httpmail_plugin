/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSTextFieldCell.h"

@class NSCell, NSPopUpButtonCell;

@interface ToDoListDateCell : NSTextFieldCell
{
    NSCell *textCell;
    NSPopUpButtonCell *buttonCell;
    BOOL _mouseDownInButton;
    BOOL _hasKeyboardFocus;
    BOOL _hasMouseFocus;
}

+ (BOOL)prefersTrackingUntilMouseUp;
- (id)initTextCell:(id)fp8;
- (void)awakeFromNib;
- (void)_generalInit;
- (void)dealloc;
- (id)placeholderString;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (BOOL)hasFocus;
- (BOOL)hasKeyboardFocus;
- (void)setHasKeyboardFocus:(BOOL)fp8;
- (BOOL)hasMouseFocus;
- (void)setHasMouseFocus:(BOOL)fp8;
- (void)setMenu:(id)fp8;
- (void)setLineBreakMode:(unsigned int)fp8;
- (void)setAlignment:(unsigned int)fp8;
- (void)setBackgroundStyle:(int)fp8;
- (void)setControlSize:(unsigned int)fp8;
- (void)setEnabled:(BOOL)fp8;
- (void)setFont:(id)fp8;
- (id)_indicatorImage;
- (void)resetWidths;
- (BOOL)drawsBackground;
- (void)updateFormatterForWidth:(float)fp8;
- (struct _NSRect)titleRectForBounds:(struct _NSRect)fp8;
- (struct _NSRect)buttonRectForBounds:(struct _NSRect)fp8;
- (void)drawInteriorWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (void)editWithFrame:(struct _NSRect)fp8 inView:(id)fp24 editor:(id)fp28 delegate:(id)fp32 event:(id)fp36;
- (void)selectWithFrame:(struct _NSRect)fp8 inView:(id)fp24 editor:(id)fp28 delegate:(id)fp32 start:(int)fp36 length:(int)fp40;
- (struct _NSRect)buttonHitTestRectForRect:(struct _NSRect)fp8;
- (unsigned int)hitTestForEvent:(id)fp8 inRect:(struct _NSRect)fp12 ofView:(id)fp28;
- (void)addTrackingAreasForView:(id)fp8 inRect:(struct _NSRect)fp12 withUserInfo:(id)fp28 mouseLocation:(struct _NSPoint)fp32;
- (void)mouseEntered:(id)fp8;
- (void)mouseExited:(id)fp8;
- (BOOL)trackMouse:(id)fp8 inRect:(struct _NSRect)fp12 ofView:(id)fp28 untilMouseUp:(BOOL)fp32;
- (id)menuForEvent:(id)fp8 inRect:(struct _NSRect)fp12 ofView:(id)fp28;
- (void)accessibilityPerformAction:(id)fp8;

@end

