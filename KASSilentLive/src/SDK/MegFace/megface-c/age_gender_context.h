/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/age_gender_context.h
 * \brief This file defines the functions to predict ages and genders.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The age and gender of a face.
 * \ingroup dtype
 */
typedef struct MGFAgeGender {
    float age;
    MGFGender gender;
    float gender_prob[MGF_GENDER_COUNT];
} MGFAgeGender;

/*! \brief The settings of a MGFAgeGenderContext object.
 */
typedef struct MGFAgeGenderSettings {
    MGFDeviceOption device; /*!< The computing device. */
} MGFAgeGenderSettings;

/*! \brief The pointer to a MGFAgeGenderContext object.
 */
typedef void* MGFAgeGenderContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFAgeGenderContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFAgeGenderContext object
 */
MGF_CAPI MGFErrorCode MGF_make_age_gender_context_from_file(
        const char* config_path, const MGFAgeGenderSettings* settings,
        MGFAgeGenderContext* result);

/*! \brief Create a MGFAgeGenderContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFAgeGenderContext object
 */
MGF_CAPI MGFErrorCode MGF_make_age_gender_context_from_memory(
        const void* config_data, const MGFAgeGenderSettings* settings,
        MGFAgeGenderContext* result);

/*! \brief Predict the age and gender of the given faces.
 * \param[in] ctx The MGFAgeGenderContext object
 * \param[in] images The start address of the MGFImage array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_age_gender(MGFAgeGenderContext ctx,
                                             MGFImage* images,
                                             const MGFLandmarkMap* faces,
                                             size_t batch_size,
                                             const MGFAgeGender** result);

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
