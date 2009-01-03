/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

#import "NSCopying-Protocol.h"

@class NSData, NSString;

@interface Signature : NSObject <NSCopying>
{
    NSString *_uniqueId;
    NSString *_name;
    NSData *_webArchiveData;
    unsigned int _isRich:1;
    unsigned int _isSavedAsRich:1;
    unsigned int _readFromTextFile;
    unsigned int _isDirty:1;
}

- (void)dealloc;
- (id)initWithName:(id)fp8;
- (id)initWithName:(id)fp8 uniqueId:(id)fp12;
- (id)initWithDictionary:(id)fp8;
- (BOOL)saveContentToDisk;
- (void)removeContentFromDisk;
- (id)dictionaryRepresentationIncludingWebArchiveData:(BOOL)fp8;
- (id)dictionaryRepresentation;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)uniqueId;
- (void)setName:(id)fp8;
- (id)name;
- (id)webArchive;
- (void)setWebArchive:(id)fp8;
- (id)attributedString;
- (id)textValue;
- (void)setTextValue:(id)fp8;
- (void)setIsRich:(BOOL)fp8;
- (BOOL)isRich;
- (BOOL)isEqual:(id)fp8;
- (unsigned int)hash;

@end

