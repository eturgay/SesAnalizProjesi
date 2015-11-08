//
//  SecondViewController.h
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "../ChartView/JBLineChartView.h"

@interface SecondViewController : UIViewController<JBLineChartViewDelegate, JBLineChartViewDataSource>

@property (weak, nonatomic) IBOutlet JBLineChartView *lcFrequencyResponse;
@property (weak, nonatomic) IBOutlet UISegmentedControl *btnAudioUnitControl;
@property (weak, nonatomic) IBOutlet UISegmentedControl *btnFtype;
@property (weak, nonatomic) IBOutlet UIButton *btnFreeze;
- (IBAction)Freeze:(id)sender;

- (IBAction)ControlAudioUnit:(id)sender;

- (IBAction)SwitchFGraph:(id)sender;

@property (weak, nonatomic) IBOutlet UILabel *lblVersion;

@property  NSTimer* tmUpdateGraph;

@end
