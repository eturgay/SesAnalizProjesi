//
//  SecondViewController.m
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import "SecondViewController.h"
#import "../Audio/AudioUnitReceive.h"
#import "../Math/SignalDefinitions.h"
#import "../Math/ProcessSignal.h"

@interface SecondViewController ()

@end

@implementation SecondViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    _lcFrequencyResponse.backgroundColor = [UIColor whiteColor];
    _lcFrequencyResponse.delegate = self;
    _lcFrequencyResponse.dataSource = self;
    _lcFrequencyResponse.minimumValue = 0;
    _lcFrequencyResponse.maximumValue = 50;
    
    
    [_lcFrequencyResponse reloadData];
    [_lcFrequencyResponse setState:JBChartViewStateExpanded animated: true];
    
    if (AudioUnitStarted)
        _btnAudioUnitControl.selectedSegmentIndex = 0;
    else
        _btnAudioUnitControl.selectedSegmentIndex = 1;
    
    [_btnFtype insertSegmentWithTitle:@"Periodogram" atIndex:3 animated:(true)];
    [_btnFtype insertSegmentWithTitle:@"ARMA" atIndex:4 animated:(true)];
    
    

  
    _tmUpdateGraph = [NSTimer scheduledTimerWithTimeInterval: 0.02
                                              target: self
                                            selector:@selector(updateLabels)
                                            userInfo: nil repeats:YES];
    
}

-(void) updateLabels{
    //_lblSignalValues.text = [NSString stringWithFormat:@"Values: %f,%f,%f", fValue0, fValue5, fValue20];
    //_lblSignalLength.text = [NSString stringWithFormat:@"Signal Length: %d",signalLength];
    if (_btnFtype.selectedSegmentIndex == 0)
        Process2(ftAbs);
    else if (_btnFtype.selectedSegmentIndex == 1)
        Process2(ftReal);
    else if (_btnFtype.selectedSegmentIndex == 2)
        Process2(ftPeriodogram);
    else if (_btnFtype.selectedSegmentIndex == 3)
        Process2(ftARMA);
    
    
    [_lcFrequencyResponse reloadData];
    
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

- (IBAction)Freeze:(id)sender {
    [_tmUpdateGraph invalidate];
    if ([_btnFreeze.titleLabel.text  isEqual: @"Freeze"]) {
        _tmUpdateGraph = [NSTimer scheduledTimerWithTimeInterval: 0.02
                                                    target: self
                                                  selector:@selector(updateLabels)
                                                  userInfo: nil repeats:NO];
        [_btnFreeze setTitle:@"Unfreeze" forState:UIControlStateNormal];
    }
    else{
        _tmUpdateGraph = [NSTimer scheduledTimerWithTimeInterval: 0.02
                                                    target: self
                                                  selector:@selector(updateLabels)
                                                        userInfo: nil repeats:YES];
        
        [_btnFreeze setTitle:@"Freeze" forState:UIControlStateNormal];    }

    
}

- (IBAction)ControlAudioUnit:(id)sender {
    if (_btnAudioUnitControl.selectedSegmentIndex == 0)
    {
        initAudioSession();
        initAudioStreams(audioUnit);
        startAudioUnit(audioUnit);
    }
    else if(_btnAudioUnitControl.selectedSegmentIndex == 1)
        stopProcessingAudio(audioUnit);
}

- (IBAction)SwitchFGraph:(id)sender {
}

// MARK: JBLineChartView

- (NSUInteger)numberOfLinesInLineChartView:(JBLineChartView *)lineChartView
{
    return 1;
}


- (NSUInteger)lineChartView:(JBLineChartView *)lineChartView numberOfVerticalValuesAtLineIndex:(NSUInteger)lineIndex
{
    return (SIGNAL_FFT_LENGTH/2);
}

- (CGFloat)lineChartView:(JBLineChartView *)lineChartView verticalValueForHorizontalIndex:(NSUInteger)horizontalIndex atLineIndex:(NSUInteger)lineIndex
{

    if (lineIndex == 0){
        return Graph2Data[horizontalIndex];
    }
    else
        return 0;
}


- (UIColor *)lineChartView:(JBLineChartView *)lineChartView colorForLineAtLineIndex:(NSUInteger)lineIndex
{
    if (lineIndex == 0)
        return [UIColor blackColor];
    else if (lineIndex == 1)
        return [UIColor blueColor];
    else
        return [UIColor lightGrayColor];
    
}


- (BOOL)lineChartView:(JBLineChartView *)lineChartView showsDotsForLineAtLineIndex:(NSUInteger)lineIndex
{
    return false;
}

- (UIColor *)lineChartView:(JBLineChartView *)lineChartView colorForDotAtHorizontalIndex:(NSUInteger)horizontalIndex atLineIndex:(NSUInteger)lineIndex
{
    return [UIColor lightGrayColor];
}


- (BOOL)lineChartView:(JBLineChartView *)lineChartView smoothLineAtLineIndex:(NSUInteger)lineIndex
{
    if (lineIndex == 0){
        return false;
    }
    return true;
}

- (CGFloat)lineChartView:(JBLineChartView *)lineChartView widthForLineAtLineIndex:(NSUInteger)lineIndex
{
    return 0.5;
}

@end
