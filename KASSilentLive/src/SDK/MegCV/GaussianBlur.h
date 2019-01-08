#pragma once

#include "common.h"
#include "enums.h"
#include "filter.h"

namespace megcv {

template <typename T>
void GaussianBlur( const Mat<T> &src, Mat<T> &dst, 
        size_t ksize_height, size_t ksize_width,
        double sigma1, double sigma2,
        BorderMode borderType);
}
