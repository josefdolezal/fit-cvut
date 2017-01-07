import Foundation
import UIKit

class PubtranTableCell: UITableViewCell {
    
    @IBOutlet weak var lineLabel: UILabel!
    @IBOutlet weak var stationLabel: UILabel!
    @IBOutlet weak var leavingTimeLabel: UILabel!
    
    var line = "" {
        willSet {
            self.lineLabel.text = "Line: \(newValue)"
        }
    }
    
    var station = "" {
        willSet {
            self.stationLabel.text = "Station: \(newValue)"
        }
    }
    
    var time = (hour: 0, minute: 0) {
        willSet {
            let t = newValue.hour * 60 + newValue.minute
            
            if t < 5 {
                self.leavingTimeLabel.textColor = UIColor.redColor()
            } else {
                self.leavingTimeLabel.textColor = UIColor.blackColor()
            }
            
            self.leavingTimeLabel.text = "\(t)"
        }
    }
    
    var leavingTime = ""
}