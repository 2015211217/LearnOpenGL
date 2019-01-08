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
 * \brief Transpose image.
 *
 * \param[in] src Input mat.
 * \param[out] dst Output mat.
 */
template <typename T> void transpose(const Mat<T> &src, Mat<T> &dst);

} // namespace megcv

// vim: syntax=cpp.doxygen
