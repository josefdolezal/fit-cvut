import Foundation
import UIKit

class MovieTableCell: UITableViewCell {
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var detailsLabel: UILabel!
    @IBOutlet weak var startsInLabel: UILabel!
    
    
    var name = "" {
        willSet {
            nameLabel.text = newValue
        }
    }
    
    var startsIn = "0" {
        willSet {
            startsInLabel.text = newValue
        }
    }
    
    func describeMovie(language lang: String, duration: String) {
        detailsLabel.text = "Language: \(lang), Duration: \(duration)"
    }
}