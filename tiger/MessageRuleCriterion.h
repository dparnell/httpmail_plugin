/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/MessageCriterion.h>

@class MessageRule;

@interface MessageRuleCriterion : MessageCriterion
{
    MessageRule *_rule;
}

- (id)objectSpecifier;
- (BOOL)performPostSyncingValidation;
- (void)setCriterionIdentifier:(id)fp8;
- (void)setMessageRule:(id)fp8;
- (void)setRuleExpression:(id)fp8;
- (void)setRuleQualifier:(int)fp8;
- (void)setRuleType:(int)fp8;

@end

