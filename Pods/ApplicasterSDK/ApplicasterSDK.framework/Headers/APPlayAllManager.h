//
//  APPlayAllManager.h
//  Pods
//
//  Created by Miri on 10/11/2016.
//
//

#import <Foundation/Foundation.h>

@interface APPlayAllManager : NSObject

/**
 * Play all local favorites list
 */
- (void)playAllFavoritesWithShuffle:(BOOL)shuffle;

/**
 * Play all hqme item list
 */
- (void)playAllHqmeWithShuffle:(BOOL)shuffle;

/**
 * Play all local favorites and hqme item list
 */
- (void)playAllFavoriteAndHqmeWithShuffle:(BOOL)shuffle;

/**
 * Play all item list
 */
- (void)playAllItems:(NSArray *)items WithShuffle:(BOOL)shuffle;

@end
