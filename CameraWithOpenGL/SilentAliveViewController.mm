//
//  SilentAliveViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/17.
//  Copyright © 2018 JiangXuanke. All rights reserved.


#import "SilentAliveViewController.h"
#import "SilentActiveView.h"

@interface SilentAliveViewController ()

@property (nonatomic, strong) SilentActiveView *openGLView;

@end

@implementation SilentAliveViewController

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self buildOpenGLView];
}

- (void)buildOpenGLView {
    UIBarButtonItem *btnItem = [[UIBarButtonItem alloc] initWithTitle:@"Back"
                                                                style:UIBarButtonItemStylePlain
                                                               target:self
                                                               action:@selector(quitShootPreviews:)];
    self.navigationItem.leftBarButtonItem = btnItem;
    
    self.openGLView = [[SilentActiveView alloc] init];
    [self.view addSubview:self.openGLView];
    [self.openGLView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.equalTo(self.view);
        make.bottom.equalTo(self.view.mas_bottom).offset(-200);
    }];
}

- (void)quitShootPreviews:(UIButton *)sender {
    [self.openGLView removeFromSuperview];
    [self.navigationController popViewControllerAnimated:YES];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"closeCamera"
                                                        object:self];
    
}

@end
