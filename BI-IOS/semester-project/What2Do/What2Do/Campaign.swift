import CoreLocation
import UIKit

class Campaign: NSObject, CLLocationManagerDelegate {
    var didRangeBeacons: ((CLLocationManager, [CLBeacon], CLBeaconRegion) -> Void)?
    var didUpdateServices: ((Campaign) -> Void)?
    var willStartScanning: (() -> Bool)?
    var serviceDetails: ((ServiceDetails, forService: Service) -> Void)?
    
    var appCode: String
    var dataSource: Beecon
    var locationManager: CLLocationManager!
    
    var uuidString: String!
    var region: CLBeaconRegion!
    var name: String!
    var availableServices: [Service]?
    var nearbyServices: [Service]?
    
    init(withAppCode code: String, proximity: CLProximity = .Near) {
        self.dataSource = Beecon(withAppCode: code)
        self.appCode = code
        super.init()
        
        self.loadCampaign()
    }
    
    func startBackgroundScanning() {
        self.startMonitoring()
    }
    
    func searchNearby() {
        if(!self.scanningIsAuthorized()) {
            self.nearbyServices = []
        }
        
        self.locationManager.startMonitoringForRegion(self.region)
    }
    
    func locationManager(manager: CLLocationManager, didEnterRegion region: CLRegion) {
        if self.region != region || self.appInForeground() {
            // Different region triggered event
            return
        }
        
        self.locationManager.startRangingBeaconsInRegion(self.region)
    }
    
    func locationManager(manager: CLLocationManager, didExitRegion region: CLRegion) {
        guard let reg = self.region else {
            return
        }
        
        if reg == region {
            self.locationManager.stopRangingBeaconsInRegion(self.region)
        }
    }
    
    func locationManager(manager: CLLocationManager, didRangeBeacons beacons: [CLBeacon], inRegion region: CLBeaconRegion) {
        if beacons.count < 1 {
            return
        }
        
        let function: ((CLLocationManager, [CLBeacon], CLBeaconRegion) -> Void)?
        
        if(self.appInForeground()) {
            function = self.foregroundRanging
        } else {
            function = self.backgroundRanging
        }
        
        function!(manager, beacons, region)
    }
    
    func backgroundRanging(manager: CLLocationManager, didRangeBeacons beacons: [CLBeacon], inRegion region: CLBeaconRegion) {
        self.didRangeBeacons?(manager, beacons, self.region)
        self.locationManager.stopRangingBeaconsInRegion(self.region)
        
        if let callback = self.serviceDetails {
            let beacon = beacons[0]
            let service = Service(major: "\(beacon.major)", minor: "\(beacon.minor)")
            
            self.dataSource.callService(service) { details in
                callback(details, forService: service)
                self.locationManager.stopRangingBeaconsInRegion(self.region)
            }
            
            self.locationManager.stopRangingBeaconsInRegion(self.region)
        }
    }
    
    func foregroundRanging(manager: CLLocationManager, didRangeBeacons beacons: [CLBeacon], inRegion region: CLBeaconRegion) {
        self.nearbyServices!.removeAll()
        
        for beacon in beacons {
            if let service = self.getAvailableServiceByMajor("\(beacon.major)", minor: "\(beacon.minor)") {
                self.nearbyServices!.append(service)
            }
        }
    }
    
    func callService( service: Service, callback: ((ServiceDetails) -> Void )) {
        self.dataSource.callService(service, completionHandle: callback)
    }
    
    func setNeedUpdateServices() {
        self.updateServices()
    }
    
    private func startMonitoring() {
        if(!self.scanningIsAuthorized()) {
            return
        }
        
        guard let uuid = NSUUID(UUIDString: self.uuidString!) else {
            return
        }
        
        guard let name = self.name else {
            return
        }
        
        let beaconRegion = CLBeaconRegion(proximityUUID: uuid, identifier: name)
        
        self.region = beaconRegion
        self.locationManager.startMonitoringForRegion(self.region)
    }
    
    private func loadManager() {
        self.locationManager = CLLocationManager()
        self.locationManager.delegate = self
        self.locationManager.requestAlwaysAuthorization()
    }
    
    private func loadCampaign() {
        dataSource.campaignInfo() { info in
            
            self.name = info.name
            self.uuidString = info.uuid
            
            self.loadManager()
            self.updateServices()
        }
    }
    
    private func updateServices() {
        dataSource.listServices() { services in
            self.availableServices = services
            self.didUpdateServices?(self)
            self.startMonitoring()
        }
    }
    
    private func scanningIsAuthorized() -> Bool {
        return CLLocationManager.authorizationStatus() == .AuthorizedAlways &&
                CLLocationManager.isMonitoringAvailableForClass(CLBeaconRegion.self) &&
                CLLocationManager.isRangingAvailable()
    }
    
    private func appInForeground() -> Bool {
        return UIApplication.sharedApplication().applicationState == .Active
    }
    
    private func getAvailableServiceByMajor(major: String, minor: String) -> Service? {
        for service in self.availableServices! {
            if service.major == major && service.minor == minor {
                return service
            }
        }
        
        return nil
    }
}