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

int potendDigitSum(int n, int exp = 5) {
    assert(n >= 0);
    int sum = 0;
    for (; n > 0; n /= 10) sum += pow(n % 10, exp);
    return sum;
}

int main() {
    int sum = 0;
    int counter = 1;
    for (int i = 2; i < 1e6; ++i) {
        if (i == potendDigitSum(i)) {
            cout << counter++ << ": " << i << endl;
            sum += i;
        }
    }
    cout << sum << endl;
}
