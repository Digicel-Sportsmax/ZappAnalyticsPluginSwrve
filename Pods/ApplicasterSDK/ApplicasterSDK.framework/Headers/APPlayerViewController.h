//
//  APPlayerViewController.h
//  applicaster
//
//  Created by Tom Susel on 1/19/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

@import UIKit;
@import ZappPlugins;

#import "APPlayerController.h"

// APPlayerCommercialsProtocol
#import "APPlayerCommercialsProtocol.h"

extern NSString *const kAPPlayerViewControllerViewDidLoad;                  // Posted when the ViewController's viewDidLoad method was called.
extern NSString *const kAPPlayerViewControllerViewWillAppear;               // Posted when the ViewController's viewWillAppear method was called.
extern NSString *const kAPPlayerViewControllerViewWillDisappear;            // Posted when the ViewController's viewWillDisappear method was called.
extern NSString *const kAPPlayerViewControllerDismissed;                    // Posted when the view controller was dismissed after the animation finished

typedef NS_ENUM(NSInteger, APPlayerViewControllerDisplayMode) {
    APPlayerViewControllerDisplayModeUnknown = 0,/**< Unknown type - Unclear */
    APPlayerViewControllerDisplayModeFullScreen,   /**< No App Preload */
    APPlayerViewControllerDisplayModeInline,    /**< Web page preload */
    APPlayerViewControllerDisplayModeFloating,  /**< Image preload */
};

/**
 Player view controller.
 A view controller intended to show the player modally.
 */
@interface APPlayerViewController : UIViewController {
    APPlayerController          *_playerController;
}

@property (nonatomic, strong, readonly) APPlayerController *playerController;   /**< Player controller used to render the playable item */

@property (nonatomic, strong) id <APPlayerCommercialsDelegate> playerCommercialsDelegate;

/**
 A bit mask for the allowed interface orientations.
 Default allowed orientations are <code>APInterfaceOrientationLandscapeLeft</code> and <code>APInterfaceOrientationLandscapeRight</code>
 */
@property (nonatomic, assign) UIInterfaceOrientationMask allowedOrientations;

/**
 indicates whether or not remove persistant resume
 */
@property (nonatomic, assign) BOOL shouldIgnoreInterruptScreen;
@property (nonatomic, assign) BOOL shouldIgnoreViewAppearanceForPlayback;
@property (nonatomic, assign) BOOL disablePictureInPicture;
@property (nonatomic, assign) BOOL disableInlineTransitionOnRotation;

/**
 Enum representing the current player display mode
 This should be set in time before displaying the view controller and prior to switching to the next mode (either by controls, gestures, rotation or similar scenario)
 */
@property (nonatomic, assign) APPlayerViewControllerDisplayMode currentPlayerDisplayMode;

/**
 Player controls.
 A view that confiorms to the <code>APPlayerControls</code> protocol.
 If not set, uses a default controls supplied by the player.
 Once you've set your controls, add them to the player heirarchy if you wish to.
 */
@property (nonatomic, strong) UIView<APPlayerControls> *controls;

/**
 Returns the first APPlayerViewController instance if it is presented in the view controllers hierarchy.
 */
+ (APPlayerViewController *)getPlayerVCFromViewHierarchy;

/**
 Creates a player controller to play an item.
 @param item - The target item to play.
 */
- (id)initWithPlayableItem:(id<ZPPlayable>)item;

/**
 Creates a player controller to play a list of items.
 @param items - An array of playable items.
 */
- (id)initWithPlayableItems:(NSArray*)items;

/**
 Creates a player controller to play a list of items.
 @param items - An array of playable items.
 @params prepareToPlay - Start loading the player
 */
- (id)initWithPlayableItems:(NSArray*)items
              prepareToPlay:(BOOL)prepareToPlay;

/**
 Starts playing.
 */
- (void)play;

/**
 Pauses playback.
 */
- (void)pause;


/**
 Stops playback.
 */
- (void)stop;

/**
 Seek to a given time in seconds
 */
- (void)seekToTime:(NSTimeInterval)time;


/**
 Closes the player with animation.
 Can be assigned to a done button.
 @param sender The caller of this method.
 */
- (IBAction)close:(id)sender;

/**
 Closes the player.
 @param animated - closes the player animated or not animated
 */
- (void)closeAnimated:(BOOL)animated;

/**
 Closes the player.
 @param animated - closes the player animated or not animated
 @param completion The completion that will be invoked after closing this ViewController.
 */
- (void)closeAnimated:(BOOL)animated
           completion:(void(^)(void))completion;

/**
 Closes the player.
 @param commercials - closes the player with commercials or without commercials
 @param animated - closes the player animated or not animated
 */
- (void)closeWithCommercials:(BOOL)commercials
                    animated:(BOOL)animated
           completionHandler:(void(^)(void))completion;

/**
 Closes the player.
 @param commercials - closes the player with commercials or without commercials
 @param animated - closes the player animated or not animated
 @param shouldDismiss - should the view controller be dismissed in the end of the process
 */
- (void)closeWithCommercials:(BOOL)commercials
                    animated:(BOOL)animated
               shouldDismiss:(BOOL)shouldDismiss
           completionHandler:(void(^)(void))completion;
/** Called when playback ends. */
- (void)playbackEnded:(NSNotification*)notification;

/** Called when playback fails. */
- (void)playbackFailure:(NSNotification*)notification;

/**
 @return The default scaling mode.
 */
+ (APMovieScalingMode)defaultScalingMode;

/**
 Sets the default scaling mode.
 @param scalingMode The scaling mode of the video. See <APMovieScalingMode>.
 */
+ (void)setDefaultScalingMode:(APMovieScalingMode)scalingMode;

- (void)checkIfNeedToRegisterToPlaylist;

/**
 Change player display mode
 */
- (void)changeDisplayMode:(APPlayerViewControllerDisplayMode)targetDisplayMode;

/**
 Set player as muted until touched for the first time
 */
- (void)playerMutedUntilTouched;

/**
 Updates player status bar state

 @param statusBarHidden Define status bar hidden state
 */
- (void)setStatusBarHidden:(BOOL)statusBarHidden;
/**
 indicates whether or not playing ads and pass to the player controller
 */
- (void)setIsPlayingAds:(BOOL)isPlayingAds;
/**
 return midroll number to play
 */
- (NSInteger)getMidrollPlace;
@end
