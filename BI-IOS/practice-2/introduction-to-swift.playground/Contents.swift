

var x: String = "Testovací string"
var y = "String" // typová inference - vytváří typ proměnné během kompilování
var i = 3

let myConst = "ImmutableString" // definování konstanty

// KOLEKCE

let array: [String] = [ "S1", "S2", "S3" ] // definování pole
let dict: [String:[String]] = [ "bi-ios" : [ "Strudent 1 ", "Strudent 2" ] ] // definování dictionary - slovníku

var names = dict["bi-ios"] // optional values

print( names )  // optional value
print( names! ) // vykřičník unwrapuje optional value

if let safeNames = names { // rozbaluje proměnnou optional - stane se jen pokud proměnná neni nil
    print( safeNames )
}

let str: String? = "Maybe" // definování optional value

print( str?.lowercaseString) // optional chaining - fce se vykoná jen pokud proměnná neni nil

// CYKLY
for ( var i = 0; i < array.count; i++ ) {
    print( array[i] )
}

for name in array { // foreach
    print(name)
}

for _ in 1...5 { // _ znamená, že nedostanu žádnou hodnotu od foreache, ... znamená vč.
    var x = "5x ahoj"
}

for _ in 1..<5 { // _ znamená, že nedostanu žádnou hodnotu od foreache, ..< není vč.
                 // range může být tvořen i z proměnných
    var x = "4x ahoj"
}

// NTICE
var tuple = ( 1, 1, "Str" )
tuple.0 = 2

// SWITCH
let somePoint = (1, 1)
switch somePoint {
case (0, 0):
    print("(0, 0) is at the origin")
    // fallthrough -> explicitně vyžaduji pokračování switch u další podmínky - nepoužívám break (opak oproti c++)
case (_, 0): // nezajímá mě první hodnota
    print("(\(somePoint.0), 0) is on the x-axis")
case (0, _):
    print("(0, \(somePoint.1)) is on the y-axis")
case (-2...2, -2...2): //range pro obě proměnné touplu
    print("(\(somePoint.0), \(somePoint.1)) is inside the box")
default:
    print("(\(somePoint.0), \(somePoint.1)) is outside of the box")
}

// SWITCH S WHERE
let yetAnotherPoint = (1, -1)
switch yetAnotherPoint {
case let (_, y) where y == 0: // mohu i vynechat jednu z hodnot
    print( "y je 0" )
case let (x, y) where x == y:
    print("(\(x), \(y)) is on the line x == y")
case let (x, y) where x == -y:
    print("(\(x), \(y)) is on the line x == -y")
case let (x, y):
    print("(\(x), \(y)) is just some arbitrary point")
}

// functions

// free function - neni obsažená v žádné třídě (globální funkce)
func myAction( i : Int ) {
    print(i)
}

myAction( 3 )

func newAction( externalName i : Int ) -> Int {
    print( i )
    return 5
}

newAction( externalName: 3 )

class A {
    func addTwoNumbers( a: Int, plus b: Int ) -> Int {
        return a + b;
    }
}

A().addTwoNumbers( 4, plus: 2 )

// closures -> nepojmenované funkce
