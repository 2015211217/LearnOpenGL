//
//  MultiPictureViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/10.
//  Copyright © 2018 JiangXuanke. All rights reserved.
//  一来就是deprecated ‘-’

#import "MultiPictureViewController.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface MultiPictureViewController () <GLKViewDelegate> {
    GLuint buffer;
    GLuint index;
}

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;
@property (nonatomic, strong) NSMutableArray *picArray;
@property (nonatomic, strong) GLKView *glkview;
@property (nonatomic, strong) NSDictionary *options;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;

@property (nonatomic, assign) int count;
@property (nonatomic, assign) int imageNumber;

@end

@implementation MultiPictureViewController

- (void)quitThoughNavigator {
    if (self.textureInfo) {
        GLuint name = self.textureInfo.name;
        glDeleteTextures(1, &name);
    }
    [self.navigationController popViewControllerAnimated:YES];
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc] initWithTitle:@"Back"
                                                                style:UIBarButtonItemStylePlain
                                                               target:self
                                                               action:@selector(quitThoughNavigator)];
    
    self.navigationItem.leftBarButtonItem = leftBtn;

    
    // 首先，创建上下文
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    _glkview = (GLKView *)self.view;
    self.glkview.context = self.context;
    self.glkview.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.context];
    
    // 顶点数据
    GLfloat squareVertexData[] = {
        0.5, -0.5, 0.0,  1.0f, 0.0f,
        0.5, 0.5, 0.0,   1.0f, 1.0f,
        -0.5, 0.5, 0.0,  0.0f, 1.0f,
        -0.5, -0.5, 0.0, 0.0f, 0.0f,
    };
    
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    self.count = sizeof(indices) / sizeof(GLuint);// 顶点的总个数
    
    
    glGenBuffers(1, &(buffer));
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexData), squareVertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
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
                          sizeof(GLfloat) * 5,
                          (GLfloat *)NULL + 3);
   
    _imageNumber = 0;
    _picArray = [[NSMutableArray alloc] initWithCapacity:4];
    [self.picArray addObject:[[NSBundle mainBundle] pathForResource:@"doge" ofType:@"png"]];
    [self.picArray addObject:[[NSBundle mainBundle] pathForResource:@"aFei1" ofType:@"png"]];
    [self.picArray addObject:[[NSBundle mainBundle] pathForResource:@"aFei2" ofType:@"png"]];
    [self.picArray addObject:[[NSBundle mainBundle] pathForResource:@"aFei3" ofType:@"png"]];
    _options = [NSDictionary dictionaryWithObjectsAndKeys:
                @(1),
                GLKTextureLoaderOriginBottomLeft,
                nil];
    
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:2.0f repeats:YES block:^(NSTimer * _Nonnull timer) {
        if (self.textureInfo) {
            GLuint name = self.textureInfo.name;
            glDeleteTextures(1, &name);
        }
        [self uploadTexture];
    }];
    [timer fire];
}

#pragma mark - texture setting
- (void)uploadTexture {// 隔一段时间图片改变
    _textureInfo = [GLKTextureLoader textureWithContentsOfFile:[self.picArray objectAtIndex:self.imageNumber++]
                                                       options:self.options
                                                         error:nil];
    if ([self.picArray count] == self.imageNumber) {
        self.imageNumber = 0;
    }
    if (!self.effect) {
        self.effect = [[GLKBaseEffect alloc] init];
    }
    self.effect.texture2d0.enabled = GL_TRUE;
    self.effect.texture2d0.name = self.textureInfo.name;

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        
    });
}

#pragma mark - GLKView Delegate
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    // 绘图的delegate 如果不写这个的话没有办法进行绘制
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    [self.effect prepareToDraw];
    glDrawElements(GL_TRIANGLES, self.count, GL_UNSIGNED_INT, 0);
}

@end
