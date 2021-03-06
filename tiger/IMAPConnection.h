/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/Connection.h>

@class NSMutableData, NSMutableSet, NSString;

@interface IMAPConnection : Connection
{
    id _delegate;
    id _mailboxListFilter;
    unsigned int _delegateShouldHandleUntaggedResponse:1;
    unsigned int _delegateDidReceiveResponse:1;
    unsigned int _delegateDidFinishSelect:1;
    unsigned int _delegateDidDisconnect:1;
    unsigned int _capabilityFlags:10;
    unsigned int _connectionState:3;
    NSString *_separatorChar;
    NSString *_serverPathPrefix;
    NSString *_selectedMailbox;
    NSMutableSet *_capabilities;
    unsigned int _commandNumber;
    NSMutableData *_data;
    unsigned int _readBufferSize;
    double _expirationTime;
}

+ (void)initialize;
+ (void)setReadSizeParameters;
- (id)_copyNextServerResponseForCommand:(CDAnonymousStruct7 *)fp8;
- (id)_copyNextTaggedOrContinuationResponseForCommand:(CDAnonymousStruct7 *)fp8;
- (BOOL)_doBasicConnectionUsingAccount:(id)fp8;
- (id)_doListCommand:(int)fp8 withReference:(id)fp12 mailboxName:(id)fp16 options:(int)fp20;
- (BOOL)_doUidFetchWithRange:(CDAnonymousStruct9)fp8 arguments:(id)fp16 validateMessage:(BOOL)fp20 responses:(id)fp24;
- (id)_errorForResponse:(id)fp8 commandParams:(CDAnonymousStruct7 *)fp12;
- (id)_headersToFetchIncludingThoseRequiredForRouting:(BOOL)fp8;
- (id)_responseFromSendingCommand:(CDAnonymousStruct7 *)fp8 andPossiblyCreateMailbox:(id)fp12;
- (unsigned int)_sendCommands:(CDAnonymousStruct7 *)fp8 count:(unsigned int)fp12 response:(id *)fp16;
- (BOOL)_sendMailboxCommand:(int)fp8 withArguments:(id)fp12;
- (BOOL)appendData:(id)fp8 toMailboxNamed:(id)fp12 flags:(id)fp16 dateReceived:(id)fp20 newMessageInfo:(id *)fp24;
- (BOOL)authenticateUsingAccount:(id)fp8;
- (BOOL)authenticateUsingAccount:(id)fp8 authenticator:(id)fp12;
- (id)capabilities;
- (void)close;
- (void)closeAndLogout;
- (BOOL)connectUsingAccount:(id)fp8;
- (int)connectionState;
- (BOOL)copyUids:(id)fp8 toMailboxNamed:(id)fp12 newMessageInfo:(id *)fp16;
- (BOOL)createMailbox:(id)fp8;
- (void)dealloc;
- (id)delegate;
- (BOOL)deleteMailbox:(id)fp8;
- (BOOL)deleteMessagesOlderThanNumberOfDays:(int)fp8;
- (id)description;
- (void)disconnect;
- (void)disconnectAndNotifyDelegate:(BOOL)fp8;
- (BOOL)examineMailbox:(id)fp8;
- (BOOL)expunge;
- (BOOL)expungeUids:(id)fp8;
- (id)fetchArgumentForMessageSkeletons;
- (id)fetchHeadersForUid:(unsigned long)fp8;
- (id)fetchInternalDateForUids:(id)fp8;
- (id)fetchMessageIDHeaderForUids:(id)fp8;
- (void)fetchQuotaRootNamesForMailboxes:(id)fp8;
- (void)fetchStatusForMailboxes:(id)fp8 args:(id)fp12;
- (void)fetchTotalSize:(unsigned long long *)fp8 andMessageCount:(unsigned int *)fp12;
- (void)finalize;
- (BOOL)getQuotaForRootName:(id)fp8;
- (id)init;
- (BOOL)isValid;
- (id)listingForMailbox:(id)fp8 options:(int)fp12;
- (void)lock;
- (BOOL)loginWithAccount:(id)fp8 password:(id)fp12;
- (BOOL)logout;
- (id)mailboxListFilter;
- (id)messageSetForNumbers:(id)fp8 range:(struct _NSRange)fp12;
- (id)messageSetForRange:(CDAnonymousStruct9)fp8;
- (void)noop;
- (id)parenthesizedStringWithObjects:(id)fp8;
- (unsigned int)readBufferSize;
- (BOOL)renameMailbox:(id)fp8 toMailbox:(id)fp12;
- (int)searchCount:(id)fp8;
- (id)searchUidSet:(id)fp8 forNewMessageIDs:(id)fp12;
- (id)searchUidSet:(id)fp8 forTerms:(id)fp12;
- (BOOL)selectMailbox:(id)fp8;
- (id)selectedMailbox;
- (id)separatorChar;
- (void)setDelegate:(id)fp8;
- (void)setMailboxListFilter:(id)fp8;
- (void)setReadBufferSize:(unsigned int)fp8;
- (void)setReadBufferSizeFromElapsedTime:(double)fp8 bytesRead:(unsigned int)fp16;
- (BOOL)startTLSForAccount:(id)fp8;
- (id)statusForMailbox:(id)fp8 args:(id)fp12;
- (BOOL)storeFlags:(id)fp8 state:(BOOL)fp12 forUids:(id)fp16;
- (id)subscribedListingForMailbox:(id)fp8 options:(int)fp12;
- (BOOL)supportsCapability:(int)fp8;
- (void)unselect;

@end

