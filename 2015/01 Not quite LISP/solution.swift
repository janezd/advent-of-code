import Foundation

let fd = String(data: NSFileHandle.fileHandleWithStandardInput().availableData, encoding: NSASCIIStringEncoding)
var floor = 0
var first_basement : Int?
for (index, c) in fd!.characters.enumerate() {
    floor = floor + (c == "(" ? 1 : -1);
    if (floor < 0) && (first_basement == nil) {
        first_basement = index + 1
    }
}
print(floor)
print(first_basement!)
