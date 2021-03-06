/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

@class NSMutableDictionary;

@interface MFError : NSError
{
    NSMutableDictionary *_moreUserInfo;
}

+ (id)errorWithDomain:(id)fp8 code:(long)fp12 localizedDescription:(id)fp16;
+ (id)errorWithDomain:(id)fp8 code:(long)fp12 localizedDescription:(id)fp16 title:(id)fp20 helpTag:(id)fp24 userInfo:(id)fp28;
+ (id)errorWithException:(id)fp8;
- (void)setUserInfoObject:(id)fp8 forKey:(id)fp12;
- (id)userInfo;
- (id)localizedDescription;
- (id)moreInfo;
- (id)helpAnchor;
- (id)shortDescription;
- (void)setLocalizedDescription:(id)fp8;
- (void)setMoreInfo:(id)fp8;
- (void)setHelpTag:(id)fp8;
- (void)setShortDescription:(id)fp8;
- (void)useGenericDescription:(id)fp8;
- (BOOL)alertShowHelp:(id)fp8;
- (void)dealloc;
- (void)finalize;

@end

