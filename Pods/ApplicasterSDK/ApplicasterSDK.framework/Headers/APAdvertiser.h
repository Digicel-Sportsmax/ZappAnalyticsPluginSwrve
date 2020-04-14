//
//  APAdvertiser.h
//  applicaster
//
//  Created by Guy Kogus on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

extern NSString *const kAPAdProviderNameApplicaster;
extern NSString *const kAPAdProviderNameZedo;
extern NSString *const kAPAdProviderNameCheckm8;
extern NSString *const kAPAdProviderNameDoubleClick;

//extern NSString *const APEnableJustAd;

extern NSString *const kAPBannerConfigURLIPhone;
extern NSString *const kAPBannerConfigURLIPad;

@class APAdProvider;
//@class justAdView;

/**
 The APAdvertiser model is used to define the Applicaster advertisement mechanism. It is used to create banners using the list of given ad providers.
 */
@interface APAdvertiser : APModel

/**
 An array of classes that conform to the <APAdProvider> protocol.
 */
@property (nonatomic, strong) NSArray *adProviders;
///** Keep a value to indicate whether or not justAds are enabled. */
//@property (nonatomic, assign) BOOL justAdEnabled;
/** The local (Applicaster) banners for this application. */
@property (nonatomic, strong, readonly) NSArray *localBanners;

/** The amount of time banners will be displayed during video playback. If <bannerDelayTime> is non-zero, the banners will be hidden after the exposure time. */
@property (nonatomic, assign) NSTimeInterval bannerExposureTime;

/** During video playback, this determines the amount of time to hide banners before showing the next one. */
@property (nonatomic, assign) NSTimeInterval bannerDelayTime;

/** The custom ad provider class MUST subclass <APCustomAdProvider>. */
@property (nonatomic, assign) Class customAdProviderClass;

/**
 Initialise the advertiser using the information received for the application-level ad providers.
 @param adProviders The array with the parameters for each advertiser type.
 @return The new Advertiser model.
 */
- (id)initWithAdProviders:(NSArray *)adProviders;

/**
 Get initial parameters for an ad provider.
 @param adProviderName See the constants defined in APAdvertiser.h
 @return The parameters for the ad provider, or nil if the ad provider was not found.
 */
- (NSDictionary *)paramsForAdProviderNamed:(NSString *)adProviderName;

/**
 Add an ad provider to the current list. This is best called once the account model has finished loading.
 @param adProvider The new ad provider.
 @param idx The index of the ad provider.
 */
- (void)insertAdProvider:(APAdProvider *)adProvider atIndex:(NSUInteger)idx;

@end
