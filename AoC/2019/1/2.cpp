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

int main() {
    ll sum = 0;
    ll t;
    while (scanf("%lld", &t) != EOF) {
        while (1) {
            t = t / 3 - 2;
            if (t > 0)
                sum += t;
            else
                break;
        }
    }
    printf("%lld\n", sum);
}
