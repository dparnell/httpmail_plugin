/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "DynamicErrorWindowDelegateProtocol.h"

@class DatabaseRecoverer;

@interface BusyStatusErrorWindowDelegate : NSObject <DynamicErrorWindowDelegate>
{
    DatabaseRecoverer *_recoverer;
}

- (void)dealloc;
- (id)initWithRecoverer:(id)fp8;
- (BOOL)displayIndeterminateProgress;
- (id)errorMessageForErrorDiagnosis:(unsigned int)fp8;
- (id)errorDescriptionForErrorDiagnosis:(unsigned int)fp8;
- (id)leftButtonTextForErrorDiagnosis:(unsigned int)fp8;
- (id)rightButtonTextForErrorDiagnosis:(unsigned int)fp8;
- (void)leftActionSelectedWithDiagnosis:(unsigned int)fp8;
- (void)rightActionSelectedWithDiagnosis:(unsigned int)fp8;
- (unsigned int)helpTopicForDiagnosis:(unsigned int)fp8;
- (id)_stringForDatabase;
- (id)recoverer;
- (void)setRecoverer:(id)fp8;

@end

