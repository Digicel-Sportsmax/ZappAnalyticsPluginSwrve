//
//  APBackgroundManager.h
//  applicaster
//
//  Created by Liviu Romascanu on 6/9/11.
//  Copyright 2011 none. All rights reserved.
//

@interface APBackgroundManager : NSObject

+ (id)sharedInstance;

/**
 Start a background task for hqme progress items
 */
- (void)startVodItemsBackgroundTask;

/**
 End a background task of the hqme progress items
 */
- (void)endVodItemsBackgroundTask;

@end 
