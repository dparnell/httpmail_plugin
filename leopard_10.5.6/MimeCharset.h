/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSString;

@interface MimeCharset : NSObject
{
    unsigned int _encoding;
    NSString *_primaryLanguage;
    NSString *_charsetName;
    unsigned int _coversLargeUnicodeSubset:1;
    unsigned int _useBase64InHeaders:1;
    unsigned int _canBeUsedForOutgoingMessages:1;
}

+ (id)allMimeCharsets;
+ (id)charsetForEncoding:(unsigned long)fp8;
+ (id)preferredMimeCharset;
- (id)retain;
- (void)release;
- (unsigned int)retainCount;
- (id)initWithEncoding:(unsigned long)fp8;
- (unsigned long)encoding;
- (id)charsetName;
- (BOOL)canBeUsedForOutgoingMessages;
- (BOOL)coversLargeUnicodeSubset;
- (BOOL)useBase64InHeaders;
- (id)displayName;
- (id)primaryLanguage;
- (id)description;

@end

