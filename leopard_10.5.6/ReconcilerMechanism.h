/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

#import "ReconciliationMechanism-Protocol.h"

@interface ReconcilerMechanism : NSObject <ReconciliationMechanism>
{
    int _conflictMode;
}

- (id)init;
- (id)initWithConflictMode:(int)fp8;
- (void)dealloc;
- (void)performReconciliationForID:(unsigned int)fp8 usingAgents:(id)fp12;
- (BOOL)areAgentsValid:(id)fp8;

@end
