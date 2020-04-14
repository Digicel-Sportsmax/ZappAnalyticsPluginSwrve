//
//  APSocialSharingManager.h
//  Caracol
//
//  Created by Hagit Shemer on 10/8/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@import UIKit;
@import Foundation;

@class APFacebookSDKClient;

extern NSString * const kAPTwitterSharedDoneNotification;
extern NSString * const kAPTwitterSharedCancelledNotification;

extern NSString * const APShowMailSentNotification;
extern NSString * const kAPMailShareFailedNotification;

@interface APSocialSharingManager : NSObject

@property (nonatomic, strong) APFacebookSDKClient *facebookClient;

+ (APSocialSharingManager *)sharedInstance;

- (void)shareViaNativeShare:(NSString *)text
                  shareLink:(NSURL *)shareLink
                    subject:(NSString *)subject
      onTopOfViewController:(UIViewController *)viewController
                     sender:(UIView *)sender;

- (void)shareViaNativeShare:(NSString *)text
                  shareLink:(NSURL *)shareLink
                    subject:(NSString *)subject
    additionalActivityItems:(NSArray *)additionalActivityItems
applicationCustomActivities:(NSArray<__kindof UIActivity *> *)applicationCustomActivities
      onTopOfViewController:(UIViewController *)viewController
                     sender:(UIView *)sender;

- (void)shareViaNativeShare:(NSString *)text
                  shareLink:(NSURL *)shareLink
      onTopOfViewController:(UIViewController *)viewController
                     sender:(UIView *)sender;

- (void)shareViaTwitter:(NSString *)text
               andImage:(UIImage *)image
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController
         withCompletion:(void(^)(BOOL result))completion;

- (void)shareViaTwitter:(NSString *)text
      andImageURLString:(NSString *)imageURLString
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController
         withCompletion:(void(^)(BOOL result))completion;

- (void)shareViaTwitter:(NSString *)text
      andImageURLString:(NSString *)imageURLString
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController;

/**
 Opens a facebook feed dialog.
 See http://developers.facebook.com/docs/reference/dialogs/feed/ for information about the parameters.
 @param text The initial message entered into the feed.
 @param imageURLString The path to the picture URL.
 @param urlStr The source of the feed.
 @param name The title of the feed.
 @param caption The caption of the feed.
 @param description A description of the feed.
 */
- (void)shareViaFacebook:(NSString *)text
       andImageURLString:(NSString *)imageURLString
               andURLStr:(NSString *)urlStr
                 andName:(NSString *)name
              andCaption:(NSString *)caption
          andDescription:(NSString *)description
                      to:(NSString *)to;

/**
 Opens a facebook feed dialog.
 See http://developers.facebook.com/docs/reference/dialogs/feed/ for information about the parameters.
 @param text The initial message entered into the feed.
 @param imageURLString The path to the picture URL.
 @param urlStr The source of the feed.
 @param name The title of the feed.
 @param caption The caption of the feed.
 @param description A description of the feed.
 */
- (void)shareViaFacebook:(NSString *)text
       andImageURLString:(NSString *)imageURLString
               andURLStr:(NSString *)urlStr
                 andName:(NSString *)name
              andCaption:(NSString *)caption
          andDescription:(NSString *)description;

/**
 Share via Email
 @param text - string representation of the share text
 @param subject - mail subject
 @param imageURLString - image url to be added to the mail
 @param linkUrlString - URL link
 @param linkLabel - Text displayed for the link
 @param viewController - view controller to present upon
 */
- (void)shareViaEmail:(NSString *)text
           andSubject:(NSString *)subject
    andImageURLString:(NSString *)imageURLString
     andLinkURLString:(NSString *)linkUrlString
         andLinkLabel:(NSString *)linkLabel
onTopOfViewController:(UIViewController *)viewController;

/**
 Share via SMS
 @param body - string representation of the share text
 @param recipients - list of recipients
 @param viewController - view controller to present upon
 */
- (void)shareViaSMS:(NSString *)body
         andSubject:(NSArray *)recipients
onTopOfViewController:(UIViewController *)viewController;


/**
 Share on What'sApp (assuming it's installed)
 @discussion
 Using URL scheme built from this knowladge base:
 https://www.whatsapp.com/faq/iphone/23559013
 @param text - text to share
 @param linkURL - will be pasted after text
 */
- (void)shareViaWhatsAppWithText:(NSString *)text
                      andLinkURL:(NSURL *)linkURL;


- (BOOL)twitterApplication:(UIApplication *)application openURL:(NSURL *)url options:(NSDictionary *)options;

@end


