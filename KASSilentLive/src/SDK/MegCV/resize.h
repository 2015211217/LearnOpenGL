#pragma once

#include "common.h"
#include "enums.h"

namespace megcv {

template <typename T>
void resize(const Mat<T> &src, Mat<T> &dst, InterpolationMode imode);

} // namespace megcv
