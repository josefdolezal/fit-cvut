//
//  PanelView.swift
//  bi-ios-recognizers
//
//  Created by Dominik Vesely on 03/11/15.
//  Copyright © 2015 Ackee s.r.o. All rights reserved.
//

import Foundation
import UIKit

class PanelView : UIView {
    
    var delegate : PanelViewDelegate?
    
    // closure, anonymni funkce
    var onSliderChange : ((CGFloat) -> ())?
    
    var syncValue : Double = 0 {
        didSet {
            if !uswitch.on {
                syncValue = oldValue
            }
            
            slider.value  = Float(syncValue)
            stepper.value = syncValue
        }
    }
    
    weak var slider : UISlider!
    weak var stepper : UIStepper!
    weak var uswitch : UISwitch!
    weak var segment : UISegmentedControl!
    
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        backgroundColor = UIColor.lightGrayColor()
        
        let slider = UISlider()
        slider.minimumValue = 0
        slider.maximumValue = 15
        slider.addTarget(self, action: "sliderChanged:", forControlEvents: UIControlEvents.ValueChanged)
        
        addSubview(slider)
        self.slider = slider
        
        let stepper = UIStepper()
        stepper.minimumValue = 0;
        stepper.maximumValue = 15;
        stepper.stepValue = 0.5;
        stepper.addTarget(self, action: "stepperChanged:", forControlEvents: UIControlEvents.ValueChanged)
       
        addSubview(stepper)
        self.stepper = stepper
        
        let uswitch = UISwitch()
        uswitch.setOn(true, animated: false)
        
        addSubview( uswitch )
        self.uswitch = uswitch
        
        let segment = UISegmentedControl(items: ["Red", "Green", "Blue"])
        segment.selectedSegmentIndex = 0
        segment.addTarget(self, action: "colorChanged:", forControlEvents: .ValueChanged );
        
        addSubview(segment)
        self.segment = segment
        
        // Automaticky se spusti, vola funkci fireTimer na self
        let timer = NSTimer.scheduledTimerWithTimeInterval(1/30, target: self, selector: "fireTimer:", userInfo: nil, repeats: true)
        //timer.performSelector("invalidate", withObject: nil, afterDelay: 5)
        
        // nelze volat selector (protoze nebere argument) -> musim si udelat vlastni metodu
        // po 5 vterinach zavola invalidateTimer
        self.performSelector("invalidateTimer:", withObject: timer, afterDelay: 5)
    }
    
    // Nastavuje natvrdo velikost views
    override func layoutSubviews() {
        super.layoutSubviews()
        
        self.uswitch.frame = CGRectMake(8, 8, CGRectGetWidth(self.bounds) - 16, 44)
        self.segment.frame = CGRectMake(CGRectGetWidth(self.bounds) - 8 - CGRectGetWidth(segment.bounds), 8, 140, 30)
        
        self.stepper.frame = CGRectMake(CGRectGetWidth(slider.bounds) + 16, 59, CGRectGetWidth(self.bounds), 44)
        self.slider.frame = CGRectMake(8, 8+44, CGRectGetWidth(self.bounds) - CGRectGetWidth(stepper.bounds) - 24, 44)
    }
    
    
    func invalidateTimer(timer: NSTimer) {
        timer.invalidate()
    }
    
    
    //MARK: Action
    func fireTimer(timer:NSTimer) {
        syncValue = Double(self.slider.value + 0.01)
        delegate?.syncedValueChanged(syncValue, panel: self)
    }
    
    
    func sliderChanged(slider : UISlider) {
        syncValue = Double(slider.value)
        delegate?.syncedValueChanged(syncValue, panel: self)
    }
    
    func stepperChanged(stepper: UIStepper) {
        syncValue = stepper.value
        delegate?.syncedValueChanged(syncValue, panel: self)
    }
    
    func colorChanged(segment: UISegmentedControl) {
        let color : [UIColor] = [ .redColor(), .greenColor(), .blueColor() ]
        
        if segment.selectedSegmentIndex < color.count {
            delegate?.selectedColorChanged(color[segment.selectedSegmentIndex], panel: self)
            return
        }
        
        delegate?.selectedColorChanged(.blackColor(), panel: self)
    }
    
    
    // Kvuli prepisovani initializeru
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

}

protocol PanelViewDelegate {
    func syncedValueChanged(syncedValue : Double, panel: PanelView)
    func selectedColorChanged(color: UIColor, panel: PanelView )
}
