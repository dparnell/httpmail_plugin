/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/ToDoAlarm.h>

#import "NSCopying-Protocol.h"

@interface LibraryToDoAlarm : ToDoAlarm <NSCopying>
{
    unsigned int _alarmLibraryID;
    unsigned int _todoLibraryID;
}

- (id)initWithAlarm:(id)fp8 todoLibraryID:(unsigned int)fp12;
- (id)initWithCalAlarm:(id)fp8 todoLibraryID:(unsigned int)fp12;
- (id)calAlarmFromToDoAlarm;
- (unsigned int)libraryID;
- (void)setLibraryID:(unsigned int)fp8;
- (unsigned int)todoLibraryID;
- (void)setToDoLibraryID:(unsigned int)fp8;
- (id)argument;
- (void)setArgument:(id)fp8;
- (unsigned long)libraryFlags;
- (void)setLibraryFlags:(unsigned long)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;

@end

