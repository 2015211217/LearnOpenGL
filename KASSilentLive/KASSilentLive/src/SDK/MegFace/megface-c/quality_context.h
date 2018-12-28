/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/quality_context.h
 * \brief This file defines the functions to predict quality.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The settings of a MGFQualityContext object.
 */
typedef struct MGFQualitySettings {
    MGFDeviceOption device; /*!< The computing device. */
} MGFQualitySettings;

/*! \brief The quality of a face.
 */
typedef struct MGFQuality {
    /*! \brief Whether the face is acceptable to be inserted into the database
     * of face features.
     */
    float acceptable;
} MGFQuality;

/*! \brief The pointer to a MGFQualityContext object.
 */
typedef void* MGFQualityContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFQualityContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFQualityContext object
 */
MGF_CAPI MGFErrorCode MGF_make_quality_context_from_file(
        const char* config_path, const MGFQualitySettings* settings,
        MGFQualityContext* result);

/*! \brief Create a MGFQualityContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFQualityContext object
 */
MGF_CAPI MGFErrorCode MGF_make_quality_context_from_memory(
        const void* config_data, const MGFQualitySettings* settings,
        MGFQualityContext* result);

/*! \brief Predict the quality of the given faces.
 * \param[in] ctx The MGFQualityContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_quality(MGFQualityContext ctx,
                                          MGFImage* images,
                                          const MGFLandmarkMap* faces,
                                          size_t batch_size,
                                          const MGFQuality** result);

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
