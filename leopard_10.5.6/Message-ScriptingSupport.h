/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/Message.h>

@interface Message (ScriptingSupport)
- (id)objectSpecifier;
- (void)_setAppleScriptFlag:(id)fp8 state:(BOOL)fp12;
- (BOOL)isRead;
- (void)setIsRead:(BOOL)fp8;
- (BOOL)wasRepliedTo;
- (void)setWasRepliedTo:(BOOL)fp8;
- (BOOL)wasForwarded;
- (void)setWasForwarded:(BOOL)fp8;
- (BOOL)wasRedirected;
- (void)setWasRedirected:(BOOL)fp8;
- (BOOL)isJunk;
- (void)setIsJunk:(BOOL)fp8;
- (BOOL)isDeleted;
- (void)setIsDeleted:(BOOL)fp8;
- (BOOL)isFlagged;
- (void)setIsFlagged:(BOOL)fp8;
- (id)replyTo;
- (id)scriptedMessageSize;
- (id)content;
- (void)_addRecipientsForKey:(id)fp8 toArray:(id)fp12;
- (id)recipients;
- (id)toRecipients;
- (id)ccRecipients;
- (id)bccRecipients;
- (id)container;
- (void)setContainer:(id)fp8;
- (id)messageIDHeader;
- (id)rawSource;
- (id)allHeaders;
- (int)actionColorMessage;
- (void)setBackgroundColor:(int)fp8;
- (int)backgroundColor;
- (id)appleScriptHeaders;
- (id)appleScriptAttachments;
- (id)valueInAppleScriptAttachmentsWithUniqueID:(id)fp8;
@end

