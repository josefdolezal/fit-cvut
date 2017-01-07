//
//  Notification.swift
//  What2Do
//
//  Created by Josef Dolezal on 16/02/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation
import UIKit

class Notify {
    static func schedule(body: String, data:[String:String]? = nil, slider: String? = nil) {
        let localNotification = UILocalNotification()
        localNotification.fireDate = NSDate(timeIntervalSinceNow: 5)
        localNotification.alertBody = "\(body)"
        
        if let usrData = data {
            localNotification.userInfo = usrData
        }
        
        if let action = slider {
            localNotification.alertAction = action
        }
        
        UIApplication.sharedApplication().scheduleLocalNotification(localNotification)
    }
}
