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

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }
    IntCodeInterpreter part1(
        programm, [](ll a) -> ll { return 1LL; },
        [](ll out) -> void { printf("%lld\n", out); });
    printf("part 1: ");
    part1.run();

    IntCodeInterpreter part2(
        programm, [](ll a) -> ll { return 2LL; },
        [](ll out) -> void { printf("%lld\n", out); });
    printf("part 2: ");
    part2.run();
}
