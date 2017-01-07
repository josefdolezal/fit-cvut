import Foundation

extension String {
    func toTimeWithFormat(format: String) -> NSDate {
        let formatter = NSDateFormatter()
        formatter.dateFormat = format
        formatter.timeZone = NSTimeZone.systemTimeZone()
        
        return formatter.dateFromString(self)!
    }
}