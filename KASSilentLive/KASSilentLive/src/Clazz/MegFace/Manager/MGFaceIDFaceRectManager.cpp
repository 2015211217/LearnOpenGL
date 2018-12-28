//
//  MGFaceIDFaceRectManager.cpp
//  KASSilentLive
//
//  Created by LiangJuzi on 2018/12/20.
//  Copyright © 2018 megvii. All rights reserved.
//

#include "MGFaceIDFaceRectManager.h"

using namespace std;
using namespace MGFaceIDFaceManager;

class FaceIDFaceRectManagerWorkder {
    MGFDetectorRectContext faceContext;
public:
    ~FaceIDFaceRectManagerWorkder() {
        MGF_release(faceContext);
    };
    FaceIDFaceRectManagerWorkder() {
    };
    bool load_model_data(const void* face_data) {
        try {
            MGFDetectorRectSettings settings;
            settings.device = {MGF_CPU, 1, 0};
            MGF_make_detector_rect_context_from_memory(face_data, &settings, &faceContext);
            return true;
        } catch (...) {
            return false;
        }
    };
    
    vector<MGFScoreRect> detect_face_rect(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
        MGFImage mgf_image = create_MGFImag(face_image, image_type, image_width, image_height);
        MGFDetectorRectOptions options;
        options = MGFDetectorRectOptions{{0, 0, image_width - 1, image_height - 1}, 0, MGF_UP};
        const MGFDetectorRectResult* detectResult;
        MGFErrorCode detectCode = MGF_detect_rect(faceContext, mgf_image, &options, &detectResult);
        MGF_release(mgf_image);
        vector<MGFScoreRect> face_rect_vct;
        if (detectCode == MGF_OK) {
            for (int i = 0; i < detectResult->size; i++) {
                MGFScoreRect face_rect_item = detectResult->items[i];
                face_rect_vct.push_back(face_rect_item);
            }
        }
        return face_rect_vct;
    };
    MGFImage create_MGFImag(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
        MGFImage mgf_image = nullptr;
        switch (image_type) {
            case MegFaceIDImageTypeBGR:
                MGF_MAKE_BGR_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            case MegFaceIDImageTypeGRAY:
                MGF_MAKE_GRAY_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            case MegFaceIDImageTypeYUVNV21:
                MGF_MAKE_YUV_NV21_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            case MegFaceIDImageTypeRGB:
                MGF_MAKE_RGB_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            case MegFaceIDImageTypeRGBA:
                MGF_MAKE_RGBA_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            case MegFaceIDImageTypeBGRA:
                MGF_MAKE_BGRA_IMAGE(face_image, image_height, image_width, &mgf_image);
                break;
            default:
                break;
        }
        return mgf_image;
    };
};

FaceIDFaceRectManager::~FaceIDFaceRectManager() {
    delete (FaceIDFaceRectManagerWorkder *)face_worker;
};

FaceIDFaceRectManager::FaceIDFaceRectManager() {
    face_worker = new FaceIDFaceRectManagerWorkder();
};

bool FaceIDFaceRectManager::load_model_data(const void* face_data) {
    return ((FaceIDFaceRectManagerWorkder *)face_worker)->load_model_data(face_data);
};

vector<MGFScoreRect> FaceIDFaceRectManager::detect_face_rect(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
    return ((FaceIDFaceRectManagerWorkder *)face_worker)->detect_face_rect(face_image, image_type, image_width,  image_height);
};
