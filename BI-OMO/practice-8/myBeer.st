Object subclass: #Order

Instance Variables
  quantity	 Float  = 0.0 Description...
  termOfDelivery	 Date  Description...

Constraints
!
  quantity := aFloat! !
  ^termOfDelivery! !
  ^quantity! !
  termOfDelivery := aDate! !
  ^ self shouldBeImplemented! !
  "Initialize a newly created instance. This method must answer the receiver."
  super initialize.
  quantity := 0.0 "Float ".
  termOfDelivery := nil "optional Date ".
  ^self! !

Instance Variables
  name	 String  Description...
  unitPrice	 Float  Description...
  ordering	Order[*] constraint: single instance of this side of link. Description...

Constraints
	"#ordering navigates from: #Beer to: #Order"
!
  ^unitPrice! !
  name := aString! !
  ^name! !
  ^ordering ifNil:  [ ordering := Set new ]! !
  unitPrice := aFloat! !
  "Initialize a newly created instance. This method must answer the receiver."
  super initialize.
  name := nil "optional String ".
  unitPrice := nil "optional Float ".
  ordering := nil"default collection typeOrderedCollection new Order [*]".
  ^self! !