//
//  SimplePictureViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/10.
//  Copyright © 2018 JiangXuanke. All rights reserved.
//  I don't know about those warnings, hhhhhhhh.

#import "SimplePictureViewController.h"
//#define GLES_SILENCE_DEPRECATION
#import <AVFoundation/AVFoundation.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <CoreImage/CoreImage.h>

@interface SimplePictureViewController ()

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *mEffect;
@property (nonatomic, assign) int count;

@end

@implementation SimplePictureViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 新建上下文
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.context];
    
    // 顶点和索引
    GLfloat squareVertexData[] = {
        0.5, -0.5, 0.0,  1.0f, 0.0f,
        -0.5, 0.5, 0.0,  0.0f, 1.0f,
        -0.5, -0.5, 0.0, 0.0f, 0.0f,
        0.5, 0.5, 0.0,   1.0f, 1.0f,
    };
    
    GLuint indices[] = {
        0, 1, 2,
        1, 3, 0
    };
    self.count = sizeof(indices) / sizeof(GLuint);
    
    // 顶点数据缓存， 不知道为什么全部都deprecated掉了
    // 还有index缓存
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexData), squareVertexData, GL_STATIC_DRAW);
    
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLfloat *)NULL + 0);
    
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    
    [self uploadTexture];
//    CVOpenGLESTextureCacheRef coreVideoTextureCache;
//    CVPixelBufferRef renderTarget;
//    CVOpenGLESTextureCacheRef renderTexture;
//    CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, self.context, NULL, &coreVideoTextureCache);
//    UIImage *image = [UIImage imageNamed:@"doge"];
//    renderTarget = [self pixelBufferFromCGImage:image.CGImage];
//
//
//    glBindTexture(CVOpenGLESTextureGetTarget(renderTarget), CVOpenGLESTextureGetName(renderTexture));
//
//    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"doge" ofType:@"png"];
//    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1), GLKTextureInfoOriginBottomLeft, nil];
//    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
//
//    // 着色器
//    self.mEffect = [[GLKBaseEffect alloc] init];
//    self.mEffect.texture2d0.enabled = GL_TRUE;
//    self.mEffect.texture2d0.name = CVOpenGLESTextureGetName(renderTarget);
//
//    // 下面的这段话是什么意思
    
    
}

- (void)uploadTexture {
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"doge" ofType:@"png"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1), GLKTextureLoaderOriginBottomLeft, nil];
    // 纹理坐标系是相反的
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath
                                                                      options:options
                                                                        error:nil];
    
    // 着色器
    self.mEffect = [[GLKBaseEffect alloc] init];
    self.mEffect.texture2d0.enabled = GL_TRUE;
    self.mEffect.texture2d0.name = textureInfo.name;
}

- (CVPixelBufferRef)pixelBufferFromCGImage: (CGImageRef)image {
    NSDictionary *options = @{
                              (NSString *)kCVPixelBufferCGImageCompatibilityKey : @YES,
                              (NSString *)kCVPixelBufferCGBitmapContextCompatibilityKey : @YES,
                              (NSString *)kCVPixelBufferIOSurfacePropertiesKey : [NSDictionary dictionary]
                              };
    CVPixelBufferRef pxbuffer = NULL;
    CGFloat frameWidth = CGImageGetWidth(image);
    CGFloat frameHeight = CGImageGetHeight(image);
    CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault,
                                          frameWidth,
                                          frameHeight,
                                          kCVPixelFormatType_32BGRA,
                                          (__bridge CFDictionaryRef) options,
                                          &pxbuffer);
    NSParameterAssert(status == kCVReturnSuccess && pxbuffer != NULL);
    CVPixelBufferLockBaseAddress(pxbuffer, 0);
    void *pxdata = CVPixelBufferGetBaseAddress(pxbuffer);
    NSParameterAssert(pxdata != NULL);
    CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pxdata,
                                                 frameWidth, frameHeight,
                                                 8,
                                                 CVPixelBufferGetBytesPerRow(pxbuffer),
                                                 rgbColorSpace,
                                                 (CGBitmapInfo)kCGImageAlphaNoneSkipFirst);
    NSParameterAssert(context);
    CGContextConcatCTM(context, CGAffineTransformIdentity);
    CGContextDrawImage(context, CGRectMake(0,
                                           0,
                                           frameWidth,
                                           frameHeight),
                       image);
    CGColorSpaceRelease(rgbColorSpace);
    CGContextRelease(context);
    CVPixelBufferUnlockBaseAddress(pxbuffer, 0);
    return pxbuffer;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    [self.mEffect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

@end
