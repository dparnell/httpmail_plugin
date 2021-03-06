/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSTextField.h"

@interface AutosizingTextField : NSTextField
{
    float _minimumHeight;
}

- (void)_editorResized;
- (void)_adjustWidth:(float)fp8 ofEditor:(id)fp12;
- (void)_adjustWidthBy:(float)fp8;
- (void)setFrameSize:(struct _NSSize)fp8;
- (void)resizeWithOldSuperviewSize:(struct _NSSize)fp8;
- (void)sizeToFit;
- (void)_setupTextView:(id)fp8;
- (void)didAddSubview:(id)fp8;
- (void)willRemoveSubview:(id)fp8;
- (float)minimumHeight;
- (void)setMinimumHeight:(float)fp8;
- (void)dealloc;

@end

