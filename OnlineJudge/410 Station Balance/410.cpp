#include <algorithm>
#include <cstdio>

using namespace std;

int obj[10];
int C, S;

double imbalance() {
    double a = 0;
    for (int i = 0; i < 2 * C; ++i) {
        a += obj[i];
    }
    a /= (double)C;
    double im = 0;
    for (int i = 0; i < C; ++i) {
        im += abs(obj[i] + obj[2 * C - i - 1] - a);
    }
    return im;
}

int main() {
    int Set = 1;
    while (scanf("%d %d", &C, &S) != EOF) {
        for (int i = 0; i < 2 * C; ++i) {
            if (i < S)
                scanf("%d", obj + i);
            else
                obj[i] = 0;
        }
        sort(obj, obj + 2 * C);
        printf("Set #%d\n", Set++);
        for (int i = 0; i < C; i++) {
            printf(" %d:", i);
            if (obj[i] != 0) printf(" %d", obj[i]);
            if (obj[2 * C - i - 1]) printf(" %d", obj[2 * C - 1 - i]);
            printf("\n");
        }
        printf("IMBALANCE = %.5lf\n\n", imbalance());
    }
}
