/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSArray;

@interface TextEncodingMenuDelegate : NSObject
{
    NSArray *_displayedCharsets;
}

- (void)dealloc;
- (id)displayedCharsets;
- (BOOL)menuHasKeyEquivalent:(id)fp8 forEvent:(id)fp12 target:(id *)fp16 action:(SEL *)fp20;
- (void)menuNeedsUpdate:(id)fp8;
- (void)setDisplayedCharsets:(id)fp8;

@end

