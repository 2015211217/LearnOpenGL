/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/blurness_context.h
 * \brief This file defines the functions to predict blurness.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The settings of a MGFBlurnessContext object.
 */
typedef struct MGFBlurnessSettings {
    MGFDeviceOption device; /*!< The computing device. */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFBlurnessSettings;

/*! \brief The pointer to a MGFBlurnessContext object.
 */
typedef void* MGFBlurnessContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFBlurnessContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFBlurnessContext object
 */
MGF_CAPI MGFErrorCode MGF_make_blurness_context_from_file(
        const char* config_path, const MGFBlurnessSettings* settings,
        MGFBlurnessContext* result);

/*! \brief Create a MGFBlurnessContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFBlurnessContext object
 */
MGF_CAPI MGFErrorCode MGF_make_blurness_context_from_memory(
        const void* config_data, const MGFBlurnessSettings* settings,
        MGFBlurnessContext* result);

/*! \brief Predict the blurness of the given faces.
 * \param[in] ctx The MGFBlurnessContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_blurness(MGFBlurnessContext ctx,
                                           MGFImage* images,
                                           const MGFLandmarkMap* faces,
                                           size_t batch_size,
                                           const float** result);

/*! \brief Predict the blurness of the given faces.
 * \param[in] ctx The MGFBlurnessContext object
 * \param[in] images The image array
 * \param[in] rect The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_blurness_from_rect(MGFBlurnessContext ctx,
                                                     MGFImage* images,
                                                     const MGFScoreRect* faces,
                                                     size_t batch_size,
                                                     const float** result);

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
