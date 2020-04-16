import ZappPlugins
import ZappAnalyticsPluginsSDK
import SwrveSDK

public class ZappAnalyticsPluginSwrvePlugin: ZPAnalyticsProvider {
    
    let eventDuration = "EVENT_DURATION"
    static var isAutoIntegrated: Bool = false
    var timedEventDictionary: NSMutableDictionary?
    var userID: String?
    
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
            ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated = true
            self.setupSwrve()
        }

        return true

    }
    
    
    fileprivate func setupSwrve() {
        let trackerConfig = SwrveConfig()
        let accountId: Int32 = 6883
        let apiKey = "eMIb7GMt6Y60SgkeGJSp"
        // SwrveConfig
        trackerConfig.stack = SWRVE_STACK_EU
        trackerConfig.pushEnabled = true

        SwrveSDK.sharedInstance(withAppID: accountId, apiKey: apiKey, config: trackerConfig)
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

}