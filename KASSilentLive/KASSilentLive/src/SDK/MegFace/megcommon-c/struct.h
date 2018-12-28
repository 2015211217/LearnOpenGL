/* -*- mode:c -*- */
#pragma once

/* \file include/megcommon-c/struct.h
 * \brief This file defines the structures and enumerations that is widely used
 * in the library.
 */

/*! \brief Error codes.
 */
typedef enum MGFErrorCode {
    MGF_OK = 0,
    MGF_INTERNAL_ERROR,
    MGF_UNKNOWN_ERROR,
    MGF_NULL_POINTER,
    MGF_UNEXPECTED_CONFIG,
    MGF_UNEXPECTED_MODEL,
    MGF_BROKEN_FILE,
    MGF_OUT_OF_RANGE,
    MGF_INVALID_SETTINGS,
    MGF_FILE_NOT_FOUND,
    MGF_INVALID_ARGUMENT,
    MGF_INVALID_OBJECT_TYPE,
    MGF_UNSUPPORTED,
    MGF_INVALID_LICENSE,
    MGF_MISSING_MAP_ELEMENT,
    MGF_UNKNOWN_GLOBAL_OPTION,
    MGF_UNAUTHORIZED,
} MGFErrorCode;

/*! \brief Device types.
 * \ingroup dtype
 *
 * MGF_CPU can be used only in the library that supports cuda. Otherwise, the
 * program will crash when it tries using a GPU device.
 */
typedef enum MGFDeviceType {
    MGF_CPU = 0, /*!< CPU */
    MGF_GPU,     /*!< GPU (CUDA) */
    MGF_OPENCL,
} MGFDeviceType;

/*! \brief Device option.
 * \ingroup dtype
 *
 * All the models on the same device, which is uniquely identified by the device
 * type, id and stream id, share one computing thread.
 */
typedef struct MGFDeviceOption {
    MGFDeviceType dev_type; /*!< The device type */
    int dev_id;    /*!< Video card id for GPU, no specific meaning for CPU */
    int stream_id; /*!< Stream id, identifying two computing threads on the
                          same video card, no specific meaning for CPU */
} MGFDeviceOption;

/*! \brief Rectangle.
 * \ingroup dtype
 */
typedef struct MGFRect {
    int left;
    int top;
    int right;
    int bottom;
} MGFRect;

/*! \brief Rectangle in float.
 * \ingroup dtype
 */
typedef struct MGFRectf {
    float left;
    float top;
    float right;
    float bottom;
} MGFRectf;

/*! \brief 2-D Point.
 * \ingroup dtype
 */
typedef struct MGFPoint2f {
    float x;
    float y;
} MGFPoint2f;

/*! \brief 2-D Shape.
 * \ingroup dtype
 */
typedef struct MGFShape2D {
    size_t row;
    size_t col;
} MGFShape2D;

/*! \brief The orientation of a face.
 * \ingroup dtype
 */
typedef enum MGFOrient {
    MGF_UP,
    MGF_RIGHT,
    MGF_DOWN,
    MGF_LEFT,
} MGFOrient;

/*! \brief Rectangle with confidence.
 * \ingroup dtype
 */
typedef struct MGFScoreRect {
    float confidence;
    MGFOrient orient;
    MGFRect rect;
    float angle;  // rad
} MGFScoreRect;

#ifndef MGF_MEGFACE_HEADER_CHECKER_v2_7_7_r1_build_789
#define MGF_MEGFACE_HEADER_CHECKER_v2_7_7_r1_build_789

MGF_CAPI_BEGIN
void MGF_megface_header_checker_v2_7_7_r1_build_789() __attribute__((weak));
MGF_CAPI void MGF_megface_v2_7_7_r1_build_789();
MGF_CAPI_END

void MGF_megface_header_checker_v2_7_7_r1_build_789() {
  (void) MGF_megface_v2_7_7_r1_build_789();
}

#endif
