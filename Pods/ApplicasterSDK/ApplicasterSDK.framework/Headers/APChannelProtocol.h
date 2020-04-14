//
//  APChannelProtocol.h
//  Pods
//
//  Created by Avi Levin on 22/08/2017.
//
//
@protocol APChannelProtocol <NSObject>


@property (nonatomic, assign) BOOL playOnLoad;
@property (nonatomic, assign) BOOL needsPurchaseCheck;

/**
 Live channel Stream URL
 */
@property (nonatomic, strong, readonly) NSString *streamURL;

/**
 Splash URL
 */
@property (nonatomic, strong, readonly) NSString *splashURL;

/**
 preroll URL
 */
@property (nonatomic, strong, readonly) NSString *prerollURL;

/**
 Channel Name
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 Channel Name
 */
@property (nonatomic, strong, readonly) NSString *channelId;


/**
 Web EPG URL
 */
@property (nonatomic, strong, readonly) NSString *epgURL;

/**
 Currently playing program name
 */
@property (nonatomic, strong, readonly) NSString *nowPlaying;

/**
 Default Image URL
 Unlike VOD Items and Categories - APChannel does not implement an image dictionary.
 Instead only a single image exist and should be used
 */
@property (nonatomic, strong, readonly) NSString *defaultImageURL;

/**
 Should not play ads for this channel
 */
@property (nonatomic, assign) BOOL shouldSkipAds;

/**
 close the player's instance and create a new instance on channel switching
 */
@property (nonatomic, assign) BOOL shouldClosePlayerOnChannelSwitching;


@end
