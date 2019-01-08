/* -*- mode:c -*- */
#pragma once

/* \file include/megcommon-c/image.h
 * \brief This file defines the function to create an image object.
 */

#include <stddef.h>
#include <stdint.h>

#include "macro.h"
#include "misc.h"
#include "struct.h"

/*! \brief The available image data in a MGFImageData object.
 */
typedef enum MGFImageType {
    MGF_IMAGE_TYPE_BGR = 1 << 0,
    MGF_IMAGE_TYPE_GRAY = 1 << 1,
    MGF_IMAGE_TYPE_YUV_NV21 = 1 << 2,
    MGF_IMAGE_TYPE_RGB = 1 << 3,
    MGF_IMAGE_TYPE_RGBA = 1 << 4,
    MGF_IMAGE_TYPE_BGRA = 1 << 5,
    MGF_IMAGE_TYPE_DEPTH = 1 << 6,
} MGFImageType;

/*! \brief The description of the image data to create a MGFImage object.
 */
typedef struct MGFImageData {
    int available; /*!< Indicates which of the following pointers are
                      available */

    size_t height; /*!< The height of the image */
    size_t width;  /*!< The width of the image */

    /*! The grayscale data, available if MGF_IMAGE_TYPE_GRAY is set */
    const void* gray;

    /*! The BGR data, available if MGF_IMAGE_TYPE_BGR is set */
    const void* bgr;

    /*! The NV21 data, available if MGF_IMAGE_TYPE_NV21 is set */
    const void* yuv_nv21;

    /*! The rgb data, available if MGF_IMAGE_TYPE_RGB is set */
    const void* rgb;

    /*! The rgba data, available if MGF_IMAGE_TYPE_RGBA is set */
    const void* rgba;

    /*! The bgra data, available if MGF_IMAGE_TYPE_BGRA is set */
    const void* bgra;

    /*! The depth data, available if MGF_IMAGE_TYPE_DEPTH is set */
    const void* depth;
} MGFImageData;

/*! \brief The pointer to a MGFImage object.
 */
typedef void* MGFImage;

MGF_CAPI_BEGIN

/*! \brief Create a MGFImage object from the given data.
 * \param[in] data The image data
 * \param[out] result The MGFImage object
 */
MGF_CAPI MGFErrorCode MGF_make_image(MGFImageData data, MGFImage* result);

MGF_CAPI_END

/*! \brief Create a MGFImage object from a grayscale data.
 */
#define MGF_MAKE_GRAY_IMAGE(data, h, w, ctx)                               \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_GRAY, size_t(h), size_t(w), \
                                data, NULL, NULL, NULL, NULL, NULL, NULL}, \
                   ctx)

/*! \brief Create a MGFImage object from a BGR data.
 */
#define MGF_MAKE_BGR_IMAGE(data, h, w, ctx)                                \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_BGR, size_t(h), size_t(w),  \
                                NULL, data, NULL, NULL, NULL, NULL, NULL}, \
                   ctx)

/*! \brief Create a MGFImage object from the NV21 data.
 */
#define MGF_MAKE_YUV_NV21_IMAGE(data, h, w, ctx)                               \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_YUV_NV21, size_t(h), size_t(w), \
                                NULL, NULL, data, NULL, NULL, NULL, NULL},     \
                   ctx)

/*! \brief Create a MGFImage object from the RGB data.
 */
#define MGF_MAKE_RGB_IMAGE(data, h, w, ctx)                                \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_RGB, size_t(h), size_t(w),  \
                                NULL, NULL, NULL, data, NULL, NULL, NULL}, \
                   ctx)

/*! \brief Create a MGFImage object from the RGBA data.
 */
#define MGF_MAKE_RGBA_IMAGE(data, h, w, ctx)                               \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_RGBA, size_t(h), size_t(w), \
                                NULL, NULL, NULL, NULL, data, NULL, NULL}, \
                   ctx)

/*! \brief Create a MGFImage object from the BGRA data.
 */
#define MGF_MAKE_BGRA_IMAGE(data, h, w, ctx)                               \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_BGRA, size_t(h), size_t(w), \
                                NULL, NULL, NULL, NULL, NULL, data, NULL}, \
                   ctx)

/*! \brief Create a MGFImage object from the DEPTH data.
 */
#define MGF_MAKE_DEPTH_IMAGE(data, h, w, ctx)                               \
    MGF_make_image(MGFImageData{MGF_IMAGE_TYPE_DEPTH, size_t(h), size_t(w), \
                                NULL, NULL, NULL, NULL, NULL, NULL, data},  \
                   ctx)

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
