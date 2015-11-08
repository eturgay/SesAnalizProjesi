//
//  ThirdViewController.m
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import "ThirdViewController.h"
#import "../Audio/AudioUnitReceive.h"

@interface ThirdViewController ()

@end

@implementation ThirdViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    if (AudioUnitStarted)
        _btnAudioUnitControl.selectedSegmentIndex = 0;
    else
        _btnAudioUnitControl.selectedSegmentIndex = 1;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)ControlAudioUnit:(id)sender {
}
@end
