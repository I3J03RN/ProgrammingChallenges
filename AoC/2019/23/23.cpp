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

ll lastNATY = numeric_limits<ll>::min();
ll NATX = -1;
ll NATY = -1337;

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }
    bitset<50> idle(false);
    array<queue<ll>, 50> qs;
    array<ll, 50> adr;
    array<ll, 50> c;
    fill(c.begin(), c.end(), 0LL);
    array<ll, 50> x;
    vector<IntCodeInterpreter> interpreters;
    for (int i = 0; i < 50; ++i) {
        qs[i].push(i);
        interpreters.emplace_back(
            programm,
            [&, i](ll a) -> ll {
                if (qs[i].empty()) {
                    idle[i] = true;
                    return -1;
                }
                idle[i] = false;
                ll ret = qs[i].front();
                qs[i].pop();
                return ret;
            },
            [&, i](ll out) -> void {
                if (c[i] == 0) adr[i] = out;
                if (c[i] == 1) x[i] = out;
                if (c[i] == 2) {
                    if (0 <= adr[i] && adr[i] < 50) {
                        // printf("sent package (%lld, %lld) to %lld\n", x[i],
                        // out,
                        //        adr[i]);
                        qs[adr[i]].push(x[i]);
                        qs[adr[i]].push(out);
                    } else if (adr[i] == 255) {
                        NATX = x[i];
                        NATY = out;
                        printf("New NAT: (%lld, %lld)\n", NATX, NATY);
                    } else
                        printf("%lld: %lld\n", adr[i], out);
                }
                c[i] = (c[i] + 1) % 3;
            });
    }
    bitset<50> halted(false);

    int idleC = 0;
    while (!halted.all()) {
        // for (int i = 0; i < 50; ++i)
        //     printf("queue %d size: %lu and front: %lld\n", i, qs[i].size(),
        //            qs[i].empty() ? -1 : qs[i].front());
        if (idle.all()) {
            idleC++;
            if (idleC > 1000) {
                printf("Sending NAT: (%lld, %lld)\n", NATX, NATY);
                qs[0].push(NATX);
                qs[0].push(NATY);
                if (NATY == lastNATY) {
                    printf("part 2: %lld\n", lastNATY);
                    return 0;
                }
                lastNATY = NATY;
                idleC = 0;
            }
        } else
            idleC = 0;

        for (int i = 0; i < 50; ++i) halted[i] = !interpreters[i].eval();
    }
}
