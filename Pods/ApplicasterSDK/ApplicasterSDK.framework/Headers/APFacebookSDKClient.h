//
//  APFacebookSDKClient.h
//  ApplicasterSDK
//
//  Facebook SDK Client - written to properly work with SDK 3.1 and the new active session mechanism
//  This SDK supports and implements old FB object to provide feed dialog operations
//
//  Created by Liviu Romascanu on 9/24/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

@import UIKit;
@import Foundation;
@import FBSDKCoreKit;

@class FBSDKGraphRequest, FBSDKGraphRequestConnection;

@class APFacebookPostObject;
@class APFBGraphUser;

/** A notification using this name is used to pass on a dictionary of paramaters, to allow calling <openFeedWithDictionary:>. The parameters should be stored as the <code>userInfo</code> of the notification. */
extern NSString * _Nonnull const APFacebookOpenFeedNotification;
/** This notification is called when the facebook feed dialog is successfully sent. */
extern NSString * _Nonnull const APFacebookFeedSentNotification;
/** This notification is called when the facebook feed dialog is opened. */
extern NSString * _Nonnull const APFacebookFeedDidOpenNotification;
/** This notification is called when the facebook feed dialog is closed, regardless of the result. */
extern NSString * _Nonnull const APFacebookFeedDidCloseNotification;
/** This notification is sent when facebook did Login */
extern NSString * _Nonnull const APFacebookDidLoginNotification;
/** This notification is sent when facebook did Logout */
extern NSString * _Nonnull const APFacebookDidLogoutNotification;
/** This notification is sent when facebook didn't manage to Login */
extern NSString * _Nonnull const APFacebookDidNotLoginNotification;

/**
 A Facebook client that can be used to perform a large number of Facebook actions.
 */
@interface APFacebookSDKClient : NSObject

/**
 Facebook App ID
 */
@property (nonatomic, readonly, nullable) NSString *facebookAppID;

/**
 Params of a saved dialog request.
 These params are used in case we need to login. When returning to the application - The saved dialog will be displayed
 */
@property (nonatomic, retain, nullable) NSMutableDictionary *paramsForDialog;

/**
 @return a shared instance of this class.
 */
+ (nullable APFacebookSDKClient *)sharedInstance;

/**
 This method should be called only once. Calling it more than once will do nothing and return the sharedInstance previously created.
 @param facebookAppID used to initialize the session with
 @param appDisplayName as appears in the facebook developer app page
 @return A new instance of APFacebookSDKClient.
 */
+ (nonnull instancetype)facebookSDKWithFacebookAppID:(nullable NSString *)facebookAppID
                                   andAppDisplayName:(nullable NSString *)appDisplayName;

//Facebook implementation:

/**
 Close current active session.
 Also clears current token - used for Sign out
 */
- (void)closeSession;

/**
 Handle URL scheme by the facebook sdk
 @return YES if handled , NO otherwise
 */
- (BOOL)application:(nullable UIApplication *)application
            openURL:(nullable NSURL *)url
  sourceApplication:(nullable NSString *)sourceApplication
         annotation:(nullable id)annotation;

/**
 New facebook share method
 @param viewController - display on top if not fastappswitching to facebook app
 @param url - URL to share
 @param title - Share title
 @param description - Short share description
 @param imageURL - Shared Image URL
 */
- (void)shareFromViewController:(nullable UIViewController *)viewController
                        withURL:(nullable NSURL *)url
                      withTitle:(nullable NSString *)title
                withDescription:(nullable NSString *)description
                   withImageURL:(nullable NSURL *)imageURL;

/**
 @return facebook token
 */
- (nullable NSString *)accessToken;

/**
 @return facebook token expiration date
 */
- (nullable NSDate *)expirationDate;

/**
 @return The currently logged in user's Facebook ID.
 */
- (nullable NSString *)userID;

/**
 @return The currently logged in user's Name.
 */
- (nullable NSString *)userName;

/**
 Gets the current Facebook user(ME) info with completion handler
 @param completion The Completion handler of the get me request returns with user dictionary @see FBGraphUser
 */
- (void)getCurrentUserWithCompletionHandler:(void(^ _Nonnull)(APFBGraphUser * _Nullable user, NSError * _Nullable error))completion;

/**
 Manually call facebook authorization function
 @param forced - If true - Delete current token and re-authorize.
 */
- (void)authorizeFacebook:(BOOL)forced;

/**
 Manually call facebook authorization function
 @discussion The permissions will be requested in a single step with the authorization
 @param forced - If true - Delete current token and re-authorize.
 @param readPermissions - Array of strings representing facebook read permissions
 @param completion - The completion that will be called after trying to login to Facebook. The completion will receive YES if the user is loged in to facebook, or NO it isn't. Returnes the error if there is any.
 */
- (void)authorizeFacebook:(BOOL)forced readPermissions:(nullable NSArray *)readPermissions completion:(void (^ _Nullable)(BOOL logedIn, NSError * _Nullable error))completion;

/**
 Manually call facebook authorization function
 @param forced - If true - Delete current token and re-authorize.
 @param completion - The completion that will be called after trying to login to Facebook. The completion will receive YES if the user is loged in to facebook, or NO it isn't. Returnes the error if there is any.
 */
- (void)authorizeFacebook:(BOOL)forced
               completion:(void (^ _Nullable)(BOOL logedIn, NSError * _Nullable error))completion;

/**
 @return YES if facebook session is valid
 */
- (BOOL)isFacebookSessionValid;

/**
 Request aditional write permissions
 @discussion A new write permission will be actually requested only if it's not in the active session permissions. Otherwise completion block will be called immidiatly.
 @param writePermissions - Array of strings representing facebook write permissions
 @param completion - returning if the permission was granted and an error if one occurs.
 */
- (void)requestNewPublishPermissions:(nullable NSArray *)writePermissions
                          completion:(void (^ _Nullable)(BOOL grantedPermission, NSError * _Nullable error))completion;

- (nullable FBSDKGraphRequest *)requestWithGraphPath:(nullable NSString *)graphPath
                                          withParams:(nullable NSMutableDictionary *)params
                                      withHTTPMethod:(nullable NSString *)httpMethod
                               withCompletionHandler:(void (^ _Nullable)(FBSDKGraphRequestConnection * _Nullable connection, id _Nullable result, NSError * _Nullable error))handler;

- (nullable FBSDKGraphRequestConnection *)runFBSDKGraphRequestConnectionWithGraphPath:(nullable NSString *)graphPath
                                                                        andParameters:(nullable NSDictionary *)params
                                                                           HTTPMethod:(nullable NSString *)method
                                                                    completionHandler:(void (^ _Nonnull)(FBSDKGraphRequestConnection * _Nullable connection, id _Nullable result, NSError * _Nullable error))handler;

/**
 Get a user profile image URL
 @param profileID - ID of a certain user
 @param size - size of the image required

 */
-(nonnull NSString *)getFacebookProfileImageUrlStringWithId:(nullable NSString *)profileID andSize:(CGSize)size;

/**
 Get a user profile image URL - Class Method
 @param profileID - ID of a certain user
 @param size - size of the image required

 */
+ (nonnull NSString *)getFacebookProfileImageUrlStringWithId:(nullable NSString *)profileID andSize:(CGSize)size;

/**
 Creates a post to a given page by the currently logged-in user
 @param postText the post text to add
 @param image - image to add to the post; can be null
 @param pageID the ID of the page to post on
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 */
- (void)createPost:(nullable NSString *)postText
         withImage:(nullable UIImage *)image
     forPageWithID:(nullable NSString *)pageID
        completion:(void (^ _Nullable)(NSString * _Nullable resultPostId, NSError * _Nullable error))completion;

/**
 Add a comment to a given post by the currently logged-in user
 @param commentText the comment to add
 @param image - image to add to the comment; can be null
 @param postId the ID of the post to attach the comment to
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 */
- (void)createComment:(nullable NSString *)commentText
            withImage:(nullable UIImage *)image
         onPostWithId:(nullable NSString *)postId
           completion:(void (^ _Nonnull)(NSString * _Nullable resultCommentId, NSError * _Nullable error))completion;

#pragma mark - Session permissions
/**
 Current active session permissions
 @return Array of strings of the current permissions.
 */
- (nullable NSArray *)sessionPermissions;

/**
 Current active session declined permissions
 @return Array of strings of declined permissions of the current active session.
 */
- (nullable NSArray *)sessionDeclinedPermissions;

/**
 Check if a certain permission has been granted
 @param permission - facebook permision string
 @return YES if the permission is granted on the current active session
 */
- (BOOL)hasGranted:(nullable NSString *)permission;

/**
 Check if an entire array of permissions is granted in the current session
 @param permissionsArray - aray of facebook permison strings
 @return YES if all the permissions are granted on the current active session
 */
- (BOOL)hasGrantedArray:(nullable NSArray *)permissionsArray;
    @end
