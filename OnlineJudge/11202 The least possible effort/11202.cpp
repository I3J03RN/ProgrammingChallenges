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
    int N;
    scanf("%d", &N);
    while (N--) {
        int x, y;
        scanf("%d %d", &x, &y);
        int result;
        if (x == y)
            result = ((x + 1) / 2 + 1) * ((x + 1) / 2) / 2;
        else
            result = (x + 1) / 2 * ((y + 1) / 2);
        printf("%d\n", result);
    }
}
