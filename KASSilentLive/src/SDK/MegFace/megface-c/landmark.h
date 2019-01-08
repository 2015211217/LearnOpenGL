/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/landmark.h
 * \brief This file defines the landmark tags and related structures.
 */

#include "megcommon-c/landmark.h"
#include "megface-c/struct.h"

/*! \deprecated Use MGFLandmarkAttributeFlag instead
 * \brief Flags to indicate what properties in MGFLandmarkExtension.
 */
typedef enum MGFLandmarkExtensionFlag {
    MGF_LMKEXT_OCCLUSION = 1 << 0,
    MGF_LMKEXT_EYEOC = 1 << 1,
    MGF_LMKEXT_POSE = 1 << 2,
} MGFLandmarkExtensionFlag;

/*! \deprecated Use MGFLandmarkAttribute instead
 * \brief Extended information for MGFLandmarkMap.
 *
 * The flag is bitwise value combined by MGFLandmarkExtendsionFlag, which
 * represents the valid information in extension, 1 is fully occluded.
 * The occlusion are stored in tag-occlusion pairs whoes size and tags are in
 * attached MGFLandmarkMap, 1 is fully occluded.
 * The left_eye_close_score and right_eye_close_score are represented for the
 * eye closed confidence, 1 is fully closed.
 * The roll, pitch, yaw, is space position angle of head.
 */
typedef struct MGFLandmarkExtension {
    int flag;
    float* occlusion;
    float left_eye_close_score;
    float right_eye_close_score;
    float roll;
    float pitch;
    float yaw;
} MGFLandmarkExtension;

/*! \brief Flags to indicate what properties are valid in MGFLandmarkAttribute.
 */
typedef enum MGFLandmarkAttributeFlag {
    MGF_LMKATTR_LANDMARK_OCCLUSION = 1 << 0,
    MGF_LMKATTR_EYE_CLOSED_STATUS = 1 << 1,
    MGF_LMKATTR_FACE_POSE = 1 << 2,
    MGF_LMKATTR_BLURRINESS = 1 << 3,
    MGF_LMKATTR_GAZE = 1 << 4,
    MGF_LMKATTR_AGE = 1 << 5,
    MGF_LMKATTR_GENDER = 1 << 6,
    MGF_LMKATTR_EYE_OCCLUSION = 1 << 7,
    MGF_LMKATTR_MOUTH_OCCLUSION = 1 << 8,
    MGF_LMKATTR_MOUTH_OPEN_STATUS = 1 << 9,
    MGF_LMKATTR_PRED = 1 << 10,
    MGF_LMKATTR_PROD = 1 << 11,
    MGF_LMKATTR_ATTENTION = 1 << 12,
    MGF_LMKATTR_NOSE_OCCLUSION = 1 << 13,
    MGF_LMKATTR_MINORITY = 1 << 14,
    MGF_LMKATTR_HEADWEAR = 1 << 15,
    MGF_LMKATTR_BEARD = 1 << 16,
    MGF_LMKATTR_RACE = 1 << 17,
    MGF_LMKATTR_EXPRESSION = 1 << 18,
} MGFLandmarkAttributeFlag;

/*! \brief The score describes eyes closed status.
 *
 * The range of score is from 0 to 1. Value 1 means fully closed.
 */
typedef struct MGFEyeClosedScore {
    float left_eye;  /*!< left eye closed score. */
    float right_eye; /*!< right eye closed score. */
} MGFEyeClosedScore;

/*! \brief The people's gazing points on the image.
 *
 * Gaze points describe the screen points a person looking at.
 * Pupil points describe the person's pupil position.
 */
typedef struct MGFGaze {
    MGFPoint2f left_pupil;  /*!< left pupil position */
    MGFPoint2f left_gaze;   /*!< left eye gazing points */
    MGFPoint2f right_pupil; /*!< right pupil position */
    MGFPoint2f right_gaze;  /*!< right eye gazing points */
} MGFGaze;

/*! \brief The gender of a person.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable gender.
 */
typedef struct MGFGenderProb {
    /*! \brief The most probable gender of a person.
     */
    MGFGender gender;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_GENDER_COUNT];
} MGFGenderProb;

/*! \brief The occlusion status of eyes.
 * \ingroup dtype.
 */
typedef enum MGFEyeOcclusionEnum {
    MGF_EYE_OCC_NO,
    MGF_EYE_OCC_TRANSPARENT_GLASSES,
    MGF_EYE_OCC_SUNGLASSES,
    MGF_EYE_OCC_OTHERS,
    MGF_EYE_OCC_COUNT,
} MGFEyeOcclusionEnum;

/*! \brief The eye occlusion status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable eye occlusion
 * status.
 */
typedef struct MGFEyeOcclusionStatus {
    /*! \brief The most probable left eye occlusion status.
     */
    MGFEyeOcclusionEnum left_eye;

    /*! \brief The most probable right eye occlusion status.
     */
    MGFEyeOcclusionEnum right_eye;

    /*! \brief The original left eye occlusion probability of each class.
     */
    float left_eye_prob[MGF_EYE_OCC_COUNT];

    /*! \brief The original right eye occlusion probability of each class.
     */
    float right_eye_prob[MGF_EYE_OCC_COUNT];
} MGFEyeOcclusionStatus;

/*! \brief The occlusion status of a mouth.
 * \ingroup dtype.
 */
typedef enum MGFMouthOcclusionEnum {
    MGF_MOUTH_OCC_NO,
    MGF_MOUTH_OCC_MASK,
    MGF_MOUTH_OCC_RESPIRATOR,
    MGF_MOUTH_OCC_OTHERS,
    MGF_MOUTH_OCC_COUNT,
} MGFMouthOcclusionEnum;

/*! \brief The mouth occlusion status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable mouth occlusion
 * status.
 */
typedef struct MGFMouthOcclusionStatus {
    /*! \brief The most probable mouth occlusion status.
     */
    MGFMouthOcclusionEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_MOUTH_OCC_COUNT];
} MGFMouthOcclusionStatus;

/*! \brief The nose occlusion status.
 * \ingroup dtype.
 */
typedef enum MGFNoseOcclusionEnum {
    MGF_NOSE_OCCLUSION_NO,
    MGF_NOSE_OCCLUSION_MASK,
    MGF_NOSE_OCCLUSION_COUNT
} MGFNoseOcclusionEnum;

/*! \brief The nose occlusion status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFNoseOcclusionStatus {
    /*! \brief The most probable nose occlusion status.
     */
    MGFNoseOcclusionEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_NOSE_OCCLUSION_COUNT];
} MGFNoseOcclusionStatus;

/*! \brief The minority status.
 * \ingroup dtype.
 */
typedef enum MGFMinorityEnum {
    MGF_MINORITY_TAOISM,
    MGF_MINORITY_OTHERS,
    MGF_MINORITY_COUNT
} MGFMinorityEnum;

/*! \brief The minority status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFMinorityStatus {
    /*! \brief The most probable minority status.
     */
    MGFMinorityEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_MINORITY_COUNT];
} MGFMinorityStatus;

/*! \brief The headwear status.
 * \ingroup dtype.
 */
typedef enum MGFHeadwearEnum {
    MGF_HEADWEAR_HAT,
    MGF_HEADWEAR_LITTLE_HAIR,
    MGF_HEADWEAR_SHORT_HAIR,
    MGF_HEADWEAR_LONG_HAIR,
    MGF_HEADWEAR_OTHERS,
    MGF_HEADWEAR_COUNT
} MGFHeadwearEnum;

/*! \brief The headwear status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFHeadwearStatus {
    /*! \brief The most probable headwear status.
     */
    MGFHeadwearEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_HEADWEAR_COUNT];
} MGFHeadwearStatus;

/*! \brief The beard status.
 * \ingroup dtype.
 */
typedef enum MGFBeardEnum {
    MGF_BEARD_NO_BEARD,
    MGF_BEARD_MOUSTACHE,
    MGF_BEARD_WHISKER,
    MGF_BEARD_OTHERS,
    MGF_BEARD_COUNT
} MGFBeardEnum;

/*! \brief The beard status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFBeardStatus {
    /*! \brief The most probable beard status.
     */
    MGFBeardEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_BEARD_COUNT];
} MGFBeardStatus;

/*! \brief The race status.
 * \ingroup dtype.
 */
typedef enum MGFRaceEnum {
    MGF_RACE_YELLOW,
    MGF_RACE_BLACK,
    MGF_RACE_WHITE,
    MGF_RACE_BROWN,
    MGF_RACE_OTHERS,
    MGF_RACE_COUNT
} MGFRaceEnum;

/*! \brief The race status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFRaceStatus {
    /*! \brief The most probable race status.
     */
    MGFRaceEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_RACE_COUNT];
} MGFRaceStatus;

/*! \brief The expression status.
 * \ingroup dtype.
 */
typedef enum MGFExpressionEnum {
    MGF_EXPRESSION_HAPPY,
    MGF_EXPRESSION_OTHERs,
    MGF_EXPRESSION_COUNT
} MGFExpressionEnum;

/*! \brief The expression status.
 *
 * It is a classified status. The sum of each class prob is 1.
 * The class with largest probability is the most probable expression
 * status.
 */
typedef struct MGFExpressionStatus {
    /*! \brief The most probable expression status.
     */
    MGFExpressionEnum status;

    /*! \brief The original probability of each class.
     */
    float prob[MGF_EXPRESSION_COUNT];
} MGFExpressionStatus;

/*! \brief Attribute informations infferred from landmark.
 */
typedef struct MGFLandmarkAttribute {
    /*! \brief The flag indicating the valid status of each member variable.
     *
     * It is bitwise value combined by MGFLandmarkAttributeFlag.
     */
    int flag;

    /*! \brief The occlusion confidence of the landmarks.
     *
     * It is a float array pointer ranging from 0 to 1. Value 1 means being
     * fully occluded. Its size and tags store in attached MGFLandmarkMap.
     *
     * If flag indicates that this information is invalid, the value would be
     * NULL.
     */
    float* landmark_occlusion;

    /*! \brief The eyes closed score.
     *
     * It contains two floats ranging from 0 to 1. Value 1 means the eye is
     * fully closed.
     */
    MGFEyeClosedScore eye_closed_score;

    /*! \brief The pose of face.
     *
     * The pose is represented by Eular angle.
     */
    MGFPose face_pose;

    /*! \brief The blurriness of face.
     *
     * It is a float ranging from 0 to 1. Value 1 means the face is blurry.
     */
    float blurriness;

    /*! \brief the people's gazing points on the image.
     */
    MGFGaze gaze;

    /*! \brief The age of the face.
     */
    float age;

    /*! \brief The gender of the face.
     */
    MGFGenderProb gender;

    /*! \brief The occlusion status of the eyes.
     */
    MGFEyeOcclusionStatus eye_occlusion_status;

    /*! \brief The mouth open score.
     *
     * It is a float ranging from 0 to 1. Value 1 means the mouth is fully open.
     */
    float mouth_open_score;

    /*! \brief The mouth occlusion status
     */
    MGFMouthOcclusionStatus mouth_occlusion_status;

    /*! \brief The attention of the face.
     * The more the value is, the more the possibility of watching screen is.
     */
    float attention;
    
    /*! \brief The nose occlusion status
     */
    MGFNoseOcclusionStatus nose_occlusion_status;

    /*! \brief The minority status
     */
    MGFMinorityStatus minority_status;

    /*! \brief The headwear status
     */
    MGFHeadwearStatus headwear_status;

    /*! \brief The beard status
     */
    MGFBeardStatus beard_status;

    /*! \brief The race status
     */
    MGFRaceStatus race_status;

    /*! \brief The expression status
     */
    MGFExpressionStatus expression_status;
} MGFLandmarkAttribute;

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
