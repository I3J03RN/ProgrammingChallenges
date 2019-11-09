#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

vector<vi> A(12, vi(2048, -1));
vector<vi> dist(11, vi(11));
int N;

int tsp(int pos, int mask) {
    if ((1 << N) - 1 == mask) return dist[pos][0];
    if (A[pos][mask] != -1) return A[pos][mask];
    int minV = 100000000;
    for (int i = 0; i < N; ++i) {
        if (i != pos && !(mask & (1 << i)))
            minV = min(minV, dist[pos][i] + tsp(i, mask | (1 << i)));
    }
    return A[pos][mask] = minV;
}

int main() {
    int s;
    scanf("%d", &s);
    vi x(11);
    vi y(11);
    while (s--) {
        scanf("%*d %*d %d %d", &x[0], &y[0]);
        scanf("%d", &N);
        N++;
        for (int i = 0; i < N; ++i) {
            A[i].assign((1 << N), -1);
        }
        for (int i = 1; i < N; ++i) {
            scanf("%d %d", &x[i], &y[i]);
        }
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                dist[i][j] = dist[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            }
        printf("The shortest path has length %d\n", tsp(0, 1));
    }
}
