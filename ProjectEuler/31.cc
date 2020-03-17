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

constexpr int goal = 200;

array<int, 8> coins = {1, 2, 5, 10, 20, 50, 100, 200};

int mem[goal + 1][coins.size()];

int ways(int type, int left) {
    if (left == 0) return 1;
    if (left < 0) return 0;
    if (type == coins.size()) return 0;
    if (mem[left][type] != -1)
        return mem[left][type];
    else
        return mem[left][type] =
                   ways(type, left - coins[type]) + ways(type + 1, left);
};

int main() {
    memset(mem, 0xff, sizeof(mem));
    cout << ways(0, goal) << endl;
    int counter = 0;
    for (auto& arr : mem) {
        cout << setw(5) << counter++ << ": ";
        for (int i : arr) cout << setw(5) << i << ' ';
        cout << '\n';
    }
    cout << ways(0, goal) << endl;
}
