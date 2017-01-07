import Foundation
import UIKit

class NearbyViewController: UITableViewController {
    var campaignDelegate: CampaignsView?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.refreshControl?.addTarget(self, action: "refreshServices", forControlEvents: .ValueChanged)
    }
    
    func refreshServices() {
        self.tableView.reloadData()
        self.refreshControl?.endRefreshing()
    }
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return self.campaignDelegate!.campaigns.count
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.campaignDelegate!.campaigns[section].nearbyServices?.count ?? 0
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("serviceCell", forIndexPath: indexPath)
        
        cell.textLabel?.text = self.campaignDelegate?.campaigns[indexPath.section].nearbyServices![indexPath.row].name
        return cell
    }
    
    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return self.campaignDelegate?.campaigns[section].name
    }
}