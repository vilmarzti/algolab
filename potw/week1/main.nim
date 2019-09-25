import strutils as str
import strformat

var input: string = readLine(stdin)
var num: int = str.parseInt(input)

proc lineToseq(s: string): seq[int] = 
    var split: seq[string] = splitWhitespace(s)
    var sequence: seq[int]
    for str_int in split:
        var i = str.parseInt(str_int)
        sequence.add(i)
    result = sequence


    

proc testcase(): bool =
    # read setup lines
    input = readLine(stdin)
    var nums = splitWhitespace(input)
    var goal = str.parseInt(nums[1])

    # read line and convert into sequence
    input = readLine(stdin)
    var sequence = lineToseq(input)

    # create prefix Sums
    var pSums: seq[int]
    for i in 0..<sequence.len:
        if i == 0:
            pSums.add(sequence[i])
        else:
            pSums.add(pSums[i-1] + sequence[i])
    
    var
        i= 0
        j = 1
        val: int
        higher: int
        lower: int
        best_i: int = 0
        best_j: int = 0
        best_val = high(int)
    
    while i<j and j<sequence.len:
        higher =  pSums[j-1]
        lower = if i == 0: 0 else: pSums[i]
        
        val = higher - lower

        if abs(val-goal) < abs(best_val-goal):
            best_val = val
            best_i = i
            best_j = j
        

        if val == goal:
            if i == 0:
                echo(fmt"{i} {j - 1}")
            else:
                echo(fmt"{i + 1} {j - 1}")
            return
        elif val > goal:
            i += 1
        elif val < goal:
            j += 1
        
    
    echo(fmt"test {best_i} {best_j}")
        

for i in 0..<num:
    discard testcase()


