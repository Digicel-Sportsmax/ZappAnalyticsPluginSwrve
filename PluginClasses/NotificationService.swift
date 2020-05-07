//
//  ZappAnalyticsPluginSwrvePlugin
//  ZappAnalyticsPluginSwrve
//
//  Created by Mohieddine Zarif on 4/30/20.
//  Copyright © 2020 CME. All rights reserved.
//

import UserNotifications
import SwrveSDKCommon

class NotificationService: UNNotificationServiceExtension {

    var contentHandler: ((UNNotificationContent) -> Void)?
    var bestAttemptContent: UNMutableNotificationContent?
    let groupId = "com.NotificationServiceExtension.sportsmax"

    override func didReceive(_ request: UNNotificationRequest, withContentHandler contentHandler: @escaping (UNNotificationContent) -> Void) {
        self.contentHandler = contentHandler

        SwrvePush.handle(request.content, withAppGroupIdentifier: groupId) {(content) in
            self.bestAttemptContent = content
            contentHandler(self.bestAttemptContent!)
        }
    }

    override func serviceExtensionTimeWillExpire() {
        if let contentHandler = contentHandler, let bestAttemptContent = bestAttemptContent {
            contentHandler(bestAttemptContent)
        }
    }

}