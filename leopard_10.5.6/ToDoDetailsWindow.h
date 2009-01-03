/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "ChildWindow.h"

@interface ToDoDetailsWindow : ChildWindow
{
    unsigned int _visualOrigin;
    float _scaleFactor;
    float _baseX;
    float _baseY;
}

- (void)finishInitialLayout;
- (void)selectKeyViewFollowingView:(id)fp8;
- (void)selectKeyViewPrecedingView:(id)fp8;
- (void)recalculateKeyViewLoop;
- (id)initWithContentRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(unsigned int)fp28 defer:(BOOL)fp32;
- (id)toDo;
- (void)setToDo:(id)fp8;
- (unsigned int)visualOrigin;
- (void)setVisualOrigin:(unsigned int)fp8;
- (BOOL)isVisualOriginTop;
- (BOOL)isVisualOriginLeft;
- (float)scaleFactor;
- (void)setScaleFactor:(float)fp8;
- (void)orderOut:(id)fp8;
- (void)setFrameOrigin:(struct _NSPoint)fp8;
- (id)accessibilityAttributeValue:(id)fp8;

@end

