/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class ISS_DMMemberAccount, NSDate, iToolsAccount;

@interface DocMacAliasUpdater : NSObject
{
    iToolsAccount *_account;
    ISS_DMMemberAccount *_dmAccount;
    id _delegate;
    int _state;
    NSDate *_syncDate;
}

- (id)_createDictionaryFromAlias:(id)fp8;
- (id)_aliasesFromXMLData:(id)fp8;
- (id)initWithIToolsAccount:(id)fp8;
- (void)dealloc;
- (void)setDelegate:(id)fp8;
- (id)delegate;
- (void)_transactionDidFinishWithError:(id)fp8;
- (void)fetchIfModifiedSinceLastUpdate;
- (id)account;
- (int)state;
- (void)transactionSuccessful:(id)fp8;
- (void)transactionHadError:(id)fp8;
- (void)transactionAborted:(id)fp8;

@end

