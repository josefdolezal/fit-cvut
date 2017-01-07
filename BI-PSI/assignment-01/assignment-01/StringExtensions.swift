//
//  StringExtensions.swift
//  assignment-01
//
//  Created by Josef Dolezal on 01/05/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

extension String {
    func sumElements() -> Int {
        return Array(self.utf8).reduce(0) { Int($0) + Int($1) }
    }
    
    func stringByRemovingSuffix(suffix: String) -> String {
        if self.hasSuffix(suffix) {
            return self.substringToIndex(self.endIndex.advancedBy(-1*suffix.characters.count))
        }
        
        return self
    }
}