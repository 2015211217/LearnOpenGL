/**
 * \file transpose.h
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
 * \brief Rotate image 90 degree.
 *
 * \param[in] src Input mat.
 * \param[out] dst Output mat.
 *
 * Currently only 8UC1 is supported.
 */
template <typename T> void rotate(const Mat<T> &src, Mat<T> &dst,
        bool clockwise);

} // namespace megcv

// vim: syntax=cpp.doxygen

