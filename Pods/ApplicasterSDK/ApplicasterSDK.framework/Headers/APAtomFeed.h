//
//  APAtomFeed.h
//  applicaster
//
//  Created by Miri on 10/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APCategory.h"
#import "APModel.h"
#import "APShareable.h"

@import ZappPlugins;

@protocol APExpirable;
@protocol APAtomEntryExtensionsProtocol;

/*
 This type of feed determined by entries
 Feed can be: 
 APAtomFeedNatureArticle type if contains just article entries,
 APAtomFeedNatureImage type if contains just images entries,
 APAtomFeedNatureImageGallery type if contains just Galery entries ,
 APAtomFeedNatureMix type if contains some types
 */

@class APAtomEntry;
typedef enum{
    APAtomFeedNatureUnknown,
    APAtomFeedNatureArticle,
    APAtomFeedNatureVideo,
    APAtomFeedNatureImage,
    APAtomFeedNatureImageGallery,
    APAtomFeedNatureMix
} APAtomFeedNature;

@interface APAtomFeed : APCategory <APShareable, APContainerProtocol, APAtomContainerProtocol, APExpirable, APAtomEntryExtensionsProtocol>

/**
 The value of the link in string will be used as the shared link URL of the feed.
 */
@property (nonatomic, strong) NSString *shareLink;

/**
 Returns the feed nature - Article, Video, Image, Gallery, mix.
 */
@property (nonatomic, assign) APAtomFeedNature atomFeedNature;


/**
 Define force to use old style xml loader
 */
@property (nonatomic, assign, readonly) BOOL forceUseOldLoaderLogic;

/**
 APModel initializer

 @param dictionary applicaster dictionary
 @return APAtomFeed instance
 */
- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (instancetype)initWithEntry:(APAtomEntry *)entry;
- (instancetype)initWithURL:(NSString *)url;


/**
 Create Atom Feed with indentifier

 @param uniqueID Unique Identifier
 @param forceUseOldLoaderLogic  Define force to use old style xml loader
 @return APAtomFeed instance
 */
- (instancetype)initWithUniqueID:(NSString *)uniqueID
          forceUseOldLoaderLogic:(BOOL)forceUseOldLoaderLogic;


/**
 Search entry in entries list by unique ID

 @param uniqueID of searched entry
 @return instance that conform APAtomEntryProtocol with specific unique ID, nil in case can not found
 */
-(id <APAtomEntryProtocol>)entryByID:(NSString *)uniqueID;

-(NSString *)actionUrl;
@end
