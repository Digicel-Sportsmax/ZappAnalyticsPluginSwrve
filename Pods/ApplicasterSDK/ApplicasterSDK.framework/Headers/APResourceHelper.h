//
//  APResourceHelper.h
//  ApplicasterUIKit
//
//  Created by reuven levitsky on 11/30/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A helper class for finding resources with fallbacks.
 The logic is - find the first bundle containing the given resource (by iterating the bundlesArray from the first to the last index).
 Usually, the first bundle given in the bundleArray will be the main bundle in order to allow overriding the resource on application level.
 */
@interface APResourceHelper : NSObject

@property (nonatomic, readonly) NSArray *bundlesArray;

/**
 Returns the default bundle, the first bundle that will be checked for resources.
 */
- (NSBundle *)defaultBundle;

/**
 Use this init method in order to define the array of bundles to look into when looking for a resource.

 @param bundlesArray - Array of NSBundle instances.

 @return the new instance created (self)
 */
- (instancetype)initWithBundlesArray:(NSArray *)bundlesArray;

/**
 Returns the bundle containing the given nibName. You may use it when initiating views in your code in order to get the correct bundle to initiate from.

 @param nibName - the name of the nib to look for.

 @return the bundle containing the given nib name.
 */
- (NSBundle *)bundleForNibNamed:(NSString *)nibName;

/**
 Returns the image with the given name.

 @param imageName - the name of the image to return. Don't have to contain the file extension - uses the native imageNamed method.

 @return the image found.
 */
- (UIImage *)imageNamed:(NSString *)imageName;

/**
 Returns the image with the given name.

 @param imageName - the name of the image to return. Don't have to contain the file extension - uses the native imageNamed method. 
                    If the image name ends with .gif it will return a FLAnimatedImage instance.
 @param bundle - the bundle to look the image in.

 @return the image found.
 */
- (UIImage *)imageNamed:(NSString *)imageName
             fromBundle:(NSBundle *)bundle;

/**
 Returns the bundle which contains the given resourceName with the given fileExtension.

 @param resourceName - The name of the resource to look for.
 @param type - The file extension of the resource to look for.

 @return The bundle containing the given resource.
 */
- (NSBundle *)bundleForResourceNamed:(NSString *)resourceName
                              ofType:(NSString *)type;

@end
