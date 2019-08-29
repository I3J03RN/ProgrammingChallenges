from random import *

n = 1000

print(n)
print()

while(n > 0):
    rooms = randrange(1, 101)
    print(rooms)
    safeRoomsN = randrange(1, rooms + 1)
    print(safeRoomsN, end=" ")
    safeRooms = list(range(1, rooms + 1))
    shuffle(safeRooms)
    print(*safeRooms[:safeRoomsN])
    corridors = randrange(0, 1001)
    coors = set()
    while corridors > 0:
        a = randrange(1, rooms + 1)
        b = randrange(1, rooms + 1)
        if a != b and (a, b) not in coors and (b, a) not in coors:
            coors.add((a, b))
        corridors -= 1
    print(len(coors))
    for i in coors:
        for x in i:
            print(x, end=" ")
        print()


    print(randrange(1, 51))    
    print()
    
    n -= 1
