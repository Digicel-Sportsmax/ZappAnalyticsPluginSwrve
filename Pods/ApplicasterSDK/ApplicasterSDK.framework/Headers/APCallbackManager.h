//
//  APCallbackManager.h
//  Applicaster SDK
//
//  Created by Liviu Romascanu on 05/04/2017.
//
//

#import <Foundation/Foundation.h>

extern NSString *const APkeepSecreenOnCommand;
extern NSString *const APShouldkeepSecreenOnKey;
extern NSString *const APCallbackGeneralCommand;
extern NSString *const APMorpheusEventCommand;
extern NSString *const APMorpheusUserCommand;


@protocol APCallbackManagerDelegate <NSObject>

@end


@interface APCallbackManager : NSObject
/**
 Optional display view controller to run modal presentation against.
 If it is not set - The topmost view controller will be used
 */
@property (nonatomic, weak) UIViewController *currentDisplayViewController;

/**
 Delegate object.
 Ideally completions will be used instead.
 */
@property (nonatomic, weak) id<APCallbackManagerDelegate> delegate;


/**
 handleCallWithCommand
 @param callbackCompletion - singleParam used if needed to pass string to JS2Native
                           - parameters used if needed to pass dictionary to JS2Native
 */
- (void)handleCallWithCommand:(NSString *)command
                andDictionary:(NSDictionary *)dictionary
                   withHanler:(NSObject *)handler
                   completion:(void (^)(NSString *callbackName, id callbackValue))callbackCompletion;
@end
