//
//  UIView+APAdditions.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 9/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 UIView additions taken from Three20
 */
@interface UIView (APAdditionsXibs)

/**
 Load the view from a XIB named after itself. This method will throw an exception if no XIB file can be found using the same name as the view's class.
 @param plistName name of the plist settings
 @param originalName of the origial view (if view is not custom)
 @return A new view loaded from the XIB file.
 */
+ (id)viewFromXIBOfPlist:(NSString *)plistName withAPOriginalName:originalName;

/**
 Load the view from a XIB named after itself. This method will throw an exception if no XIB file can be found using the same name as the view's class.
 @return A new view loaded from the XIB file.
 */
+ (id)viewFromXIB;


@end


