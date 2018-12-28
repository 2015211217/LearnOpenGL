/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/eye_status_context.h
 * \brief This file defines the functions to predict eye statuses.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The status of an eye.
 * \ingroup dtype
 *
 * The eye status is represented in a Descartes-production of the existence of
 * glasses and the openness of the eye, with two extraneous statuses: dark
 * glasses (for sunglasses, for examples) and occlusions (sheltered by
 * hands, for examples).
 */
typedef enum MGFEyeStatus {
    MGF_NO_GLASSES_EYE_OPEN = 0,   //!< No glasses, eye open
    MGF_NO_GLASSES_EYE_CLOSE,      //!< No glasses, eye close
    MGF_NORMAL_GLASSES_EYE_OPEN,   //!< Transparent glasses, eye open
    MGF_NORMAL_GLASSES_EYE_CLOSE,  //!< Transparent glasses, eye close
    MGF_DARK_GLASSES,              //!< Dark glasses (non-transparent)
    MGF_OTHER_OCCLUSION,           //<! Other occlusions (hands, books, ...)
    MGF_EYE_STATUS_COUNT,
} MGFEyeStatus;

/*! \brief The status of left and right eyes.
 * \ingroup dtype
 */
typedef struct MGFLeftRightEyeStatus {
    MGFEyeStatus left_eye;
    MGFEyeStatus right_eye;
    float left_eye_prob[MGF_EYE_STATUS_COUNT];
    float right_eye_prob[MGF_EYE_STATUS_COUNT];
} MGFLeftRightEyeStatus;

/*! \brief The settings of a MGFEyeStatusContext object.
 */
typedef struct MGFEyeStatusSettings {
    MGFDeviceOption device; /*!< The computing device. */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFEyeStatusSettings;

/*! \brief The pointer to a MGFEyeStatusContext object.
 */
typedef void* MGFEyeStatusContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFEyeStatusContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFEyeStatusContext object
 */
MGF_CAPI MGFErrorCode MGF_make_eye_status_context_from_file(
        const char* config_path, const MGFEyeStatusSettings* settings,
        MGFEyeStatusContext* result);

/*! \brief Create a MGFEyeStatusContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFEyeStatusContext object
 */
MGF_CAPI MGFErrorCode MGF_make_eye_status_context_from_memory(
        const void* config_data, const MGFEyeStatusSettings* settings,
        MGFEyeStatusContext* result);

/*! \brief Predict the eye statuses of the given faces.
 * \param[in] ctx The MGFEyeStatusContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_eye_status(
        MGFEyeStatusContext ctx, MGFImage* image, const MGFLandmarkMap* faces,
        size_t batch_size, const MGFLeftRightEyeStatus** result);

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
