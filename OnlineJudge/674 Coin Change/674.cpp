#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

vi C = {50, 25, 10, 5, 1};

vector<vi> A(5, vi(10000, -1));

int value(int type, int v) {
    if (v < 0) return 0;
    if (v == 0) return 1;
    if (type == 5) return 0;

    if (A[type][v] != -1) return A[type][v];

    return A[type][v] = value(type + 1, v) + value(type, v - C[type]);
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) printf("%d\n", value(0, n));
}
