//
//  TooPictureViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/14.
//  Copyright © 2018 JiangXuanke. All rights reserved.
//  fine，让我们来看一下他是怎么弄的🤔

#import "TooPictureViewController.h"
#import "GLProgram.h"
#import "MGCameraManager.h"
#import "MGCameraImage.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface TooPictureViewController () <GLKViewDelegate, MGCameraDelegate>

@property (nonatomic, strong) EAGLContext *context;// 首先当然是上下文
@property (nonatomic, strong) CAEAGLLayer *eagLayer;// ???
@property (nonatomic, strong) GLKBaseEffect *effect;
@property (nonatomic, assign) GLuint program;
@property (nonatomic, assign) GLuint colorRenderBuffer;
@property (nonatomic, assign) GLuint colorFrameBuffer;
@property (nonatomic, strong) GLProgram *glProgram;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, assign) GLuint count;
@property (nonatomic, strong) GLKTextureInfo *texture0;
@property (nonatomic, strong) GLKTextureInfo *texture1;
@property (nonatomic, strong) MGCameraManager *cameraManager;
@property (nonatomic, assign) int circlePercentage;

@end

@implementation TooPictureViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initOpenGLView];
}

- (void)initOpenGLView {
    UIBarButtonItem *btnItem = [[UIBarButtonItem alloc] initWithTitle:@"Back"
                                                                style:UIBarButtonItemStylePlain
                                                               target:self
                                                               action:@selector(quitShootPreviews)];
    self.navigationItem.leftBarButtonItem = btnItem;
    [self buildOpenGLView];
}

- (void)quitShootPreviews {
    [self.cameraManager stopRunning];
    _cameraManager = nil;
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - nothing
- (void)buildOpenGLView {
    GLKView *view = (GLKView *)self.view;
    view.context = [[EAGLContext alloc]initWithAPI: kEAGLRenderingAPIOpenGLES2];
    //设置当前上下文
    [EAGLContext setCurrentContext:view.context];
    
    // 顶点坐标
    GLfloat squarePoints[] = {
        1.0, 1.0, 0.0,  0.0f, 0.0f,
        1.0, -0.5, 0.0, 0.0f, 1.0f,
        -1.0, 1.0, 0.0, 1.0f, 0.0f,
        -1.0, -0.5, 0.0, 1.0f, 1.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 1, 3
    };
    
    _count = sizeof(indices) / sizeof(GLuint);

//    // 绑定顶点坐标
//    self.effect = [[GLKBaseEffect alloc] init];
//    self.effect.useConstantColor = GL_TRUE;
//    self.effect.constantColor = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    
    GLuint buffer;// 顶点缓冲对象
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squarePoints), squarePoints, GL_DYNAMIC_DRAW);
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(GLKVertexAttribPosition,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          NULL);
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    
    glVertexAttribPointer(GLKVertexAttribTexCoord0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    
    glVertexAttribPointer(GLKVertexAttribTexCoord1,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    glEnableVertexAttribArray(GLKVertexAttribTexCoord1);
//
//    glGenTextures(1, &self.texture0);
//    glBindTexture(GL_TEXTURE_2D, self.texture0);
    
    [self startCameraManager];
    [self renderCircle];
}

- (void)renderCircle {
    // 绘制圆形
    GLuint vertexCount = 100;
    float delta = 2.0 * M_PI / vertexCount;
    
    float a = 0.8;
    float b = a * self.view.frame.size.width / self.view.frame.size.height;
    
    for (int i = 0; i < vertexCount; i++) {
        GLfloat x = a * cos(delta * i); // 计算x
        GLfloat y = b * sin(delta * i);
        GLfloat z = 0.0f;
    }
    
    
}

#pragma mark - cameraManager
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

- (void)mgCaptureOutput:(AVCaptureOutput *)captureOutput
  didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
         fromConnection:(AVCaptureConnection *)connection {
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
                self.effect = [[GLKBaseEffect alloc] init];
            }
            self.effect.texture2d0.enabled = GL_TRUE;
            self.effect.texture2d0.name = texture.name;
            self.effect.texture2d0.target = texture.target;
            
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

#pragma mark - uploadTexture
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.1, 0.8, 0.1, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    [self.effect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

@end
