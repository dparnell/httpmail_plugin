/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class LibraryIMAPStore, NSMutableArray;

@interface _LibraryThreadRequest : NSObject
{
    NSMutableArray *messages;
    LibraryIMAPStore *store;
    BOOL isFollowOnToProgressTask;
}

- (void)dealloc;

@end

