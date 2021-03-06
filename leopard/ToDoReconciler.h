/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSConditionLock, NSLock, NSMutableDictionary;

@interface ToDoReconciler : NSObject
{
    NSMutableDictionary *_reconciliationAgentsData;
    int _reconcilerPhase;
    unsigned int _identifier;
    // Error parsing type: @"<ReconciliationMechanism>", name: _mechanism
    unsigned int _numAgentsCompleteForPhase;
    NSConditionLock *_agentConditionLock;
    BOOL _requestsPending;
    BOOL _isReconciling;
    NSLock *_reconcilerBusyLock;
}

+ (id)reconcilerForID:(unsigned int)fp8;
- (id)init;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)retain;
- (unsigned int)retainCount;
- (void)release;
- (id)autorelease;
- (void)dealloc;
- (void)requestReconciliation:(id)fp8;

@end

