#include <cmath>
#include <cstdio>
#include <limits>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<double> A(70000);

int N;

double solve(int mask) {
    if (A[mask] < numeric_limits<double>::max()) return A[mask];
    int i = 0;
    for (; !((1 << i) & mask); ++i)
        ;
    int tmask = mask & ~(1 << i);
    for (int j = i + 1; j < N * 2; ++j) {
        if ((1 << j) & mask)
            A[mask] =
                min(A[mask], solve(tmask & ~(1 << j)) + A[(1 << i) | (1 << j)]);
    }
    return A[mask];
}

int main() {
    int caseNr = 1;
    while (scanf("%d", &N), N) {
        A.assign(1 << (N * 2), numeric_limits<double>::max());
        vii v(N * 2);
        for (int i = 0; i < N * 2; ++i) {
            scanf(" %*s %d %d", &v[i].first, &v[i].second);
        }
        for (int i = 0; i < N * 2; ++i)
            for (int j = i + 1; j < N * 2; ++j) {
                A[(1 << i) | (1 << j)] =
                    hypot(v[i].first - v[j].first, v[i].second - v[j].second);
            }

        printf("Case %d: %.2lf\n", caseNr++, solve((1 << (N * 2)) - 1));
    }
}
