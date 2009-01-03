/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSTableHeaderCell.h"

@class MessageListCell, NSString;

@interface MessageListHeaderCell : NSTableHeaderCell
{
    MessageListCell *_realCell;
    unsigned int _imageAlignment;
    NSString *_accessibilityTitle;
}

- (void)dealloc;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (void)drawInteriorWithFrame:(struct _NSRect)fp8 inView:(id)fp24;
- (void)setImageAlignment:(unsigned int)fp8;
- (void)setAccessibilityTitle:(id)fp8;
- (id)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(id)fp8;
- (BOOL)accessibilityIsAttributeSettable:(id)fp8;

@end

