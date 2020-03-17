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

bitset<2000001> isPrime;

int main() {
    isPrime.set();
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i < isPrime.size(); ++i) {
        if (isPrime[i])
            for (int j = i + i; j < isPrime.size(); j += i) isPrime[j] = false;
    }

    int m = 0, ma = 0, mb = 0;
    for (int a = -999; a < 1000; ++a)
        for (int b = -1000; b <= 1000; ++b) {
            int count = 0;
            for (int n = 0;
                 n * n + a * n + b >= 0 && isPrime[n * n + a * n + b]; ++n)
                ++count;

            if (count > m) {
                m = count;
                ma = a;
                mb = b;
            }
        }
    cout << ma * mb << endl;
}
