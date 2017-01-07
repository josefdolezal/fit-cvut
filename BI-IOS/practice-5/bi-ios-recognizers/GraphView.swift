//
//  GraphView.swift
//  bi-ios-recognizers
//
//  Created by Dominik Vesely on 03/11/15.
//  Copyright © 2015 Ackee s.r.o. All rights reserved.
//

//

import Foundation
import UIKit

class GraphView : UIView {
    
    var graphRealPosition: CGPoint = CGPointMake(0, 0)
    
    var graphBeginPosition: CGPoint = CGPointMake(0, 0) {
        didSet {
            graphRealPosition = graphBeginPosition
            setNeedsDisplay()
        }
    }
    
    var tapPosition: CGPoint = CGPointMake(0, 0)
    
    var amplitude : CGFloat = 2.0 {
        didSet {
            setLabelText()
            setNeedsDisplay()
        }
    }
    
    var lineColor : UIColor = .redColor() {
        didSet {
            setNeedsDisplay()
        }
    }
    
    weak var label : UILabel!
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.backgroundColor = UIColor.lightGrayColor()
    
        print(CGRectGetHeight(self.bounds))
        
        let label = UILabel(frame: CGRectMake(10, 10, 150, 25))
        
        addSubview(label)
        self.label = label
        
        let panGesture = UIPanGestureRecognizer(target: self, action: "moveGraph:")
        addGestureRecognizer(panGesture)
        
        let doubleTap = UITapGestureRecognizer(target: self, action: "resetGraphPosition:")
        doubleTap.numberOfTapsRequired = 2
        addGestureRecognizer(doubleTap)
    }

    // Vola se pokazde, kdyz ma byt vykresleno view (klidne az 30fps)
    override func drawRect(rect: CGRect) {
        // Aktualni kontext - kam se kresli
        let context = UIGraphicsGetCurrentContext();
        
        // Nastaveni vlastnosti cary
        CGContextSetStrokeColorWithColor(context, lineColor.CGColor);
        CGContextSetLineWidth(context, 2);
        
        // Nastaveni pocatecniho bodu pro kresleni
        CGContextMoveToPoint(context, graphRealPosition.x, graphRealPosition.y);
        
        for (var i : CGFloat = 0; i < 900; i += 4) {
            CGContextAddLineToPoint(context, i + graphRealPosition.x, self.amplitude * 10 * sin(i) + graphRealPosition.y);
        }
        
        // Doposud se objekty ukladali do buffery, tato metoda je skutecne vykresli
        CGContextStrokePath(context);
        
    }
    
    func setLabelText() {
        label?.text = String(format: "Amplitude: %.2f", arguments: [amplitude])
    }
    
    // vyzadovana swiftem, ale neni nikdy volana
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    //MARK: Action
    func moveGraph(reco: UIGestureRecognizer) {
        let actualPosition = reco.locationInView(self)
        
        switch(reco.state) {
        case .Began:
            tapPosition = actualPosition
        case .Changed:
            graphRealPosition.x = graphBeginPosition.x + actualPosition.x - tapPosition.x
            graphRealPosition.y = graphBeginPosition.y + actualPosition.y - tapPosition.y
            setNeedsDisplay()
        case .Ended:
            graphBeginPosition = graphRealPosition
        default:
            return
        }
    }
    
    func resetGraphPosition(reco: UITapGestureRecognizer) {
        graphBeginPosition = CGPointMake(0, CGRectGetHeight(self.bounds) / 2.0)
    }

}
