/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSMatrix.h"

@interface ThumbnailMatrix : NSMatrix
{
    BOOL shouldShowButtons;
}

- (void)awakeFromNib;
- (void)highlightCell:(BOOL)fp8 atRow:(int)fp12 column:(int)fp16;
- (void)showDeleteButtons:(BOOL)fp8 beginningAtIndex:(int)fp12;
- (void)addButtonAtIndex:(int)fp8;
- (struct _NSRect)frameOfThumbnailAtIndex:(int)fp8;
- (BOOL)_performDragFromMouseDown:(id)fp8;

@end

