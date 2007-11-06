/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@interface ImageJunkMetadata : NSObject
{
    int _type;
    struct _NSSize _size;
    unsigned int _frameCount;
    unsigned int _pixelCount;
    unsigned int _byteCount;
    float _density;
    BOOL _isAnimated;
}

+ (id)stringForImageType:(int)fp8;
+ (id)lsmMarkerForImageSizeCategory:(int)fp8;
+ (id)lsmMarkerForImageDensityCategory:(int)fp8;
- (id)initWithImage:(id)fp8 name:(id)fp12 type:(int)fp16;
- (void)dealloc;
- (void)computeDensity;
- (void)setByteCount:(unsigned int)fp8;
- (void)setPixelCount:(unsigned int)fp8;
- (int)sizeCategory;
- (int)densityCategory;
- (id)description;
- (unsigned int)frameCount;
- (void)setFrameCount:(unsigned int)fp8;
- (BOOL)isAnimated;
- (void)setIsAnimated:(BOOL)fp8;
- (float)density;
- (void)setDensity:(float)fp8;
- (unsigned int)byteCount;
- (unsigned int)pixelCount;
- (struct _NSSize)size;
- (void)setSize:(struct _NSSize)fp8;
- (int)type;
- (void)setType:(int)fp8;

@end

