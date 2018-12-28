//
//  MGFaceIDFaceRectManager.h
//  KASSilentLive
//
//  Created by LiangJuzi on 2018/12/20.
//  Copyright © 2018 megvii. All rights reserved.
//

#ifndef MGFaceIDFaceRectManager_h
#define MGFaceIDFaceRectManager_h


#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>
#include "MegFaceIDConfig.h"


#include "megface-c/detector_rect_context.h"

namespace MGFaceIDFaceManager {
    class FaceIDFaceRectManager {
        void* face_worker;
    public:
        ~FaceIDFaceRectManager();
        FaceIDFaceRectManager();
        bool load_model_data(const void* face_data);
        std::vector<MGFScoreRect> detect_face_rect(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height);
    };
}


#endif /* MGFaceIDFaceRectManager_h */
