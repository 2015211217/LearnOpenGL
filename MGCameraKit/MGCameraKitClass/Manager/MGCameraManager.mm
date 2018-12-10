//
//  MGCameraManager.m
//  MGFaceIDGeneralModule
//
//  Created by MegviiDev on 2018/5/18.
//  Copyright © 2018年 Megvii. All rights reserved.
//

#import "MGCameraManager.h"
#import "MGCameraRecordManager.h"
#import "MGCameraConfig.h"
#import "MGCameraImage.h"
#import <AVFoundation/AVFoundation.h>

@interface MGCameraManager () <AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate, MGCameraRecordDelegate>
{
    AVCaptureConnection *_audioConnection;
    AVCaptureConnection *_videoConnection;
    NSDictionary        *_audioCompressionSettings;
    AVCaptureDevice     *_videoDevice;
    
    dispatch_queue_t _videoQueue;
    
    int _recordCount;
    int _recordFPSCount;
    long _startRecordTime;
    BOOL _isSilentLive;
    BOOL _resetReocrd;
    BOOL _startVideo;
    
}

@property (nonatomic, assign) CMFormatDescriptionRef outputAudioFormatDescription;
@property (nonatomic, assign) CMFormatDescriptionRef outputVideoFormatDescription;

@property (nonatomic, strong) NSString* movieNameStr;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *videoPreviewLayer;
@property (nonatomic, copy) NSString *sessionPreset;
@property (nonatomic, strong) NSString *tempVideoPath;

@property (nonatomic, strong) MGCameraRecordManager *recordManager;

@property (nonatomic, assign) BOOL videoRecord;
@property (nonatomic, assign) BOOL videoSound;
@property (nonatomic, assign) BOOL startRecord;

@end

@implementation MGCameraManager

- (void)dealloc {
    [_recordManager finishRecording];
    _recordManager = nil;
    _audioConnection = nil;
    _videoConnection = nil;
    _delegate = nil;
    _sessionPreset = nil;
    _videoQueue = nil;
}

- (instancetype)initWithPreset:(NSString *)sessionPreset
               devicePosition:(AVCaptureDevicePosition)devicePosition
                  videoRecord:(BOOL)record
                   videoSound:(BOOL)sound
                     videoName:(NSString *)name{
    self = [super init];
    if (self) {
        self.sessionPreset = sessionPreset;
        _devicePosition = devicePosition;
        self.videoRecord = record;
        self.videoSound = sound;
        
        self.startRecord = NO;
        _isSilentLive = NO;
        _startVideo = NO;
        _resetReocrd = NO;
        _recordCount = 1;
        _startRecordTime = 0;
        _movieNameStr = name;
        _videoQueue = dispatch_queue_create("com.megvii.face.video", NULL);
        
        NSString *mediaType = AVMediaTypeVideo;
        [AVCaptureDevice requestAccessForMediaType:mediaType completionHandler:^(BOOL granted) {
            if (NO == granted) {
                [self videoError:MGCameraErrorNOPermission];
                [self stopRunning];
            }
        }];
    }
    return self;
}

+ (instancetype)videoPreset:(NSString *)sessionPreset
             devicePosition:(AVCaptureDevicePosition)devicePosition
                videoRecord:(BOOL)record
                 videoSound:(BOOL)sound
                  videoName:(NSString *)name{
    MGCameraManager* manager = [[MGCameraManager alloc] initWithPreset:sessionPreset
                                                        devicePosition:devicePosition
                                                           videoRecord:record
                                                            videoSound:sound
                                                             videoName:name];
    return manager;
}

#pragma mark - Default Video Config
- (NSString *)sessionPreset {
    if (!_sessionPreset) {
        _sessionPreset = AVCaptureSessionPreset640x480;
    }
    return _sessionPreset;
}

- (AVCaptureVideoPreviewLayer *)videoPreviewLayer {
    if (nil == _videoPreviewLayer) {
        _videoPreviewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:self.videoSession];
        [_videoPreviewLayer setFrame:CGRectMake(0, 0, MG_WIN_WIDTH, MG_WIN_HEIGHT)];
        [_videoPreviewLayer setVideoGravity:AVLayerVideoGravityResizeAspectFill];
    }
    return _videoPreviewLayer;
}

- (AVCaptureVideoPreviewLayer *)videoPreview {
    return self.videoPreviewLayer;
}

- (CMFormatDescriptionRef)formatDescription {
    return self.outputVideoFormatDescription;
}

- (dispatch_queue_t)getVideoQueue {
    return _videoQueue;
}

- (BOOL)videoSound {
    if (_videoRecord && _videoSound) {
        return YES;
    }
    return NO;
}

#pragma mark - VideoOperation
- (void)startRunning {
    NSString *mediaType = AVMediaTypeVideo;
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];
    if(authStatus == AVAuthorizationStatusRestricted ||
       authStatus == AVAuthorizationStatusDenied) {
        [self videoError:MGCameraErrorNOPermission];
        return;
    }
    [self initialSession];
    
    if (self.videoSession) {
        [self.videoSession startRunning];
    }
}

- (void)stopRunning {
    if (self.videoSession) {
        [self.videoSession stopRunning];
    }
}

- (void)startRecording {
    [self startRunning];
    
    if (!self.videoRecord) {
        return;
    }
    _startRecord = YES;
}

- (NSString *)stopRecording {
    _startRecord = NO;
    
    if (self.recordManager) {
        if (self.recordManager.status == MGCameraRecordStatusRecording) {
            [self.recordManager finishRecording];
        }
        [self.recordManager stopRecording];
        self.recordManager = nil;
    }
    return @"";
}

#pragma mark - SilentLive
- (void)silentLiveWithMoveName:(NSString *)nameStr {
    _isSilentLive = YES;
    _movieNameStr = nameStr;
}

- (void)startSilentLiveRecording:(NSUInteger)recordFPS {
    if (recordFPS == 0) {
        _startVideo = YES;
        return;
    }
    [self startRunning];
    _recordFPSCount = (int)recordFPS;
    if (self.videoRecord) {
        _startRecord = YES;
    }
}

- (void)resetSilentLiveRecording {
    _startVideo = NO;
    _resetReocrd = YES;
    _tempVideoPath = nil;
    _startRecordTime = 0;
    _recordCount = 0;
    if (self.recordManager != nil) {
        if (self.recordManager.status == MGCameraRecordStatusRecording) {
            [self.recordManager finishRecording];
        }
        [self.recordManager stopRecording];
        self.recordManager = nil;
    }
}

- (void)stopSilentLiveRecording {
    _startVideo = NO;
    _startRecordTime = 0;
}

#pragma mark - Init session
- (void)initialSession {
    if (!self.videoSession) {
        //  session
        _videoSession = [[AVCaptureSession alloc] init];
        //  Camera
        _videoDevice = [self cameraWithPosition:self.devicePosition];
        [self setMaxVideoFrame:60 videoDevice:_videoDevice];
        
        // input
        NSError *DeviceError;
        _videoInput = [[AVCaptureDeviceInput alloc] initWithDevice:_videoDevice error:&DeviceError];
        if (DeviceError) {
            [self videoError:MGCameraErrorNODevice];
            return;
        }
        if ([self.videoSession canAddInput:self.videoInput]) {
            [self.videoSession addInput:self.videoInput];
        }
        
        //  output
        AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
        [output setSampleBufferDelegate:self queue:_videoQueue];
        output.videoSettings = @{(id)kCVPixelBufferPixelFormatTypeKey:@(kCVPixelFormatType_32BGRA)};
        output.alwaysDiscardsLateVideoFrames = NO;
        
        if ([self.videoSession canAddOutput:output]) {
            [self.videoSession addOutput:output];
        }
        
        //  sessionPreset
        if ([self.videoSession canSetSessionPreset:self.sessionPreset]) {
            [self.videoSession setSessionPreset: self.sessionPreset];
        } else {
            [self videoError:MGCameraErrorNOPermission];
            return;
        }
        
        _videoConnection = [output connectionWithMediaType:AVMediaTypeVideo];
        _videoConnection.videoOrientation = self.videoOrientation;
        if (_isSilentLive == YES) {
            [output recommendedVideoSettingsForAssetWriterWithOutputFileType:AVFileTypeQuickTimeMovie];
        }
        
        //  Setting Video sound
        if (self.videoSound) {
            AVCaptureDevice *audioDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
            AVCaptureDeviceInput *audioIn = [[AVCaptureDeviceInput alloc] initWithDevice:audioDevice error:nil];
            if ([self.videoSession canAddInput:audioIn]) {
                [self.videoSession addInput:audioIn];
            }
            
            AVCaptureAudioDataOutput *audioOut = [[AVCaptureAudioDataOutput alloc] init];
            dispatch_queue_t audioCaptureQueue = dispatch_queue_create("com.megvii.audio", DISPATCH_QUEUE_SERIAL );
            [audioOut setSampleBufferDelegate:self queue:audioCaptureQueue];
            if ([self.videoSession canAddOutput:audioOut]) {
                [self.videoSession addOutput:audioOut];
            }
            _audioConnection = [audioOut connectionWithMediaType:AVMediaTypeAudio];
            output.alwaysDiscardsLateVideoFrames = YES;
            
            _audioCompressionSettings = [[audioOut recommendedAudioSettingsForAssetWriterWithOutputFileType:AVFileTypeQuickTimeMovie] copy];
        }
    }
}

#pragma mark - InitVideoRecord
- (void)initVideoRecord:(CMFormatDescriptionRef)formatDescription {
    if (!self.recordManager) {
        NSLog(@"================");
        NSString *moveName = [NSString stringWithFormat:@"%@", _movieNameStr];
        NSString* documentStr = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];

        _tempVideoPath = [NSString stringWithFormat:@"%@/%@", documentStr, moveName];
        
        
        NSURL *url = [[NSURL alloc] initFileURLWithPath:_tempVideoPath];
        MGCameraRecordManager* recordManager = [[MGCameraRecordManager alloc] initWithURL:url];
        
#if RECORD_AUDIO
        [recordManager addAudioTrackWithSourceFormatDescription:self.outputAudioFormatDescription];
#endif // RECORD_AUDIO
        
        CGAffineTransform videoTransform = [self transformFromVideoBufferOrientationToOrientation:(AVCaptureVideoOrientation)UIDeviceOrientationPortrait withAutoMirroring:NO]; // Front camera recording shouldn't be mirrored
        [recordManager addVideoTrackWithSourceFormatDescription:self.outputVideoFormatDescription transform:videoTransform];
        
        dispatch_queue_t callbackQueue = dispatch_queue_create("com.megvii.recordercallback", DISPATCH_QUEUE_SERIAL);
        [recordManager setDelegate:self callbackQueue:callbackQueue];
        self.recordManager = recordManager;
    }
    [self.recordManager prepareToRecord];
}

#pragma mark - Camera Device
- (AVCaptureDevice *)cameraWithPosition:(AVCaptureDevicePosition)position {
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices) {
        if ([device position] == position) {
            return device;
        }
    }
    return nil;
}

#pragma mark - Toggle Camera
- (void)toggleCamera:(id)sender {
    NSUInteger cameraCount = [[AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo] count];
    if (cameraCount > 1) {
        NSError *error;
        AVCaptureDeviceInput *newVideoInput;
        AVCaptureDevicePosition position = [[_videoInput device] position];
        if (position == AVCaptureDevicePositionBack) {
            newVideoInput = [[AVCaptureDeviceInput alloc] initWithDevice:[self cameraWithPosition:AVCaptureDevicePositionFront] error:&error];
        } else if (position == AVCaptureDevicePositionFront) {
            newVideoInput = [[AVCaptureDeviceInput alloc] initWithDevice:[self cameraWithPosition:AVCaptureDevicePositionBack] error:&error];
        } else {
            return;
        }
        
        if (newVideoInput) {
            [self.videoSession beginConfiguration];
            [self.videoSession removeInput:self.videoInput];
            if ([self.videoSession canAddInput:newVideoInput]) {
                [self.videoSession addInput:newVideoInput];
                _videoInput = newVideoInput;
            } else {
                [self.videoSession addInput:self.videoInput];
            }
            [self.videoSession commitConfiguration];
        } else if (error) {
            [self videoError:MGCameraErrorNODevice];
        }
    }
}

#pragma mark - MaxVideoFrame
- (void)setMaxVideoFrame:(NSInteger)frame videoDevice:(AVCaptureDevice *)videoDevice {
    for(AVCaptureDeviceFormat *vFormat in [videoDevice formats]) {
        CMFormatDescriptionRef description= vFormat.formatDescription;
        AVFrameRateRange *rateRange = (AVFrameRateRange*)[vFormat.videoSupportedFrameRateRanges objectAtIndex:0];
        float maxrate = rateRange.maxFrameRate;
        
        if(maxrate >= frame && CMFormatDescriptionGetMediaSubType(description)==kCVPixelFormatType_420YpCbCr8BiPlanarFullRange) {
            if (YES == [videoDevice lockForConfiguration:NULL]) {
                videoDevice.activeFormat = vFormat;
                [videoDevice setActiveVideoMinFrameDuration:CMTimeMake(1, int32_t(frame / 3))];
                [videoDevice setActiveVideoMaxFrameDuration:CMTimeMake(1, int32_t(frame))];
                [videoDevice unlockForConfiguration];
            }
        }
    }
}

#pragma mark - Video
- (void)appendVideoBuffer:(CMSampleBufferRef)sampleBuffer {
    @synchronized(self) {
        if (_startVideo == NO) {
            CMFormatDescriptionRef formatDescription = CMSampleBufferGetFormatDescription(sampleBuffer);
            if (_startRecord == YES && !self.recordManager) {
                [self initVideoRecord:formatDescription];
            }
        } else {
            if (self.recordManager && self.recordManager.status >= MGCameraRecordStatusRecording) {
                [self.recordManager appendVideoSampleBuffer:sampleBuffer];
            }
        }
    }
}

- (void)appendAudioBuffer:(CMSampleBufferRef)sampleBuffer {
    @synchronized(self) {
        if (self.recordManager) {
            [self.recordManager appendAudioSampleBuffer:sampleBuffer];
        }
    }
}

- (CGFloat)angleOffsetFromPortraitOrientationToOrientation:(AVCaptureVideoOrientation)orientation {
    CGFloat angle = 0.0;
    switch (orientation) {
        case AVCaptureVideoOrientationPortrait:
            angle = 0.0;
            break;
        case AVCaptureVideoOrientationPortraitUpsideDown:
            angle = M_PI;
            break;
        case AVCaptureVideoOrientationLandscapeRight:
            angle = -M_PI_2;
            break;
        case AVCaptureVideoOrientationLandscapeLeft:
            angle = M_PI_2;
            break;
        default:
            break;
    }
    return angle;
}

- (CGAffineTransform)transformFromVideoBufferOrientationToOrientation:(AVCaptureVideoOrientation)orientation withAutoMirroring:(BOOL)mirror {
    CGAffineTransform transform = CGAffineTransformIdentity;
    CGFloat orientationAngleOffset = [self angleOffsetFromPortraitOrientationToOrientation:orientation];
    CGFloat videoOrientationAngleOffset = [self angleOffsetFromPortraitOrientationToOrientation:self.videoOrientation];
        
    CGFloat angleOffset = orientationAngleOffset - videoOrientationAngleOffset;
    transform = CGAffineTransformMakeRotation(angleOffset);
    transform = CGAffineTransformRotate(transform, -M_PI);
    
    if (_videoDevice.position == AVCaptureDevicePositionFront) {
        if (mirror) {
            transform = CGAffineTransformScale(transform, -1, 1);
        } else {
            transform = CGAffineTransformRotate(transform, M_PI);
        }
    }
    return transform;
}

#pragma mark - AVCaptureVideoDataOutputSampleBufferDelegate
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    @autoreleasepool {
        if (connection == _videoConnection) {
            if (!self.outputVideoFormatDescription) {
                CMFormatDescriptionRef formatDescription = CMSampleBufferGetFormatDescription(sampleBuffer);
                usleep(10000);
                self.outputVideoFormatDescription = (CMFormatDescriptionRef)formatDescription;
            }
            if (_delegate && [_delegate respondsToSelector:@selector(mgCaptureOutput:didOutputSampleBuffer:fromConnection:)]) {
                [_delegate mgCaptureOutput:captureOutput
                     didOutputSampleBuffer:sampleBuffer
                            fromConnection:connection];
            }
            if (self.videoRecord && self.startRecord) {
                [self appendVideoBuffer:sampleBuffer];
            }
        } else if (connection == _audioConnection) {
            if (nil == self.outputAudioFormatDescription) {
                CMFormatDescriptionRef formatDescription = CMSampleBufferGetFormatDescription(sampleBuffer);
                self.outputAudioFormatDescription = (CMFormatDescriptionRef)formatDescription;
            }
            if (self.videoRecord && self.startRecord) {
                [self appendAudioBuffer:sampleBuffer];
            }
        }
    }
}

#pragma mark - MGCameraRecordDelegate
- (void)mgCameraRecordDidFinishPreparing:(MGCameraRecordManager *)recorder {
    
}

- (void)mgCameraRecord:(MGCameraRecordManager *)recorder didFailWithError:(NSError *)error {
    
}

- (void)mgCameraRecordDidFinishRecording:(MGCameraRecordManager *)recorder {
    
}

#pragma mark - MGVideoDelegate
- (void)videoError:(MGCameraErrorType)error {
    if (_delegate && [_delegate respondsToSelector:@selector(mgCaptureOutput:error:)]) {
        [_delegate mgCaptureOutput:nil error:error];
    }
}

@end
