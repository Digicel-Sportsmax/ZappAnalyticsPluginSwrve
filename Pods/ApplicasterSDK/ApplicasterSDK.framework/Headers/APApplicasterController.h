//
//  APApplicasterController.h
//  applicaster
//
//  Created by Neer Friedman on 1/23/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

@import ZappPlugins;
@import Foundation;
@import UIKit;

#import "APAccount.h"
#import "APApplicasterController.h"
#import "APStoreKitManager.h"
#import "APTakeoverCallbackHandler.h"

extern NSString *const APErrorDomain;
extern NSString *const kAPPlayerControlsClass;
extern NSString *const kAPSocialPlayerControlsClass;
extern NSString *const kAPInlinePlayerControlsClass;

@class APCategory, APCategoryView, APAccount, APChannel, APLoadingViewController,
		APStoreKitManager, APEndUserProfile, APModel, APStoreKitPurchase, APStoreKitPurchaseParams,
        APModelCollection, APFacebookSDKClient, APNotificationManager;

@protocol APApplicasterControllerDelegate, ZPPlayable;

@class APBroadcaster, APVodItem;

extern NSString * const APApplicasterControllerCurrentBroadcasterChanged;

/**
 Applicaster controller represents a singleton object in charge of handling Applicaster actions agains the application and holding various parts of the SDK like the player.
 
 This object should be set up and loaded from the Application's delegate.
 Short code example of basic setup and loading that should be done in the app delegate::
 <code>
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
    _applicaster = [APApplicasterController initSharedInstanceWithAccountID:<Account id - String> withSecretKey:<Acount Secret - String>]; 
    _applicaster.delegate = self;
    [APPlayerViewContrlller setDefaultLoadingViewClass:<i>A class that conforms to <APPlayerControls>. The view is loaded using the <initWithFrame:> method, so any initialization should be done there.</i>];
    _applicaster.rootViewController = <i>The applications Root view controller - used to display video on top of</i>;
    [_applicaster load];
 } </code>
 
 Notes:
 
 1 .To use a local intro movie - just add a .mp4 file to the bundle with the following naming conventions:
    iPhone - local_splash_video.mp4
    iPhone 5 - local_splash_video-568h.mp4
    iPad   - local_splash_video-iPad.mp4
 
 2. To set the splash image before the local intro movie - just put the next images to the budle with the following naming conventions:
    iPhone - local_splash
    iPhone 5 - local_splash-568h
    iPad - local_splash~ipad
 */
@interface APApplicasterController : NSObject<UIAlertViewDelegate> 

@property (nonatomic, strong) APEndUserProfile *endUserProfile;

/**
    APApplicaster Controller Delegate - This should usually be set as the application delegate
 */
@property (nonatomic, strong) id<APApplicasterControllerDelegate> delegate;

/**
 Account object
 Created after initial loading process of applicaster
 */
@property (readonly) APAccount *account;

/**
 The root view controller of the application.
 As a referece point to display videos on.
 */
@property (nonatomic, strong) UIViewController *rootViewController;

/**
 Default Applicaster Storekit manager.
 This is used to manage purchases (Either with no UI or against an application storefront).
 */
@property (nonatomic, strong, readonly) APStoreKitManager *storeKitManager;

/**
 Current broadcaster used by Applicaster.
 This should be set by the application once the acount is returned.
 */
@property (nonatomic, strong) APBroadcaster *currentBroadcaster;

/**
 Singleton class of the APSocial manager handling all social interaction inside Applicaster.
 For example - Facebook calls
 */
@property (nonatomic, readonly) APFacebookSDKClient *facebookClient;

/**
 APNotification manager singleton class - Used to handle all kind of local and remote notifications.
 For example - This class manages implementation of different push engines
 */
@property (nonatomic, strong) APNotificationManager *notificationManager;


/**
 Localization language value is given in (usually) 2 letters code string to represent a language.
 check out http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes for example.
 We sometimes use longer codes to reprsented localizations - like en-UK (language 2 letters - country / region 2 letters)
 
 NOTE: Do not use this setter to change localization language anymore.
 Instead use setLocalizationLanguage:success:failure: instad
 */
@property (readonly, nonatomic, copy) NSString *localizationLanguage;

/**
 Boolean value representing if subcategory images should be saved.
 By defaul - this value is NO.
 
 This should be disabled on apps that do not use full tree navigation for HQME , enabled for full tree navigations
 */
@property (nonatomic, assign) BOOL  shouldSaveSubcategoryImages;

/**
Boolean value representing if category images should be saved.
By defaul - this value is NO.

 This should be disabled on apps that do not use full tree navigation for HQME , enabled for full tree navigations
*/
@property (nonatomic, assign) BOOL  shouldSaveCategoryImages;

/**
 Applicaster Settings plist in NSDictionary form
*/
@property (nonatomic, strong) NSDictionary *applicasterSettings;

/**
 Returns the value of APRTLApp in the Applicaster settings dictionary
 This value can than be used to make UI decissions about content allignment.
 */
@property (nonatomic, readonly) BOOL isAppRTL;

// General Setup and initialization

/**
 Main function to initialize the Applicaster shared instance - updated with bucket ID for AIS
 @param accountID The account ID from the Applicaster CMS
 @param secretKey The secret key value for the application from the Applicaster CMS
 @param bucketID - used for AIS to generate UUID Correctly
 @return Applicaster shared instance
 */
+(id)initSharedInstanceWithAccountID:(NSString *)accountID withSecretKey:(NSString *)secretKey withBucketID:(NSString *)bucketID DEPRECATED_ATTRIBUTE;

/**
 Updated function to initialize shared Instance using ApplicasterSettings Plist file
 The Plist file which is used is called "ApplicasterSettings.plist"

 It should contain the following values:
    APAccountID - Account ID - Must
    APBucketID - Bucket ID - Must
    APDefaultVideoLoadingClass - Default Video loading class name
    APAudioOnlyImageName - Audio only image name (let's still leave the option for a view seperate? or should we do a view class name?)
    APPlayerControlsClass (for custom controls)
	APSocialPlayerControlsClass (for custom controls for live videos)
    APCurrentLanguage - Current language code string
    APAppSpecificLocalizationBundle - Specific localization bundle prefix
    APBackgroundHqmeCompletionSound - Sound file name
    APDefaultBroadcasterName - DEPRECATED - DO NOT USE!
    APBroadcasterID - Broadcaster ID to be selected , if none exists - first broadcaster will be chosen by default
    APGoogleAnalyticsOverride - Application level override to analytics ID (like in Televisa)
    APBackFromBackgroundViewEnabled - default - On
 
 @param secretKey The secret key for loading the account.
 @param launchOptions The launch option of the application.
 
 @return Applicaster shared instance
 */
+ (id)initSharedInstanceWithPListSettingsWithSecretKey:(NSString *)secretKey
                                          launchOption:(NSDictionary *)launchOptions;

/**
 * Basic initializer which creates the sharedInstance and only assigns the applicasterSettings dictionary from the ApplicasterSettings.plist file, and the launch options - used by Quick Brick
 */
+ (instancetype)initSharedInstancePlistSettingsWithLaunchOptions:(NSDictionary *)launchOptions;

/**
 Returns the Applicaster sharedInstance
 @return Applicaster Shared Instance Singleton
 */
+(APApplicasterController *)sharedInstance;

/**
 Load APApplicasterController.
 This should be ran after initial configuration
 */
- (void)load;

/**
 Called from HQMEManager when account cant be fetched due to limited connectivity until succeed.
 */
- (void)tryLoadingAccountWhileLimitedConnectivity;

/**
 Verifies if the Applicaster Shared Instance is ready (After initial load)
 @return YES if Applicaster / account is loaded , No otherwise
 */
- (BOOL)isReady;

/**
 Verifies if the Applicaster Shared Instance is still loading / started loading
 @return YES if Applicaster / account is loading , No otherwise
 */
- (BOOL)isLoading;

/**
 Sets No Video background slide
 @param fileName of a png file inside the main bundle
 */
- (void)setBackgroundHqmeCompletionSoundFileName:(NSString*)fileName;

/**
 *  applicastion preload activity indicator (spinner) color that is definied in the applicasterSettings plist.
 *  @return string hex color with alpha the is defined in applicasterSettings plist
 */
- (NSString *)appPreloadActivityIndicatorHexColor;

/**
 @return accountsAccountID variable from Applicaster Settings
 */
- (NSString *)accountsAccountID;

//API METHODS:

/**
 Returns channel with a set ID
 @param channelID unique identifier for channel
 @return Autoreleased, non-loaded APChannel object with a set ID
 */
- (APChannel *)channelWithID:(NSString *)channelID;

/**
 Returns channel with a set name. 
 This should not be used - instead use channel with ID / get channel list from account object
 @param channelName The channel's name.
 @return Autoreleased, non-loaded APChannel object with a set name
 */
- (APChannel *)channelWithName:(NSString *)channelName;

/**
 Returns the current user profile.
 @return APEndUserProfile
 */
- (APEndUserProfile*)endUserProfile;

/**
 Start listen to applicaster activities.
 This method will start listening to activties, is should be called ONLY when the account is loaded. 
 When the account is loaded by default applicasterController start listening to activites.
 */
//- (void)startActivitiesListener;

/**
 Takeover screen handler
 */
@property (nonatomic, strong) APTakeoverCallbackHandler *takeOverScreenHandler;

/**
 Pause listen to applicaster activities.
 */
//- (void)pauseActivitiesListener;

/**
 Resume listen to applicaster activities.
 */
//- (void)resumeActivitiesListener;

/**
 Set localization language with success and failure blocks.
 Do not - if language is already available or in offline mode and exists in cache - this might be called synchronously.
 @param localizationLanguage - Two letters language code
 @param shouldCache - default is NO. If you set it to YES the language will be device cached and will not be loaded from ApplicasterSettings anymore.
 */
- (void)setLocalizationLanguage:(NSString *)localizationLanguage
                    shouldCache:(BOOL)shouldCache;

/**
 Implement this method in order to handle the changing of the localization triggered by different places in the app. For example, when pressing a broadcaster in the broadcaster switch screen.
 
 @param localization The localization you want to change to - localization string, for example 'es'.
 */
- (void)changeAppLocalization:(NSString *)localization;

#pragma mark - StoreKit

/**
 restore all previous purchases
 */
- (void)restoreCompletedTransactions;

#pragma mark - Favorites

/**
 Returns the favorites array of Vod Items for the current user profile
 @return NSArray of VOD Items
 */
- (NSArray *)favorites;

/**
 Returns the favorites array of models.
 @return NSArray of favorites models
 */
- (NSArray *)localFavorites;

// HQME

/**
 Returns only the VOD items that have completely local. This differs to getAllLocalVodItems in that
 getAllLocalVodItems returns all the items that have been stored on the local data storage.
 @return The local VOD items.
 */
- (NSArray *)getAllHqmeCompletedVodItems;

/** 
 Return List of local items - HQME
 @return NSArray of local VOD Items
 */
- (NSArray *)getAllLocalVodItems;

/**
 Reloads the app completely after removing the runtime cache.
 */
- (void)reloadApp;

// URL Scheme Handling
/**
 THIS METHOD IS DEPRECATED - please use the same method that passes the complete information.
 This method is used to pass the Applicaster Controller a URL that it can parse and pass on to its delegate.
 
 If the Applicaster controller is going to handle opening URL schemes automatically, it is essential that you set the current broadcaster
 using the  setCurrentBroadcaster: method.
 @param url The URL used for opening the application.
 @param sourceApplication application
 @return YES if URL opened successfully. NO otherwise.
 */
- (BOOL)applicationDidOpenURL:(NSURL *)url withSourceApplication:(NSString *)sourceApplication DEPRECATED_ATTRIBUTE;

/**
 This method is used to pass the Applicaster Controller a URL that it can parse and pass on to its delegate.
 
 If the Applicaster controller is going to handle opening URL schemes automatically, it is essential that you set the current broadcaster
 using the  setCurrentBroadcaster: method.
 @param application Current application usually
 @param url The URL used for opening the application.
 @param options Dictionary object usually passed by file handling applications.
 @return YES if URL opened successfully. NO otherwise.
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options;

// End URL Scheme Handling

//TODO: Check removal
- (void)applicationWillResignActive:(UIApplication *)application;

-(void)clearAppCache;

/**
 Call to display preloaded if needed with completion to finish the app loading step
 @param completion indicates completion of the presentation
 */
-(void)displayPreloadIfNeeded:(void (^)(void))completion;
@end

#pragma mark - APApplicasterController Delegate
/**
 The following protocol represents the Applicaster Controller Delegate.
 The delegate in most applications will be the application delegate as a big part of the functions refer directly to the application loading process
 */

@protocol APApplicasterControllerDelegate<NSObject>

@required
/**
 This function is called when Applicaster's account object finished loading for the respective account ID
 @param applicaster Applicaster controller that loaded the account
 @param accountID of the loaded Account
 At this stage application can (and should) for example do the following operations:
 1. Choose a specific broadcaster
 2. Load content categories 
 */
- (void)applicaster:(APApplicasterController *)applicaster loadedWithAccountID:(NSString *)accountID;

/**
 Applicaster failed to load content category
 @param applicaster Applicaster controller that loaded the account
 @param accountID of the loaded Account
 @param error The error that caused the failure. If the domain of the error is APErrorDomain, the error's <localizedDescription> should be presented.
 In this state the application should either show the error message on the application loading screen, or should re-attemt load after some time.
 */
- (void)applicaster:(APApplicasterController *)applicaster withAccountID:(NSString *)accountID didFailLoadWithError:(NSError *)error;

@optional

/**
 Sets if applicaster controller should manually start listening
 to applicaster activities by calling the method @startActivitiesListener
 @param applicaster The main Applicaster controller.
 @return BOOL if start listening to applicaster activities.
 */
- (BOOL)manuallyStartActivitiesListenerForApplicaster:(APApplicasterController *)applicaster;

/**
 Asks Application delegate if a URL should be allowed to open the application.
 @param applicaster The main Applicaster controller.
 @param aURL The URL used for launching the application.
 */
- (BOOL)applicaster:(APApplicasterController *)applicaster shouldOpenURL:(NSURL*)aURL;

/**
 *  Present subscription for application that uses subscrption
 *
 @param applicaster The main Applicaster controller.
 @param subscriptionItem The item that is being purchased.
 */
- (void)applicaster:(APApplicasterController *)applicaster
showSubscriptionFor:(id<ZPPurchasableItemProtocol>)subscriptionItem;

/**
 In some cases - an application specific storefront is avilable.
 Implement this method if you would like the application to handle the storefront display of purchasable items
 @param applicaster The main Applicaster controller.
 @param purchasableItem The item that is being purchased.
 */
- (void)applicaster:(APApplicasterController *)applicaster showStoreFrontFor:(id<ZPPurchasableItemProtocol>)purchasableItem;

/**
 This function is called to update application of the changes in HQME State.
 This should be used instead of reachability tests - as this is done saftley and in a single place.
 This way - The application can handle reload , going into offline mode etc.
 @param applicaster The main Applicaster controller.
 @param isOnline The online status.
 */
- (void)applicaster:(APApplicasterController *)applicaster changedOnlineState:(BOOL)isOnline;

// URL Scheme Handling

/**
 This method tells the delegate to present a VOD item either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param vodItemID The ID of the VOD item to play.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally or any other, which is easier since it does not involve loading the parent categories.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentVODItemByID:(NSString *)vodItemID inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a category item either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param externalId The external_id of the category to be loaded.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally or any other, which is easier since it does not involve loading the parent categories.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentCategoryByExternalId:(NSString *)externalId inContext:(BOOL)inContext;

/**
 This method tells the delegate to play a VOD item, and present it either in context or modally.
 
 If the delegate does not respond to this method, the Applicaster controller automatically attempts to play a VOD item. To allow this to perform correctly,
 set the current broadcaster through the setCurrentBroadcaster: method.
 @param applicaster The shared Applicaster controller.
 @param vodItem VOD item to present.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally or any other, which is easier since it does not involve loading the parent categories.
 */
- (void)applicaster:(APApplicasterController *)applicaster playVODItem:(APVodItem *)vodItem inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a UIBuilder generic screen item
 
 @param applicaster The shared Applicaster controller.
 @param screenIDs Array of ID of the screen that was configured in UIBuilder
 @param model APAtomFeed instance is optional parameter, will be used if in url scheme exists ds param
 @return Bool value if screen was presented
 */
- (BOOL)applicaster:(APApplicasterController *)applicaster
presentUIBuilderScreen:(NSArray *)screenIDs
      fromURLScheme:(NSURL *)urlScheme
              model:(NSObject *)model;

/**
 This method is intended to pass screen ids , model and the containing data source model.
 This is meant to be used to display a screen + playable in context
 
 @param applicaster The shared Applicaster controller.
 @param screenIDs Array of ID of the screen that was configured in UIBuilder
 @param model APAtomEntry model
 @param dataSourceModel APAtomFeed model
 @return Bool value if screen was presented
 */
- (BOOL)applicaster:(APApplicasterController *)applicaster
presentUIBuilderScreen:(NSArray *)screenIDs
      fromURLScheme:(NSURL *)urlScheme
              model:(NSObject *)model
    dataSourceModel:(NSObject *)dataSourceModel;

/**
 This method tells the delegate to present a category either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param categoryIDs The IDs of the categories to present. The IDs are in hierarchical order, i.e. The first ID is the first category to load, the next ID is the subcategory, and so forth.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentCategoryByIDs:(NSArray *)categoryIDs inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a url either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param url The url should be presented. 
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentURL:(NSURL *)url inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a react native viewController either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param pluginName The plugin name of the react view - this value most be sent, it's the `name` value in the plugin's manifest in Zapp. Should be consistent for both platforms if both having same screens.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentReactNativePluginName:(NSString *)pluginName inContext:(BOOL)inContext additionalParameters:(NSDictionary*)additionalParameters;

/**
 This method tells the delegate to present a url either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param url The url should be presented.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 @param associatedParameters - additional parameters that might be required when presented modally
 */
- (void)applicaster:(APApplicasterController *)applicaster presentURL:(NSURL *)url inContext:(BOOL)inContext withAdditionalParameters:(NSMutableDictionary *)associatedParameters;

/**
 This method allows the delegate to begin playing a channel.
 
 If the delegate does not respond to this method, the Applicaster controller automatically attempts to play the live channel.  To avoid this behaviour, implement this method and leave it blank.
 @param applicaster The shared Applicaster controller.
 @param channel The channel that needs to be played. The channel will need to be loaded first.
 */
- (void)applicaster:(APApplicasterController *)applicaster playChannel:(APChannel *)channel;

/**
 Note - This method is deprecated - AND WILL NOT BE CALLED.
 If you need extra permissions - request them from the APFacebookSDKClient class individually.
 
 This method allows the delegate to add additional facebook permissions to the facebook client instance.
 
 @param applicaster The shared Applicaster controller.
 @return Array of permissions for Facebook needed by the application (Array of NSStrings).
 */
- (NSArray *)extraFacebookPermissionsWithApplicaster:(APApplicasterController *)applicaster DEPRECATED_ATTRIBUTE;

// End URL Scheme Handling

/**
 Implement this method in order to handle the changing of the localization triggered by different places in the app. For example, when pressing a broadcaster in the broadcaster switch screen.
 
 @param localization The localization you want to change to - localization string, for example 'es'.
 */
- (void)changeAppLocalization:(NSString *)localization;


@end
