/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSAppleScript.h"

@interface NSAppleScript (MessageRuleAdditions)
+ (id)_createScriptAtPath:(id)fp8 errorInfo:(id *)fp12;
+ (id)appleScriptLock;
+ (BOOL)executeHandlerWithEventClass:(unsigned long)fp8 eventID:(unsigned long)fp12 inScriptAtPath:(id)fp16 withArguments:(id)fp20 error:(id *)fp24;
+ (BOOL)executeHandlerWithName:(id)fp8 inScriptAtPath:(id)fp12 withArguments:(id)fp16 error:(id *)fp20;
- (id)executeHandlerWithEventClass:(unsigned long)fp8 eventID:(unsigned long)fp12 andArguments:(id)fp16 error:(id *)fp20;
- (id)executeHandlerWithName:(id)fp8 andArguments:(id)fp12 error:(id *)fp16;
@end

