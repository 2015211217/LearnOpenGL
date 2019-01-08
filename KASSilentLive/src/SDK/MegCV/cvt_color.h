#pragma once

#include "common.h"

namespace megcv {

template <typename T> void cvt_rgb2gray(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_rgb2yuv(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_yuv2rgb(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_gray2rgb(const Mat<T> &src, Mat<T> &dst);

template <typename T> void cvt_rgba2rgb(const Mat<T> &src, Mat<T> &dst); //== bgra2bgr
template <typename T> void cvt_rgba2bgr(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_rgba2gray(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_rgb2bgr(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_bgr2gray(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_bgr2rgb(const Mat<T> &src, Mat<T> &dst);

template <typename T> void cvt_yuv2gray_nv21(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_yuv2rgb_nv21(const Mat<T> &src, Mat<T> &dst);
template <typename T> void cvt_yuv2bgr_nv21(const Mat<T> &src, Mat<T> &dst);
}
