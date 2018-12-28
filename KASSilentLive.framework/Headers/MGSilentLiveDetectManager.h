//
//  MGSilentLiveDetectManager.h
//  KASSilentLive
//
//  Created by megvii on 2017/9/12.
//  Copyright © 2017年 megvii. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class MGSilentLiveDetectItem;

@interface MGSilentLiveDetectManager : NSObject

- (instancetype)initWithFaceModel:(NSData *)faceData fmpModel:(NSData *)fmpData;

- (MGSilentLiveDetectItem *)detectImageIsLiveWithFMP:(UIImage *)originImage;

@end
