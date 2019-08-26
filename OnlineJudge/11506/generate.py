from random import *

n = 1000

while(n > 0):
    M = randrange(2, 51)
    W = randrange(0, 1001)
    Ms = list(range(2, M))
    shuffle(Ms)
    wires = set()
    while W > 0:
        a = randrange(1, M)
        b = randrange(a + 1, M + 1)
        if (a, b) not in wires:
            wires.add((a, b))
        W -= 1
        
    W = len(wires)
    
    print(M, W)

    for i in Ms:
        print(i, randrange(0, 100001))
    
    for i in wires:
        for x in i:
            print(x, end=" ")
        print(randrange(0, 100001))


    
    n -= 1

print("0 0")
