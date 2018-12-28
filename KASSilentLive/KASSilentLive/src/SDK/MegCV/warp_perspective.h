#pragma once

#include "common.h"
#include "enums.h"

namespace megcv {

template <typename T>
void warp_perspective(const Mat<T> &src, Mat<T> &dst, const double *trans,
        BorderMode bmode, InterpolationMode imode,
        bool inverse, const T *border_val);


}
