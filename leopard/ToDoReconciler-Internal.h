/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/ToDoReconciler.h>

@interface ToDoReconciler (Internal)
+ (id)objectAsKey:(id)fp8;
- (id)_initWithID:(unsigned int)fp8;
- (BOOL)addAgent:(id)fp8;
- (void)removeAgent:(id)fp8;
- (void)setState:(int)fp8 forAgent:(id)fp12;
- (void)_triggerAgentsForPhase;
- (void)_reconcile;
@end

