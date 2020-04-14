//
//  SHMRequestFactoryDelegate.h
//  SHMKit
//
//  Created by Matthew Dobson on 5/11/14.
//  Copyright (c) 2014 Matthew Dobson. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APSHMAction.h"

@protocol APSHMRequestFactoryDelegate <NSObject>

-(NSURLRequest *) buildRequestForAction:(APSHMAction *)action withParameters:(NSDictionary *)params;

-(NSURLRequest *) buildBodylessRequestForAction:(APSHMAction *)action withParameters:(NSDictionary *)params;

@end
