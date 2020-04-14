//
//  APChannelHelper.h
//  Pods
//
//  Created by Avi Levin on 27/08/2017.
//
//

#import <Foundation/Foundation.h>
#import "ApplicasterSDK/APChannelProtocol.h"
#import "APChannel.h"

@interface APChannelHelper : NSObject

+(APChannel *)getAPChannelObjectFromProtocol:(NSObject <APChannelProtocol> *)model;

@end
