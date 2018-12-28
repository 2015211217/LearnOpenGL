/**
 * \file flip.h
 *
 * This file is part of MegCV, a computer vision run-time library developed by
 * Megvii.
 *
 * \author Ming Wei <weiming@megvii.com>
 *
 * \copyright Copyright (c) 2015-2016 Megvii Inc. All rights reserved.
 */
#pragma once
#include "common.h"

namespace megcv {

/**
 * \brief Flips an image around vertical and/or horizontal axes.
 *
 * \param[in] src Input mat.
 * \param[out] dst Output mat.
 * \param[in] vertical Specifying whether the image should be flipped vertically.
 * \param[in] horizontal Specifying whether the image should be flipped horizontally.
 *
 * `vertical' and `horizontal' can be set at the same time.
 */
template <typename T>
void flip(const Mat<T> &src, Mat<T> &dst, bool vertical, bool horizontal);

} // namespace megcv

// vim: syntax=cpp.doxygen
