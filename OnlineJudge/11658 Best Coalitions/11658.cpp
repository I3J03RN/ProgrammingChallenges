#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

int mem[10100][110];
int N, x, xShare;

int getMem(int p, int n) {
    if (n < 0) return 0;
    if (p < xShare) return 0;
    return mem[p][n];
}

int main() {
    vi shares;
    shares.reserve(110);
    while (scanf("%d %d", &N, &x), N) {
        shares.clear();
        shares.push_back(0);
        for (int i = 1; i <= N; ++i) {
            int t1, t2;
            scanf("%d.%d", &t1, &t2);
            if (i == x)
                xShare = t1 * 100 + t2;
            else
                shares.push_back(t1 * 100 + t2);
        }
        shares[0] = xShare;

        memset(mem, 0, sizeof(mem));
        int bestComb = 0;
        if (xShare >= 5000) {
            printf("100.00\n");
            continue;
        }
        // cout << "shares:\n";
        // for (int i : shares) cout << i << endl;
        for (int i = 0; i < N; ++i) mem[xShare][i] = 1;
        for (int p = xShare + 1; p <= 10000; ++p)
            for (int n = 1; n < N; ++n) {
                mem[p][n] = getMem(p, n - 1) || getMem(p - shares[n], n - 1);
                if (p > 5000 && mem[p][n]) {
                    bestComb = p;
                    goto end;
                }
            }
        for (int p = xShare; p <= 10000; ++p, printf("\n")) {
            printf("%5d: ", p);
            for (int n = 0; n + 1 < N; ++n) printf(" %d", mem[p][n]);
        }

    end:
        // printf("xShare: %d, bestComb: %d\n", xShare, bestComb);
        int tmp = round(xShare * 10000.0 / bestComb);
        printf("%d.%02d\n", tmp / 100, tmp % 100);
    }
}
