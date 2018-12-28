/* -*- mode:c -*- */
#pragma once

/* \file include/megcommon-c/misc.h
 * \brief This file defines the functions hard to categorized.
 */

#include <stddef.h>
#include <stdint.h>

#include "macro.h"
#include "struct.h"

MGF_CAPI_BEGIN

/*! \brief Release an object made from MGF_make_xxx.
 * \param[in] ptr The pointer to the object to be released
 *
 * An object cannot be released twice, and releasing a null pointer has no
 * effects.
 */
MGF_CAPI void MGF_release(void* ptr);

/*! \brief Clean up the library.
 *
 * In some situations, the program may crash during termination because of the
 * order of destruction of the global objects used in the library. To avoid the
 * crash, it is encouraged to call this function before the exit of the program
 * to clean up the library.
 *
 * The behavior is undefined to call any of API functions of the library after
 * it has been cleaned up.
 */
MGF_CAPI void MGF_shutdown();

/*! \brief Describe the models in the given context.
 *
 * The buffer of the description is managed by the context object, which is
 * reclaimed when the context object is released.
 *
 * \param[in] ctx The context object
 * \param[out] desc The pointer to the description buffer.
 */
MGF_CAPI MGFErrorCode MGF_describe(void* ctx, const char** desc);

/*! \brief The color space that a model requires.
 */
typedef enum MGFColorSpace {
    MGF_GRAY_SCALE = 1 << 0,
    MGF_BGR = 1 << 1,
    MGF_DEPTH = 1 << 2,
} MGFColorSpace;

/*! \brief Return the desired colors of the given context.
 *
 * \param[in] ctx The context object
 * \param[out] result The desired color spaces by bit-or.
 */
MGF_CAPI MGFErrorCode MGF_get_color_spaces(void* ctx, MGFColorSpace* result);

/*! \brief The global options.
 */
typedef enum MGFGlobalOption {
    /*! \brief Disable the model cache in order to reduce the memory cost.
     *
     * The model cache can reduce the memory usage if the same model is loaded
     * more than once. However, it also causes the model to be persistent in the
     * memory through the execution of the process.
     */
    MGF_DISABLE_MODEL_CACHE = 1,

    /*! \brief Disable the sanity check in order to reduce the time of the first
     * run of a context.
     *
     * The var sanity check procedure ensures that the device memory is
     * functioning, which is essential for the graphic memory. However, it
     * causes the time of the first run to be much slower than its average time.
     */
    MGF_DISABLE_VAR_SANITY_CHECK_FIRST_RUN,

    /*! \brief Enable the debug mode in megface.
     *
     * The debug mode can help MGF_API user to print intermediate results.
     * The debug output contains how much time and memory consumed by every
     * module.
     */
    MGF_ENABLE_DEBUG_MODE,

    /*! \brief Enable model warming up.
     *
     * The warming up procedure will speed up the first running of model .
     * However this will slightly slow down the speed of model loading.
     */
    MGF_ENABLE_MODEL_WARMING_UP,

    /*! \brief Enable sharing model memory in MegBrain
     *
     * If this option is enabled, then MGF_make_*_from_memory() calls would
     * modify and decrypt the input buffer inplace, and ask MegBrain to reuse
     * the memory for parameter storage.
     *
     * It is the caller's responsibility to ensure that the lifespan of the
     * buffer passed to MGF_make*_from_memory() is longer than that of the
     * created handler.
     *
     * Be careful when this option is enabled but MGF_DISABLE_MODEL_CACHE is not
     * enabled: in such case, the memory buffer must remain valid while model
     * cache might be used.
     *
     * This option must be used with extreme caution. It is currently only used
     * in TEE.
     */
    MGF_ENABLE_SHARE_MODEL_MEMORY,

    /*! \brief Reduce memory usage by requiring that only one face would be
     *      passed to attribute/feature drivers.
     *
     * Memory usage can be reduced because megbrain graphs would have constant
     * var shape. The cost is that batch size must be one.
     */
    MGF_ENABLE_SINGLE_BATCH_MODE,

} MGFGlobalOption;

/*! \brief Set the global option to be the desired value.
 */
MGF_CAPI MGFErrorCode MGF_set_global_option(MGFGlobalOption option, int value);

/*! \brief Get the value of the global option.
 */
MGF_CAPI MGFErrorCode MGF_get_global_option(MGFGlobalOption option, int* value);

typedef enum MGFOpenclSearchMode {
    /*! \brief search all algos, bruth force. 
     */ 
    MGF_FULL_SEARCH = 0,

    /*! \brief search part of the algos, for fast searching. 
     * Default search mode. 
     */
    MGF_FAST_SEARCH = 1

} MGFOpenclSearchMode;

/*! \brief Set program cache file path to be used by opencl backend
 */
MGF_CAPI MGFErrorCode MGF_set_opencl_cache(const char* path);

/*! \brief Set program algo policy file name to be used by opencl backend
 */
MGF_CAPI MGFErrorCode MGF_set_opencl_algo_policy(const void* algo_policy_bin, const size_t bin_size);

/*! \brief Set opencl algo cache search mode 
 * \[param in] algo_cache_path the file saving the searched algo cache
 * \[param in] search_mode algo cache search mode
 */
MGF_CAPI MGFErrorCode MGF_set_opencl_search_algo(const char* algo_cache_path, MGFOpenclSearchMode search_mode = MGF_FAST_SEARCH);

/*! \brief Clear global data related to opencl
 
 * This would be automatically called in MGF_shutdown()
 */
MGF_CAPI MGFErrorCode MGF_clear_opencl_global_data();

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
