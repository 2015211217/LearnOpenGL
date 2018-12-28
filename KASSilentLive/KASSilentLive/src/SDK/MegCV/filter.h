#pragma once

#include "common.h"
#include "enums.h"

namespace megcv 
{
template<typename T, typename T1>
void sepFilter2D( const Mat<T> & src, Mat<T> & dst, Mat<T1> & kernelX, Mat<T1> & kernelY, BorderMode borderType );

}

