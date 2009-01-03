/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject-Protocol.h"

@protocol CalendarStoreConduit <NSObject>
- (id)initWithToDosCache:(id)fp8 todoCalendars:(id)fp12;
- (void)initialSynchronization;
- (id)calTaskWithID:(id)fp8;
- (void)synchronize;
- (void)addToDo:(id)fp8;
- (void)saveToDo:(id)fp8;
- (void)removeToDo:(id)fp8;
- (void)addCalendar:(id)fp8;
- (void)saveCalendar:(id)fp8;
- (void)removeCalendar:(id)fp8;
- (void)addCalendarGroup:(id)fp8;
- (void)saveCalendarGroup:(id)fp8;
- (void)removeCalendarGroup:(id)fp8;
- (void)holdNotifications;
- (void)resumeNotifications;
- (void)recreateIMAPGroups:(id)fp8 calendars:(id)fp12 todos:(id)fp16;
@end
