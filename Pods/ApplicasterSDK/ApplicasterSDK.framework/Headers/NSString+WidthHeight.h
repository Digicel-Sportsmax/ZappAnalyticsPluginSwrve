//
//  NSString+WidthHeight.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 8/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 Additions taken from Three20.
 */
@interface NSString (APAdditionsWidthHeight)


/**
 Returns the height of the text when contained in the given label.
 @param label name of the label item for which the height is being computed
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label;

/**
 Returns the height of the text when contained in the given label.
 @param label name of the label item for which the height is being computed
 @param maxHeight the max height you allow the label to have.
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label
                      maxHeight:(CGFloat)maxHeight;

/**
 Returns the height of the text when contained in the given label but limits the number of characters
 @param label name of the label item for which the height is being computed
 @param maximumCharacters maximum number of characters in the label's text that is allowed
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label maximumCharacters:(NSUInteger)maximumCharacters;

/**
 Returns the width of the text when contained in the given label.
 @param label name of the label item for which the width is being computed.
 @return the computed width (float) of the label
 */
- (CGFloat)widthForTextInLabel:(UILabel *)label;

/**
 Returns the width of the text when contained in the given label.
 @param label name of the label item for which the width is being computed.
 @param maxWidth the max width you allow the label to have.
 @return the computed width (float) of the label
 */
- (CGFloat)widthForTextInLabel:(UILabel *)label
                      maxWidth:(CGFloat)maxWidth;

@end
