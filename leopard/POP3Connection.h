/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/Connection.h>

@class NSData, NSMutableData;

@interface POP3Connection : Connection
{
    NSMutableData *_sendBuffer;
    struct __CFDictionary *_listResults;
    NSData *_apopTimeStamp;
    id _delegate;
    unsigned int _numberOfMessagesAvailable:24;
    unsigned int _state:4;
    unsigned int _delegateRespondsToReceivedNumberOfBytes:1;
    unsigned int _delegateRespondsToWillRetrieveMessageNumber:1;
    unsigned int _delegateRespondsToDidRetrieveMessageNumber:1;
    unsigned int _connectionShouldPrefetchMessages:1;
    unsigned int _hidingPassword:1;
}

- (id)init;
- (void)dealloc;
- (void)finalize;
- (id)capabilities;
- (id)authenticationMechanisms;
- (BOOL)_teardownConnectionWithResult:(BOOL)fp8;
- (BOOL)authenticateUsingAccount:(id)fp8;
- (BOOL)_authenticateUsingAccount:(id)fp8 authenticator:(id)fp12;
- (int)_authenticateUsingHostname:(id)fp8 username:(id)fp12 password:(id)fp16 authenticator:(id)fp20;
- (int)_authenticateWithUsername:(id)fp8 password:(id)fp12;
- (int)quit;
- (BOOL)supportsAPOP;
- (void)disableAPOP;
- (int)doStat;
- (int)list:(int)fp8;
- (int)_getListResults;
- (int)getMessageNumbers:(const struct __CFArray **)fp8 andMessageIdsByNumber:(const struct __CFDictionary **)fp12;
- (id)idForMessageNumber:(int)fp8;
- (id)_retrieveMessage:(unsigned long)fp8 ofSize:(unsigned int)fp12 informDelegate:(BOOL)fp16;
- (int)retr:(unsigned long)fp8;
- (int)dele:(unsigned long)fp8;
- (id)retainedMessageHeaderForMessageNumber:(unsigned long)fp8;
- (void)getTopOfMessageNumber:(unsigned long)fp8 intoMutableData:(id)fp12;
- (unsigned long)sizeOfMessageNumber:(unsigned long)fp8;
- (BOOL)messagesAvailable;
- (unsigned int)numberOfMessagesAvailable;
- (int)fetchMessages:(struct __CFArray *)fp8;
- (int)deleteMessagesOnServer:(struct __CFArray *)fp8;
- (void)setDelegate:(id)fp8;
- (id)delegate;
- (int)_startTLSForSecurityLayerType:(int)fp8;

@end

