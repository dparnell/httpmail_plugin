/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@interface ToDoUndoCenter : NSObject
{
}

+ (id)sharedInstance;
+ (void)setDefaultCalendarFromToDo:(id)fp8 key:(id)fp12;
- (void)setValue:(id)fp8 forKey:(id)fp12 inToDo:(id)fp16 withUndoManager:(id)fp20;
- (void)setValue:(id)fp8 forKey:(id)fp12 inAlarm:(id)fp16 withUndoManager:(id)fp20;
- (void)addToDo:(id)fp8 withUndoManager:(id)fp12;
- (void)addToDos:(id)fp8 withUndoManager:(id)fp12;
- (void)deleteToDos:(id)fp8 withUndoManager:(id)fp12;
- (void)addAlarm:(id)fp8 toAlarms:(id)fp12 withUndoManager:(id)fp16;
- (void)insertAlarm:(id)fp8 atIndex:(unsigned int)fp12 intoAlarms:(id)fp16 withUndoManager:(id)fp20;
- (void)removeAlarmAtIndex:(unsigned int)fp8 fromAlarms:(id)fp12 withUndoManager:(id)fp16;
- (void)removeAlarm:(id)fp8 fromAlarms:(id)fp12 withUndoManager:(id)fp16;

@end

