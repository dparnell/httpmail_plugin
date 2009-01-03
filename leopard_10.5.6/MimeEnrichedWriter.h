/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSAttributedString, NSFont, NSString;

@interface MimeEnrichedWriter : NSObject
{
    NSAttributedString *_attributedString;
    NSString *_string;
    CDAnonymousStruct5 _stringBuffer;
    NSFont *_defaultFont;
    NSFont *_defaultFixedPitchFont;
    float _defaultPointSize;
    struct _CommandStackEntry *_commandStack;
    struct _CommandStackEntry *_topOfStack;
    struct EnrichedState _currentState;
    unsigned int _currentLineStart;
    unsigned int _lastSpace;
}

+ (void)initialize;
- (void)setState:(struct EnrichedState *)fp8 fromAttributes:(id)fp12;
- (void)setState:(struct EnrichedState *)fp8 fromStackEntry:(struct _CommandStackEntry *)fp12;
- (void)dealloc;
- (void)finalize;
- (id)convertAttributedString:(id)fp8;
- (void)updateOutput:(id)fp8 forAttributes:(id)fp12 range:(struct _NSRange)fp16;
- (void)appendTextFromRange:(struct _NSRange)fp8 toString:(id)fp16;

@end

