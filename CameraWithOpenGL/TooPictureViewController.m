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

//@property (nonatomic, assign) GLuint texture0;
//@property (nonatomic, assign) GLuint texture1;
@property (nonatomic, strong) GLKTextureInfo *texture0;
@property (nonatomic, strong) GLKTextureInfo *texture1;

@end

@implementation TooPictureViewController

//- (void)dealloc{
//    GLKView *view = (GLKView *)self.view;
//    [EAGLContext setCurrentContext:view.context];
//    if ( 0 != vertextBufferID) {
//        glDeleteBuffers(1,
//                        &vertextBufferID);
//        vertextBufferID = 0;
//    }
//    [EAGLContext setCurrentContext:nil];
//}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initOpenGLView];
 //   [self updateOpenGLView];
}

- (void)initOpenGLView {
//    [self buildLayer];
//    [self buildContext];
    [self buildOpenGLView];
}

- (void)updateOpenGLView {
    [self destoryRenderAndFrameBuffer];
    [self buildRenderBuffer];
    [self buildFrameBuffer];
    [self render];
}

+ (Class)layerClass {
    // 相当于重写了layer，将layer变为CAEAGLLayer
    return [CAEAGLLayer class];
}

- (void)buildLayer {
    _eagLayer = (CAEAGLLayer *)self.view.layer;
    
    [self.view setContentScaleFactor:[[UIScreen mainScreen] scale]];
    // layer
    self.eagLayer.opaque = YES;
    self.eagLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],
                                        kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8,
                                        kEAGLDrawablePropertyColorFormat,
                                        nil];
}

- (void)buildContext {
    // 建立上下文 context
    EAGLContext *context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    // 设置为当前上下文
    if (![EAGLContext setCurrentContext:context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    // 现在突然有了？？
    self.context = context;
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.context];
    
}

#pragma mark - nothing
- (void)buildOpenGLView {
//    CGFloat scale = [[UIScreen mainScreen] scale];
//    glViewport(self.view.frame.origin.x * scale, self.view.frame.origin.y * scale, self.view.frame.size.width * scale, self.view.frame.size.height * scale);
//
//    NSString* vertFile = [[NSBundle mainBundle] pathForResource:@"shaderv" ofType:@"vsh"];
//    NSString* fragFile = [[NSBundle mainBundle] pathForResource:@"shaderf" ofType:@"fsh"];
//
//    self.glProgram = [[GLProgram alloc] initWithVertexShaderString:[NSString stringWithContentsOfFile:vertFile encoding:NSUTF8StringEncoding error:nil] fragmentShaderString:[NSString stringWithContentsOfFile:fragFile encoding:NSUTF8StringEncoding error:nil]];
//
//    if (!self.glProgram.initialized) {
//        [self.glProgram addAttribute:@"position"];// 位置
//        [self.glProgram addAttribute:@"textCoordinate"];// 纹理
//        if (![self.glProgram link]) {
//            // because of the difficulty of searching for mistake, logs are somehow important
//            NSString *progLog = [self.glProgram programLog];
//            NSLog(@"Program link log:%@", progLog);
//            NSString *fragLog = [self.glProgram fragmentShaderLog];
//            NSLog(@"Fragment shader compile log : %@", fragLog);
//            NSString *vertLog = [self.glProgram vertexShaderLog];
//            NSLog(@"Vertex shader compile log : %@", vertLog);
//            self.glProgram = nil;
//            NSAssert(NO, @"Filter shader link failed");
//        }
//    }
//
//    GLuint texture0Uniform = [self.glProgram uniformIndex:@"texture0"];
//    GLuint texture1Uniform = [self.glProgram uniformIndex:@"texture1"];
//    GLuint leftBottomUniform = [self.glProgram uniformIndex:@"leftBottom"];
//    GLuint rightTopUniform = [self.glProgram uniformIndex:@"rightTop"];
//    GLuint displayPositionAttribute = [self.glProgram attributeIndex:@"position"];
//    GLuint displayTextureCoordinateAttribute = [self.glProgram attributeIndex:@"textCoordinate"];
//
//    [self.glProgram use];// 这又是什么意思
//    glEnableVertexAttribArray(displayPositionAttribute);
//    glEnableVertexAttribArray(displayTextureCoordinateAttribute);
//
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

    // 绑定顶点坐标
    self.effect = [[GLKBaseEffect alloc] init];
    self.effect.useConstantColor = GL_TRUE;
    self.effect.constantColor = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    
    [self fillTexture];
    
    GLuint buffer;
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
    
    glVertexAttribPointer(displayTextureCoordinateAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    glEnableVertexAttribArray(displayTextureCoordinateAttribute);
    // texture 0
    
    glVertexAttribPointer(GLKVertexAttribTexCoord0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    
//    glVertexAttribPointer(GLKVertexAttribTexCoord1,
//                          2,
//                          GL_FLOAT,
//                          GL_FALSE,
//                          sizeof(GLfloat) * 5,
//                          (GLfloat *)NULL + 3);
//    glEnableVertexAttribArray(GLKVertexAttribTexCoord1);
    // texture 1
    
    
//    [self drawTexture:@"doge" texture:_texture0];
//    [self drawTexture:@"aFei1" texture:_texture1];
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, self.texture0);
//    glUniform1i(texture0Uniform, 0);
//
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, self.texture1);
//    glUniform1i(texture1Uniform, 1);
//
//    glUniform2f(leftBottomUniform, -0.15, -0.15);
//    glUniform2f(rightTopUniform, 0.30, 0.30);
    [self fillTexture];
}

- (void)fillTexture {
    CGImageRef imageOne = [UIImage imageNamed:@"doge"].CGImage;
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1), GLKTextureLoaderOriginBottomLeft, nil];
    self.texture0 = [GLKTextureLoader textureWithCGImage:imageOne options:options error:nil];

    
    self.effect.texture2d0.name = self.texture0.name;
    self.effect.texture2d0.target = self.texture0.target;
    
    
    CGImageRef imageTwo = [UIImage imageNamed:@"aFei1"].CGImage;
    self.texture1 = [GLKTextureLoader textureWithCGImage:imageTwo options:options error:nil];

    self.effect.texture2d1.name = self.texture1.name;
    self.effect.texture2d1.target = self.texture1.target;
    // 混合起来
    self.effect.texture2d1.envMode = GLKTextureEnvModeDecal;
    
}

#pragma mark - uploadTexture
- (void)drawTexture:(NSString *)fileName texture:(GLuint)texture{
    CGImageRef spriteImage = [UIImage imageNamed:fileName].CGImage;
    size_t width = CGImageGetWidth(spriteImage);
    size_t height = CGImageGetHeight(spriteImage);
    
    GLubyte *spriteData = (GLubyte *) calloc(width * height * 4, sizeof(GLubyte));
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData,
                                                width,
                                                height,
                                                8,
                                                width * 4,
                                                CGImageGetColorSpace(spriteImage),
                                                kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(spriteContext,
                       CGRectMake(0, 0, width, height),
                       spriteImage);
    CGContextRelease(spriteContext);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    float fw = width, fh = height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fw, fh, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
    free(spriteData);
}

- (void)destoryRenderAndFrameBuffer {
    glDeleteFramebuffers(1, &_colorFrameBuffer);
    glDeleteFramebuffers(1, &_colorRenderBuffer);
    self.colorFrameBuffer = 0;
    self.colorRenderBuffer = 0;
}

#pragma mark - settings
- (void)render {
    glClearColor(0, 1.0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)buildFrameBuffer {
    GLuint buffer;
    glGenFramebuffers(1, &buffer);
    self.colorFrameBuffer = buffer;
    // 设置为当前frameBuffer
    glBindFramebuffer(GL_FRAMEBUFFER, self.colorRenderBuffer);
    // 将colorRenderBuffer 装配到 glcolorattachment0
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              self.colorRenderBuffer);
}

- (void)buildRenderBuffer {
    GLuint buffer;
    glGenRenderbuffers(1, &buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, self.colorRenderBuffer);
    // 为颜色缓冲区分配空间
    [self.context renderbufferStorage:GL_RENDERBUFFER fromDrawable:self.eagLayer];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.1, 0.8, 0.1, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    [self.effect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

@end
