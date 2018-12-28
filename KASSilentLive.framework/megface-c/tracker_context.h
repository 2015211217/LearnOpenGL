/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/tracker_context.h
 * \brief This file defines the functions to track faces.
 */

#include <stddef.h>
#include <stdint.h>

#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/macro.h"
#include "megface-c/misc.h"
#include "megface-c/pose_context.h"
#include "megface-c/struct.h"

/*! \brief The maximum of the number of detectors.
 */
#define MGF_MAX_TRACKER_DETECTORS 16

/*! \brief The type of the tracker.
 */
typedef enum MGFTrackerType {
    /*! \brief The detectors work independently.
     *
     * Each detector is controlled by its own options. Each time the tracker
     * assigns a new frame to the detector, the detector preprocesses the image
     * according to its own options, predicting the faces and returning the
     * results, independent of other detectors.
     */
    MGF_INDEPENDENT_DETECTOR_TRACKER = 0,

    /* \brief The detectors cooperate on a global state automaton.
     *
     * Each time the tracker assigns a new frame to the detector, the detector
     * retrieves the next region to detect from the global state automaton and
     * then advance it.
     *
     * For a 4x3 grid, the status automaton has 13 states and the images is
     * splitted to 4x3 overlapping cells. The first 12 states correspond to the
     * 12 cells, respectively. In the last state, the detector detects the
     * thumbnail of the image to find the faces larger than any of the cells.
     */
    MGF_GRID_DETECTOR_TRACKER = 1,

    /* \brief The detector works synchronously with the tracker.
     */
    MGF_SYNC_DETECTOR_TRACKER = 2,
} MGFTrackerType;

/*! \brief The options of the detectors.
 * /see MGFDetectorOptions
 */
typedef struct MGFTrackerDetectorOptions {
    MGFRect roi;
    size_t min_face;
    MGFOrient orient;

    /*! \brief The work load of the detector thread.
     *
     * Its value is between 0 and 1. If the work load is 0.3, the detector
     * thread is computing in 30% of the time and sleeping in the rest 70% of
     * the time.
     *
     * Any value below 0 or above 1 is illegal, and the behavior is undefined.
     */
    float work_load;
} MGFTrackerDetectorOptions;

/*! \brief The settings of a tracker with independent detectors.
 */
typedef struct MGFIndenpendentDetectorTracker {
    MGFDeviceOption tracker_device;

    int num_detectors;
    MGFDeviceOption detector_devices[MGF_MAX_TRACKER_DETECTORS];
    MGFTrackerDetectorOptions detector_options[MGF_MAX_TRACKER_DETECTORS];

    /*! \brief The missing tolerance.
     *
     * If the confidence of a track is below a threshold, the tracker will not
     * be deleted at once, but hidden temporarily in the internal state of the
     * tracker. Only after N consecutive frames in which the confidence scores
     * are all below the threshold, will the track be deleted. Otherwise, the
     * track will be resumed.
     */
    int missing_tolerance;

    /*! \brief The delay between detection and tracking. At least 1.
     */
    int delay;

    /*! \breif The maximum number of faces to track.
     *
     * The detector is supended when the number of tracked faces reached this
     * value.
     */
    int max_num_faces;
} MGFIndenpendentDetectorTracker;

/*! \brief The settings of a tracker with the detectors that share a global
 * state automaton for grid.
 */
typedef struct MGFGridDetectorTracker {
    MGFDeviceOption tracker_device;

    int num_detectors;
    MGFDeviceOption detector_devices[MGF_MAX_TRACKER_DETECTORS];
    MGFTrackerDetectorOptions detector_shared_options;

    /*! \brief The missing tolerance.
     *
     * If the confidence of a track is below a threshold, the tracker will not
     * be deleted at once, but hidden temporarily in the internal state of the
     * tracker. Only after N consecutive frames in which the confidence scores
     * are all below the threshold, will the track be deleted. Otherwise, the
     * track will be resumed.
     */
    int missing_tolerance;

    /*! \brief The delay between detection and tracking. At least 1.
     */
    int delay;

    size_t grid_num_row;
    size_t grid_num_column;

    /*! \breif The maximum number of faces to track.
     *
     * The detector is supended when the number of tracked faces reached this
     * value.
     */
    int max_num_faces;
} MGFGridDetectorTracker;

typedef struct MGFSyncDetectorTracker {
    MGFDeviceOption tracker_device; /*!< Device for the tracker and detector. */

    /*! \brief The options for the detector.
     *
     * work_load is useless in this settings.
     */
    MGFTrackerDetectorOptions detector_options;

    /*! \brief The missing tolerance.
     *
     * If the confidence of a track is below a threshold, the tracker will not
     * be deleted at once, but hidden temporarily in the internal state of the
     * tracker. Only after N consecutive frames in which the confidence scores
     * are all below the threshold, will the track be deleted. Otherwise, the
     * track will be resumed.
     */
    int missing_tolerance;

    size_t grid_num_row;
    size_t grid_num_column;

    /*! \breif The maximum number of faces to track.
     *
     * The detector is supended when the number of tracked faces reached this
     * value.
     */
    int max_num_faces;
} MGFSyncDetectorTracker;

/*! \brief The settings of a tracker.
 */
typedef struct MGFTrackerSettings {
    MGFTrackerType type;
    union {
        MGFIndenpendentDetectorTracker indep;
        MGFGridDetectorTracker grid;
        MGFSyncDetectorTracker sync;
    };
    bool allow_single_batch; /*!< The batch size to allow single batch */
} MGFTrackerSettings;

/*! \brief The tracked face structure.
 * \see MGFDetectedFace
 */
typedef struct MGFTrackedFace {
    uint64_t track_id; /*!< The unique track id. */
    float confidence;
    MGFRect rect;
    MGFLandmarkMap landmark;

    int attr_flags;
    MGFPose pose;

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
} MGFTrackedFace;

typedef enum MGFTrackedFaceAttrFlag {
    MGF_TRACK_ATTR_POSE = 1 << 0,
} MGFTrackedFaceAttrFlag;

/*! \brief The tracker result.
 * \see MGFDetectorResult
 */
typedef struct MGFTrackerResult {
    const MGFTrackedFace* items;
    size_t size;
} MGFTrackerResult;

/*! \brief The pointer to a MGFTrackerContext object.
 */
typedef void* MGFTrackerContext;

MGF_CAPI_BEGIN

/*! \brief Create a MGFTrackerContext object from a configuration file.
 * \param[in] config_path The configuration to load
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFTrackerContext object
 */
MGF_CAPI MGFErrorCode MGF_make_tracker_context_from_file(
        const char* config_path, const MGFTrackerSettings* settings,
        MGFTrackerContext* result);

/*! \brief Create a MGFTrackerContext object from a configuration in the
 * memory.
 * \param[in] config_data The address of the configuration data (the base
 * address + the offset of the configuration in the packed data)
 * \param[in] settings The settings of the context (NULL for default settings)
 * \param[out] result The MGFTrackerContext object
 */
MGF_CAPI MGFErrorCode MGF_make_tracker_context_from_memory(
        const void* config_data, const MGFTrackerSettings* settings,
        MGFTrackerContext* result);

/*! \brief Track old faces and detect new ones.
 * \param[in] ctx The MGFTrackerContext object
 * \param[in] frame The image to be tracked
 * \param[result] The pointer to the read-only tracking result
 */
MGF_CAPI MGFErrorCode MGF_track_frame(MGFTrackerContext ctx, MGFImage frame,
                                      const MGFTrackerResult** result);

/*! \brief Set the detector options of a given detector.
 * \parma[in] ctx The MGFTrackerContext object
 * \param[in] detector_idx The index of the detector, starting from 0
 * \param[in] options The detector option
 *
 * If detector_idx = -1, all the detectors will be affected.
 *
 * Only -1 is allowed in grid tracker.
 */
MGF_CAPI MGFErrorCode
MGF_set_tracker_detector_options(MGFTrackerContext ctx, int detector_idx,
                                 const MGFTrackerDetectorOptions* options);

/*! \brief Remove a track from being tracked.
 * \param[in] ctx The MGFTrackerContext object
 * \param[in] track_id The id of the track to be removed
 */
MGF_CAPI MGFErrorCode MGF_remove_track(MGFTrackerContext ctx,
                                       uint64_t track_id);

/*! \brief Clear the internal state of the tracker.
 * \param[in] ctx The MGFTrackerContext object
 *
 * The tracker can be used to track another video stream after the internal
 * state is cleared.
 */
MGF_CAPI MGFErrorCode MGF_reset_tracker_context(MGFTrackerContext ctx);

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
