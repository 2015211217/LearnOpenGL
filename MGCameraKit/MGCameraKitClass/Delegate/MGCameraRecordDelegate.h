//
//  MGCameraRecordDelegate.h
//  MGFaceIDGeneralModule
//
//  Created by MegviiDev on 2018/5/18.
//  Copyright © 2018年 Megvii. All rights reserved.
//

#ifndef MGCameraRecordDelegate_h
#define MGCameraRecordDelegate_h
#import <Foundation/Foundation.h>

@class MGCameraRecordManager;

@protocol MGCameraRecordDelegate <NSObject>

@required
- (void)mgCameraRecordDidFinishPreparing:(MGCameraRecordManager *)recorder;
- (void)mgCameraRecord:(MGCameraRecordManager *)recorder didFailWithError:(NSError *)error;
- (void)mgCameraRecordDidFinishRecording:(MGCameraRecordManager *)recorder;
@end

#endif /* MGCameraRecordDelegate_h */
