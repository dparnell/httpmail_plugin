/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/Message.h>

@class MessageBody, MutableMessageHeaders, NSData, NSString;

@interface OutgoingMessage : Message
{
    NSData *rawData;
    NSString *remoteID;
    unsigned int bodyOffset;
    unsigned int localAttachmentsSize;
    MessageBody *messageBody;
    MutableMessageHeaders *messageHeaders;
}

- (void)dealloc;
- (id)bodyData;
- (id)messageStore;
- (id)messageBody;
- (id)messageBodyIfAvailable;
- (id)messageDataIncludingFromSpace:(BOOL)fp8 newDocumentID:(id)fp12;
- (id)messageDataIncludingFromSpace:(BOOL)fp8;
- (id)mutableHeaders;
- (void)setMutableHeaders:(id)fp8;
- (id)headers;
- (id)headersIfAvailable;
- (unsigned int)messageSize;
- (void)setRawData:(id)fp8 offsetOfBody:(unsigned int)fp12;
- (void)setLocalAttachmentsSize:(unsigned int)fp8;
- (void)setRemoteID:(id)fp8;
- (id)remoteID;

@end

