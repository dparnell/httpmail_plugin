/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@interface SqliteHandle : NSObject
{
    struct sqlite3 *db;
}

+ (id)handleForDB:(struct sqlite3 *)fp8;

@end

