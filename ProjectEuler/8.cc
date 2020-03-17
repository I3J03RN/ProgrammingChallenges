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

vi nums;

ll mult(int start) {
    ll ret = 1;
    for (int i = start; i < start + 13; ++i) {
        ret *= nums[i];
    }
    return ret;
}

int main() {
    char c;
    while (scanf(" %c", &c) != EOF) nums.push_back(c - '0');
    cout << nums.size() << endl;

    ll maxnum = -1;
    for (int l = 0; l + 12 < nums.size(); ++l) {
        maxnum = max(mult(l), maxnum);
    }
    cout << maxnum << endl;
}
