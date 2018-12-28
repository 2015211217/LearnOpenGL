#import "SilentActiveView.h"
#import "GLProgram.h"
#import "MGCameraManager.h"
#import <OpenGLES/ES2/gl.h>
#include <KASSilentLive/KASSilentLive.h>
//#include "MGFaceIDFaceManager.h"

// 我似乎只能够使用framework里面有的头文件，就相当于添加了一个framework
// 所以这个C++到底是怎么弄的鸭。

using namespace std;

@interface SilentActiveView() <MGCameraDelegate>

@property (nonatomic, strong) EAGLContext *myContext;
@property (nonatomic, strong) CAEAGLLayer *myEagLayer;
@property (nonatomic, assign) GLuint count;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, assign) GLuint myTexture0;
@property (nonatomic, assign) GLuint myTexture1;
@property (nonatomic, assign) GLuint texture0Uniform;
@property (nonatomic, assign) GLuint texture1Uniform;
@property (nonatomic, assign) GLuint leftBottomUniform;
@property (nonatomic, assign) GLuint rightTopUniform;
@property (nonatomic, assign) GLuint myColorRenderBuffer;
@property (nonatomic, assign) GLuint myColorFrameBuffer;

@property (nonatomic, strong) MGCameraManager *cameraManager;
@property (nonatomic, strong) MGSilentLiveDetectManager *silentManager;
@property (nonatomic, strong) MGSilentLiveDetectItem *detectItem;

- (void)setupLayer;

@end

@implementation SilentActiveView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)layoutSubviews {
    [self setupLayer];
    [self setupContext];
    [self setupProgram];

    [self destoryRenderAndFrameBuffer];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self render];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(closeCamera)
                                                 name:@"closeCamera"
                                               object:nil];
}

- (void)render {
    glClearColor(0.3, 0.3, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
    [self.myContext presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupProgram {
    CGFloat scale = [[UIScreen mainScreen] scale]; //获取视图放大倍数，可以把scale设置为1试试
    glViewport(self.frame.origin.x * scale, self.frame.origin.y * scale, self.frame.size.width * scale, self.frame.size.height * scale); //设置视口大小
    //读取文件路径
    NSString *vertFile = [[NSBundle mainBundle] pathForResource:@"shaderv" ofType:@"vsh"];
    NSString *fragFile = [[NSBundle mainBundle] pathForResource:@"shaderf" ofType:@"fsh"];

    //加载shader,顶点着色器和片段着色器
    self.program = [[GLProgram alloc] initWithVertexShaderString:[NSString stringWithContentsOfFile:vertFile encoding:NSUTF8StringEncoding error:nil] fragmentShaderString:[NSString stringWithContentsOfFile:fragFile encoding:NSUTF8StringEncoding error:nil]];
    //链接
    if (!self.program.initialized)
    {
        [self.program addAttribute:@"position"];
        [self.program addAttribute:@"textCoordinate"];
        if (![self.program link])
        {
            NSString *progLog = [self.program programLog];
            NSLog(@"Program link log: %@", progLog);
            NSString *fragLog = [self.program fragmentShaderLog];
            NSLog(@"Fragment shader compile log: %@", fragLog);
            NSString *vertLog = [self.program vertexShaderLog];
            NSLog(@"Vertex shader compile log: %@", vertLog);
            self.program = nil;
            NSAssert(NO, @"Filter shader link failed");
        }
    }
    _texture0Uniform = [self.program uniformIndex:@"myTexture0"];
    _texture1Uniform = [self.program uniformIndex:@"myTexture1"];
    _leftBottomUniform = [self.program uniformIndex:@"leftBottom"];
    _rightTopUniform = [self.program uniformIndex:@"rightTop"];
    GLuint displayPositionAttribute = [self.program attributeIndex:@"position"];
    GLuint displayTextureCoordinateAttribute = [self.program attributeIndex:@"textCoordinate"];
    [self.program use];
    glEnableVertexAttribArray(displayPositionAttribute);
    glEnableVertexAttribArray(displayTextureCoordinateAttribute);

    GLfloat attrArr[] = {
        1.0f, -0.5f, -1.0f,     1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f,     0.0f, 1.0f,
        -1.0f, -0.5f, -1.0f,    0.0f, 0.0f,
        1.0f, 1.0f, -1.0f,      1.0f, 1.0f,
    };
    GLuint attrIndex[] = {
        0, 1, 2,
        0, 1, 3
    };
    self.count = sizeof(attrIndex) / sizeof(GLuint);

    GLuint attrBuffer;
    glGenBuffers(1, &attrBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, attrBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(attrArr), attrArr, GL_DYNAMIC_DRAW);
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(attrIndex), attrIndex, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(displayPositionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);
    glEnableVertexAttribArray(displayPositionAttribute);
    glVertexAttribPointer(displayTextureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (float *)NULL + 3);
    glEnableVertexAttribArray(displayTextureCoordinateAttribute);
    
    [self setupTexture:[UIImage imageNamed:@"doge"].CGImage texture:_myTexture0];
    [self setupTexture:[UIImage imageNamed:@"aFei1"].CGImage texture:_myTexture1];
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self.myTexture0);
    glUniform1i(self.texture0Uniform, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.myTexture1);
    glUniform1i(self.texture1Uniform, 1);
    glUniform2f(self.leftBottomUniform, -0.15, -0.15);
    glUniform2f(self.rightTopUniform, 0.30, 0.30);

    if (!_silentManager) {
        NSData *faceModel = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Meg_Face"
                                                                                           ofType:nil]];
        NSData *fmpModel = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Meg_FMPLive"
                                                                                          ofType:nil]];
        
        _silentManager = [[MGSilentLiveDetectManager alloc] initWithFaceModel:faceModel fmpModel:fmpModel];
        if (_silentManager) {
            NSLog(@"加载成功");
        } else {
            NSLog(@"加载失败");
        }
    }

    [self startCameraManager];
}

/*
 *  c语言编译流程：预编译、编译、汇编、链接
 *  glsl的编译过程主要有glCompileShader、glAttachShader、glLinkProgram三步；
 *  @param vert 顶点着色器
 *  @param frag 片元着色器
 *
 *  @return 编译成功的shaders
 */
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
            [self setupTexture:image.CGImage texture:_myTexture0];
            [self render];
            [self buildSilentViewModel:image];
        });

        CVPixelBufferUnlockBaseAddress(imageBuffer,0);
        CGImageRelease(quartzImage);
        CGContextRelease(context);
        CGColorSpaceRelease(colorSpace);

        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            glDeleteTextures(1, &_myTexture0);
            glDeleteTextures(1, &_myTexture1);
            glDeleteTextures(1, &_texture0Uniform);
            glDeleteTextures(1, &_texture1Uniform);
        });
    }
}

- (void)closeCamera {
    [self.cameraManager stopRunning];
}

#pragma mark - setup
- (void)setupLayer {
    self.myEagLayer = (CAEAGLLayer*) self.layer;
    [self setContentScaleFactor:[[UIScreen mainScreen] scale]];
    self.myEagLayer.opaque = YES;
    self.myEagLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                          [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
}


- (void)setupContext {
    // 指定 OpenGL 渲染 API 的版本，在这里我们使用 OpenGL ES 2.0
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    EAGLContext* context = [[EAGLContext alloc] initWithAPI:api];
    if (!context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }

    // 设置为当前上下文
    if (![EAGLContext setCurrentContext:context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    self.myContext = context;
}

- (void)setupRenderBuffer {
    GLuint buffer;
    glGenRenderbuffers(1, &buffer);
    self.myColorRenderBuffer = buffer;
    glBindRenderbuffer(GL_RENDERBUFFER, self.myColorRenderBuffer);
    // 为 颜色缓冲区 分配存储空间
    [self.myContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:self.myEagLayer];
}


- (void)setupFrameBuffer {
    GLuint buffer;
    glGenFramebuffers(1, &buffer);
    self.myColorFrameBuffer = buffer;

    // 设置为当前 framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, self.myColorRenderBuffer);
    // 将 _colorRenderBuffer 装配到 GL_COLOR_ATTACHMENT0 这个装配点上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, self.myColorRenderBuffer);
}

- (void)destoryRenderAndFrameBuffer
{
    glDeleteFramebuffers(1, &_myColorFrameBuffer);
    self.myColorFrameBuffer = 0;
    glDeleteRenderbuffers(1, &_myColorRenderBuffer);
    self.myColorRenderBuffer = 0;
}

#pragma mark - texture
- (GLuint)setupTexture:(CGImageRef)spriteImage texture:(GLuint)texture {
    // 1获取图片的CGImageRef
//    CGImageRef spriteImage = [UIImage imageNamed:fileName].CGImage;
    if (!spriteImage) {
        NSLog(@"No Image to show.");
        exit(1);
    }
//    // 读取图片的大小
    size_t width = CGImageGetWidth(spriteImage);
    size_t height = CGImageGetHeight(spriteImage);
    GLubyte *spriteData = (GLubyte *) calloc(width * height * 4, sizeof(GLubyte)); //rgba共4个byte
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4,
                                                       CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
    // 3在CGContextRef上绘图
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
    CGContextRelease(spriteContext);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    float fw = width, fh = height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fw, fh, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
    free(spriteData);
    return 0;
    
}


#pragma mark - silent model
- (void)buildSilentViewModel:(UIImage *)image { // 添加图片信息
    
    if (!_detectItem) {
        
        _detectItem = [[MGSilentLiveDetectItem alloc] init];
    
    }
    
    // 。。。。。。这个到底是什么来着
    
    self.detectItem = [self.silentManager detectImageIsLiveWithFMP:image];
    
    
    NSLog(@" detect result: hasFace:%@ isLive:%@", _detectItem.hasFace ? @"YES" : @"NO", _detectItem.isLive ? @"YES" : @"NO");
}

@end
