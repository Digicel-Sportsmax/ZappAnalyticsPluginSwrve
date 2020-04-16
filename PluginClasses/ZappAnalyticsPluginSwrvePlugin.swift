//
//  ZappAnalyticsPluginSwrvePlugin
//  ZappAnalyticsPluginSwrve
//
//  Created by Mohieddine Zarif on 4/14/20.
//  Copyright © 2020 CME. All rights reserved.
//

import ZappPlugins
import ZappAnalyticsPluginsSDK
import SwrveSDK

public class ZappAnalyticsPluginSwrvePlugin: ZPAnalyticsProvider {
    
    let eventDuration = "EVENT_DURATION"
    fileprivate let ACCOUNT_ID_KEY = "swrve_account_id"
    fileprivate let SANDBOX_API_KEY = "swrve_sandbox_key"
    fileprivate let PRODUCTION_API_KEY = "swrve_production_key"
    
    static var isAutoIntegrated: Bool = false
    var timedEventDictionary: NSMutableDictionary?
    
    public required init() {
        super.init()
        self.configurationJSON = configurationJSON
    }

    public required init(configurationJSON: NSDictionary?) {
        super.init()
        self.configurationJSON = configurationJSON
    }
    
    public override func createAnalyticsProvider(_ allProvidersSetting: [String : NSObject]) -> Bool {
        return super.createAnalyticsProvider(allProvidersSetting)
    }

    public override func configureProvider() -> Bool {
        if !(ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated) {
            self.setupSwrve()
        }
        return ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated

    }

    fileprivate func setupSwrve() {
        let trackerConfig = SwrveConfig()
        // SwrveConfig
        trackerConfig.stack = SWRVE_STACK_EU
        trackerConfig.pushEnabled = true
        
        if let accountIdVal = self.configurationJSON?[self.ACCOUNT_ID_KEY] as? String,
            let accountIdAsInt = Int32(accountIdVal),
            let sandboxApiKeyVal = self.configurationJSON?[self.SANDBOX_API_KEY] as? String,
            let productionApiKeyVal = self.configurationJSON?[self.PRODUCTION_API_KEY] as? String {
            
            #if PROD
            SwrveSDK.sharedInstance(withAppID: accountIdAsInt, apiKey: productionApiKeyVal, config: trackerConfig)
            #else
            SwrveSDK.sharedInstance(withAppID: accountIdAsInt, apiKey: sandboxApiKeyVal, config: trackerConfig)
            #endif
            ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated = true
        }

    }
    
    public override func getKey() -> String {
        return "swrve_analytics"
    }
    
    public override func trackEvent(_ eventName: String, parameters: [String : NSObject], completion: ((Bool, String?) -> Void)?) {
        if parameters.isEmpty {
            SwrveSDK.sharedInstance()?.event(eventName)
        } else {
            SwrveSDK.sharedInstance()?.event(eventName, payload: parameters)
        }
    }

    public override func shouldTrackEvent(_ eventName: String) -> Bool {
        return true
    }
    
    public override func trackEvent(_ eventName: String) {
        trackEvent(eventName, parameters: [String : NSObject](), completion: nil)
    }
    
    public override func trackEvent(_ eventName: String, timed: Bool) {
        trackEvent(eventName, parameters: [String : NSObject](), timed: timed)
    }
    
    public override func trackEvent(_ eventName: String, parameters: [String : NSObject], timed: Bool) {
        if timedEventDictionary == nil {
            timedEventDictionary = NSMutableDictionary()
        }
        timedEventDictionary![eventName] = Date()
    }
    
    public override func endTimedEvent(_ eventName: String, parameters: [String : NSObject]) {
        if let timedEventDictionary = timedEventDictionary {
            if let startDate = timedEventDictionary[eventName] as? Date {
                let endDate = Date()
                let elapsed = endDate.timeIntervalSince(startDate)
                var params = parameters.count > 0 ? parameters : [String : NSObject]()
                let durationInMilSec = NSString(format:"%f",elapsed * 1000)
                params[eventDuration] = durationInMilSec
                trackEvent(eventName, parameters: params)
            }
        }
    }
    
    public override func trackEvent(_ eventName: String, parameters: [String : NSObject]) {
        trackEvent(eventName, parameters: parameters, completion: nil)
    }

    public override func trackScreenView(_ screenName: String, parameters: [String : NSObject]) {
        let eventName = "Screen Visit: "+screenName
        trackEvent(eventName, parameters: parameters)
    }

    public override func setPushNotificationDeviceToken(_ deviceToken: Data) {
        super.setPushNotificationDeviceToken(deviceToken)
    }

}
