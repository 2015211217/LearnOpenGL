/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/landmark_context.h
 * \brief This file defines the functions to predict landmark.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/detector_context.h"
#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The settings of a MGFLandmarkRefinerContext object.
 */
typedef struct MGFLandmarkRefinerSettings {
    MGFDeviceOption device; /*!< The computing device. */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFLandmarkRefinerSettings;

/*! \brief The pointer to a MGFLandmarkRefinerContext object.
 */
typedef void* MGFLandmarkRefinerContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFLandmarkRefinerContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFLandmarkRefinerContext object
 */
MGF_CAPI MGFErrorCode MGF_make_landmark_refiner_context_from_file(
        const char* config_path, const MGFLandmarkRefinerSettings* settings,
        MGFLandmarkRefinerContext* result);

/*! \brief Create a MGFLandmarkRefinerContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFLandmarkRefinerContext object
 */
MGF_CAPI MGFErrorCode MGF_make_landmark_refiner_context_from_memory(
        const void* config_data, const MGFLandmarkRefinerSettings* settings,
        MGFLandmarkRefinerContext* result);

/*! \brief Refine the landmark in the given images.
 * \param[in] ctx The MGFLandmarkRefinerContext object
 * \param[in] images The image array
 * \param[in] landmark_corse The corse landmark array, the length of which
 * equals to that of the image array \param[in] batch_size The length of the
 * image/face array \param[result] The pointer to the read-only refined result,
 * whose length equals to batch_size
 */
MGF_CAPI MGFErrorCode
MGF_predict_landmark_refine(MGFLandmarkRefinerContext ctx, MGFImage* images,
                            const MGFLandmarkMap* landmark_corse,
                            size_t batch_size, const MGFLandmarkMap** result);

MGF_CAPI MGFErrorCode
MGF_predict_landmark_attribute(MGFLandmarkRefinerContext ctx, MGFImage* images,
                            const MGFLandmarkMap* landmark_corse,
                            size_t batch_size, const MGFDetectedFace** result);

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
