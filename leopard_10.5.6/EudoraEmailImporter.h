/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "FilesystemEmailImporter.h"

@interface EudoraEmailImporter : FilesystemEmailImporter
{
}

+ (id)name;
+ (id)explanatoryText;
- (char *)fromString;
- (BOOL)isValidMailbox:(id)fp8;
- (id)preProcessSourceData:(id)fp8;
- (struct _NSRange)_rangeOfDataContainedByTag:(char *)fp8 endTag:(char *)fp12 inData:(id)fp16;
- (void)_stripTag:(char *)fp8 fromData:(id)fp12;
- (id)_attachmentsInEudoraMessage:(id)fp8;
- (BOOL)_isAttachmentBeingSearchedFor:(id)fp8;

@end

