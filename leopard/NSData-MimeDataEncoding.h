/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSData.h"

@interface NSData (MimeDataEncoding)
+ (unsigned int)quotedPrintableLengthOfHeaderBytes:(const char *)fp8 length:(unsigned int)fp12;
- (id)decodeQuotedPrintableForText:(BOOL)fp8;
- (id)encodeQuotedPrintableForText:(BOOL)fp8;
- (id)encodeQuotedPrintableForText:(BOOL)fp8 allowCancel:(BOOL)fp12;
- (id)decodeBase64;
- (BOOL)isValidBase64Data;
- (id)encodeBase64WithoutLineBreaks;
- (id)encodeBase64;
- (id)encodeBase64AllowCancel:(BOOL)fp8;
- (id)decodeModifiedBase64;
- (id)encodeModifiedBase64;
- (id)encodeBase64HeaderData;
@end

