//
//  APAtomEntry.h
//  applicaster
//
//  Created by Miri on 10/23/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

@import ZappPlugins;
@import Foundation;

#import "APURLPlayable.h"
#import "APShareable.h"
#import "APFavoritesManager.h"

@class APContent;
@class APAtomMediaGroup;
@class APAtomEntryPlayable;
@class APAtomFeed;

@protocol APAtomEntryExtensionsProtocol;

#pragma mark - APAtomEntry

@interface APAtomEntry : NSObject <APShareable, APAtomEntryProtocol, APAtomEntryExtensionsProtocol, APFavoritesProtocol, NSCoding, APUICustomizationProtocol, ZPHqmeSupportingItemProtocol>

/*
 Title - title of the parent feed (forward from the parent).
 */
@property (nonatomic, strong) NSString *parentTitle;

/*
 HTML url
 */
@property (nonatomic, copy) NSString *htmlUrl;

/*
 Share Url - is taken from URL Scheme if ShareUrl parameter is defined. If shareUrl is not null it is taken on sharing.
 It is in CACellAtomMediaPlayerViewController's use
 New URL can be shown like: kan://audioPlayer?title=88&summary=88&mediaUrl=http://ipbc-metadata-rr-d.vidnt.com/live/ipbc/IPBC88LAM/hls/redirection_playback_url.m3u8&imageUrl=http://assets-production.applicaster.com.s3.amazonaws.com/achievement-center/ILAPAC/KAN/88_870.png&isLive=true&htmlUrl= &shareUrl= < urlencoded_url_to_share >
 */
@property (nonatomic, copy) NSString *shareUrl;


+ (instancetype)linkEntryWithURLString:(NSString *)urlString;

/*
 Sets the atom entry values from a dictionary containing the title, summary, stream url and image url
 */
- (id)initWithParams:(NSDictionary *)parameters;

/**
 Initiates a new instance by the pipes object dictionary.
 Used for example for parsing an entry back from React Native.
 */
- (instancetype)initWithPipesObject:(NSDictionary *)object;

/**
 *  Finds the first media group by wanted type
 *  @param type wanted type
 *  @return first wanted media group
 */
- (APAtomMediaGroup *)mediaGroupWithType:(APAtomMediaGroupType)type;

/**
 Compares to models.
 @param otherModel The other model to compare to.
 @return YES if models points are equal, NO if not.
 */
- (BOOL)isEqualToModel:(APAtomEntry *)otherModel;

/**
 @return A new instance of playable for this entry each call.
 */
- (APAtomEntryPlayable *)playable;

/*
 Adds a mediaitem to the appropriate media groups of the atom entry
 */
- (void)addMediaItemType:(APAtomMediaGroupType)mediaGroupType
               stringURL:(NSString *)stringURL
                     key:(NSString *)key;

/*
fetch the content url
 */
- (void)fetchContentUrlWithCompletion:(void (^)(void))completion;

/*
 content url placeholder
 */
+ (NSString *)contentUrlPlaceholder;
@end
