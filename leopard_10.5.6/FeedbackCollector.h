/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSButton, NSMutableString, NSProgressIndicator, NSTextField, NSView, NSWindow, WebView;

@interface FeedbackCollector : NSObject
{
    WebView *metricsWebView;
    NSButton *includeMetricsCheckbox;
    NSWindow *window;
    NSProgressIndicator *spinner;
    NSTextField *collectingTextField;
    NSView *statusContainerView;
    NSButton *continueButton;
    NSMutableString *feedbackHTMLString;
    BOOL sendMetricsImmediately;
    BOOL currentlyLoading;
}

+ (id)sharedInstance;
- (id)init;
- (void)dealloc;
- (void)run;
- (void)collectMetrics;
- (void)webView:(id)fp8 didFinishLoadForFrame:(id)fp12;
- (void)sendMetricsIfRequested;
- (void)cleanUpWindow;
- (void)loadStringIntoWebView;
- (BOOL)windowShouldClose:(id)fp8;
- (void)continue:(id)fp8;
- (void)cancel:(id)fp8;

@end
