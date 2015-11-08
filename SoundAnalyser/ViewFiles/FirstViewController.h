//
//  FirstViewController.h
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "../ChartView/JBLineChartView.h"

@interface FirstViewController : UIViewController <JBLineChartViewDelegate, JBLineChartViewDataSource,UITabBarDelegate>

@property (weak, nonatomic) IBOutlet JBLineChartView *lcRawSignal;
@property (weak, nonatomic) IBOutlet UISegmentedControl *btnAudioUnitControl;

- (IBAction)ControlAudioUnit:(id)sender;
- (IBAction)Test:(id)sender;

@property (weak, nonatomic) IBOutlet UILabel *lblVersion;

@end
