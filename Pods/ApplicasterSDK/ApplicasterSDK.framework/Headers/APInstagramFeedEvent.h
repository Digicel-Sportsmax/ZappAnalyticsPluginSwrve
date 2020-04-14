//
//  APInstagramFeedEvent.h
//  Pods
//
//  Created by Liviu Romascanu on 12/04/2017.
//
//

#import "APFeedEvent.h"
#import "APInstagramMedia.h"

@interface APInstagramFeedEvent : APFeedEvent

@property (nonatomic, strong) APInstagramMedia *instagramMediaItem;

- (NSString *)uniqueID;
- (NSDate *)createdAt;
- (instancetype)initWithMediaItem:(APInstagramMedia *)mediaItem;
- (instancetype)initWithInstagramMediaDictionary:(NSDictionary *)dictionary;

@end
