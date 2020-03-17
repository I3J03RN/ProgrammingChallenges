#include <bits/stdc++.h>

#include "../intcode.hpp"
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

ll sum, x, y;
ll last = 0;

vii rows;

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }
    sum = 0;
    IntCodeInterpreter part1(
        programm,
        [](ll a) -> ll {
            assert(x >= 0 && y >= 0);
            if (a & 1) return y;
            return x;
        },
        [](ll out) -> void { last = out; }, false);
    auto test = [&](const ll xx, const ll yy) -> ll {
        x = xx;
        y = yy;
        part1.reset(programm);
        part1.run();
        return last;
    };
    for (int r = 0; r < 50; ++r) {
        int start, end = 0;
        for (int c = 0; c < 50; ++c) {
            sum += test(c, r);
        }
    }
    printf("part 1: %lld\n", sum);

    /* Part 2 */
    ll xx = 0;
    ll yy = 4;
    while (1) {
        // printf("y: %lld\n", yy);
        xx = 0;
        while (!test(xx, yy)) xx++;
        // x is now on the first beamtile

        while (test(xx + 99, yy)) {
            if (test(xx, yy + 99)) goto end;
            xx++;
        }
        yy++;
    }
end:

    printf("part 2: %lld\n", xx * 10000 + yy);
}
