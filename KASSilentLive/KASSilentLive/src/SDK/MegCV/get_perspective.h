/*
 * $File: get_perspective.h
 * $Date: Sat Sep 12 12:33:11 2015 +0800
 * $Author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */

#pragma once

#include "common.h"
#include <type_traits>


namespace megcv {

	/*!
	 * Compute homography matrix given at least 4 pairs.
	 * If more than 4 points are given, we will fit
	 * homography using least square regression.
	 *
	 * \param src coordinates of vertices in the source image.
	 * \parma dst coordinates of the corresponding vertices in the destination image.
	 * \param trans an array of 9 elements, will store the resulting homography matrix.
	 */
	template <class T,
			 class should_enable_t = typename std::enable_if<std::is_same<float, T>::value || std::is_same<double, T>::value>::type>
		void get_perspective_transform(const std::vector<Point<T>> &src,
				const std::vector<Point<T>> &dst, T *trans);


}


/*
 * vim: syntax=cpp.doxygen foldmethod=marker foldmarker=f{{{,f}}}
 */

