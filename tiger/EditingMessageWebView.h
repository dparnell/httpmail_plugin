/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "WebView.h"

@interface EditingMessageWebView : WebView
{
}

- (void)addHorizontalRule:(id)fp8;
- (BOOL)canPasteAsHTML;
- (void)changeQuoteLevel:(id)fp8;
- (int)compareRange:(id)fp8 toEndOfNode:(id)fp12;
- (void)concludeDragOperation:(id)fp8;
- (void)consolidateTextAndWhitespaceInTree:(id)fp8;
- (void)deleteNode:(id)fp8;
- (void)deleteRange:(id)fp8;
- (unsigned int)draggingEntered:(id)fp8;
- (void)draggingExited:(id)fp8;
- (unsigned int)draggingUpdated:(id)fp8;
- (void)editLink:(id)fp8;
- (void)insertNode:(id)fp8 parent:(id)fp12 nextSibling:(id)fp16;
- (void)insertTemporarySelectionMarkersForRange:(id)fp8;
- (void)makeFontBigger:(id)fp8;
- (void)makeFontSmaller:(id)fp8;
- (void)paste:(id)fp8;
- (void)pasteAsHTML:(id)fp8;
- (void)pasteAsQuotation:(id)fp8;
- (void)pasteWithCurrentStyle:(id)fp8;
- (BOOL)performDragOperation:(id)fp8;
- (BOOL)prepareForDragOperation:(id)fp8;
- (void)registerForDraggedTypes:(id)fp8;
- (void)removeAllFormatting;
- (BOOL)removeFormattingFromTree:(id)fp8 forDocument:(id)fp12 plainTextDelegate:(id)fp16;
- (BOOL)removeRichNodesAndStyleFromTree:(id)fp8 forDocument:(id)fp12 plainTextDelegate:(id)fp16;
- (void)restoreSelectionFromTemporaryMarkers;
- (void)saveSelectionForUndo;
- (void)setValue:(id)fp8 forAttribute:(id)fp12 ofElement:(id)fp16;
- (BOOL)splitUpBlockQuotesPartiallyContainedInRange:(id)fp8;
- (BOOL)validateUserInterfaceItem:(id)fp8;
- (BOOL)wantsPeriodicDraggingUpdates;

@end

