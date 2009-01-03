/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/MessageRule.h>

@interface MessageRule (Applescript)
- (void)updateIsActive;
- (int)actionColorMessage;
- (void)setActionColorMessage:(int)fp8;
- (int)highlightColorValue:(id)fp8;
- (BOOL)actionDeleteMessage;
- (void)setActionDeleteMessage:(BOOL)fp8;
- (id)actionForwardToAddress;
- (void)setActionForwardToAddress:(id)fp8;
- (id)actionForwardText;
- (void)setActionForwardText:(id)fp8;
- (BOOL)actionMarkAsFlagged;
- (void)setActionMarkAsFlagged:(BOOL)fp8;
- (BOOL)actionMarkAsRead;
- (void)setActionMarkAsRead:(BOOL)fp8;
- (id)actionPlaySound;
- (void)setActionPlaySound:(id)fp8;
- (id)actionRedirectToAddress;
- (void)setActionRedirectToAddress:(id)fp8;
- (id)actionReplyText;
- (void)setActionReplyText:(id)fp8;
- (id)actionRunApplescript;
- (void)setActionRunApplescript:(id)fp8;
- (id)ruleDescription;
- (void)setRuleDescription:(id)fp8;
- (void)insertInCriteria:(id)fp8 atIndex:(unsigned int)fp12;
- (void)insertInCriteria:(id)fp8;
- (void)removeFromCriteriaAtIndex:(unsigned int)fp8;
- (void)setAddress:(id)fp8 forResponseType:(int)fp12;
@end

