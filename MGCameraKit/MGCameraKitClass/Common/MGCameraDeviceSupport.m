//
//  MGCameraDeviceSupport.m
//  MGFaceIDGeneralModule
//
//  Created by MegviiDev on 2017/7/18.
//  Copyright © 2017年 megvii. All rights reserved.
//

#import "MGCameraDeviceSupport.h"
#import <sys/utsname.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@implementation MGCameraDeviceSupport

+ (BOOL)isCameraAvailable {
    return [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceFront];
}

+ (BOOL)isCameraPermissions {
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    return !(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied);
}

@end
