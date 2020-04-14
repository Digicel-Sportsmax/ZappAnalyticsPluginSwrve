//
//  APProgramHelper.h
//  ApplicasterSDK
//
//  Created by Anton Kononenko on 07/06/2017.
//  Copyright © 2017 Applicaster Ltd. All rights reserved.
//

@import ZappPlugins;
@import Foundation;

@protocol APProgramHelperProtocol

/**
 Return Date from date string

 @param dateString Date string instancce
 @return New Date retrieved from dateString
 */
+ (NSDate *)dateFromString:(NSString*)dateString;

/**
 Retrieved screen title for analytics
 @param model APProgramProtocol model instance
 */
+ (NSString *)screenViewTitleForModel:(NSObject <APProgramProtocol> *)model;

/**
 Retrieves local notificatino sound
 */
+ (NSString *)localNotificationSound;

/**
 Set local notification sound for program
 */
+ (void)setLocalNotificationSound:(NSString *)localNotificationSound;

/**
 Checks if there is a local notification with current programID
 */
+ (BOOL)isLocalNotificationScheduledForProgramID:(NSString *)programID;

/**
 Remove the local notification for the given program.

 @param program The program that you used to add a previous local notification.
 @param showPopUp Flag to indicate if we should show a pop up message when the alarm is removed.
 */
+ (void)removeLocalNotificationForProgram:(NSObject <APProgramProtocol> *)program
                                  showPopUp:(BOOL)showPopUp;

/**
 Add a local notification when the given program is about to start.

 @param program The program that you want to add.
 @param extraInfo Dictionary that will be received in the local notification. This dictionary will be put in the notification's userInfo under kAPLocalNotificationsExtraInfo key.
 @param showPopUp Flag to indicate if we should show a pop up message when the alarm is added.
 */
+ (void)addLocalNotificationForProgram:(NSObject <APProgramProtocol> *)program
                              extraInfo:(NSDictionary *)extraInfo
                               showPopUp:(BOOL)showPopUp;

/**
 Check if program has already finished

 @param program model instance
 @return Bool value TRUE if program has beed finished FALSE in case not
 */
+ (BOOL)programDidEnd:(NSObject <APProgramProtocol> *)program;

/**
 Check if program is playing

 @param program model instance
 @return Bool value TRUE if program is playing FALSE in case not
 */
+ (BOOL)programIsPlaying:(NSObject <APProgramProtocol> *)program;

/**
 Retrieve a program instance of expected type APProgram or APAtomProgramEntry

 @param dataDict raw dict for the model
 @return Instance of APProgramProtocol
 */
+ (NSObject <APProgramProtocol> *)programByDictionary:(NSDictionary *)dataDict;

@end

@interface APProgramHelper : NSObject<APProgramHelperProtocol>

@end

