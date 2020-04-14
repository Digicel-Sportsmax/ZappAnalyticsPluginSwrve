//
//  SHMHTTPHelper.h
//  SHMKit
//
//  Created by Matthew Dobson on 4/28/14.
//  Copyright (c) 2014 Matthew Dobson. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APSHMEntity.h"
#import "APSHMEntityFactoryDelegate.h"

typedef void (^APSirenHTTPResult) (NSError *error, APSHMEntity *entity);

@interface APSHMEntityFactory : NSObject

@property (nonatomic, retain) id<APSHMEntityFactoryDelegate> delegate;

+(id) sharedFactory;

-(void) sendSirenRequest:(NSURLRequest *)req withBlock:(void (^)(NSError *error, APSHMEntity *entity))block;

@end
