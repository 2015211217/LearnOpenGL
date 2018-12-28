//
//  MegFaceIDSilentLiveConfig.h
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#ifndef MegFaceIDSilentLiveConfig_h
#define MegFaceIDSilentLiveConfig_h

typedef enum : int {
    MegFaceIDSilentStepLookMirror,
    MegFaceIDSilentStepLive,
    MegFaceIDSilentStepFinish,
} MegFaceIDSilentStep;

typedef enum : int {
    MegFaceIDSilentLiveFailedTypeNone,
    MegFaceIDSilentLiveFailedTypeTimeout,
    MegFaceIDSilentLiveFailedTypeScoreLow,
} MegFaceIDSilentLiveFailedType;

#endif /* MegFaceIDSilentLiveConfig_h */
