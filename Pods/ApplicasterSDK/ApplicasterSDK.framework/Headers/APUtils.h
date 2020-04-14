//
//  APUtils.h
//  applicaster
//
//  Created by Neer Friedman on 12/8/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/**
 This class provides some basic utility methods.
 */
@interface APUtils : NSObject

+ (NSDictionary *)signRequestParams:(NSDictionary *)params URL:(NSString *)url withKey:(NSString *)key;
+ (NSString *)signedURLPath:(NSString *)urlPath withParams:(NSDictionary *)params withKey:(NSString *)key;

/**
 * Parse string to date
 * @param stringDate - the date as string
 * @return the NSString of the format dd.mm.yyyy 
 */
+ (NSString *)dateFormatFromString:(NSString *)stringDate;

/**
 Checks if the stream is valid.
 @param streamPath - The path of the stream to test
 @return NO if the stream is empty or has expired, YES otherwise.
 */
+ (BOOL)isStreamValid:(NSString *)streamPath;

/**
 Converts a date from local time zone to UTC.
 @param localDate - A date in local time zone.
 @return The date normalized to UTC time zone.
 */
+ (NSDate *)getUTCDateFromLocalDate:(NSDate *)localDate;

/**
 Checks if a selected URL link should be opened externally or internally.
 @param URL The URL being checked.
 @return YES if the link should be opened externally. NO otherwise.
 */
+ (BOOL)shouldOpenURLExternally:(NSURL *)URL;

/**
 @return YES if the given URL is a web one (one that can be opened from the Safari for example)
 */
+ (BOOL)isWebURL:(NSURL*)URL;

/**
 @return YES if the given URL is a web one (one that can be opened from the Safari for example)
 */
+ (BOOL)isWebStringURL:(NSString *)stringURL;

/**
 This method caches the current version number of the app.
 
 @discussion In order to implement the version logic correctly, please make sure to call this method as soon as you can in order to populate the version field correctly. Without calling this method 'isFirstLaunchOfTheApp' and 'isFirstLaunchOfCurrentVersion' will return wrong value.
 */
+ (void)cacheVersionNumber;

/**
 Make sure that 'cacheVersionNumber' was being called - otherwise this value will be wrong.
 
 @return  YES if this is the first launch of this app. (Or first time it was launched after installing version containing this method)
 */
+ (BOOL)isFirstLaunchOfTheApp;

/**
 Make sure that 'cacheVersionNumber' was being called - otherwise this value will be wrong.
 
 @return YES if this is the first launch of this version (Either first launch of the app or update of the version). (Or first time it was launched after installing version containing this method)
 */
+ (BOOL)isFirstLaunchOfCurrentVersion;

/**
 This method returns the current short version of the application installed. (1.0 / 1.1 / ...)
 */
+ (NSString *)applicationShortVersion;

+ (BOOL)isReactNativeURL:(NSURL*)URL;
@end
