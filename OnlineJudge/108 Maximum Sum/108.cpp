#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

int main() {
    int N;
    scanf("%d", &N);
    vector<vi> A(N, vi(N));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            int sum;
            scanf("%d", &sum);
            if (r > 0) sum += A[r - 1][c];
            if (c > 0) {
                sum += A[r][c - 1];
                if (r > 0) sum -= A[r - 1][c - 1];
            }
            A[r][c] = sum;
        }
    }

    int maxSum = A[0][0];
    for (int r1 = 0; r1 < N; ++r1)
        for (int c1 = 0; c1 < N; ++c1)
            for (int r2 = r1; r2 < N; ++r2)
                for (int c2 = c1; c2 < N; ++c2) {
                    int sum = A[r2][c2];
                    if (r1 > 0) sum -= A[r1 - 1][c2];
                    if (c1 > 0) {
                        sum -= A[r2][c1 - 1];
                        if (r1 > 0) sum += A[r1 - 1][c1 - 1];
                    }
                    maxSum = max(sum, maxSum);
                }
    printf("%d\n", maxSum);
}
