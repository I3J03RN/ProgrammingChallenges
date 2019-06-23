import sys

def solveSub(p):
    counter = 0;
    for i in p:
        if i < 0:
            counter += 1

    if counter == 1:
        pro1 = 1
        for i in range(len(p)):
            
    if counter & 1 == 0:
        return reduce((lambda x, y: x * y), p)


def solve(p):
    subsets = []
    startIndex = 0
    for i in range(len(p)):
        if p[i] == 0:
            subsets.append(p[startIndex:i])
            startIndex = i + 1
    if startIndex != len(p):
        subsets.append(p[startIndex:len(p)])

    print(subsets)

    
numbers = []

input = sys.stdin.readlines()

for s in input:
    numbers.extend(list(map(lambda s: int(s), s.rstrip("\n").split())))

problems = []
currentP = []
for i in numbers:
    if i == -999999:
        problems.append(currentP)
        currentP = []
    else:
        currentP.append(i)


for p in problems:
    print(solve(p))


    

