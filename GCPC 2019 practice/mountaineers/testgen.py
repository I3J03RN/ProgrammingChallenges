from random import randrange

m = 500  # randrange(10)
n = 500  # randrange(10)
q = 1000

print(m, n, q)
for i in range(m):
    for j in range(n):
        print(randrange(1, 1000000), end=" ")
    print()

for i in range(q):
    print(
        randrange(1, m + 1),
        randrange(1, n + 1),
        randrange(1, m + 1),
        randrange(1, n + 1),
    )
