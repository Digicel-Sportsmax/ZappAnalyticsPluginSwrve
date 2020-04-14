//
//  APAuthorizationManager.h
//  applicaster
//
//  Created by Reuven Levitsky on 6/22/15.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APAuthorizationManager.h"

@interface APWebAuthorizationClient : NSObject <APAuthorizationClient> {

}

/**
 Current state string
 @discussion
 We use this auto generated string in order to make sure that the URL scheme is authentic and not faked by someone.
 */
@property (nonatomic, strong) NSString *state;

/**
 Should validate state when returning from URL scheme
 */
@property (nonatomic, assign) BOOL shouldValidateState;

/**
 Authorization provider
 */
@property (nonatomic, strong) APAuthorizationProvider *provider;

/**
 URL used for the authorization webview
 */
- (NSURL *)providerURL;

/**
 InterfaceOrientationMask used for the authorization webview
 */
- (UIInterfaceOrientationMask)webViewInterfaceOrientation;
@end
