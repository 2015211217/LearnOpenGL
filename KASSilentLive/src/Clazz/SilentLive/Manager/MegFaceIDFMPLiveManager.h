//
//  MegFaceIDFMPLiveManager.h
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#ifndef MegFaceIDFMPLiveManager_hpp
#define MegFaceIDFMPLiveManager_hpp

#include <stdio.h>
#include "MegFaceIDFMPLiveItem.h"
#include "MegFaceIDConfig.h"

namespace MegFaceIDSilentLive {
    class FaceIDFMPLiveManager {
        void* fmp_worker;
    public:
        ~FaceIDFMPLiveManager();
        FaceIDFMPLiveManager();
        bool load_model_data(const void* face_data, const void* fmp_data);
        FaceIDFMPLiveItem fmp_detect_image(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height);
    };
}

#endif /* MegFaceIDFMPLiveManager_hpp */
