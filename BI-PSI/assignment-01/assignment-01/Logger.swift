//
//  Logger.swift
//  assignment-01
//
//  Created by Josef Dolezal on 30/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation
import QuartzCore

class Logger {
    private static var logs = [String: CFTimeInterval]()
    
    static func start(id: String, description: String = "") {
        logs[id] = CACurrentMediaTime()
        print("[Start:\(id)] \(description)")
    }
    
    static func stop(id: String) {
        if let start = logs[id] {
            logs.removeValueForKey(id)
            print("[Stop:\(id) ] End in \(CACurrentMediaTime() - start)")
        }
    }
}