/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/detect_context.h
 * \brief This file defines the functions to detect faces.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The settings of a MGFDetectorContext object.
 */
typedef struct MGFDetectorSettings {
    MGFDeviceOption device;    /*!< The computing device. */
    MGFShape2D supposed_detect_shape; /*!< The supposed shape for future image */
    MGFShape2D supposed_attr_shape; /*!< The supposed shape for future image */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFDetectorSettings;

/*! \brief The options that affects detector behaviors.
 *
 * The order of the application of the options is:
 * - roi
 * - min_face
 * - orient
 */
typedef struct MGFDetectorOptions {
    /*! \brief The region to detect.
     *
     * The detector detects the whole image if the area of ROI is not larger
     * than 0. The boundary of ROI is adjusted to the boundary of the image if
     * the former exceeds the latter.
     *
     * The default behavior is to detect the whole image.
     */
    MGFRect roi;

    /*! \brief The minimal face to detect.
     *
     * It is not a mandatory option which guarantees that no faces smaller that
     * it will be detected, but an advisory one which suggests the detector
     * resizing the image to reduce the time cost.
     *
     * The default behavior is to detect the images as small as possible.
     */
    size_t min_face;

    /*! \brief The orientation of the faces.
     *
     * It is an advisory option for the detector to rotate the image in order to
     * detect the faces in other directions other than up-right.
     *
     * The default behavior is to the detect only up-right faces.
     */
    MGFOrient orient;
    float posfilter_threshold;
} MGFDetectorOptions;

/*! \brief The detected face structure.
 */
typedef struct MGFDetectedFace {
    /*! \brief The confidence of the rectangle being a face.
     *
     * It is a value between 0 (very unlikely) and 1 (very likely).
     * All the detected faces including those with low confidence are returned.
     * The API caller should skip the faces with low confidence in the
     * consideration of the use case.
     */
    float confidence;
    MGFOrient orient;
    /*! \brief The position of the face.
     */
    MGFRect rect;

    /*! \brief The landmarks of the face.
     */
    MGFLandmarkMap landmark;

    /*! \deprecated Use landmark_attribute instead.
     * \brief The landmarks extended information.
     *
     * The extension is the struct store the extended information for the
     * landmark.
     * Extension might be nullptr, which means there are no extension for this
     * MGFLandmarkMap.
     */
    MGFLandmarkExtension* landmark_extension;

    /*!
     * \brief The various attribute information inferred from landmark.
     *
     * The structure contains a member variable flag. The flag is a bitwise
     * value indicating the valid status of attribute information. If the flag
     * is 0, all the attribute informations in landmark_attribute are invalid.
     */
    MGFLandmarkAttribute landmark_attribute;
} MGFDetectedFace;

/*! \brief The detection result.
 */
typedef struct MGFDetectorResult {
    const MGFDetectedFace* items; /*!< The result array. */
    size_t size;                  /*!< The length of the result array. */
} MGFDetectorResult;

/*! \brief The pointer to a MGFDetectorContext object.
 */
typedef void* MGFDetectorContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFDetectorContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFDetectorContext object
 */
MGF_CAPI MGFErrorCode MGF_make_detector_context_from_file(
        const char* config_path, const MGFDetectorSettings* settings,
        MGFDetectorContext* result);

/*! \brief Create a MGFDetectorContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFDetectorContext object
 */
MGF_CAPI MGFErrorCode MGF_make_detector_context_from_memory(
        const void* config_data, const MGFDetectorSettings* settings,
        MGFDetectorContext* result);

/*! \brief Predict the faces.
 * \param[in] ctx The MGFDetectorContext object
 * \param[in] image The image to be detected
 * \param[in] options The options to use (NULL for default options)
 * \param[result] The pointer to the read-only prediction result
 */
MGF_CAPI MGFErrorCode MGF_detect(MGFDetectorContext ctx, MGFImage image,
                                 const MGFDetectorOptions* options,
                                 const MGFDetectorResult** result);

MGF_CAPI_END

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
