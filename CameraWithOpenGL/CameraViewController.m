//
//  CameraViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/10.
//  Copyright © 2018 JiangXuanke. All rights reserved.
//

#import "CameraViewController.h"
#import "MGCameraManager.h"
#import "MGCameraImage.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface CameraViewController () <GLKViewDelegate, MGCameraDelegate>

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) MGCameraManager *cameraManager;
@property (nonatomic, assign) int count;

@end

@implementation CameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // new context
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    _glkView = (GLKView *)self.view;
    self.glkView.context = self.context;
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.context];
    
    // indices and points
    GLfloat squarePoints[] = {
        0.5, 0.5, 0.0,  1.0f, 1.0f,
        0.5, -0.5, 0.0, 1.0f, 0.0f,
        -0.5, 0.5, 0.0, 0.0f, 1.0f,
        -0.5, -0.5, 0.0, 0.0f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 1, 3
    };
    self.count = sizeof(indices) / sizeof(GLuint);
    
    // bind points
    GLuint point;
    glGenBuffers(1, &point);
    glBindBuffer(GL_ARRAY_BUFFER, point);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squarePoints), squarePoints, GL_STATIC_DRAW);
    
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    // GL_STATIC_DRAW 意思是一次修改，多次使用，除此之外如果需要修改point或者index的位置那么
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 0);
    
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5, //
                          (GLfloat *)NULL + 3);// 3 ： 偏移量
    [self uploadTexture];
}

- (void)uploadTexture {
    // 将摄像机的界面贴到上面
    [self startCameraManager];
   
}

- (void)startCameraManager {
    if (!_cameraManager) {
        _cameraManager = [MGCameraManager videoPreset:AVCaptureSessionPreset640x480
                                       devicePosition:AVCaptureDevicePositionFront
                                          videoRecord:YES
                                           videoSound:NO
                                            videoName:@"test"];
        self.cameraManager.videoOrientation = AVCaptureVideoOrientationPortrait;
        [self.cameraManager setDelegate:self];
        [self.cameraManager startRunning];
    }
}

// 等一下，仔细想一想，找到那个imageBuffer

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT); // 清除深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区
    [self.effect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

- (void)mgCaptureOutput:(AVCaptureOutput *)captureOutput
  didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
         fromConnection:(AVCaptureConnection *)connection{
    @synchronized (self) {
        
        CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
        CVPixelBufferLockBaseAddress(imageBuffer, 0);
        
        void *baseAddress = CVPixelBufferGetBaseAddress(imageBuffer);
        
        size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
        size_t width = CVPixelBufferGetWidth(imageBuffer);
        size_t height = CVPixelBufferGetHeight(imageBuffer);
        
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef context = CGBitmapContextCreate(baseAddress, width, height, 8,
                                                     bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
        CGImageRef quartzImage = CGBitmapContextCreateImage(context);
        CGImageRef copyedImage = CGImageCreateWithImageInRect(quartzImage, CGRectMake(0, 0, width, height));
        UIImage *image = [UIImage imageWithCGImage:copyedImage scale:1.0 orientation:UIImageOrientationUp];
        CGImageRelease(copyedImage);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            NSError *error;
            NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:
                                     @(1),
                                     GLKTextureLoaderOriginBottomLeft,
                                     nil];
            GLKTextureInfo *texture = [GLKTextureLoader textureWithCGImage:image.CGImage
                                                                   options:options
                                                                     error:&error];
            if (error) {
                NSLog(@"%@", error);
            }
            
            if (!self.effect) {
                _effect = [[GLKBaseEffect alloc] init];
            }
            
            self.effect.texture2d0.enabled = GL_TRUE;
            self.effect.texture2d0.name = texture.name;
            
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                GLuint name = texture.name;
                glDeleteTextures(1, &name);
            });
            
        });
        CVPixelBufferUnlockBaseAddress(imageBuffer,0);
        CGImageRelease(quartzImage);
        CGContextRelease(context);
        CGColorSpaceRelease(colorSpace);
    }
}

@end
