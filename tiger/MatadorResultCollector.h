/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class MessageCriterion, NSMutableSet;

@interface MatadorResultCollector : NSObject
{
    MessageCriterion *criterion;
    id target;
    struct __MDQuery *query;
    NSMutableSet *seenItems;
    unsigned int options;
}

- (void)dealloc;
- (void)finalize;
- (id)initWithCriterion:(id)fp8 target:(id)fp12 query:(struct __MDQuery *)fp16;

@end

