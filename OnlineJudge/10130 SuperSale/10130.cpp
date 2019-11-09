#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int NINF = -1000000;

vector<vi> A(1000, vi(31000, NINF));
// first is weight, second is profit
vii I(1000);
int N;  // Number of Items

int value(int id, int avaiW) {
    if (avaiW < 0) return NINF;
    if (avaiW == 0 || id == N) return 0;
    if (A[id][avaiW] > 0) return A[id][avaiW];
    return A[id][avaiW] =
               max(value(id + 1, avaiW),
                   value(id + 1, avaiW - I[id].second) + I[id].first);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) scanf("%d %d", &I[i].first, &I[i].second);
        for (int n = 0; n < N; ++n) A[n].assign(N * 30 + 100, NINF);
        int G;
        scanf("%d", &G);
        int sum = 0;
        while (G--) {
            int W;
            scanf("%d", &W);
            sum += value(0, W);
            //            printf("\n");
        }
        printf("%d\n", sum);
    }
}
