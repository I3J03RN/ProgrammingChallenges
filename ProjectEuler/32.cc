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

template <size_t N = 9>
bool isPandigital(initializer_list<int> nums) {
    static array<int, N> c;
    fill(c.begin(), c.end(), 0);
    for (int i : nums) {
        while (i > 0) {
            int rem = i % N;
            if (rem <= N && c[rem]++ > 0) return false;
        }
    }
    return true;
}

int main() {
    int num = 12345;
    cout << num << ": " << isPandigital({num}) << endl;
}
