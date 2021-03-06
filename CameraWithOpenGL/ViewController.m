//
//  ViewController.m
//  CameraWithOpenGL
//
//  Created by JiangXuanke on 2018/12/10.
//  Copyright © 2018 JiangXuanke. All rights reserved.

#import "ViewController.h"
#import "SimplePictureViewController.h"
#import "MultiPictureViewController.h"
#import "TooPictureViewController.h"
#import "CameraViewController.h"
#import "SilentAliveViewController.h"
#import <Masonry/Masonry.h>

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self buildView];
}

#pragma mark - build views
- (void)buildView {
    UIButton *picBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.view addSubview:picBtn];
    [picBtn.titleLabel setTextAlignment:NSTextAlignmentCenter];
    [picBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [picBtn setTitle:@"Picture" forState:UIControlStateNormal];
    [picBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.view.mas_top).offset(200.0f);
        make.centerX.equalTo(self.view.mas_centerX);
        make.width.offset(100.0f);
        make.height.offset(40.0f);
    }];
    [picBtn addTarget:self
               action:@selector(pictureOpenGLView:)
     forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *gifBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.view addSubview:gifBtn];
    [gifBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [gifBtn.titleLabel setTextAlignment:NSTextAlignmentCenter];
    [gifBtn setTitle:@"gif" forState:UIControlStateNormal];
    [gifBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(picBtn.mas_bottom).offset(50.0f);
        make.centerX.equalTo(self.view.mas_centerX);
        make.width.offset(100.0f);
        make.height.offset(40.0f);
    }];
    [gifBtn addTarget:self
               action:@selector(gifOpenGLView:)
     forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *cameraBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.view addSubview:cameraBtn];
    [cameraBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [cameraBtn.titleLabel setTextAlignment:NSTextAlignmentCenter];
    [cameraBtn setTitle:@"camera" forState:UIControlStateNormal];
    [cameraBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(gifBtn.mas_bottom).offset(50.0f);
        make.centerX.equalTo(self.view.mas_centerX);
        make.width.offset(100.0f);
        make.height.offset(40.0f);
    }];
    [cameraBtn addTarget:self
                  action:@selector(cameraOpenGLView:)
        forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *tooPicBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.view addSubview:tooPicBtn];
    [tooPicBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [tooPicBtn.titleLabel setTextAlignment:NSTextAlignmentCenter];
    [tooPicBtn setTitle:@"blend" forState:UIControlStateNormal];
    [tooPicBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(cameraBtn.mas_bottom).offset(50.0f);
        make.centerX.equalTo(self.view.mas_centerX);
        make.width.offset(100.0f);
        make.height.offset(40.0f);
    }];
    [tooPicBtn addTarget:self
                  action:@selector(silentActionView:)
        forControlEvents:UIControlEventTouchUpInside];
}

#pragma mark - operations
- (void)pictureOpenGLView:(UIButton *)sender {
    [sender setBackgroundColor:[UIColor grayColor]];
    [NSThread sleepForTimeInterval:0.1f];
    
    [sender setBackgroundColor:[UIColor whiteColor]];
    
    SimplePictureViewController *view = [[SimplePictureViewController alloc] init];
    [self.navigationController pushViewController:view animated:YES];
}

- (void)gifOpenGLView:(UIButton *)sender {
    MultiPictureViewController *view = [[MultiPictureViewController alloc] init];
    [self.navigationController pushViewController:view animated:YES];
}

- (void)cameraOpenGLView:(UIButton *)sender {
    CameraViewController *view = [[CameraViewController alloc] init];
    [self.navigationController pushViewController:view animated:YES];
}

- (void)tooPictureOpenGLView:(UIButton *)sender {
    TooPictureViewController *view = [[TooPictureViewController alloc] init];
    [self.navigationController pushViewController:view animated:YES];
}

- (void)silentActionView:(UIButton *)sender {
    SilentAliveViewController *view = [[SilentAliveViewController alloc] init];
    [self.navigationController pushViewController:view animated:YES];
}
@end
