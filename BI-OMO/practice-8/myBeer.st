Object subclass: #Order	instanceVariableNames: 'quantity termOfDelivery'	classVariableNames: ''	poolDictionaries: ''	category: 'myBeer'!!Order commentStamp: '<historical>' prior: 0!Order.  The comment should state the purpose of the class and also explain any unobvious aspects of the implementation.

Instance Variables
  quantity	 Float  = 0.0 Description...
  termOfDelivery	 Date  Description...

Constraints
!!Order methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!quantity: aFloat
  quantity := aFloat! !!Order methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!termOfDelivery
  ^termOfDelivery! !!Order methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!quantity
  ^quantity! !!Order methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!termOfDelivery: aDate
  termOfDelivery := aDate! !!Order methodsFor: 'public' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!totalPrice
  ^ self shouldBeImplemented! !!Order methodsFor: 'initialize-release' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!initialize
  "Initialize a newly created instance. This method must answer the receiver."
  super initialize.
  quantity := 0.0 "Float ".
  termOfDelivery := nil "optional Date ".
  ^self! !Object subclass: #Beer	instanceVariableNames: 'name unitPrice ordering'	classVariableNames: ''	poolDictionaries: ''	category: 'myBeer'!!Beer commentStamp: '<historical>' prior: 0!Beer.  The comment should state the purpose of the class and also explain any unobvious aspects of the implementation.

Instance Variables
  name	 String  Description...
  unitPrice	 Float  Description...
  ordering	Order[*] constraint: single instance of this side of link. Description...

Constraints
	"#ordering navigates from: #Beer to: #Order"
!!Beer methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!unitPrice
  ^unitPrice! !!Beer methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!name: aString
  name := aString! !!Beer methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!name
  ^name! !!Beer methodsFor: 'accessing' stamp: 'Anonymous 11/30/2015 10:13'!ordering
  ^ordering ifNil:  [ ordering := Set new ]! !!Beer methodsFor: 'accessing' stamp: 'Uxf2Smalltalk 11/30/2015 9:45'!unitPrice: aFloat
  unitPrice := aFloat! !!Beer methodsFor: 'initialize-release' stamp: 'Anonymous 11/30/2015 10:12'!initialize
  "Initialize a newly created instance. This method must answer the receiver."
  super initialize.
  name := nil "optional String ".
  unitPrice := nil "optional Float ".
  ordering := nil"default collection typeOrderedCollection new Order [*]".
  ^self! !