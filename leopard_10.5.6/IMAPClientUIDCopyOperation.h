/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/IMAPClientUIDOperation.h>

@class NSDictionary, NSString;

@interface IMAPClientUIDCopyOperation : IMAPClientUIDOperation
{
    NSString *_copyMailboxName;
    NSString *_copyMailboxArgumentName;
    NSDictionary *_newMessageInfo;
    BOOL _shouldTryCreate;
}

- (void)dealloc;
- (id)initWithMailboxName:(id)fp8 UIDs:(id)fp12 destinationMailboxName:(id)fp16;
- (const char *)commandTypeCString;
- (id)detailsString;
- (id)createCommandDataForLiteralPlus:(BOOL)fp8;
- (BOOL)executeOnConnection:(id)fp8;
- (BOOL)shouldTryCreate;
- (void)setShouldTryCreate:(BOOL)fp8;
- (id)newMessageInfo;
- (void)setNewMessageInfo:(id)fp8;
- (id)copyMailboxArgumentName;
- (void)setCopyMailboxArgumentName:(id)fp8;
- (id)copyMailboxName;
- (void)setCopyMailboxName:(id)fp8;

@end

