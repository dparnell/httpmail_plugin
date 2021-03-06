/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/MessageBody.h>

@class MimePart;

@interface MimeBody : MessageBody
{
    MimePart *_topLevelPart;
    unsigned int _preferredTextEncoding;
    unsigned int _preferredAlternative:16;
    unsigned int _numAlternatives:16;
}

+ (id)createMimeBoundary;
+ (void)initialize;
+ (id)versionString;
- (BOOL)_isPossiblySignedOrEncrypted;
- (id)attachments;
- (id)attributedString;
- (void)calculateNumberOfAttachmentsDecodeIfNeeded;
- (void)calculateNumberOfAttachmentsIfNeeded;
- (void)dealloc;
- (id)init;
- (BOOL)isHTML;
- (BOOL)isRich;
- (id)mimeSubtype;
- (id)mimeType;
- (int)numberOfAlternatives;
- (id)partWithNumber:(id)fp8;
- (int)preferredAlternative;
- (id)preferredBodyPart;
- (unsigned long)preferredTextEncoding;
- (void)setPreferredAlternative:(int)fp8;
- (void)setPreferredTextEncoding:(unsigned long)fp8;
- (void)setTopLevelPart:(id)fp8;
- (id)stringValueForJunkEvaluation:(BOOL)fp8;
- (id)textHtmlPart;
- (id)topLevelPart;
- (id)webArchive;

@end

