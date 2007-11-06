/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSArray;

@interface MessageSigner : NSObject
{
    int _verificationStatus;
    NSArray *_certificates;
    struct OpaqueSecTrustRef *_trust;
    int _trustResult;
}

- (void)dealloc;
- (void)finalize;
- (id)initWithCmsSignerInfo:(struct SecCmsSignerInfoStr *)fp8 trust:(struct OpaqueSecTrustRef *)fp12;
- (id)description;
- (id)label;
- (id)commonName;
- (id)emailAddress;
- (struct OpaqueSecTrustRef *)trust;
- (struct OpaqueSecCertificateRef *)signingCertificate;
- (id)certificates;
- (id)signingError;

@end

