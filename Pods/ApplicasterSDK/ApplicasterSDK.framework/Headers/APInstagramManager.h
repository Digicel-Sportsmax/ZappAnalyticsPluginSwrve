//
//  APInstagramManager.h
//  Pods
//
//  Created by Liviu Romascanu on 11/04/2017.
//
//

#import <Foundation/Foundation.h>
#import "APEventsPollingManager.h"

@protocol APInstagramManagerDelegate

- (void)instagramPostsUpdated:(NSArray *)postsArray newPostsCount:(NSInteger)newPostsCount andNewPosts:(NSArray *)posts;

- (void)postsLoadingFailed;

@end

@interface APInstagramManager : NSObject <APEventsPollingManager>

/**
 ALL posts that were polled from start date till last polling date
 **/
@property (nonatomic,strong) NSMutableArray *postsArray;

/**
 Query objects array
 **/
@property (nonatomic,strong) NSArray *queryObjectsArray;

/**
 Posts start date
 */
@property (nonatomic, strong) NSDate *startDate;

/**
 Feed Timeline ID
 */
@property (nonatomic, strong) NSString *timelineID;

/**
 Accounts system Account ID
 */
@property (nonatomic, strong) NSString *accountID;

/**
 Instagram Manager Delegate
 **/
@property (nonatomic,weak) id<APInstagramManagerDelegate> delegate;

/**
 @param queryObjectsArray - currently unused
 @param accountID - Used to build the path for the static instagram json
 @param timelineID - Used to build the path for the static instagram json
 @param startDate - Used to filter events older than an hour before the episode start date
 @param pollingInterval - posts polling interval in seconds
 @param pollingLimit the max number of items to pull for each poll. If <= 0 there will be no limitation on the number of items.
 @return APInstagramManager instance
 **/
- (id)initWithQueryObjectsArray:(NSArray *)queryObjectsArray
                      accountID:(NSString *)accountID
                     timelineID:(NSString *)timelineID
                      startDate:(NSDate *)startDate
                pollingInterval:(NSTimeInterval)pollingInterval
                   pollingLimit:(NSInteger)pollingLimit;

/**
 Force post poll action
 **/
- (void)forcePollingNow;

@end
