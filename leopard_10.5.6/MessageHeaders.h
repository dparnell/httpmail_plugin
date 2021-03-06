/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

#import "NSCopying-Protocol.h"

@class NSData;

@interface MessageHeaders : NSObject <NSCopying>
{
    NSData *_data;
    unsigned int _preferredEncoding;
}

+ (BOOL)isStructuredHeaderKey:(id)fp8;
+ (BOOL)_isImageHeaderKey:(id)fp8;
+ (const char *)cstringForKey:(id)fp8;
+ (id)localizedHeaders;
+ (id)localizedHeadersFromEnglishHeaders:(id)fp8;
+ (id)englishHeadersFromLocalizedHeaders:(id)fp8;
- (id)initWithHeaderData:(id)fp8 encoding:(unsigned long)fp12;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)finalize;
- (id)mutableCopy;
- (id)headerData;
- (unsigned long)preferredEncoding;
- (void)setPreferredEncoding:(unsigned long)fp8;
- (id)htmlHeaderKey:(id)fp8 useBold:(BOOL)fp12;
- (id)htmlValueWithKey:(id)fp8 value:(id)fp12 useBold:(BOOL)fp16;
- (id)htmlStringShowingHeaderDetailLevel:(int)fp8;
- (id)htmlStringShowingHeaderDetailLevel:(int)fp8 useBold:(BOOL)fp12;
- (id)attributedStringShowingHeaderDetailLevel:(int)fp8;
- (id)attributedStringShowingHeaderDetailLevel:(int)fp8 useHeadIndents:(BOOL)fp12 useBold:(BOOL)fp16 includeBCC:(BOOL)fp20;
- (id)headersDictionaryWithHeaderDetailLevel:(int)fp8;
- (id)headersDictionaryWithHeaderDetailLevel:(int)fp8 forMessageType:(int)fp12;
- (id)allHeaderKeys;
- (void)_setCapitalizedKey:(id)fp8 forKey:(id)fp12;
- (id)_capitalizedKeyForKey:(id)fp8;
- (id)_createHeaderValueForKey:(id)fp8 offset:(unsigned int *)fp12;
- (id)_createHeaderValueForKey:(id)fp8;
- (BOOL)hasHeaderForKey:(id)fp8;
- (id)headersForKey:(id)fp8;
- (id)firstHeaderForKey:(id)fp8;
- (id)_decodeHeaderKeysFromData:(id)fp8;
- (id)isoLatin1CharsetHint;
- (id)mailVersion;
- (BOOL)messageIsFromMicrosoft;
- (void)_appendAddressList:(id)fp8 toData:(id)fp12;
- (id)encodedHeaders;
- (id)encodedHeadersIncludingFromSpace:(BOOL)fp8;
- (void)_appendHeaderData:(id)fp8 andRecipients:(id)fp12 expandPrivate:(BOOL)fp16 includeComment:(BOOL)fp20;
- (void)appendHeaderData:(id)fp8 andRecipients:(id)fp12;
- (id)allRecipientsExpandPrivate:(BOOL)fp8 includeComment:(BOOL)fp12;
- (id)_encodedHeadersIncludingFromSpace:(BOOL)fp8;

@end

