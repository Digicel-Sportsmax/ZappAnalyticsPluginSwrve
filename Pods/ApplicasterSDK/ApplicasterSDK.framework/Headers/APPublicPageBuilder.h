//
//  APPublicPageBuilder.h
//  applicaster
//
//  Created by dan g / applicaster on 8/31/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APPublicPageBuilder : NSObject

/**
 get public page for the app
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForApp;

/**
 get public page for an Applicaster VOD item
 @param vodItemUniqueID - String vod item unique ID
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForVodITem:(NSString *)vodItemUniqueID;

/**
 get public page for a live channel
 @param channelUniqueID - String channel ID
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForChannel:(NSString *)channelUniqueID;

/**
 get public page for Applicaster social feed
 @discussion - Please migrate to use the new function that defines if to use the new feed. This by default will launch the old feed.
 @param timelineID - String timeline ID
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForFeed:(NSString *)timelineID;

/**
 get public page for Applicaster social feed
 @param timelineID - String timeline ID
 @param newFeed - Boolean value - true if new feed
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForFeed:(NSString *)timelineID newFeed:(BOOL)newFeed;

/**
 get public page for Crossmates
 @param timelineID - String timeline ID
 @param eventID - Unique ID of a specific event
 @return NSURL - URL with the Public page with the proper scheme parameter
 */
+ (NSURL *)getPublicPageForCM:(NSString *)timelineID andFeedID:(NSString *)feedID andEventID:(NSString *)eventID;

/**
 Build a public page for a url scheme without prefix - for example play?voditemid=123
 @param urlScheme in string
 @return URL for public page
 */
+ (NSURL *)getPublicPageForURLSchemeWithoutPrefix:(NSString *)urlScheme;

/**
 Build a public page url with actions and parameters
 Please make sure parameters themselves are already URL encoded if needed
 @param action Action string
 @param parameters Dictionary of parameters for the URL scheme
 @return URL for public page
 */
+ (NSURL *)getPublicPageForAction:(NSString *)action andParameters:(NSDictionary *)parameters;
@end
