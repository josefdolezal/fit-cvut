import UIKit
import Foundation

enum AvailableCampaigns: String {
    case Pubtran = "508ba"
    case Cinemas = "299d4"
}

class CampaignsView: UITableViewController, UITabBarControllerDelegate {
    
    var campaigns = [Campaign]()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        NSNotificationCenter.defaultCenter().addObserver(
            self,
            selector: Selector("willEnterBackground:"),
            name: UIApplicationDidEnterBackgroundNotification,
            object: nil
        )
        
        let pubtran = Campaign(withAppCode: AvailableCampaigns.Pubtran.rawValue)
        let cinemas = Campaign(withAppCode: AvailableCampaigns.Cinemas.rawValue)
        
        pubtran.serviceDetails = self.pubtranHandler
        pubtran.didUpdateServices = self.servicesLoadedForCampaign
        cinemas.serviceDetails = self.cinemasHandler
        cinemas.didUpdateServices = self.servicesLoadedForCampaign
        
        self.campaigns.append(pubtran)
        self.campaigns.append(cinemas)
        
        self.tableView.tableFooterView = UIView(frame: CGRect.zero)
        self.refreshControl?.addTarget(self, action: "refreshCampaigns", forControlEvents: .ValueChanged)
        self.tabBarController?.delegate = self
        
        Notify.schedule("Test", data: ["test": "tst"], slider: "slider")
    }
    
    func servicesLoadedForCampaign( campaign: Campaign ) {
        self.tableView.reloadData()
        self.refreshControl?.endRefreshing()
    }
    
    func cinemasHandler(details: ServiceDetails, forSevice service: Service) {
        let data = [
            "major": service.major,
            "minor": service.minor,
            "trigger": service.name
        ]
        
        Notify.schedule("You have notification from \(campaigns[0].name) campaign.", data: data)
    }
    
    func pubtranHandler(details: ServiceDetails, forService service: Service) {
        let data = [
            "major": service.major,
            "minor": service.minor,
            "trigger": service.name
        ]
        
        Notify.schedule("You have notification from \(campaigns[0].name) campaign.", data: data)
    }
    
    func willEnterBackground(notification: NSNotification) {
        for campaign in self.campaigns {
            campaign.startBackgroundScanning()
        }
    }
    
    func refreshCampaigns() {
        for campaign in campaigns {
            campaign.setNeedUpdateServices()
        }
    }
    
    func tabBarController(tabBarController: UITabBarController, shouldSelectViewController viewController: UIViewController) -> Bool {
        if viewController.isKindOfClass(NearbyViewController) {
            let nearby = viewController as! NearbyViewController
            nearby.campaignDelegate = self
        }
        
        return true
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let campaign = self.campaigns[indexPath.section].availableServices![indexPath.row].name
        let cellID: String
        
        switch self.campaigns[indexPath.section].appCode {
        case AvailableCampaigns.Pubtran.rawValue:
            cellID = "pubtranCell"
        default:
            cellID = "cinemasCell"
        }
        
        let cell = tableView.dequeueReusableCellWithIdentifier(cellID, forIndexPath: indexPath)
        cell.textLabel?.text = campaign
        
        return cell
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        let cellIndex = self.tableView.indexPathForSelectedRow! as NSIndexPath
        let service = self.campaigns[cellIndex.section].availableServices![cellIndex.row]
        
        guard let identifier = segue.identifier else {
            return
        }
        
        let cell = sender as! UITableViewCell
        
        switch(identifier) {
        case "pubtranDetailSegue":
            let controller = segue.destinationViewController as! PubtranDetailTableViewController
            
            controller.navigationItem.title = cell.textLabel?.text
            campaigns[cellIndex.section].callService(service, callback: controller.dataLoaded)
        case "cinemaDetailSegue":
            let controller = segue.destinationViewController as! MovieDetailTableViewContoller
            
            controller.navigationItem.title = cell.textLabel?.text
            campaigns[cellIndex.section].callService(service, callback: controller.dataLoaded)
        default:
            break
        }
        
        self.tableView.deselectRowAtIndexPath(cellIndex, animated: true)
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.campaigns[section].availableServices?.count ?? 0
    }
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return self.campaigns.count
    }
    
    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return self.campaigns[section].name?.uppercaseString
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}