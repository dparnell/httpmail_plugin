/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSMutableAttributedString.h"

@interface NSMutableAttributedString (MessageFrameworkAdditions)
- (void)removeTabs;
- (void)replaceCustomAttachmentAttributesWithAttachments:(id)fp8 confirmWithView:(id)fp12;
- (void)_removeAttachmentsAndReplaceWithCustomAttribute:(BOOL)fp8;
- (void)removeAllAttachmentsAndReplaceWithCustomAttachmentAttribute;
- (void)removeAllAttachments;
- (void)removeAllFormattingExceptAttachments;
- (void)removeQuotingDisplayAttributesInRange:(struct _NSRange)fp8;
- (void)fixQuotingDisplayAttributesInRange:(struct _NSRange)fp8;
- (void)changeQuoteLevelInRange:(struct _NSRange)fp8 by:(int)fp16 undoManager:(id)fp20;
@end

