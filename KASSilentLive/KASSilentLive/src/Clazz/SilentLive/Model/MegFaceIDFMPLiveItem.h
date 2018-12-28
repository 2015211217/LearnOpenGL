//
//  MegFaceIDFMPLiveItem.h
//  MegLive
//
//  Created by megvii on 2017/8/16.
//  Copyright © 2017年 megvii. All rights reserved.
//

#ifndef MegFaceIDFMPLiveItem_hpp
#define MegFaceIDFMPLiveItem_hpp

#include <stdio.h>

namespace MegFaceIDSilentLive {
    class FaceIDFMPLiveItem {
    public:
        bool has_face;
        bool is_live;
        float fabricate;
        float mask;
        float panorama;
        FaceIDFMPLiveItem();
    };
}

#endif /* MegFaceIDFMPLiveItem_hpp */
