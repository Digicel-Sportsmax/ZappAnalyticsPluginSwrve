//
//  APContent.h
//  ApplicasterSDK
//
//  Created by Anton Kononenko on 02/04/2017.
//  Copyright © 2017 Applicaster Ltd. All rights reserved.
//

@import Foundation;
@import ZappPlugins;

#import "APURLPlayable.h"

@class APAtomEntry;

#pragma mark -  APAtomEntryPlayable

@interface APAtomEntryPlayable : APURLPlayable <ZPAtomEntryPlayableProtocol>

#pragma mark - Init

- (instancetype)initWithAtomEntry:(APAtomEntry *)atomEntry;

#pragma mark - Properties
@property (nonatomic, weak) NSDictionary *pipesObject;
@property (nonatomic, readonly) NSArray *mediaGroups;
@property (nonatomic, readonly) NSString *atomEntryId;
@property (nonatomic, readonly) NSString *publishDate;
@property (nonatomic, readonly) NSString *link;
@property (nonatomic, weak) APAtomEntry *atomEntry;

/**
 @return The name of the AtomFeed that contains this entry.
 */
- (NSString *)feedName;

- (NSDictionary *)authorizationProvidersHeaders;
@end
