/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSToolbarItem.h"

@class SegmentedToolbarItem;

@interface SegmentedToolbarItemSegmentItem : NSToolbarItem
{
    SegmentedToolbarItem *parent;
    int segmentNumber;
}

- (id)menuFormRepresentation;
- (void)setToolTip:(id)fp8;
- (void)_setToolTip:(id)fp8;
- (void)setTag:(int)fp8;
- (void)_setTag:(int)fp8;
- (void)setImage:(id)fp8;
- (int)segmentNumber;
- (void)setSegmentNumber:(int)fp8;
- (id)parent;
- (void)setParent:(id)fp8;

@end

