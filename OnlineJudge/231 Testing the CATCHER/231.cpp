#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (b) < (c); ++(c))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).begin; ++(a))

int main() {
    vi array;
    int test = 1;
    while (1) {
        int first;
        array.clear();
        scanf("%d", &first);
        if (first == -1) break;
        array.push_back(first);
        int t;
        while (scanf("%d", &t), t != -1) array.push_back(t);
        vi dp;
        dp.reserve(array.size());
        for (auto it = array.rbegin(); it != array.rend(); ++it) {
            int insertIndex =
                lower_bound(dp.begin(), dp.end(), *it) - dp.begin();
            if (insertIndex == dp.size())
                dp.push_back(*it);
            else
                dp[insertIndex] = *it;
        }
        if (test > 1) printf("\n");
        printf("Test #%d:\n  maximum possible interceptions: %d\n", test++,
               (int)dp.size());
    }
}
