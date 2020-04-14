//
//  APCallbackHandler.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/26/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APTimedWebViewController.h"
#import "APTimedWebViewControllerDelegate.h"

@import WebKit;

/**
 Protocol for Decision making in takeover screen
 */
@protocol APTakeOverScreenHandlerPolicy <NSObject>
/**
 Method to be implemented to see if a certain object allowes Takeover screen
 */
- (BOOL)canShowTakeoverScreen;

@end

@protocol APJavaScriptListenerDelegate;
@class APJavaScriptListener;

@interface APCallbackHandler : NSObject <APJavaScriptListenerDelegate, APTimedWebViewControllerDelegate> {
    UIViewController                    *__unsafe_unretained _displayViewController;
    APJavaScriptListener                *_listener;
}

/**
 Display View controller - used to display the actions above
 */
@property (nonatomic, unsafe_unretained) UIViewController *displayViewController;

/**
 Javascript listener
 */
@property (nonatomic, strong) APJavaScriptListener *listener;

/**
 Instance of current takeover screen displayed or loading.
 */
@property (nonatomic, strong) APTimedWebViewController *takeoverInstance;


/**
 Initialization function - Uses "applicaster://" as the scheme string.
 This should be used to get a properly defined default TOS Handler
 @param vc controller used to display actions on. if nil value is passed - ApplicasterController's Root View Controller is used
 @param url for JS
 @retun Initialized TOS Handler
 */
- (id)initWithViewController:(UIViewController *)vc andURL:(NSURL *)url;

/**
 Initialization function , Creates it's own webView
 @param vc controller used to display actions on. if nil value is passed - ApplicasterController's Root View Controller is used
 @param string string to catch commands
 @param url for JS
 */
- (id)initWithViewController:(UIViewController *)vc andSchemeString:(NSString *)string andURL:(NSURL *)url;


/**
 Initialization function , Uses am existing webView.
 @param vc controller used to display actions on. if nil value is passed - ApplicasterController's Root View Controller is used
 @param string string to catch commands
 @param url for JS
 @param webView existing web view
 */
- (id)initWithViewController:(UIViewController *)vc andSchemeString:(NSString *)string andURL:(NSURL *)url andWebView:(WKWebView *)webView;

/**
 Runs a callback script to pass information back to the overlay in JSON format.
 @param callbackName The name of the callback script.
 @param parameters The parameters to pass on to the callback script. This dictionary will be transformed into a JSON string.
 */
- (void)runCallbackScriptWithName:(NSString *)callbackName parameters:(NSDictionary *)parameters;

- (void)handleJavaScriptCallWithCommand:(NSString *)command
                          dictionary:(NSDictionary *)dictionary;

@end
