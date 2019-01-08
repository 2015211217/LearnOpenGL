//
//  MGSilentLiveDetectItem.h
//  KASSilentLive
//
//  Created by megvii on 2017/9/12.
//  Copyright © 2017年 megvii. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MGSilentLiveDetectItem : NSObject

@property (nonatomic, assign) BOOL hasFace;
@property (nonatomic, assign) BOOL isLive;

@property (nonatomic, assign) float confidence;
@property (nonatomic, assign) int left;
@property (nonatomic, assign) int right;
@property (nonatomic, assign) int top;
@property (nonatomic, assign) int bottom;

@end

