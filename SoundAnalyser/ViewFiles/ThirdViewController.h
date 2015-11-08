//
//  ThirdViewController.h
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ThirdViewController : UIViewController
- (IBAction)ControlAudioUnit:(id)sender;
@property (weak, nonatomic) IBOutlet UISegmentedControl *btnAudioUnitControl;
@property (weak, nonatomic) IBOutlet UILabel *lblVersion;

@end
