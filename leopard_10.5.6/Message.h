/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class MFUUID, MessageStore, NSData, NSString;

@interface Message : NSObject
{
    MessageStore *_store;
    unsigned int _messageFlags;
    CDAnonymousStruct6 _flags;
    unsigned int _preferredEncoding;
    NSString *_senderAddressComment;
    unsigned int _dateSentInterval;
    unsigned int _dateReceivedInterval;
    unsigned int _dateLastViewedInterval;
    NSString *_subject;
    unsigned char _subjectPrefixLength;
    NSString *_to;
    NSString *_sender;
    NSString *_author;
    NSData *_messageIDHeaderDigest;
    NSData *_inReplyToHeaderDigest;
    int _type;
    MFUUID *_documentID;
}

+ (void)initialize;
+ (id)verboseVersion;
+ (id)frameworkVersion;
+ (void)setUserAgent:(id)fp8;
+ (id)userAgent;
+ (id)messageWithRFC822Data:(id)fp8;
+ (id)forwardedMessagePrefixWithSpacer:(BOOL)fp8;
+ (id)replyPrefixWithSpacer:(BOOL)fp8;
+ (id)descriptionForType:(int)fp8 plural:(BOOL)fp12;
+ (id)messageTypeKeyForMessageType:(int)fp8;
+ (int)_messageTypeForMessageTypeKey:(id)fp8;
+ (id)unreadMessagesFromMessages:(id)fp8;
+ (BOOL)allMessages:(id)fp8 areSameType:(int)fp12;
+ (unsigned int)validatePriority:(int)fp8;
+ (unsigned int)displayablePriorityForPriority:(int)fp8;
+ (BOOL)isMessageURL:(id)fp8;
+ (id)messageWithURL:(id)fp8;
+ (id)messageWithPersistentID:(id)fp8;
- (id)init;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)messageStore;
- (void)setMessageStore:(id)fp8;
- (BOOL)messageStoreShouldBeSet;
- (id)mailbox;
- (id)headers;
- (id)headersIfAvailable;
- (int)type;
- (void)setType:(int)fp8;
- (BOOL)isEditable;
- (BOOL)isAnnotatable;
- (BOOL)isMetadataMessage;
- (id)documentID;
- (void)setDocumentID:(id)fp8;
- (unsigned long)messageFlags;
- (void)setMessageFlags:(unsigned long)fp8;
- (id)messageBody;
- (id)messageBodyIfAvailable;
- (id)messageBodyUpdatingFlags:(BOOL)fp8;
- (id)messageBodyForIndexingAttachments;
- (id)messageBodyIfAvailableUpdatingFlags:(BOOL)fp8;
- (id)messageDataIncludingFromSpace:(BOOL)fp8;
- (id)messageDataIncludingFromSpace:(BOOL)fp8 newDocumentID:(id)fp12;
- (BOOL)colorHasBeenEvaluated;
- (id)color;
- (BOOL)isMarkedForOverwrite;
- (void)setMarkedForOverwrite:(BOOL)fp8;
- (void)setColor:(id)fp8;
- (void)setColorHasBeenEvaluated:(BOOL)fp8;
- (void)setColor:(id)fp8 hasBeenEvaluated:(BOOL)fp12 flags:(unsigned long)fp16;
- (void)dealloc;
- (void)finalize;
- (unsigned int)messageSize;
- (id)attributedString;
- (id)preferredEmailAddressToReplyWith;
- (id)messageID;
- (id)messageIDHeaderDigest;
- (void)unlockedSetMessageIDHeaderDigest:(id)fp8;
- (void)setMessageIDHeaderDigest:(id)fp8;
- (id)_messageIDHeaderDigestIvar;
- (BOOL)needsMessageIDHeader;
- (id)inReplyToHeaderDigest;
- (void)unlockedSetInReplyToHeaderDigest:(id)fp8;
- (void)setInReplyToHeaderDigest:(id)fp8;
- (id)_inReplyToHeaderDigestIvar;
- (int)compareByNumberWithMessage:(id)fp8;
- (BOOL)isMessageContentsLocallyAvailable;
- (id)stringValueRenderMode:(int)fp8 updateBodyFlags:(BOOL)fp12 junkRecorder:(id)fp16;
- (id)stringForIndexing;
- (id)stringForIndexingUpdatingBodyFlags:(BOOL)fp8;
- (id)stringForJunk;
- (id)stringForJunk:(id)fp8;
- (BOOL)hasCalculatedNumberOfAttachments;
- (unsigned int)numberOfAttachments;
- (int)junkMailLevel;
- (void)setPriorityFromHeaders:(id)fp8;
- (int)priority;
- (unsigned long)preferredEncoding;
- (void)setPreferredEncoding:(unsigned long)fp8;
- (id)rawSourceFromHeaders:(id)fp8 body:(id)fp12;
- (BOOL)_doesDateAppearToBeSane:(id)fp8;
- (id)_createDateFromReceivedHeadersInHeaders:(id)fp8;
- (id)_createDateFromHeader:(id)fp8 inHeaders:(id)fp12;
- (id)_createDateFromDateHeaderInHeaders:(id)fp8;
- (id)_createDateFromCreatedDateHeaderInHeaders:(id)fp8;
- (void)_setDateReceivedFromHeaders:(id)fp8;
- (void)_setDateSentFromHeaders:(id)fp8;
- (void)loadCachedHeaderValuesFromHeaders:(id)fp8 type:(int)fp12;
- (id)subjectAndPrefixLength:(unsigned int *)fp8;
- (id)subjectNotIncludingReAndFwdPrefix;
- (id)subjectAddition;
- (id)subject;
- (void)setSubject:(id)fp8;
- (id)dateReceived;
- (id)dateSent;
- (void)setDateReceivedTimeIntervalSince1970:(double)fp8;
- (double)dateReceivedAsTimeIntervalSince1970;
- (BOOL)needsDateReceived;
- (double)dateSentAsTimeIntervalSince1970;
- (void)setDateSentTimeIntervalSince1970:(double)fp8;
- (id)dateLastViewed;
- (double)dateLastViewedAsTimeIntervalSince1970;
- (id)sender;
- (void)setSender:(id)fp8;
- (id)senderAddressComment;
- (id)to;
- (void)setTo:(id)fp8;
- (id)author;
- (void)setAuthor:(id)fp8;
- (void)setMessageInfo:(id)fp8 to:(id)fp12 sender:(id)fp16 type:(int)fp20 dateReceivedTimeIntervalSince1970:(double)fp24 dateSentTimeIntervalSince1970:(double)fp32 messageIDHeaderDigest:(id)fp40 inReplyToHeaderDigest:(id)fp44;
- (void)setMessageInfo:(id)fp8 to:(id)fp12 sender:(id)fp16 type:(int)fp20 dateReceivedTimeIntervalSince1970:(double)fp24 dateSentTimeIntervalSince1970:(double)fp32 messageIDHeaderDigest:(id)fp40 inReplyToHeaderDigest:(id)fp44 dateLastViewedTimeIntervalSince1970:(double)fp48;
- (void)setMessageInfoFromMessage:(id)fp8;
- (id)references;
- (id)note;
- (void)setNote:(id)fp8;
- (id)todos;
- (void)setTodos:(id)fp8;
- (id)remoteID;
- (unsigned long)uid;
- (CDAnonymousStruct6)moreMessageFlags;
- (id)path;
- (id)account;
- (void)markAsViewed;
- (id)remoteMailboxURL;
- (id)originalMailboxURL;
- (id)URL;
- (id)persistentID;
- (id)bodyData;
- (id)headerData;
- (id)dataForMimePart:(id)fp8;
- (BOOL)hasCachedDataForMimePart:(id)fp8;
- (id)matadorAttributes;
- (void)_calculateAttachmentInfoFromBody:(id)fp8;
- (void)forceSetAttachmentInfoFromBody:(id)fp8;
- (void)setAttachmentInfoFromBody:(id)fp8;
- (void)setAttachmentInfoFromBody:(id)fp8 forced:(BOOL)fp12;
- (BOOL)calculateAttachmentInfoFromBody:(id)fp8 numberOfAttachments:(unsigned int *)fp12 isSigned:(char *)fp16 isEncrypted:(char *)fp20;
- (BOOL)calculateAttachmentInfoFromBody:(id)fp8 numberOfAttachments:(unsigned int *)fp12 isSigned:(char *)fp16 isEncrypted:(char *)fp20 force:(BOOL)fp24;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(BOOL)fp12 isEncrypted:(BOOL)fp16;
- (double)dateCreatedAsTimeIntervalSince1970;
- (double)dateModifiedAsTimeIntervalSince1970;

@end

