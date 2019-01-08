//
//  MGFaceIDFaceManager.cpp
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#include "MGFaceIDFaceManager.h"

using namespace std;
using namespace MGFaceIDFaceManager;

class FaceIDFaceManagerWorkder {
    MGFDetectorContext faceContext;
public:
    ~FaceIDFaceManagerWorkder() {
        MGF_release(faceContext);
    };
    FaceIDFaceManagerWorkder() {
    };
    bool load_model_data(const void* face_data) {
        try {
            MGFDetectorSettings settings;
            settings.device = {MGF_CPU, 1, 0};
            MGF_make_detector_context_from_memory(face_data, &settings, &faceContext);
            return true;
        } catch (...) {
            return false;
        }
    };

    vector<MGFLandmarkMap> detect_face_landmark(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
        MGFImage mgf_image = create_MGFImag(face_image, image_type, image_width, image_height);
        MGFDetectorOptions options;
        options = MGFDetectorOptions{{0, 0, image_width - 1, image_height - 1}, 0, MGF_UP};
        const MGFDetectorResult* detectResult;
        MGFErrorCode detectCode = MGF_detect(faceContext, mgf_image, &options, &detectResult);
        MGF_release(mgf_image);
        vector<MGFLandmarkMap> face_landmark_vct;
        if (detectCode == MGF_OK) {
            for (int i = 0; i < detectResult->size; i++) {
                MGFDetectedFace face_item = detectResult->items[i];
                MGFLandmarkMap face_landmark = face_item.landmark;
                face_landmark_vct.push_back(face_landmark);
            }
        }
        return face_landmark_vct;
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

FaceIDFaceManager::~FaceIDFaceManager() {
    delete (FaceIDFaceManagerWorkder *)face_worker;
};

FaceIDFaceManager::FaceIDFaceManager() {
    face_worker = new FaceIDFaceManagerWorkder();
};

bool FaceIDFaceManager::load_model_data(const void* face_data) {
    return ((FaceIDFaceManagerWorkder *)face_worker)->load_model_data(face_data);
};


vector<MGFLandmarkMap> FaceIDFaceManager::detect_face_landmark(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
    return ((FaceIDFaceManagerWorkder *)face_worker)->detect_face_landmark(face_image, image_type, image_width,  image_height);
};
