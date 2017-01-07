//
//  ViewController.swift
//  app-two
//
//  Created by Josef Dolezal on 27/10/15.
//  Copyright © 2015 Josef Dolezal. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var label: UILabel!
    @IBOutlet weak var segment: UISegmentedControl!
    /*override func loadView() {
        print("test");
        self.view = UIView();
    }*/
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        changeColor(segment)
        // segment.selectedSegmentIndex = 1
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func changeColor(sender: UISegmentedControl) {
        if sender.selectedSegmentIndex == 0 {
            view.backgroundColor = .redColor();
        } else {
            view.backgroundColor = .greenColor();
        }
        
        self.label.text = view.backgroundColor?.description
    }


}

