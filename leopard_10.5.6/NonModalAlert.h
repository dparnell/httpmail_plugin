/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSPanel, NSTextField;

@interface NonModalAlert : NSObject
{
    id _representedObject;
    NSPanel *_panel;
    NSTextField *_title;
    NSTextField *_message;
}

+ (void)runNonModalForObject:(id)fp8 error:(id)fp12;
+ (void)dismissNonModalAlertForObject:(id)fp8;
- (void)dealloc;
- (id)initWithError:(id)fp8 representedObject:(id)fp12;
- (void)show;
- (id)representedObject;
- (void)okClicked:(id)fp8;

@end

