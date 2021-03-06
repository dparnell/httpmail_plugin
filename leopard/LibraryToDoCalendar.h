/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/ToDoCalendar.h>

#import "NSCopyingProtocol.h"

@interface LibraryToDoCalendar : ToDoCalendar <NSCopying>
{
    unsigned int _libraryID;
}

- (unsigned int)libraryID;
- (void)setLibraryID:(unsigned int)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (unsigned long)libraryFlags;
- (void)setLibraryFlags:(unsigned long)fp8;
- (BOOL)hasBeenStoredInDatabase;

@end

