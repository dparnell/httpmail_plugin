/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "WebMessageController.h"

@interface WebMessageController (WebViewDelegateMethods)
- (BOOL)_isInternalURL:(id)fp8;
- (BOOL)considerBaseURLsInternal;
- (void)webView:(id)fp8 decidePolicyForNavigationAction:(id)fp12 request:(id)fp16 frame:(id)fp20 decisionListener:(id)fp24;
- (void)webView:(id)fp8 decidePolicyForNewWindowAction:(id)fp12 request:(id)fp16 newFrameName:(id)fp20 decisionListener:(id)fp24;
- (id)webView:(id)fp8 identifierForInitialRequest:(id)fp12 fromDataSource:(id)fp16;
- (id)webView:(id)fp8 resource:(id)fp12 willSendRequest:(id)fp16 redirectResponse:(id)fp20 fromDataSource:(id)fp24;
- (void)webView:(id)fp8 didStartProvisionalLoadForFrame:(id)fp12;
- (void)webView:(id)fp8 didCommitLoadForFrame:(id)fp12;
- (void)webView:(id)fp8 didFailProvisionalLoadWithError:(id)fp12 forFrame:(id)fp16;
- (unsigned int)webView:(id)fp8 dragDestinationActionMaskForDraggingInfo:(id)fp12;
- (id)webView:(id)fp8 plugInViewWithArguments:(id)fp12;
- (id)webView:(id)fp8 contextMenuItemsForElement:(id)fp12 defaultMenuItems:(id)fp16;
- (void)download:(id)fp8 decideDestinationWithSuggestedFilename:(id)fp12;
@end

