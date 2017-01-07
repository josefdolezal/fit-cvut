import Foundation
import UIKit
import SVProgressHUD

struct Departure {
    let destination: String
    let line: String
    let time: (Int, Int)
    
    init(destination: String, line: String, time: (Int, Int)) {
        self.destination = destination
        self.line = line
        self.time = time
    }
}

class PubtranDetailTableViewController: UITableViewController {
    var departures = [[Departure]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        SVProgressHUD.show()
    }
    
    func dataLoaded(details: ServiceDetails) {
        self.parseDetails(details)
        self.tableView.reloadData()
        
        SVProgressHUD.dismiss()
    }
    
    private func parseDetails(details: ServiceDetails) {
        guard let lines = details.data?.array else {
            return
        }
        
        let dateNow = NSDate()
        var tmp = [String: [String: [Departure]]]()
        
        for line in lines {
            let lineNumber = line["line"].stringValue
            let destination = line["termstation"].stringValue
            
            let dp = Departure(
                destination: destination,
                line: lineNumber,
                time: dateNow.timeDelta(line["time"].stringValue.toTimeWithFormat("HH:mm"))
            )
            
            if let _ = tmp[lineNumber] {
                if let _ = tmp[lineNumber]![destination] {
                    if tmp[lineNumber]![destination]!.count < 2 {
                        tmp[lineNumber]![destination]!.append(dp)
                    }
                } else {
                    tmp[lineNumber]![destination] = [dp]
                }
            } else {
                tmp[lineNumber] = [destination: [dp]]
            }
        }
        
        self.departures.removeAll()
        
        for (_, dict) in tmp {
            var lines = [Departure]()
            
            for (_, depts) in dict {
                lines += (depts)
            }
            
            self.departures.append(lines)
        }
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("pubtranDetailCell", forIndexPath: indexPath) as! PubtranTableCell
        let departure = self.departures[indexPath.section][indexPath.row]
        
        cell.line = departure.line
        cell.station = departure.destination
        cell.time = departure.time
        
        return cell
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.departures[section].count
    }
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return self.departures.count
    }
    
    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Line: \(departures[section][0].line)"
    }
}