//
//  APVodItem.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

// Remove this when we can
@import UIKit;
@import ZappPlugins;

#import "APShareable.h"
#import "APPurchasableItem.h"
#import "APFavoritesManager.h"

@class APStoreKitPurchaseParams;
@protocol ZPPlayable;

extern NSString *const APVodItemCacheStateChangedNotification;
extern NSString *const APVodItemHqmeInProgressNotification;
extern NSString *const APVodItemHqmeCompletedNotification;

extern NSString *const APVodItemProgressKey;	//A key that will contain an NSNumber with the progress float

extern NSString *const APHqmeDidAddNotification;      // Fired when 'markForHqmeProcess' method is called.
extern NSString *const APHqmeDidRemoveNotification;      // Fired when 'deleteFromCache', 'cancelHqmeProcess' methods are called.

/** 
 Key of the VOD Item Object in the User Info. Currently relevant for:
 APHqmeItemAddedNotification, APHqmeItemRemovedNotification
 */
extern NSString *const APVODItemKey;

// Used for the player
extern NSString *const kAPPlayerControllerPlayingItemShowName;              // Contains the current item's show name property.
extern NSString *const kAPPlayerControllerPlayingItemIsFavorite;            // The current item's isFavorite status
extern NSString *const kAPPlayerControllerPlayingItemHqmeInProgress;         // The current item's hqme in progress status
extern NSString *const kAPPlayerControllerPlayingItemHqmeCompleted;          // Contains the current item's hqme completed status

/**
 APVodItem represents a model containing a VOD item to be played.
 
 While some data arives cashed on the category children level (like images , name and description) the URLs for the stream and advertising products do not.
 They are however loaded automatically when running the - (void)play; function.
 
 In general - a VOD item is usually generated from a parent category children array , displayed and played using the play function.
 In case of a purchase - The play method will invoke the relevant interface for purchasing (either UI-less or with an app specific storefront
 */
@interface APVodItem : APPurchasableItem <ZPPlayable, APFavoritesProtocol , APUICustomizationExtendedProtocol, APShareable, ZPHqmeSupportingItemProtocol> {
	BOOL _waitingForStream;
	BOOL _playOnLoad;
	BOOL _needsPurchaseCheck;
    BOOL _ignorePromotions;
	NSString *_overridePreroll;
	NSString *_overrideSplash;
	APStoreKitPurchaseParams *_itemVoucherParams;
	APStoreKitPurchaseParams *_seasonVoucherParams;
	APStoreKitPurchaseParams *_showVoucherParams;
	NSArray *_associatedProductIdentifiers;
}

#pragma mark - Properties
/**
 Order date on the server.
 This can be parsed to an NSDate for comparison in the following way:
 <code>
 NSDateFormatter* dateFormatter = [[[NSDateFormatter alloc] init] autoRelease];
 [dateFormatter setDateFormat:@"yyyy/MM/dd HH:mm:ss Z"];
 NSLocale *enUSPOSIXLocale = [[[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"] autorelease];
 dateFormatter.locale = enUSPOSIXLocale;
 NSDate *date = [dateFormatter dateFromString:[vodItem orderDate]];
 </code>
 */
@property (unsafe_unretained, readonly) NSDate *orderDate;

/**
 Parent Category Identifier
 */
@property (unsafe_unretained, readonly) NSString *categoryID;

/**
 VodItem title
 */
@property (unsafe_unretained, readonly) NSString *title;

/**
 VOD Item Duration
 Exists only if requestd and generated on the server side
 */
@property (unsafe_unretained, readonly) NSString *duration;

/**
 Vod Item Summery
 */
@property (unsafe_unretained, readonly) NSString *summary;

/**
 VOD Item streamURL
 Usually an m3u8 stream
 */
@property (nonatomic, strong, readwrite) NSString *streamURL;

/**
 Splash URL for preroll
 */
@property (unsafe_unretained, readonly) NSString *splashURL;

/**
 Returns YES if a preroll splash is provided from the category exists
 */
@property (readonly) BOOL isSplashDefault;

/**
 Video Preroll URL
 */
@property (unsafe_unretained, readonly) NSString *prerollURL;

/**
 Returns YES if a preroll is provided from the category exists
 */
@property (readonly) BOOL isPrerollDefault;

/**
 EPG URL to be used with the player
 */
@property (unsafe_unretained, readonly) NSString *epgURL;

/**
 Parent broadcaster ID
 */
@property (unsafe_unretained, readonly) NSString *broadcasterID;

/**
 Array of product identifiers that cover the item in case a purchase is needed.
 (Used for non subscription based apps - for example Item , Season , Series identifiers)
 */
@property (nonatomic, strong, readonly) NSArray	*productIdentifiers;

/**
 If preroll override is set - this preroll will be used rather then the default
 */
@property (nonatomic, copy) NSString *overridePreroll;

/**
 If splash ovveride is set - this splas will be used rather then the defualt
 */
@property (nonatomic, copy) NSString *overrideSplash;

/**
 VOD Item Model URL
 */
@property (unsafe_unretained, readonly) NSString *URL;

/**
 Purchase paramethers for voucher
 */
@property (nonatomic, strong, readonly) APStoreKitPurchaseParams *itemVoucherParams;

/**
 Relevant vod item voucher template ID - to be used with single item purchase
 */
@property (nonatomic, strong, readonly) NSString *itemVoucherTemplateID;

/**
 Season name
 */
@property (nonatomic, strong, readonly) NSString *seasonName;

/**
 Season purchase parameters
 */
@property (nonatomic, strong, readonly) APStoreKitPurchaseParams *seasonVoucherParams;

/**
 Relevant Season voucehr template ID - to be used with a full season purchase
 */
@property (nonatomic, strong, readonly) NSString *seasonVoucherTemplateID;

/**
 Season category ID
 */
@property (nonatomic, strong, readonly) NSString *seasonCategoryID;

/**
 Show name
 */
@property (nonatomic, strong, readonly) NSString *showName;

/**
 Show voucher parameters
 */
@property (nonatomic, strong, readonly) APStoreKitPurchaseParams *showVoucherParams;

/**
 Relevant Show voucher template ID - to be used with a full show purchase
 */
@property (nonatomic, strong, readonly) NSString *showVoucherTemplateID;

/**
 Top level category ID.
 */
@property (unsafe_unretained, readonly) NSString *topLevelCategoryID;

/**
 Returns the name of the TLC which this vod item is under.
 */
@property (nonatomic, strong, readonly) NSString *topLevelCategoryName;

/**
 Show category ID
 */
@property (nonatomic, strong, readonly) NSString *showCategoryID;

/**
 Returns a boolean value if the VOD item exists in the EUP's favorites list
 */
@property (nonatomic, readonly) BOOL isFavorite;

/**
 Boolean value , This can be set by the application so no Advertising will be used when displaying this VOD item.
 */
@property (nonatomic, assign) BOOL ignorePromotions;

/**
 HQME Item expiration date from the server.
 The following logics is used - Either return 1 month or the time left on the subscription
 */
@property (nonatomic, strong, readonly) NSDate *hqmeExpirationDate;

/**
 Checks if a VOD item is HQME enabled (allowed for hqme)
 */
@property (readonly) BOOL isHQME;

/**
 Checks if the vod item should be set as non deletable by the user
 */
@property (readonly) BOOL notDeleteable;

/**
 Longtitude values for Geo
 */
@property (unsafe_unretained, nonatomic,readonly) NSString *longtitude;

/**
 Latitude values for Geo
 */
@property (unsafe_unretained, nonatomic,readonly) NSString *latitude;


/**
 Returns a boolean value of the vod item or the its category active for viewing flag. YES - active for viewing is mark, NO - active for viewing is unchecked.
 */

@property (nonatomic, assign, getter = isAllowPlay) BOOL allowPlay;

#pragma mark - Legacy properties
/**
 The following properties are probably no longer avilable through the CMS and should be discussed before used
 */
@property (unsafe_unretained, readonly) NSString *director;
@property (unsafe_unretained, readonly) NSString *genreID;
@property (unsafe_unretained, readonly) NSString *language;
@property (unsafe_unretained, readonly) NSString *provider;
@property (unsafe_unretained, readonly) NSString *rating;
@property (unsafe_unretained, readonly) NSString *rentPeriod;
@property (unsafe_unretained, readonly) NSString *rentPeriodFrequency;
@property (unsafe_unretained, readonly) NSString *subtitles;
@property (unsafe_unretained, readonly) NSString *linkURL;

#pragma mark - Deprecated Properties

/**
 Returns the thumbnailURL
 This property should not be used.
 Instead use imageNamed:
 */
@property (unsafe_unretained, readonly) NSString *thumbnailURL;

/**
 Returns the thumbnail238URL
 This property should not be used.
 Instead use imageNamed:
 */
@property (unsafe_unretained, readonly) NSString *thumbnail238URL;

/**
 External link URL
 */
@property (unsafe_unretained, nonatomic,readonly) NSString *externalLink;

/**
 External vod item ID
 */
@property (unsafe_unretained, nonatomic,readonly) NSString *externalID;

/**
 External vod item policy
 */
@property (unsafe_unretained, nonatomic,readonly) NSDictionary *externalPolicy;

/**
 Vod item source file
 */
@property (weak, nonatomic,readonly) NSString *sourceFile;

/**
 indicates whether or not remove persistant resume
 */
@property (nonatomic, assign) BOOL shouldIgnoreInterruptScreen;

/**
 Should not play ads for this item
 */
@property (nonatomic, assign) BOOL shouldSkipAds;

#pragma mark - APVodItem


/**
 Initialise with uniqueID and externalID
 @param uniqueID - item id
 @param externalID - external item id
 */
- (id)initWithUniqueID:(NSString *)uniqueID externalID:(NSString *)externalID;

/**
 Compares if 2 VOD items are equal by comparing their class types both being APVodItem and their uniqueID properties being equal.
 @param otherVODItem The other VOD item being compared.
 @return YES if the VOD items have the same unique ID. NO otherwise.
 */
- (BOOL)isEqualToVodItem:(APVodItem *)otherVODItem;

/**
 The VOD item can play if it agrees any of 4 conditions:
 1. It's free
 2. The user is online (if it's not free they can attempt purchase if required)
 3. The user has a valid subscription
 4. The user owns the VOD item
 
 For now SSO is not taking care in this method.
 
 @return YES if the VOD item matches the conditions. NO otherwise.
 */
- (BOOL)canPlay;

/**
 Plays the vod item using the new player.
 showing the the new player with animated presentation
 */
- (void)play;

/**
 Plays the vod item using the new player.
 showing the the new player with animated or non animated presentation
 @param animated Present the new player animated or not animated
 */
- (void)playAnimated:(BOOL)animated;

/**
 Plays vod item using a new stream url.
 @param overrideStreamURL the stream url that will be played
 @param animated Present the new player animated or not animated
 */
- (void)playWithOverrideStreamURL:(NSString *)overrideStreamURL animated:(BOOL)animated;

/**
 Plays the vod item using the new player within a given timeframe.
 @param startTime The start time of the clip.
 @param endTime The end time of the clip.
 */
- (void)playFromStartTime:(NSTimeInterval)startTime toEndTime:(NSTimeInterval)endTime;

/**
 Checks if an image exists lcoally and returns it
 @param name of the image from the VOD Item Image Dictionary
 @return UIImage object if image exists or nil if it does not.
 */
- (UIImage*)localImageForName:(NSString*)name;

/**
 Price String from the relevant item voucher
 @return price string
 */
- (NSString*)price;

/**
 @return YES if storefront should be displayed
 */
- (BOOL)shouldShowStoreFront;

/**
 @return cache state notification name
 */
- (NSString*)cacheStateChangedNotification;

/**
 @return hqme progress changed notification name
 */
- (NSString*)hqmeProgressChangedNotification;

/**
 @return hqme failure notification name - posted when a process fails
 */
- (NSString*)hqmeFailureNotification;

/**
 Checks if VOD item offline state
 @return current offline state
 */
- (ZPHqmeItemState)itemHqmeState;

/**
 Indicates whether or not item opens by url scheme.
 */
@property (nonatomic, assign) BOOL isInitViaUrlScheme;

#pragma mark - HQME

/**
 hqme progress percentage
 @return percentage in CGFloat
 */
- (CGFloat)hqmeProgress;
/**
 Add VOD Item to start hqme process
 @return YES if marked for hqme process , NO otherwise
 */
- (BOOL)markForHqmeProcess;

/**
 Delete VOD item Cache data
 @return YES if item deleted from cache , NO otherwise
 */
- (BOOL)deleteFromCache;

/**
 Cancel process and delete/not delete the local data.
 @param deleteCache - BOOL that defines if to delete the local data or not.
 */
- (void)cancelHqmeProcessAndDeleteCache:(BOOL)deleteCache;

/**
 Cancel hqme process
 */
- (void)cancelHqmeProcess;


#pragma mark - Favorites

/**
 Add VOD item to favorites
 */
- (void)addToFavorites;

/**
 Remove VOD Item from favorites
 */
- (void)removeFromFavorites;

//Check functionality
+ (NSString *)URL;

@end
