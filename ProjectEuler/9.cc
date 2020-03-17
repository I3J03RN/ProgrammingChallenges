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
    for (int a = 1; a < 1000; ++a)
        for (int b = a + 1; b < 1000; ++b)
            for (int c = b + 1; c < 1000; ++c)
                if (a + b + c == 1000)
                    if (a * a + b * b == c * c) {
                        cout << a * b * c << endl;
                        return 0;
                    }
}
