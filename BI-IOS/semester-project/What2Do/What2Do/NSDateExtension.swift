import Foundation

extension NSDate {
    func timeComponent() -> NSDateComponents {
        let calendar = NSCalendar.currentCalendar()
        return calendar.components([.Hour, .Minute], fromDate: self)
    }
    
    func timeDelta(date: NSDate) -> (hours: Int, minutes: Int) {
        let lowerTime = self.timeComponent()
        let biggerTime = date.timeComponent()
        
        // Easier difference
        if lowerTime.minute > biggerTime.minute {
            biggerTime.minute += 60
            lowerTime.hour += 1
        }
        
        // Over midnight
        if lowerTime.hour > biggerTime.hour {
            biggerTime.hour += 24
        }
        
        return (biggerTime.hour - lowerTime.hour, biggerTime.minute - lowerTime.minute)
    }
    
    func timeDelta(date: NSDate, lessThan min: Int) -> Bool {
        let time = self.timeDelta(date)
        
        return (time.hours * 60 + time.minutes) < min
    }
}