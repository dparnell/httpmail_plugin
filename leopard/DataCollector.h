/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "DataConsumerProtocol.h"

@class LibraryMessage, NSDictionary, NSFileHandle, NSString;

@interface DataCollector : NSObject <DataConsumer>
{
    NSString *_path;
    NSString *_tmpPath;
    LibraryMessage *_message;
    NSString *_part;
    NSFileHandle *_fileHandle;
    unsigned int _length;
    NSDictionary *_plist;
    BOOL _isEmpty;
}

- (id)initWithMessage:(id)fp8 isPartial:(BOOL)fp12 part:(id)fp16;
- (void)appendData:(id)fp8;
- (void)setData:(id)fp8;
- (void)done;
- (void)dealloc;
- (void)finalize;

@end

