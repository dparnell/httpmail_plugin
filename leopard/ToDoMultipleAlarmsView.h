/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSView.h"

@class NSMutableArray;

@interface ToDoMultipleAlarmsView : NSView
{
    NSMutableArray *_alarmViews;
    BOOL _collapsed;
    BOOL _enabled;
    BOOL _reLayoutEnabled;
    id _controller;
    NSView *_followingKeyView;
}

- (id)initWithFrame:(struct _NSRect)fp8;
- (void)dealloc;
- (void)drawRect:(struct _NSRect)fp8;
- (struct _NSRect)bounds;
- (struct _NSRect)frame;
- (id)alarms;
- (void)setAlarms:(id)fp8;
- (unsigned int)indexOfAlarmView:(id)fp8;
- (void)removeAlarmViewOnly:(id)fp8;
- (BOOL)collapsed;
- (void)setCollapsed:(BOOL)fp8;
- (BOOL)enabled;
- (void)setEnabled:(BOOL)fp8;
- (BOOL)reLayoutEnabled;
- (void)setReLayoutEnabled:(BOOL)fp8;
- (void)alarmSubViewLayoutChanged:(id)fp8;
- (void)reLayout;

@end

