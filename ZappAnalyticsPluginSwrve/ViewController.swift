//
//  ViewController.swift
//  ZappAnalyticsPluginExample-iOS
//
//  Created by Mohieddine Zarif on 4/14/20.
//  Copyright © 2020 CME. All rights reserved.
//

import UIKit
import ApplicasterSDK
import ZappAnalyticsPluginSwrvePlugin

class ViewController: UIViewController {
    
    let CLICKING_BUTTON_1 = "testing_301";
    let CLICKING_BUTTON_2 = "testing_302";
    let EVENT_WITH_PARAMS = "Action with parameters";
    let ERROR_EVENT = "Error Event";
    let SCREEN_NAME = "Home Screen";

    @IBOutlet var eventButtons: [UIButton]!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Ignore this portion of the flow, this will happen automatically in the Applicaster App initilization flow
        let provider = ZappAnalyticsPluginSwrvePlugin()
        if provider.configureProvider() {
            //ZAAppConnector.sharedInstance().analyticsDelegate.startManager(withAccountId: nil)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func eventClicked(_ sender: UIButton) {
        /**
        This simulates various events that might happen in the app. Use this to see how the TestAnalyticsProvider reacts
        to these events.
        */
        switch sender.tag {
        case 1:
            ZappAnalyticsPluginSwrvePlugin().trackEvent(CLICKING_BUTTON_1, parameters: [:])
        case 2:
            ZappAnalyticsPluginSwrvePlugin().trackEvent(CLICKING_BUTTON_2, parameters: [:])
        default: break
            //TestAnalyticsProvider().trackEvent(name: CLICKING_BUTTON_1, parameters: nil, timed: false)
        }
    }
    
}
