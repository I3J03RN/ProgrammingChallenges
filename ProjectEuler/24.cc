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
    array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 1; i < 1000000; ++i) next_permutation(arr.begin(), arr.end());
    for (int i : arr) cout << i;
    cout << endl;
}
