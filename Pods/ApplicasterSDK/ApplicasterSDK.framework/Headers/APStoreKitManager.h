//
//  APStoreKitManager.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/5/12.
//  Copyright (c) 2012 none. All rights reserved.
//

@import ZappPlugins;
@import StoreKit;
#import "APStoreKitPurchaseParams.h"

extern NSString *const APStoreKitPurchaseFailedNotification;        /**< Posted when purchase process fails, Notification object is the store manager. */
extern NSString *const APStoreKitPurchaseCompleteNotification;      /**< Posted when purchase process completes successfully, Notification object is the store manager. */
extern NSString *const APStoreKitPurchaseCancelledNotification;      /**< Posted when purchase process is canceled by the user, Notification object is the store manager. */
extern NSString *const APStoreKitManagerProductsInfoUpdated;       /**< Called when products info is updated, Notification object is the store manager. */

extern NSString *const APStoreKitNotificationTargetItemKey; /**< When a purchase notification is sent, this key returns the ZPPurchasableItemProtocol item whose purchase was failed/succeeded/cancelled. */

@class APApplicasterController, APStoreKitManager, APStoreKitPurchase;

@protocol APStoreKitManagerDelegate<NSObject>
@optional
- (void)purchaseDidStart:(APStoreKitManager *)purchase;
- (void)purchaseDidFinish:(APStoreKitManager *)purchase;
- (void)purchaseDidFail:(APStoreKitManager *)purchase;

- (void)restoreDidStart:(APStoreKitManager *)purchase;
- (void)restoreDidFailed:(APStoreKitManager *)purchase;

/**
 *  This method will override all the logic in side notifyPurchaseFail method.
 *  protocol method purchaseDidFail will not be called when this protocol is implemented.
 *
 *  @param purchase StoreKitManager that called this protocol method.
 */
- (void)purchaseDidFailOverride:(APStoreKitManager *)purchase;

- (void)purchaseDidCancel:(APStoreKitManager *)purchase;

/**
 *  This method will override all the logic in side notifyPurchaseCancel method.
 *  Protocol method purchaseDidCancel will not be called when this protocol is implemented.
 *
 *  @param purchase StoreKitManager that called this protocol method.
 */
- (void)purchaseDidCancelOverride:(APStoreKitManager *)purchase;

- (void)productsInfoRetrieved:(NSArray*) products; //An array of SKProduct
- (void)purchaseIgnoredSinceAlreadyPurchasing:(APStoreKitManager *)purchase;
@end

/**
 The store kit manager is responsible for all in-app purchase management. It also communicates with the Applicaster servers to validate in-app purchases properly.
 */
@interface APStoreKitManager : NSObject <SKPaymentTransactionObserver>
{
	APApplicasterController			*_controller;
	NSSet *_targetProducts;
	APStoreKitPurchase *_currentStoreKitPurchase;
}


/** The item currently being purchased */
@property (nonatomic, strong) id<ZPPurchasableItemProtocol> targetItem;
@property (nonatomic, copy) void(^purchasableItemCompletion)(ZPPurchasableItemPurchaseResult);
@property (nonatomic, weak) id<APStoreKitManagerDelegate> delegate;

- (id)initWithController:(APApplicasterController *)apController;

#pragma mark Products


/**
 *  Retrive SKProducts from itunes connect for productIdentifiers.
 *
 *  @param productIdentifiers Array of product identifiers of the in-app purchase products in the App Store.
 *  @param completionBlock    The completionBlock will be call with array of SKProducts. The completion block will return synchronic if the SKProducts were loaded otherwise the block will be call after the all products are loaded.
 */
- (void)productsForProductIdentifiers:(NSArray *)productIdentifiers
                  withCompletionBlock:(void (^)(NSArray *array))completionBlock;

/**
 *  Localized price of the productIdentifier. If the productIdentifier is loaded the completionBlock will be called return synchronic.
 *  Otherwise it the block will be called after the product will be loaded.
 *
 *  @param productIdentifier The product identifier of the in-app purchase product in the App Store.
 *  @param completionBlock The completionBlock will be call with localized price. The completion block will return synchronic if the productIdentifier was loaded otherwise the block will be call after the product will be loaded.
 */
- (void)localizedPriceForProductWithProductIdentifier:(NSString *)productIdentifier
                                  withCompletionBlock:(void (^)(NSString *price))completionBlock;



- (NSString*)priceForProductWithIdentifier:(NSString*)productIdentifier;
- (NSString*)productNameForIdentifier:(NSString*)productIdentifier;

- (void)retrieveProductInfoIdentifier:(NSString*)productIdentifier;
- (void)retrieveProductInfoWithIdentifiers:(NSSet*)productIdentifiers;

#pragma mark Purchases

- (void)purchaseProductWithIdentifier:(NSString*)productIdentifier;

/**
 Initiates the purchase process.
 @param productIdentifier The product identifier of the in-app purchase product in the App Store.
 @param item Item to be purchased
 */
- (void)purchaseProductWithIdentifier:(NSString*)productIdentifier 
                                 item:(APModel*)item;

- (void)purchaseProduct:(id<ZPPurchasableItemProtocol>)purchasebleItem
		 withIdentifier:(NSString *)productIdentifier;

- (void)purchaseWithStoreKitPurchaseParams:(APStoreKitPurchaseParams*)storeKitPurchaseParams 
							 andIdentifier:(NSString*)productIdentifier;

/**
 Initiates the purchase process.
 @param storeKitPurchaseParams The parameters of the purchase.
 @param productIdentifier The product identifier of the in-app purchase product in the App Store.
 @param item Item to be purchased
 */
- (void)purchaseWithStoreKitPurchaseParams:(APStoreKitPurchaseParams*)storeKitPurchaseParams 
							 andIdentifier:(NSString*)productIdentifier
                                      item:(APModel*)item;

// Deprecated function - should not be used
- (void)renewSubscriptions;
/**
 Restores completed transactions - without checking the flow if it should be restored
 */
- (void)restoreCompletedTransactions;

/**
 Notify observers of cancelation. 
 Call this method if the user cancels purchase so that the player would be dismissed.
 @param purchasable The purchasable item that has just had its purchase cancelled.
 */
- (void)notifyPurchaseCancel:(id<ZPPurchasableItemProtocol>)purchasable;

/**
 Notify observers of failed.
 Call this method if the purchase flow failed, for example no itunes connect connection. 
 The player would be dismissed.
 @param purchasable The purchasable item that has just had its purchase failed.
 */
- (void)notifyPurchaseFail:(id<ZPPurchasableItemProtocol>)purchasable;

/** 
 Notify observers of success. 
 @param purchasable The purchasable item that has just been purchased.
 */
- (void)notifyPurchaseSuccess:(id<ZPPurchasableItemProtocol>)purchasable;

/**
 Get purchasable item instance from object.
 @param item - The purchasable item.
 */
+ (id<ZPPurchasableItemProtocol>)purchasableItemFromObject:(id)item;
@end
