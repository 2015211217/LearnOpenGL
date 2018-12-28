//
//  MGSilentLiveDetectManager.m
//  KASSilentLive
//
//  Created by megvii on 2017/9/12.
//  Copyright © 2017年 megvii. All rights reserved.
//

#import "MGSilentLiveDetectManager.h"
#import "MGSilentLiveDetectItem.h"
#include "MegFaceIDFMPLiveManager.h"

using namespace MegFaceIDSilentLive;

@interface MGSilentLiveDetectManager ()
{
    FaceIDFMPLiveManager* _fmpLiveManager;
}
@end

@implementation MGSilentLiveDetectManager

- (void)dealloc {
    delete _fmpLiveManager;
}

- (instancetype)initWithFaceModel:(NSData *)faceData fmpModel:(NSData *)fmpData {
    self = [super init];
    if (self) {
        _fmpLiveManager = new FaceIDFMPLiveManager();
        bool loadModel = _fmpLiveManager->load_model_data([faceData bytes], [fmpData bytes]);
        if (loadModel == false) {
            return nil;
        }
    }
    return self;
}

- (MGSilentLiveDetectItem *)detectImageIsLiveWithFMP:(UIImage *)originImage {
    @synchronized (self) {
        if (originImage) {
            unsigned char* imageChar = [self toImageRGBADataWithImage:originImage];
            FaceIDFMPLiveItem liveItem = _fmpLiveManager->fmp_detect_image(imageChar, MegFaceIDImageTypeRGBA, (int)CGImageGetWidth(originImage.CGImage), (int)CGImageGetHeight(originImage.CGImage));
            MGSilentLiveDetectItem* detectItem = [MGSilentLiveDetectItem new];
            detectItem.hasFace = liveItem.has_face;
            detectItem.isLive = liveItem.is_live;
            free(imageChar);
            return detectItem;
        }
    }
    return nil;
}

- (unsigned char *)toImageRGBADataWithImage:(UIImage *)image {
    int RGBA = 4;
    CGImageRef imageRef = image.CGImage;
    NSUInteger width = CGImageGetWidth(imageRef);
    NSUInteger height = CGImageGetHeight(imageRef);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    unsigned char *rawData = (unsigned char*)malloc(width*height*4*sizeof(unsigned char));
    NSUInteger bytesPerPixel = RGBA;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    CGContextRef context = CGBitmapContextCreate(rawData,
                                                 width,
                                                 height,
                                                 bitsPerComponent,
                                                 bytesPerRow,
                                                 colorSpace,
                                                 kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    return rawData;
}


@end
