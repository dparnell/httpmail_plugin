/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "MVMailBundle.h"

#import "SyncableDataOwner-Protocol.h"

@class NSMutableArray, NSMutableDictionary;

@interface SignatureBundle : MVMailBundle <SyncableDataOwner>
{
    NSMutableDictionary *_signatures;
    NSMutableArray *accounts;
    BOOL _isDirty;
    BOOL _isSavingSyncResults;
    NSMutableDictionary *_lastDefaultSignatures;
    int fileVersionNumber;
}

+ (void)initialize;
+ (id)allSignaturesAccount;
+ (id)_reallyOldSignaturesPath;
+ (id)_oldSignaturesPath;
+ (id)signaturesFolderPath;
+ (id)signaturesPlistPath;
- (id)init;
- (void)dealloc;
- (void)loadLastDefaultSignatures;
- (id)signatureAccounts;
- (BOOL)updateAccountList;
- (id)loadFromDictionary:(id)fp8;
- (BOOL)deleteSignaturesNotPresentInNewSignatures:(id)fp8;
- (id)signatures;
- (id)fixAccountIdsInPlist:(id)fp8;
- (unsigned int)numberOfSignatures;
- (id)signaturesForAccount:(id)fp8;
- (id)signatureAtIndex:(int)fp8 forAccount:(id)fp12;
- (id)signatureAtIndex:(int)fp8;
- (void)removeSignatureAtIndex:(int)fp8;
- (void)removeSignature:(id)fp8;
- (void)removeSignatureAtIndex:(int)fp8 forAccount:(id)fp12;
- (void)insertSignature:(id)fp8 atIndex:(int)fp12 forAccount:(id)fp16;
- (void)insertSignature:(id)fp8 atIndex:(int)fp12;
- (void)addSignature:(id)fp8;
- (void)signatureNameChanged:(id)fp8;
- (void)saveChangesToDisk;
- (id)dictionaryRepresentationIncludingSyncInformation:(BOOL)fp8;
- (void)setDefaultSignatureId:(id)fp8 forAccountId:(id)fp12;
- (void)setDefaultSignature:(id)fp8 forAccount:(id)fp12;
- (id)defaultSignatureForAccount:(id)fp8;
- (int)signatureSelectionMethodForAccount:(id)fp8;
- (void)setSignatureSelectionMethod:(int)fp8 forAccount:(id)fp12;
- (id)activeSignatureWithName:(id)fp8;
- (id)activeSignatureWithId:(id)fp8;
- (BOOL)showComposeAccessoryView:(char *)fp8;
- (BOOL)showComposeAccessoryView;
- (void)setShowsComposeAccessoryView:(BOOL)fp8;
- (void)unsetShowsComposeAccessoryView;
- (BOOL)placeSignatureAboveQuotedText;
- (void)setPlaceSignatureAboveQuotedText:(BOOL)fp8;
- (void)configurePopUpButton:(id)fp8 forAccount:(id)fp12 defaultSignature:(id)fp16 selectionMethod:(int)fp20 showAccount:(BOOL)fp24;
- (void)syncSignatures;
- (BOOL)dataWillBeSyncedVersion:(id *)fp8 data:(id *)fp12 type:(id)fp16;
- (BOOL)dataWasSyncedVersion:(id)fp8 type:(id)fp12 newData:(id)fp16 acceptedChanges:(id)fp20;

@end

