/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSMutableDictionary;

@interface ChangeMerger : NSObject
{
    NSMutableDictionary *_adds;
    NSMutableDictionary *_updates;
    NSMutableDictionary *_deletes;
}

- (void)add:(id)fp8;
- (void)update:(id)fp8;
- (void)delete:(id)fp8;
- (id)addedObjects;
- (id)updatedObjects;
- (id)deletedObjects;
- (void)changesSaved;

@end

