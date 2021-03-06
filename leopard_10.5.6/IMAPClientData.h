/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSMutableData, NSMutableString;

@interface IMAPClientData : NSObject
{
    NSMutableData *_data;
    NSMutableString *_commandString;
    IMAPClientData *_nextData;
    struct _NSRange _dontLogRange;
    BOOL _isFrozen;
}

- (void)dealloc;
- (id)initWithData:(id)fp8;
- (id)initWithStringWaitingForArguments:(id)fp8;
- (void)addStringArgument:(id)fp8;
- (void)addDataArgument:(id)fp8 literalPlus:(BOOL)fp12;
- (void)freeze;
- (BOOL)isFrozen;
- (void)setIsFrozen:(BOOL)fp8;
- (struct _NSRange)dontLogRange;
- (void)setDontLogRange:(struct _NSRange)fp8;
- (id)nextData;
- (void)setNextData:(id)fp8;
- (id)commandString;
- (void)setCommandString:(id)fp8;
- (id)data;
- (void)setData:(id)fp8;

@end

