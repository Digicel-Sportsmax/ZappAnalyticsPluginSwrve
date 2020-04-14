//
//  APFeedUser.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 1/9/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//
@import UIKit;
@import Foundation;

extern NSString * const APFeedUserAvatarLoadedNotification;

typedef enum {
    APFeedUserTypeNone = 0,
    APFeedUserTypeStars,
    APFeedUserTypeFacebook,
    APFeedUserTypeTwitter,
    APFeedUserTypeInstagram
    
} APFeedUserType;

@interface APFeedUser : NSObject <NSCoding>

/**
 User type - Star/Facebook/Twitter
 **/
@property (nonatomic, readonly) APFeedUserType type;
/**
 User unique ID
 **/
@property (nonatomic, strong, readonly) NSString *userID;
/**
 User name
 **/
@property (nonatomic, strong, readonly) NSString *name;
/**
 User avatar image
 **/
@property (nonatomic, strong) UIImage *avatarImage;

/**
 User avatar image
 **/
@property (nonatomic, strong, readonly) NSURL *avatarImageURL;

/**
 Initializer
 @param type - Star/Facebook/Twitter
 @param userID - unique ID
 @param name name
 @param avatarImage name
 **/
- (id)initWithType:(APFeedUserType)type andID:(NSString *)userID andName:(NSString *)name andAvatarImage:(UIImage *)avatarImage;

/**
 Initializer
 @param type - Star/Facebook/Twitter
 @param userID - unique ID
 @param name name
 @param avatarImageURL avatarImageURL
 **/
- (id)initWithType:(APFeedUserType)type andID:(NSString *)userID andName:(NSString *)name andAvatarImageURL:(NSURL *)avatarImageURL;

/**
 Initializer
 @param dictionary - Facebook author dictionary
 **/
- (id)initWithFacebookDictionary:(NSDictionary *)dictionary;

@end
