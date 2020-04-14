//
//  MPNotificationView.h
//  Moped
//
//  Created by Engin Kurutepe on 1/2/13.
//  Copyright (c) 2013 Moped Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APMPNotificationView;
@protocol APMPNotificationViewDelegate;

extern NSString *kAPMPNotificationViewTapReceivedNotification;

typedef void (^APMPNotificationSimpleAction)(APMPNotificationView * view);

@interface APMPNotificationView : UIView

@property (nonatomic, strong) IBOutlet UILabel *textLabel;
@property (nonatomic, strong) IBOutlet UILabel *detailTextLabel;
@property (nonatomic, strong) IBOutlet UIImageView *imageView;
@property (nonatomic, assign) IBOutlet id<APMPNotificationViewDelegate> delegate;

@property (nonatomic) NSTimeInterval duration;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                                  image:(UIImage*)image
                            andDuration:(NSTimeInterval)duration;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                            andDuration:(NSTimeInterval)duration;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                              andDetail:(NSString*)detail;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                                  image:(UIImage*)image
                               duration:(NSTimeInterval)duration
                          andTouchBlock:(APMPNotificationSimpleAction)block;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                               duration:(NSTimeInterval)duration
                          andTouchBlock:(APMPNotificationSimpleAction)block;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                          andTouchBlock:(APMPNotificationSimpleAction)block;

+ (APMPNotificationView *) notifyWithText:(NSString*)text
                                 detail:(NSString*)detail
                                  image:(UIImage*)image
                               duration:(NSTimeInterval)duration
                                   type:(NSString *)type
                          andTouchBlock:(APMPNotificationSimpleAction)block;


+ (void)registerNibNameOrClass:(id)nibNameOrClass
        forNotificationsOfType:(NSString *)type;
+ (void) showNextNotification;

+ (void)setDefaultDetailFontSize:(float)fontSize;

@end

@protocol APMPNotificationViewDelegate <NSObject>

@optional
- (void)didTapOnNotificationView:(APMPNotificationView *)notificationView;

@end
