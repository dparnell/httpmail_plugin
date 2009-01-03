/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSMutableArray, NSMutableDictionary, ToDoSnapshot;

@interface ToDoDifferenceAnalyzer : NSObject
{
    NSMutableDictionary *_differenceTable;
    int _conflictMode;
    NSMutableArray *_storeAdds;
    NSMutableArray *_storeDeletes;
    NSMutableArray *_storeUpdates;
    NSMutableArray *_storeUnknowns;
    NSMutableArray *_cacheAdds;
    NSMutableArray *_cacheDeletes;
    NSMutableArray *_cacheUpdates;
    NSMutableArray *_cacheUnknowns;
    id <ReconciliationAgent> _storeAgent;
    id <ReconciliationAgent> _cacheAgent;
    ToDoSnapshot *_storeSnapshot;
    ToDoSnapshot *_cacheSnapshot;
    unsigned int _mailboxID;
    BOOL _analyzed;
    BOOL _avoidAsserts;
}

- (id)initWithStoreAgent:(id)fp8 cacheAgent:(id)fp12 referenceSnapshot:(id)fp16;
- (void)dealloc;
- (void)analyze;
- (void)setConflictHandlingMode:(int)fp8;
- (id)storeAdds;
- (id)storeDeletes;
- (id)storeUpdates;
- (id)storeUnknowns;
- (id)cacheAdds;
- (id)cacheDeletes;
- (id)cacheUpdates;
- (id)cacheUnknowns;
- (id)diffTableDescription;
- (void)setAvoidAsserts:(BOOL)fp8;

@end

