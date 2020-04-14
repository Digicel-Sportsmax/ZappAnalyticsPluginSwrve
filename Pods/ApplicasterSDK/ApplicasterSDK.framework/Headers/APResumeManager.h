//
//  APResumeManager.h
//  ApplicasterSDK
//
//  Created by user on 23/10/2017.
//

#import <Foundation/Foundation.h>

/** This class manage persistent resume.
 ** All data are saved in plist on documentation folder that will be deleted if user deletes the app
 ** Data is saved in dictionary. Key is playable item id and value is playable item values
 **/

extern NSString *const APPersistenceDidSaveNotification;


@interface APResumeManager : NSObject
+ (instancetype)sharedInstance;

- (void)saveLastPlayedTime:(NSTimeInterval)time forPlayableID:(NSString *)playableID;
- (void)saveDuration:(NSTimeInterval)time forPlayableID:(NSString *)playableID;
- (NSTimeInterval)lastPlayedTimeForPlayableID:(NSString *)playableID;
- (NSTimeInterval)durationForPlayableID:(NSString *)playableID;
@end
