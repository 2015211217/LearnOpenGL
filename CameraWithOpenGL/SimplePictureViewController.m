//
//  SimplePictureViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/10.
//  Copyright © 2018 JiangXuanke. All rights reserved.

#import "SimplePictureViewController.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface SimplePictureViewController () <GLKViewDelegate>

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
    // 似乎有什么可以让他不受到屏幕比例影响的方法
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
    glVertexAttribPointer(GLKVertexAttribPosition,
                          3,
                          GL_FLOAT, GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 0);
    
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
    [self uploadTexture];
}

- (void)uploadTexture {
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"doge" ofType:@"png"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:
                             @(1),
                             GLKTextureLoaderOriginBottomLeft,
                             nil];
    // 纹理坐标系是相反的
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath
                                                                      options:options
                                                                        error:nil];
    // 着色器
    self.mEffect = [[GLKBaseEffect alloc] init];
    self.mEffect.texture2d0.enabled = GL_TRUE;
    self.mEffect.texture2d0.name = textureInfo.name;
    
}

#pragma mark - delegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    [self.mEffect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

@end
