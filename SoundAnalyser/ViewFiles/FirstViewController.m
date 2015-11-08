//
//  FirstViewController.m
//  SoundAnalyser
//
//  Created by Apple on 31/10/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#import "FirstViewController.h"
#import "../Audio/AudioUnitReceive.h"
#import "../Math/SignalDefinitions.h"
#import "../Math/ProcessSignal.h"

@interface FirstViewController ()

@end

@implementation FirstViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    GenerateTestSignals();
    
    _lcRawSignal.backgroundColor = [UIColor whiteColor];
    _lcRawSignal.delegate = self;
    _lcRawSignal.dataSource = self;
    _lcRawSignal.minimumValue = 0;
    _lcRawSignal.maximumValue = 50;
    
    
    [_lcRawSignal reloadData];
    [_lcRawSignal setState:JBChartViewStateExpanded animated: true];
    
    if (AudioUnitStarted)
        _btnAudioUnitControl.selectedSegmentIndex = 0;
    else
        _btnAudioUnitControl.selectedSegmentIndex = 1;
    
    
    
    
    NSTimer* timer3;
    timer3 = [NSTimer scheduledTimerWithTimeInterval: 0.02
                                              target: self
                                            selector:@selector(updateLabels)
                                            userInfo: nil repeats:YES];
    
}

-(void) updateLabels{
    //_lblSignalValues.text = [NSString stringWithFormat:@"Values: %f,%f,%f", fValue0, fValue5, fValue20];
    //_lblSignalLength.text = [NSString stringWithFormat:@"Signal Length: %d",signalLength];
    Process1();
    [_lcRawSignal reloadData];
    
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
    if (_btnAudioUnitControl.selectedSegmentIndex == 0)
    {
        initAudioSession();
        initAudioStreams(audioUnit);
        startAudioUnit(audioUnit);
    }
    else if(_btnAudioUnitControl.selectedSegmentIndex == 1)
        stopProcessingAudio(audioUnit);
}

- (IBAction)Test:(id)sender {
    TestCase1();
}


// MARK: JBLineChartView

- (NSUInteger)numberOfLinesInLineChartView:(JBLineChartView *)lineChartView
{
    return 1;
}


- (NSUInteger)lineChartView:(JBLineChartView *)lineChartView numberOfVerticalValuesAtLineIndex:(NSUInteger)lineIndex
{
    return SIGNAL_LENGTH;
}

- (CGFloat)lineChartView:(JBLineChartView *)lineChartView verticalValueForHorizontalIndex:(NSUInteger)horizontalIndex atLineIndex:(NSUInteger)lineIndex
{
    if (lineIndex == 0)
        return Graph1Data[horizontalIndex];
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
