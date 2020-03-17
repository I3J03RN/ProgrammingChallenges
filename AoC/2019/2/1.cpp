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

vector<ll> programm;
vector<ll> mem;

ll eval(int noun, int verb) {
    mem[1] = noun;
    mem[2] = verb;
    int p = 0;
    while (1) {
        switch (mem[p]) {
            case 1:
                mem[mem[p + 3]] = mem[mem[p + 1]] + mem[mem[p + 2]];
                p += 4;
                break;
            case 2:
                mem[mem[p + 3]] = mem[mem[p + 1]] * mem[mem[p + 2]];
                p += 4;
                break;
            case 99:
                return mem[0];
            default:
                return -1;
        }
    }
}

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }

    for (int n = 0; n < 100; ++n)
        for (int v = 0; v < 100; ++v) {
            mem = programm;
            if (eval(n, v) == 19690720) printf("n: %d, v: %d\n", n, v);
        }
}
