//
//  ZappAnalyticsPluginSwrvePlugin
//  ZappAnalyticsPluginSwrve
//
//  Created by Mohieddine Zarif on 4/14/20.
//  Copyright © 2020 CME. All rights reserved.
//

import Foundation
import ZappAnalyticsPluginsSDK
import ZappPlugins
import SwrveSDK

/**
This Template contains protocol methods to be implemented according to your needs.
Some of the methods can be removed if they are not relevant for your implementation.
You can also add methods from the protocol, for more information about the available methods, please check ZPAnalyticsProviderProtocol under ZappPlugins.
**/

open class ZappAnalyticsPluginSwrvePlugin: ZPAnalyticsProvider {
    
    let eventDuration = "EVENT_DURATION"
    var accountId: Int32 = 0
    var apiKey: String = ""
    static var isAutoIntegrated: Bool = false
    var timedEventDictionary: NSMutableDictionary?

    public required init() {
        super.init()
    }
    
    public required init(configurationJSON: NSDictionary?) {
        super.init()
        self.configurationJSON = configurationJSON
       // self.configureProvider()
    }
    
    required public init(pluginModel: ZPPluginModel) {
        fatalError("init(pluginModel:) has not been implemented")
    }
    
    /**
     Configures the provider, here is where the analytics provider should be configured.
     The custom configs from the manifest are extracted and available in `self.providedProperties` variable.
     If the configuration of the provider is successful return true otherwise retrun false
    */
    open override func configureProvider() -> Bool {
        
        let trackerConfig = SwrveConfig()
        accountId = 6883
        apiKey = "eMIb7GMt6Y60SgkeGJSp"
        // SwrveConfig
        trackerConfig.stack = SWRVE_STACK_EU
        trackerConfig.pushEnabled = true

        #if PROD
        SwrveSDK.sharedInstance(withAppID: accountId, apiKey: apiKey, config: trackerConfig)
        #else
        SwrveSDK.sharedInstance(withAppID: accountId, apiKey: apiKey, config: trackerConfig)
        #endif
        
        return true
    }
    
    // Returns the provider key (a unique identifier for your provider)
    open override func getKey() -> String {
        return "SwrveAnalyticsProvider"
    }
    
    open override func trackEvent(_ eventName: String, parameters: [String : NSObject], completion: ((Bool, String?) -> Void)?) {
        if parameters.isEmpty {
            SwrveSDK.sharedInstance()?.event(eventName)
        } else {
            SwrveSDK.sharedInstance()?.event(eventName, payload: parameters)
        }
    }
    
    open override func trackEvent(_ eventName: String) {
        trackEvent(eventName, parameters: [String : NSObject](), completion: nil)
    }
    
    open override func trackEvent(_ eventName: String, timed: Bool) {
        trackEvent(eventName, parameters: [String : NSObject](), timed: timed)
    }
    
    open override func trackEvent(_ eventName: String, parameters: [String : NSObject], timed: Bool) {
        if timedEventDictionary == nil {
            timedEventDictionary = NSMutableDictionary()
        }
        timedEventDictionary![eventName] = Date()
    }
    
    open override func endTimedEvent(_ eventName: String, parameters: [String : NSObject]) {
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
    
    open override func trackEvent(_ eventName: String, parameters: [String : NSObject]) {
        trackEvent(eventName, parameters: parameters, completion: nil)
    }
    
    open override func trackScreenView(_ screenName: String, parameters: [String : NSObject]) {
        let eventName = "screen_"+screenName
        trackEvent(eventName, parameters: [String : NSObject](), completion: nil)
    }
    
    // MARK: Extra Analytics methods

    public override func analyticsMaxParametersAllowed() -> Int {
        return 1
    }
    
    public override func setBaseParameter(_ value: NSObject?, forKey key: String) {
        super.setBaseParameter(value, forKey: key)
    }
    
    public override func sortPropertiesAlphabeticallyAndCutThemByLimitation(_ properties: [String : NSObject]) -> [String : NSObject] {
        return properties
    }
    
    public override func createAnalyticsProvider(_ allProvidersSetting: [String : NSObject]) -> Bool {
        return self.configureProvider()
    }
    
    public override func updateGenericUserProperties(_ genericUserProfile: [String : NSObject]) {
        super.updateGenericUserProperties(genericUserProfile)
    }
    
    public override func updateDefaultEventProperties(_ eventProperties: [String : NSObject]) {
        super.updateDefaultEventProperties(eventProperties)
    }
    
    public override func trackScreenView(_ screenName: String, parameters: [String : NSObject], completion: ((Bool, String?) -> Void)?) {
        let eventName = "visited_"+screenName
        trackEvent(eventName, parameters: [String : NSObject](), completion: nil)
    }
    
    public override func presentToastForLoggedEvent(_ eventDescription: String?) {
        super.presentToastForLoggedEvent(eventDescription)
    }
    
    public override func canPresentToastForLoggedEvents() -> Bool {
        return false
    }
    
    public override func shouldTrackEvent(_ eventName: String) -> Bool {
        return true
    }
    
    //MARK: Push Notification Token
    
    /**
     sets the Push Notification deviceToken
     */
    open override func setPushNotificationDeviceToken(_ deviceToken: Data) {
        super.setPushNotificationDeviceToken(deviceToken)
    }
    
}