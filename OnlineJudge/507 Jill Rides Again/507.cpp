#include <cstdio>

using namespace std;

int main() {
    int b;
    int route = 1;
    scanf("%d", &b);
    while (b--) {
        int s;
        scanf("%d", &s);
        int bestStart = -1;
        int bestEnd = -1;
        int bestSum = -1;
        int sum = 0;
        int start = 1;
        int end = 1;
        for (int i = 2; i <= s; ++i) {
            int t;
            scanf("%d", &t);
            if (sum + t >= 0) {
                sum += t;
                end = i;
                if (sum > bestSum) {
                    bestStart = start;
                    bestEnd = end;
                    bestSum = sum;
                } else if (sum == bestSum &&
                           end - start > bestEnd - bestStart) {
                    bestStart = start;
                    bestEnd = end;
                    bestSum = sum;
                }
            } else {
                start = i;
                sum = 0;
            }
        }
        if (bestSum == -1) {
            printf("Route %d has no nice parts\n", route++);
        } else {
            printf("The nicest part of route %d is between stops %d and %d\n",
                   route++, bestStart, bestEnd);
        }
    }
}
