//
//  MegFaceIDFMPLiveManager.cpp
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#include "MegFaceIDFMPLiveManager.h"
#include "meglive-c/fmp_context.h"
#include "MGFaceIDFaceManager.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>
#define kLiveStandard 0.5f

using namespace std;
using namespace MegFaceIDSilentLive;
using namespace MGFaceIDFaceManager;

class FaceIDFMPLiveManagerWorker {
public:
    ~FaceIDFMPLiveManagerWorker() {
        delete _faceManager;
        MGF_release(_fmpContext);
    };
    FaceIDFMPLiveManagerWorker() {
        _faceManager = new FaceIDFaceManager();
    };
    
    bool load_model_data(const void* face_data, const void* fmp_data) {
        MGFErrorCode loadFMPModelCode = MGL_make_fmp_context_from_memory(fmp_data, 0, &_fmpContext);
        bool loadFaceModel = _faceManager->load_model_data(face_data);
        return loadFMPModelCode == MGF_OK && loadFaceModel;
    };
    
    FaceIDFMPLiveItem init_item_fmp(const MGLFMPResult *result) {
        FaceIDFMPLiveItem fmp_item = FaceIDFMPLiveItem();
        fmp_item.is_live = result->pred < kLiveStandard ? true : false;
        fmp_item.fabricate = result->fabricate;
        fmp_item.mask = result->mask;
        fmp_item.panorama=result->panorama;
        return fmp_item;
    };
    
    FaceIDFMPLiveItem fmp_detect_image(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
        vector<MGFLandmarkMap> face_landmark_vct = _faceManager->detect_face_landmark(face_image, image_type, image_width, image_height);
        FaceIDFMPLiveItem fmp_item = FaceIDFMPLiveItem();
        if (face_landmark_vct.size() > 0) {
            MGFImage mgf_image;
            switch (image_type) {
                case MegFaceIDImageTypeRGB:
                    MGF_MAKE_RGB_IMAGE(face_image, image_height, image_width, &mgf_image);
                case MegFaceIDImageTypeBGR:
                    MGF_MAKE_BGR_IMAGE(face_image, image_height, image_width, &mgf_image);
                case MegFaceIDImageTypeYUVNV21:
                    MGF_MAKE_YUV_NV21_IMAGE(face_image, image_height, image_width, &mgf_image);
                    break;
                case MegFaceIDImageTypeBGRA:
                    MGF_MAKE_BGRA_IMAGE(face_image, image_height, image_width, &mgf_image);
                case MegFaceIDImageTypeRGBA:
                    MGF_MAKE_RGBA_IMAGE(face_image, image_height, image_width, &mgf_image);
                    break;
                default:
                    break;
            }
            
            MGFLandmarkMap face_landmark = face_landmark_vct[0];
            const MGLFMPResult* detect_result;
            MGL_fmp_classify(_fmpContext,
                             &mgf_image,
                             &face_landmark,
                             1,
                             &detect_result);
            fmp_item = init_item_fmp(detect_result);
            fmp_item.has_face = true;
            MGF_release(mgf_image);
        } else {
            fmp_item.has_face = false;
        }
        face_landmark_vct.clear();
        face_landmark_vct.shrink_to_fit();
        return fmp_item;
    };
private:
    FaceIDFaceManager* _faceManager;
    MGLFMPContext _fmpContext;
};

FaceIDFMPLiveManager::~FaceIDFMPLiveManager() {
    delete (FaceIDFMPLiveManagerWorker *)fmp_worker;
};

FaceIDFMPLiveManager::FaceIDFMPLiveManager(){
    fmp_worker = new FaceIDFMPLiveManagerWorker();
};

bool FaceIDFMPLiveManager::load_model_data(const void* face_data, const void* fmp_data) {
    return ((FaceIDFMPLiveManagerWorker *)fmp_worker)->load_model_data(face_data, fmp_data);
};

FaceIDFMPLiveItem FaceIDFMPLiveManager::fmp_detect_image(const void* face_image, MegFaceIDImageType image_type, int image_width, int image_height) {
    return ((FaceIDFMPLiveManagerWorker *)fmp_worker)->fmp_detect_image(face_image, image_type, image_width,image_height);
};
