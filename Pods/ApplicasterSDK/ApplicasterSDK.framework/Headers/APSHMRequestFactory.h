//
//  SHMRequestFactory.h
//  SHMKit
//
//  Created by Matthew Dobson on 5/11/14.
//  Copyright (c) 2014 Matthew Dobson. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APSHMAction.h"
#import "APSHMRequestFactoryDelegate.h"

@interface APSHMRequestFactory : NSObject

@property (nonatomic, retain) id<APSHMRequestFactoryDelegate> delegate;

+ (id)sharedFactory;

/*
 Construct an HTTP request with a body or with URL parameters depending on the request verb itself.
 */
-(NSURLRequest *) constructRequestForAction:(APSHMAction *)action withParams:(NSDictionary *)dict;

/*
 Create an HTTP request with a body instead of URL parameters. POST, PUT, PATCH.
 */
-(NSURLRequest *) constructHTTPRequestForAction:(APSHMAction *)action withParams:(NSDictionary *)dict;

/*
 Create an http request that has URL parameters instead of parameters in the body. GET, DELETE, TRACE, HEAD, OPTIONS, CONNECT
 */
-(NSURLRequest *) constructBodylessHTTPRequestForAction:(APSHMAction *)action withParams:(NSDictionary *)dict;

@end
