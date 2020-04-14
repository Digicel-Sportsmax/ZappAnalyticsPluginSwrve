//
//  APAtomFeedParser.h
//  applicaster
//
//  Created by Miri on 10/26/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APAtomFeed;

extern NSString *const kAPAtomEntryNatureArticle;
extern NSString *const kAPAtomEntryNatureImage;
extern NSString *const kAPAtomEntryNatureImageGallery;
extern NSString *const kAPAtomEntryNatureVideo;
extern NSString *const kAPAtomEntryNatureAudio;
extern NSString *const kAPAtomEntryNatureLink;
extern NSString *const kAPAtomEntryNaturePlaylist;
extern NSString *const kAPAtomEntryNatureAtomFeed;
extern NSString *const kAPAtomEntryNatureProgram;
extern NSString *const kAPAtomEntryNatureChannel;
extern NSString *const kAPAtomEntryNatureApplicasterFeed;
extern NSString *const kAPAtomEntryNatureApplicasterCrossmates;
extern NSString *const kAPAtomEntryNatureApplicasterLiveDrawer;
extern NSString *const kAPAtomEntryNatureChromecast;
extern NSString *const kAPAtomEntryNatureHeader;
@interface APAtomFeedParser : NSObject

/*
 The result of the ParsingComplete Method - parsed Feed
 */
@property (nonatomic, weak, readonly) APAtomFeed *parsedFeed;

/*
 ParsingComplete - Whether NSXMLParser parsing has completed
 */
@property (nonatomic, assign) BOOL parsingComplete;

/*
 IsFirstElement - Whether element has first - feed.
 */
@property (nonatomic, assign) BOOL isFirstElement;

/*
 */
- (instancetype)initWithAtomFeed:(APAtomFeed *)atomFeed;

/*
 Parse Applicaster Media Atom Feed
 @param: dataTask - Session Data task indstance
 @param: feed - model of atom feed.
 @param: error: if discarded - returns an error with explanation.
 */
- (void)dataTaskWithTextEncodingName:(NSString *)textEncodingName
        responseObject:(id)responseObject
 withCompletionHandler:(void (^)(BOOL success, NSError *error))completion;

@end
