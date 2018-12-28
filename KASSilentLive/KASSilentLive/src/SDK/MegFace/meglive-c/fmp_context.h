/* -*- mode:c -*- */
#pragma once

#include "megcommon-c/image.h"
#include "megcommon-c/landmark.h"
#include "megcommon-c/macro.h"
#include "megcommon-c/struct.h"

/*! \brief The settings used to make a MGLFMPContext.
 */
typedef struct MGLFMPSettings {
    MGFDeviceOption device; /*!< The computing device. */
} MGLFMPSettings;

typedef struct MGLFMPResult {
    float pred; /*!< The liveness score: <0.5 live, >0.5 dead */

    float fabricate;
    float mask;
    float panorama;
} MGLFMPResult;

/*! \brief The pointer to a MGLFMPContext object.
 */
typedef void* MGLFMPContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGLFMPContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for the default
 * settings) \param[out] result The MGLFMPContext object
 */
MGF_CAPI MGFErrorCode MGL_make_fmp_context_from_file(
        const char* config_path, const MGLFMPSettings* settings,
        MGLFMPContext* result);

/*! \brief Create a MGLFMPContext object from a configuration in the memory.
 * \param[in] config_data The address of the configuration data
 * \param[in] settings The settings of the context (NULL for the default
 * settings) \param[out] result The MGLFMPContext object
 */
MGF_CAPI MGFErrorCode MGL_make_fmp_context_from_memory(
        const void* config_data, const MGLFMPSettings* settings,
        MGLFMPContext* result);

#define MGL_FMP_RESULT_FABRICATE_FLAG (1 << 0)
#define MGL_FMP_RESULT_MASK_FLAG (1 << 1)
#define MGL_FMP_RESULT_PANORAMA_FLAG (1 << 2)

/*! \brief Get the fmp-classification result flags
 * \param[in] ctx The MGLFMPContext object
 * \param[out] result The result flags
 */
MGF_CAPI MGFErrorCode MGL_fmp_get_result_flags(MGLFMPContext ctx,
                                               unsigned int* result);

/*! \brief Get the fmp-classification score
 * \param[in] ctx The MGLFMPContext object
 * \param[in] images The input image array
 * \param[in] landmarks The face's landmark array
 * \param[in] batch_size The length of the image/landmark array
 * \param[out] result The classification score
 */
MGF_CAPI MGFErrorCode MGL_fmp_classify(MGLFMPContext ctx, MGFImage* images,
                                       const MGFLandmarkMap* landmarks,
                                       size_t batch_size,
                                       const MGLFMPResult** result);

MGF_CAPI MGFErrorCode MGL_fmp_classify_pre(MGLFMPContext ctx, MGFImage* images,
                                           const MGFLandmarkMap* landmarks,
                                           size_t batch_size, void*& result);

MGF_CAPI MGFErrorCode MGL_fmp_classify_result(MGLFMPContext ctx,
                                              MGFImage* images,
                                              const MGFLandmarkMap* landmarks,
                                              size_t batch_size, void* trans,
                                              const MGLFMPResult** result);

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
