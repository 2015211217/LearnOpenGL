/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/feature_context.h
 * \brief This file defines the functions to extract features.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/struct.h"

/*! \brief The feature extractor settings.
 */
typedef struct MGFFeatureSettings {
    MGFDeviceOption device; /*!< The device on which the feature model runs. */
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFFeatureSettings;

/*! \brief The extracted feature.
 *
 * The features are encrypted as byte stream.
 */
typedef struct MGFFeature {
    const char* data;
    size_t size;
} MGFFeature;

/*! \brief The feature comparison method.
 */
typedef enum MGFComparisonMethod {
    MGF_COMPARISON_METHOD_L2_SIGMOID = 0,
} MGFComparisonMethod;

/*! \brief The L2Sigmoid paramters.
 *
 * score = 100 / ( 1 + exp( alpha * ( ||a - b||_2 )^2 + beta ) )
 */
typedef struct MGFL2SigmoidParameters {
    float alpha;
    float beta;
    size_t feature_size;
} MGFL2SigmoidParameters;

/*! \brief The feature comparison method and parameters.
 */
typedef struct MGFComparisonAlgorithm {
    MGFComparisonMethod method;
    union {
        MGFL2SigmoidParameters l2_sigmoid_params;
    };
} MGFComparisonAlgorithm;

/*! \brief The feature score thresholds.
 *
 * The thresholds are only advisory, the performance of which highly depends on
 * the practical situation.
 */
typedef struct MGFFeatureScoreThresholds {
    float hundredth;
    float thousandth;
    float ten_thousandth;
    float hundred_thousandth;
    float millionth;
} MGFFeatureScoreThresholds;

/*! \brief The pointer to a feature context.
 */
typedef void* MGFFeatureContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFFeatureContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFFeatureContext object
 */
MGF_CAPI MGFErrorCode MGF_make_feature_context_from_file(
        const char* config_path, const MGFFeatureSettings* settings,
        MGFFeatureContext* result);

/*! \brief Create a MGFFeatureContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFFeatureContext object
 */
MGF_CAPI MGFErrorCode MGF_make_feature_context_from_memory(
        const void* config_data, const MGFFeatureSettings* settings,
        MGFFeatureContext* result);

/*! \brief Extract the features of the given faces.
 * \param[in] ctx The MGFFeatureContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only extraction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_extract(MGFFeatureContext ctx, MGFImage* images,
                                  const MGFLandmarkMap* faces,
                                  size_t batch_size, const MGFFeature** result);

/*! \brief Extract the features of the given faces, extract twice, flip the image at the second time
 * \param[in] ctx The MGFFeatureContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only extraction result, whose length
 * equals to batch_size
 */
MGF_CAPI MGFErrorCode MGF_extract_for_snpe(MGFFeatureContext ctx, MGFImage* images,
                                           const MGFLandmarkMap* faces,
                                           size_t batch_size,
                                           const MGFFeature** result);
                                           
/*! \brief Extract the features of the given faces.
 * \param[in] ctx The MGFFeatureContext object
 * \param[in] images The image array
 * \param[in] faces The face array, the length of which equals to that of the
 * image array
 * \param[in] batch_size The length of the image/face array
 * \param[result] The pointer to the read-only extraction result, whose length
 * equals to batch_size
 *
 * This API is DEPRECATED.
 */
MGF_CAPI MGF_DEPRECATED MGFErrorCode MGF_extract_from_rect(
        MGFFeatureContext ctx, MGFImage* images, const MGFRect* face_rects,
        size_t batch_size, const MGFFeature** result);

/*! \brief Get the score thresholds of the feature model.
 */
MGF_CAPI MGFErrorCode MGF_get_feature_score_thresholds(
        MGFFeatureContext ctx, MGFFeatureScoreThresholds* result);

/*! \brief Get the comparison method of the feature model.
 */
MGF_CAPI MGFErrorCode MGF_get_comparison_algorithm(
        MGFFeatureContext ctx, MGFComparisonAlgorithm* result);

/*! \brief Compare two features.
 */
MGF_CAPI MGFErrorCode MGF_compare_features(MGFFeatureContext ctx,
                                           const MGFFeature* a,
                                           const MGFFeature* b, float* result);

/*! \brief Compare two groups of features.
 *
 * The result are stored in an A-first manner.
 */
MGF_CAPI MGFErrorCode MGF_compare_features_MxN(MGFFeatureContext ctx,
                                               const MGFFeature* a,
                                               size_t a_count,
                                               const MGFFeature* b,
                                               size_t b_count, float** result);

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
