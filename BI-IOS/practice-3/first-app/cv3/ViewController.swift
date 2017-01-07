//
//  ViewController.swift
//  cv3
//
//  Created by Josef Dolezal on 20/10/15.
//  Copyright © 2015 Josef Dolezal. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UIWebViewDelegate, UIScrollViewDelegate {

    
    @IBOutlet weak var webView: UIWebView!
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // sitove requesty by mely pouzivat ssl, musi se upravit v plist
        let url = NSURL(string: "http://apple.com")
        
        webView.loadRequest(NSURLRequest(URL: url!))
        webView.delegate = self
        webView.scrollView.delegate = self
        webView.hidden = true
        
        let view = UIView(frame: CGRect(x: 30, y: 48, width: 200, height: 200))
        view.backgroundColor = UIColor.greenColor()
        view.alpha = 0.5
        view.layer.cornerRadius = 10
        view.layer.borderColor = UIColor.blackColor().CGColor
        view.layer.borderWidth = 3

        
        self.view.addSubview(view)
    }
    
    func webViewDidFinishLoad(webView: UIWebView) {
        print(webView.frame)
        print(webView.bounds)
    }
    
    func scrollViewDidScroll(scrollView: UIScrollView) {
        print(webView.frame)
        print(webView.bounds)
        
        print("------------")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
}

