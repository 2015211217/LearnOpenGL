//
//  MGFaceIDFaceManager.h
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#ifndef MGFaceIDFaceManager_hpp
#define MGFaceIDFaceManager_hpp

#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "megface-c/detector_context.h"
#include "MegFaceIDConfig.h"

namespace MGFaceIDFaceManager {
    class FaceIDFaceManager {
        void* face_worker;
    public:
        ~FaceIDFaceManager();
        FaceIDFaceManager();
        bool load_model_data(const void* face_data);
        std::vector<MGFLandmarkMap> detect_face_landmark(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height);
    };
}

#endif /* MGFaceIDFaceManager_hpp */
