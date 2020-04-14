//
//  APAdProvider.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 14/03/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The APADProvider protocol is to be used by the different ad providers required for creating banners.
 */
@interface APAdProvider : NSObject

/** The time used to refresh banners. */
@property (nonatomic, assign) NSTimeInterval bannerRefreshRate;

/** The parameters of the ad provider */
@property (nonatomic, strong) NSDictionary *parameters;

/** The analytics dictionary */
@property (nonatomic, strong) NSDictionary *analyticsDictionary;

@end
