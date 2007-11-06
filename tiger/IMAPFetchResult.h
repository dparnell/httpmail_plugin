/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSArray, NSData, NSDate, NSString;

@interface IMAPFetchResult : NSObject
{
    int _itemType;
    union {
        NSArray *envelope;
        NSDate *internalDate;
        unsigned int messageSize;
        NSArray *bodyStructure;
        struct {
            NSString *section;
            unsigned int startOffset;
            NSData *sectionData;
        } bodySectionInfo;
        unsigned int uid;
        NSArray *flags;
    } _typeSpecific;
}

- (id)bodyStructure;
- (void)dealloc;
- (id)description;
- (unsigned long)encoding;
- (id)envelope;
- (id)fetchData;
- (id)flagsArray;
- (id)initWithType:(int)fp8;
- (id)internalDate;
- (unsigned long)messageFlags;
- (unsigned long)messageSize;
- (id)section;
- (void)setBodyStructure:(id)fp8;
- (void)setEnvelope:(id)fp8;
- (void)setFetchData:(id)fp8;
- (void)setFlagsArray:(id)fp8;
- (void)setInternalDate:(id)fp8;
- (void)setMessageSize:(unsigned long)fp8;
- (void)setSection:(id)fp8;
- (void)setStartOffset:(unsigned long)fp8;
- (void)setUid:(unsigned long)fp8;
- (unsigned long)startOffset;
- (int)type;
- (unsigned long)uid;

@end

