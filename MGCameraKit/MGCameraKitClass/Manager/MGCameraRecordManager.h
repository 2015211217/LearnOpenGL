//
//  MGCameraRecordManager.h
//  MGFaceIDGeneralModule
//
//  Created by MegviiDev on 2018/5/18.
//  Copyright © 2018年 Megvii. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MGCameraRecordDelegate.h"
#import <CoreMedia/CoreMedia.h>

typedef enum : NSUInteger {
    MGCameraRecordStatusIdle = 0,
    MGCameraRecordStatusPreparingToRecord,
    MGCameraRecordStatusRecording,
    MGCameraRecordStatusFinishingRecordingPart1, // waiting for inflight buffers to be appended
    MGCameraRecordStatusFinishingRecordingPart2, // calling finish writing on the asset writer
    MGCameraRecordStatusFinished,                // terminal state
    MGCameraRecordStatusFailed                   // terminal state
} MGCameraRecordStatus;  // internal state machine

@interface MGCameraRecordManager : NSObject

@property (nonatomic, assign) MGCameraRecordStatus status;

- (id)initWithURL:(NSURL *)URL;

// Only one audio and video track each are allowed.
- (void)addVideoTrackWithSourceFormatDescription:(CMFormatDescriptionRef)formatDescription transform:(CGAffineTransform)transform;
- (void)addAudioTrackWithSourceFormatDescription:(CMFormatDescriptionRef)formatDescription;

- (void)setDelegate:(id<MGCameraRecordDelegate>)delegate callbackQueue:(dispatch_queue_t)delegateCallbackQueue; // delegate is weak referenced

- (void)prepareToRecord; // Asynchronous, might take several hunderd milliseconds. When finished the delegate's recorderDidFinishPreparing: or recorder:didFailWithError: method will be called.

- (void)appendVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;
- (void)appendVideoPixelBuffer:(CVPixelBufferRef)pixelBuffer withPresentationTime:(CMTime)presentationTime;
- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)finishRecording; // Asynchronous, might take several hundred milliseconds. When finished the delegate's recorderDidFinishRecording: or recorder:didFailWithError: method will be called.
- (void)stopRecording;

@end
