/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "ComposeBackEnd.h"

@class MessageTextStorage;

@interface ComposeBackEnd_Scripting : ComposeBackEnd
{
    MessageTextStorage *_textStorage;
}

- (id)init;
- (void)dealloc;
- (void)setTextStorage:(id)fp8;
- (id)textStorage;
- (id)content;
- (void)setContent:(id)fp8;
- (void)_pushTextStorage;
- (void)_convertTextStorage;
- (void)_coalescedConvertTextStorage;

@end

