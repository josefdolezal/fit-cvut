//
//  ViewController.swift
//  bi-ios-tableview
//
//  Created by Dominik Vesely on 10/11/15.
//  Copyright © 2015 Ackee s.r.o. All rights reserved.
//

import UIKit
import Alamofire

struct POI {
    var name : String
    var link : String
}

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {

    @IBOutlet weak var tableView: UITableView!
    var array : [POI] = Array()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
       // tableView.registerClass(UITableViewCell.self, forHeaderFooterViewReuseIdentifier: "Cell2")
        
        // Musi se nastavit delegate i dataSource
        // Je potreba implementovat protokoly (datasource a delegate)
        tableView.delegate = self
        tableView.dataSource = self
        
        // Pokud ma tabulka footer, nedoplnuje na obrazovku prazdne radky
        tableView.tableFooterView = UIView()
        
        
        
        Alamofire.request(.GET, "https://private-anon-9901a264a-biioshomework2.apiary-mock.com/points")
            .responseJSON { response in
                print(response.request)  // original URL request
                print(response.response) // URL response
                print(response.data)     // server data
                print(response.result)   // result of response serialization
                
                if let JSON = response.result.value {
                    print("JSON: \(JSON)")
                    if let points = JSON["points"]! {
                        
                        for dict in (points as! [[String : AnyObject]] ) {
                            
                            let name = dict["name"] as! String
                            let link = dict["link"] as! String
                            
                           let poi = POI(name: name, link: link)
                            self.array.append(poi)
                        }
                        // Tabulka se muze nacist jete pred tim, nez probehne request
                        // data se musi nacist rucne
                        self.tableView.reloadData()
                    }
                }
        }
        
        
        
        print("ahoj")
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    
    ////MARK: tableview
    // Pocet sekci v tabulce (napr adresar ma 26 -> abeceda)
    // Neni potreba implemetovat, default je 1
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    // Pocet radku v sekci
    // V defaultu doplni obrazovku prazdnymi radky
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return array.count
    }
    
    //
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        // Identifier je nastaven ve storyboardu
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell")
        cell?.textLabel?.text = array[indexPath.row].name
        return cell!
        
    }
    
    func tableView(tableView: UITableView, didDeselectRowAtIndexPath indexPath: NSIndexPath) {
        print("Odesel sem z \(indexPath.row)")
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        print("Vybral jsem \(indexPath.row)")
    }
    
    func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Tabulka"
    }
    
    func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        return 80
    }


}

