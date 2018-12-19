//
//  SilentAliveViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/17.
//  Copyright © 2018 JiangXuanke. All rights reserved.
//

#import "SilentAliveViewController.h"
#import "SilentActiveView.h"

@interface SilentAliveViewController ()

@property (nonatomic, strong) SilentActiveView *openGLView;

@end

@implementation SilentAliveViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self buildOpenGLView];
}

- (void)buildOpenGLView {
    self.openGLView = [[SilentActiveView alloc] init];
    [self.view addSubview:self.openGLView];
    [self.openGLView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.openGLView layoutSubviews];
   // [self.openGLView customInit];
}

@end
