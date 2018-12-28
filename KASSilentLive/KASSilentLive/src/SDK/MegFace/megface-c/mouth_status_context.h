/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/mouth_status_context.h
 * \brief This file defines the functions to predict eye statuses.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The status of a mouth.
 * \ingroup dtype
 */
typedef enum MGFMouthStatusEnum {
    MGF_MOUTH_MASK_OR_RESPIRATOR = 0,
    MGF_MOUTH_OTHER_OCCLUSION,
    MGF_MOUTH_CLOSE,
    MGF_MOUTH_OPEN,
    MGF_MOUTH_STATUS_COUNT
} MGFMouthStatusEnum;

typedef struct MGFMouthStatus {
    MGFMouthStatusEnum status;
    float prob[MGF_MOUTH_STATUS_COUNT];
} MGFMouthStatus;

/*! \brief The settings of a MGFMouthStatusContext object.
 */
typedef struct MGFMouthStatusSettings {
    MGFDeviceOption device; /*!< The computing device. */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFMouthStatusSettings;

/*! \brief The pointer to a MGFMouthStatusContext object.
 */
typedef void* MGFMouthStatusContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFMouthStatusContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFMouthStatusContext object
 */
MGF_CAPI MGFErrorCode MGF_make_mouth_status_context_from_file(
        const char* config_path, const MGFMouthStatusSettings* settings,
        MGFMouthStatusContext* result);

/*! \brief Create a MGFMouthStatusContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFMouthStatusContext object
 */
MGF_CAPI MGFErrorCode MGF_make_mouth_status_context_from_memory(
        const void* config_data, const MGFMouthStatusSettings* settings,
        MGFMouthStatusContext* result);

/*! \brief Predict the mouth status of the given faces.
 * \param[in] ctx The MGFMouthStatusContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only prediction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_predict_mouth_status(MGFMouthStatusContext ctx,
                                               MGFImage* image,
                                               const MGFLandmarkMap* faces,
                                               size_t batch_size,
                                               const MGFMouthStatus** result);

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
