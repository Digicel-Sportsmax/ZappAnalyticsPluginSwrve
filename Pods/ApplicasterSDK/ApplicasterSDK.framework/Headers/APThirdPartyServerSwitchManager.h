//
//  APThirdPartyServerSwitchManager.h
//  Applicaster
//
//  Created by Alex Zchut on 7/20/16.
//  Copyright (c) 2016 Applicaster Ltd. All rights reserved.
//

@import UIKit;

typedef NS_ENUM(NSUInteger, APThirdPartyServerSwitchServerType) {
    APThirdPartyServerSwitchProductionServer,
    APThirdPartyServerSwitchDevelopmentServer,
    APThirdPartyServerSwitchCustomServer
};

@interface APThirdPartyServerSwitchManager : NSObject


+ (instancetype)sharedInstance;

/**
 Server type enum. Default server is set as APSettingProductionServer.
 Changing between servers in device settings will call exit(0) to restart application.
 @returns The enum @see APServerSwitchServerType of selected server in the settings of the device.
 */
+ (APThirdPartyServerSwitchServerType)serverType;

/**
 Custom Server type value. Populated only if custom server type is selected.
 */
+ (NSString *)customServerType;
@end
