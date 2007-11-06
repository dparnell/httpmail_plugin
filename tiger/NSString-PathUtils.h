/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSString.h"

@interface NSString (PathUtils)
+ (id)pathWithDirectory:(id)fp8 filename:(id)fp12 extension:(id)fp16;
- (id)betterStringByResolvingSymlinksInPath;
- (BOOL)deletePath;
- (BOOL)isSubdirectoryOfPath:(id)fp8;
- (BOOL)makeDirectoryWithMode:(int)fp8;
- (BOOL)makePathReadOnly:(int *)fp8;
- (BOOL)makePathReadOnly:(int *)fp8 recursively:(BOOL)fp12;
- (BOOL)makePathWritable:(int *)fp8;
- (void)setPosixFilePermissions:(int)fp8;
- (id)stringByReallyAbbreviatingWithTildeInPath;
- (id)uniquePathWithMaximumLength:(int)fp8;
@end

