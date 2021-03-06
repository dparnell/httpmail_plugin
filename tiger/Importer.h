/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class ImportAssistant, NSArray, NSMutableArray, NSString;

@interface Importer : NSObject
{
    ImportAssistant *_delegate;
    NSMutableArray *_importArray;
    NSString *_applicationString;
    NSArray *_importFields;
    int _errorNumber;
    BOOL _importCanceled;
}

+ (id)explanatoryText;
+ (id)name;
- (void)_runApplescript:(id)fp8 andReturnArray:(id)fp12;
- (void)addItemToImportArray:(id)fp8;
- (id)arrayFromDescriptor:(id)fp8;
- (void)cleanup;
- (void)clearImportArray;
- (int)countOfEnabledItems;
- (id)creatorCode;
- (void)dealloc;
- (id)delegate;
- (id)importArray;
- (id)importArrayEnumerator;
- (BOOL)importCanceled;
- (id)importFields;
- (void)importFinished;
- (id)importFinishedText;
- (id)init;
- (id)name;
- (void)performImport;
- (id)prepareForImport;
- (id)runApplescript:(id)fp8;
- (BOOL)setApplicationString;
- (void)setDelegate:(id)fp8;
- (void)setImportCanceled:(BOOL)fp8;
- (void)setImportFields:(id)fp8;
- (void)sortArray:(id)fp8;
- (id)statusLine;

@end

