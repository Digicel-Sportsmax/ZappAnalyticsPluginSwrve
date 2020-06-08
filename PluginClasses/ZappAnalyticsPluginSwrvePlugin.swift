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


open class ZappAnalyticsPluginSwrvePlugin: ZPAnalyticsProvider, ZPPlayerAnalyticsProviderProtocol {

    public let MAX_PARAM_NAME_CHARACTERS_LONG  :Int = 40
    public let MAX_PARAM_VALUE_CHARACTERS_LONG :Int = 100
    public let FIREBASE_PREFIX : String = "Firebase_"
    public let APPLICASTER_PREFIX : String = "applicaster_"
    private var LEGENT : Dictionary<String, String> = [:]
    private var LEGENT_JSON : String = "{\" \":\"__\",\"_\":\"_0\",\"-\":\"_1\",\":\":\"_2\",\"'\":\"_3\",\".\":\"_4\",\",\":\"_5\",\"/\":\"_6\",\"\\\\\":\"_7\",\"(\":\"_8\",\")\":\"_A\",\"?\":\"_B\",\"\\\"\":\"_C\",\"!\":\"_D\",\"@\":\"_E\",\"#\":\"_F\",\"$\":\"_G\",\"%\":\"_H\",\"^\":\"_I\",\"&\":\"_J\",\"*\":\"_K\",\"=\":\"_M\",\"+\":\"_N\",\"~\":\"_L\",\"`\":\"_O\",\"|\":\"_P\",\";\":\"_Q\",\"[\":\"_R\",\"]\":\"_S\",\"}\":\"_T\",\"{\":\"_U\"}"
    
    fileprivate let video_prefix = "(VOD)"
    fileprivate let video_play_event = "VOD Item: Play was Triggered"
    fileprivate let item_name_key = "Item Name"
    let eventDuration = "EVENT_DURATION"
    fileprivate let ACCOUNT_ID_KEY_SANDBOX = "swrve_account_id_sandbox"
    fileprivate let ACCOUNT_ID_KEY_PRODUCTION = "swrve_account_id_production"
    fileprivate let SANDBOX_API_KEY = "swrve_sandbox_key"
    fileprivate let PRODUCTION_API_KEY = "swrve_production_key"
    fileprivate let SCREEN_VISIT_KEY = "screen_visit"
    static var isAutoIntegrated: Bool = false
    var timedEventDictionary: NSMutableDictionary?

    lazy var blacklistedEvents:[String] = {
        if let events = self.configurationJSON?["blacklisted_events"] as? String {
            return events.components(separatedBy: ";").filter { $0.isEmpty == false }.map { $0.lowercased() }
        }
        else {
            return []
        }
    }()

    
    var isUserProfileEnabled = true
    
    //Firebase User Profile
    struct UserProfile {
        static let created = "$created"
        static let iOSDevices = "$ios_devices"
    }
    
    //Json Keys
    struct JsonKeys {
        static let sendUserData = "Send_User_Data"
    }
    
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
    
    override open func getKey() -> String {
        return "swrve_analytics"
    }
    
    override open func configureProvider() -> Bool {
        if !(ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated) {
            self.setupSwrve()
        }
        return ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated

    }
    
    fileprivate func setupSwrve() {
        let trackerConfig = SwrveConfig()
        // SwrveConfig
        trackerConfig.stack = SWRVE_STACK_EU
        trackerConfig.pushResponseDelegate = self
        trackerConfig.pushEnabled = true
        trackerConfig.pushNotificationEvents = Set(["tutorial.complete", "subscribe"])
        
        if let accountIdValSandbox = self.configurationJSON?[self.ACCOUNT_ID_KEY_SANDBOX] as? String,
            let accountIdValProduction = self.configurationJSON?[self.ACCOUNT_ID_KEY_PRODUCTION] as? String,
            let accountIdAsIntSandbox = Int32(accountIdValSandbox),
            let accountIdAsIntProduction = Int32(accountIdValProduction),
            let sandboxApiKeyVal = self.configurationJSON?[self.SANDBOX_API_KEY] as? String,
            let productionApiKeyVal = self.configurationJSON?[self.PRODUCTION_API_KEY] as? String {
            
            #if PROD
            SwrveSDK.sharedInstance(withAppID: accountIdAsIntProduction, apiKey: productionApiKeyVal, config: trackerConfig)
            #else
            SwrveSDK.sharedInstance(withAppID: accountIdAsIntSandbox, apiKey: sandboxApiKeyVal, config: trackerConfig)
            #endif
            ZappAnalyticsPluginSwrvePlugin.isAutoIntegrated = true
        }

    }
    
    override open func trackEvent(_ eventName: String, parameters: [String : NSObject], completion: ((Bool, String?) -> Void)?) {
        super.trackEvent(eventName, parameters: parameters)
        var combinedParameters = ZPAnalyticsProvider.defaultProperties(self.defaultEventProperties, combinedWithEventParams: parameters)

        let eventName = refactorParamName(eventName: eventName)

        if combinedParameters.isEmpty == true {
            SwrveSDK.sharedInstance()?.event(eventName)
        }
        else {
            combinedParameters = refactorEventParameters(parameters: combinedParameters)
            SwrveSDK.sharedInstance()?.event(eventName, payload: parameters)
        }
    }

    public override func shouldTrackEvent(_ eventName: String) -> Bool {
        return true
    }
    
    override open func trackEvent(_ eventName:String, parameters:[String:NSObject]) {
        super.trackEvent(eventName, parameters: parameters)
        var combinedParameters = ZPAnalyticsProvider.defaultProperties(self.defaultEventProperties, combinedWithEventParams: parameters)

        let eventName = refactorParamName(eventName: eventName)

        if combinedParameters.isEmpty == true {
            SwrveSDK.sharedInstance()?.event(eventName)
        }
        else {
            combinedParameters = refactorEventParameters(parameters: combinedParameters)
            SwrveSDK.sharedInstance()?.event(eventName, payload: parameters)
        }
    }

    open func trackEvent(_ eventName:String, parameters:[String:NSObject], model: Any?) {
        trackEvent(eventName, parameters: parameters)
    }
    
    override open func trackEvent(_ eventName:String, action:String, label:String, value:Int) {
        
    }
    
    public func startStreaming(withURL url: URL) {
        
    }

    override open func trackEvent(_ eventName:String, message: String, exception:NSException) {
        trackEvent(eventName, parameters: [String : NSObject]())
    }
    
    override open func trackEvent(_ eventName:String, message: String, error: NSError) {
        trackEvent(eventName, parameters: [String : NSObject]())

    }
    
    override open func trackEvent(_ eventName:String, timed:Bool) {
        if timed {
            registerTimedEvent(eventName, parameters: nil)
        } else {
            trackEvent(eventName, parameters: [String : NSObject]())
        }
    }
    
    override open func trackEvent(_ eventName:String, parameters: [String:NSObject], timed:Bool) {
        if timed {
            registerTimedEvent(eventName, parameters: parameters)
        } else {
            trackEvent(eventName, parameters: parameters)
        }
    }
    
    override open func trackEvent(_ eventName: String) {
        trackEvent(eventName, parameters: [String : NSObject]())
    }
    
    override open func endTimedEvent(_ eventName: String, parameters: [String : NSObject]) {
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
    
    override open func setUserProfile(genericUserProperties dictGenericUserProperties: [String : NSObject],
                                      piiUserProperties dictPiiUserProperties: [String : NSObject]) {
        if isUserProfileEnabled {
            var swrveParameters = [String : NSObject]()
            for (key, value) in dictGenericUserProperties {
                switch key {
                case kUserPropertiesCreatedKey:
                    swrveParameters[UserProfile.created] = value
                case kUserPropertiesiOSDevicesKey:
                    swrveParameters[UserProfile.iOSDevices] = value
                default:
                    swrveParameters[key] = value
                }
            }
            
            SwrveSDK.sharedInstance()?.userUpdate(swrveParameters)
        }
    }
    
    public override func trackScreenView(_ screenName: String, parameters: [String : NSObject]) {
        let eventName = self.SCREEN_VISIT_KEY
        trackEvent(eventName, parameters: parameters)
    }
    
    public func startTrackingPlayerEvents(forPlayer player: Any) {
    }
    
    /*
     * loading LEGENT Dictionary according LEGENT_JSON
     */
    public func initLegent() {
        LEGENT = convertToDictionary(jsonString: LEGENT_JSON)
    }
    
    /**
     * @param eventValue the text we should encode according param value limitations.
     * @return encoded string base on eventValue
     * @discussion  Firebase param value limitations:
     * @discussion  **********************
     * @discussion  1. Param values can be up to 100 characters long.
     * @discussion  2. The "firebase_" prefix is reserved and should not be used so APPLICASTER_PREFIX will be added.
     */
    public func  refactorParamValue(eventValue:  String) -> String{
        var returnValue:String = eventValue
        
        if (returnValue.hasPrefix(FIREBASE_PREFIX)) {
            returnValue = APPLICASTER_PREFIX + returnValue;
        }
        
        //Param values can be up to 100 characters long.
        if (returnValue.count > MAX_PARAM_VALUE_CHARACTERS_LONG) {
            returnValue = String(returnValue[returnValue.startIndex..<returnValue.index(returnValue.startIndex, offsetBy: MAX_PARAM_VALUE_CHARACTERS_LONG)])
        }
        
        return returnValue;
    }
    
    /*
     * @param eventValue the text we should encode according param name limitations.
     * @return encoded string base on eventName
     * @discussion  Firebase param names limitations:
     * @discussion  **********************
     * @discussion  1. Param names can be up to 40 characters long.
     * @discussion  2. Contain alphanumeric characters and underscores ("_").
     * @discussion  3. must start with an alphabetic character.
     * @discussion  4. The "firebase_" prefix is reserved and should not be used so APPLICASTER_PREFIX will be added.
     */
    public func refactorParamName( eventName: String) -> String {
        var returnValue:String = eventName
        //Contain alphanumeric characters and underscores ("_").
        returnValue = recursiveEncodeAlphanumericCharacters(eventName: returnValue)
        
        if (returnValue.hasPrefix(FIREBASE_PREFIX)) {
            returnValue = APPLICASTER_PREFIX + returnValue
        }
        
        // 3. must start with an alphabetic chaacter.
        if returnValue.isEmpty == false {
            switch returnValue[returnValue.startIndex] {
            case "0"..."9" , "a"..."z", "A"..."Z":
                break
            default:
                returnValue = APPLICASTER_PREFIX + returnValue;
                break
            }
        }
        
        //Param names can be up to 40 characters long.
        if (returnValue.count > MAX_PARAM_NAME_CHARACTERS_LONG) {
            returnValue = String(returnValue[returnValue.startIndex..<returnValue.index(returnValue.startIndex, offsetBy: MAX_PARAM_NAME_CHARACTERS_LONG)])
        }
        
        returnValue = returnValue.replacingOccurrences(of: " ", with: "_")
        returnValue = returnValue.replacingOccurrences(of: ":", with: "")

        return returnValue;
    }
    
    /*
     * Convert json string to dictionary
     */
    private func convertToDictionary(jsonString: String) -> [String: String] {
        guard let data = jsonString.data(using: String.Encoding.utf8) else {
            return [:]
        }
        
        guard let jsonDictionary = try? JSONSerialization.jsonObject(with: data, options: [] ) as! [String: String] else {
            return [:]
        }
        
        return jsonDictionary
    }
    
    /*
     * This function replace all the forbidden charcters with new one, according the legend dictionary.
    */
    private func recursiveEncodeAlphanumericCharacters( eventName: String ) -> String {
        let name:String = eventName
        if name.count > 0 {
            let send = name.index(name.startIndex, offsetBy: 1)
            let sendvalue = String(name[send..<name.endIndex])
            if let prefix = LEGENT[name.swrveGetFirstCharacter! as String] {
                return prefix + recursiveEncodeAlphanumericCharacters( eventName: sendvalue)
            }else{
                return name.swrveGetFirstCharacter! + recursiveEncodeAlphanumericCharacters( eventName: sendvalue)
            }
        }
        return ""
    }
    
    /*
     * Validate and refactor parameters before sending event
     */
    public func refactorEventParameters(parameters: [String: NSObject]) -> [String: NSObject]{
        var validateParameters = [String: NSObject]()
        for (key, value) in parameters {
            let validateParamName = refactorParamName(eventName:key)
            var validateParamValue = value
            if ((value as? String) != nil){
                validateParamValue = refactorParamValue(eventValue:value as! String) as NSObject
            }
            validateParameters[validateParamName] = validateParamValue
        }
        return validateParameters
    }
    
    public func setUserProfileWithGenericUserProperties(genericUserProperties: [String : NSObject],
                                                        piiUserProperties: [String : NSObject]) {
        
    }
    
    public override func setPushNotificationDeviceToken(_ deviceToken: Data) {
        super.setPushNotificationDeviceToken(deviceToken)
    }
    
}

// TODO: Create a plugin for all extensions and utitlies
extension String {
    public var swrveGetFirstCharacter: String? {
        guard 0 < self.count else { return "" }
        let idx = index(startIndex, offsetBy: 0)
        return String(self[idx...idx])
    }
}


extension ZappAnalyticsPluginSwrvePlugin: SwrvePushResponseDelegate {
    @available(iOS 10.0, *)
    public func didReceive(_ response: UNNotificationResponse, withCompletionHandler completionHandler: (() -> Void)) {
        print("Got iOS 10 Notification with Identifier - (response.actionIdentifier)")
        // Called when the push is interacted with. (pressed, button or dismiss)
        completionHandler()
    }
     
    @available(iOS 10.0, *)
    public func willPresent(_ notification: UNNotification, withCompletionHandler completionHandler: ((UNNotificationPresentationOptions) -> Void)) {
        // Called when a push is received when the app is in the foreground.
        completionHandler([])
    }
     
    /** Background update processing **/
    func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
     
        let handled = SwrveSDK.didReceiveRemoteNotification(userInfo, withBackgroundCompletionHandler: { fetchResult, swrvePayload in
                // NOTE: Do not call the Swrve SDK from this context
                // Your code here to process a Swrve remote push and payload
                // This can be used to process DeepLinks
                completionHandler(fetchResult)
            })
     
        if(!handled){
            // Your code here, it is either a non-background push received in the background or a non-Swrve remote push
            // You’ll have to process the payload on your own and call the completionHandler as normal
        }
    }
}
