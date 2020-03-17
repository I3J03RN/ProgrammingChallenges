#include <bits/stdc++.h>

#include "../intcode.hpp"
#include "programm.hh"
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
    IntCodeInterpreter textBasedRPG(
        programm, [](ll a) -> ll { return (ll)getchar(); },
        [](ll out) -> void {
            if (0 <= out && out < 128)
                putchar((char)out);
            else
                printf("non-ascii: %lld\n", out);
        });
    textBasedRPG.run();
}
