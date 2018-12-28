#pragma once

namespace megcv {

enum InterpolationMode {
    INTER_NEAREST,
    INTER_LINEAR,
    INTER_AREA,
    INTER_CUBIC,
    INTER_LANCZOS4
};

enum BorderMode {
    BORDER_REPLICATE,
    BORDER_REFLECT,
    BORDER_REFLECT_101,
    BORDER_WRAP,
    BORDER_CONSTANT,
    // DO NOT use BORDER_TRANSPARENT, has not been tested
    BORDER_TRANSPARENT,

    BORDER_DEFAULT = BORDER_REFLECT_101,
    BORDER_ISOLATED = 16,
};

}

