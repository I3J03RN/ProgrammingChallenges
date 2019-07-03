from random import randrange

m = 300  # randrange(1, 10)
n = 300  # randrange(1, 10)
q = 5

print(m, n, q)
for i in range(m):
    for j in range(n):
        print(randrange(1, 20), end=" ")
    print()

for i in range(q):
    print(
        randrange(1, m + 1),
        randrange(1, n + 1),
        randrange(1, m + 1),
        randrange(1, n + 1),
    )
