//
//  ViewController.swift
//  beta01
//
//  Created by Josef Dolezal on 07/11/15.
//  Copyright © 2015 Josef Dolezal. All rights reserved.
//

import UIKit
import CoreLocation

class ViewController: UIViewController, CLLocationManagerDelegate {
    
    let locationManager = CLLocationManager()
    let region = CLBeaconRegion(proximityUUID: NSUUID(UUIDString: "B0702880-A295-A8AB-F734-031A98A512DE")!, identifier: "Mac")
    let colors = [
        3289: UIColor.redColor()
    ]

    override func viewDidLoad() {
        super.viewDidLoad()
        locationManager.delegate = self
        
        if(CLLocationManager.authorizationStatus() != CLAuthorizationStatus.AuthorizedWhenInUse ) {
            locationManager.requestWhenInUseAuthorization()
        }
        
        locationManager.startRangingBeaconsInRegion(region)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func locationManager(manager: CLLocationManager, didRangeBeacons beacons: [CLBeacon], inRegion region: CLBeaconRegion) {
        let knownBeacons = beacons.filter{ $0.proximity != CLProximity.Unknown }
        if( knownBeacons.count > 0) {
            let closestBeacon = knownBeacons[0]
            view.backgroundColor = colors[closestBeacon.minor.integerValue]
        }
    }


}

