//
//  NSString+APRemoteLocalization.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 4/1/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

@import Foundation;

@interface NSString (APRemoteLocalization)

/**
 Calls <code>APLocalizedString(localizationKey,self)</code>
 Example of use: <code>[@"The sentence to be localized" withKey:@"APExampleSentence"]</code>
 @param localizationKey The key to be checked in the localization table.
 @return The localized string that matches the localization key.
 */
- (NSString*)withKey:(NSString*)localizationKey;

@end

