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

set<ii> paintedFields;

char field[10000][10000];
ii pos(5000, 5000);

ii tl = pos;
ii br = pos;

int dir = 0;

void paint(ll in) { field[pos.first][pos.second] = in ? '#' : '.'; }

void move(ll in) {
    dir = (dir + 4 + (in ? 1 : -1)) % 4;
    switch (dir) {
        case 0:
            pos.first--;
            break;
        case 2:
            pos.first++;
            break;
        case 1:
            pos.second++;
            break;
        case 3:
            pos.second--;
            break;
        default:
            printf("unknown dir %d\n", dir);
            break;
    }
    tl.first = min(tl.first, pos.first);
    tl.second = min(tl.second, pos.second);

    br.first = max(br.first, pos.first);
    br.second = max(br.second, pos.second);
}

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }

    memset(field, '.', sizeof(field));
    IntCodeInterpreter part1(
        programm,
        [](ll count) -> ll {
            return field[pos.first][pos.second] == '.' ? 0 : 1;
        },
        [](ll out) -> void {
            static bool paintp = true;
            if (paintp) {
                paintedFields.insert(pos);
                paint(out);
            } else
                move(out);
            paintp = !paintp;
        });
    part1.run();
    printf("part 1: %lu\n", paintedFields.size());

    dir = 0;
    pos = tl = br = make_pair<ll, ll>(5000, 5000);
    memset(field, '.', sizeof(field));
    field[5000][5000] = '#';
    IntCodeInterpreter part2(
        programm,
        [](ll count) -> ll {
            return field[pos.first][pos.second] == '.' ? 0 : 1;
        },
        [](ll out) -> void {
            static bool paintp = true;
            if (paintp)
                paint(out);
            else
                move(out);
            paintp = !paintp;
        });

    part2.run();

    printf("part 2:\n");
    for (int r = tl.first; r <= br.first; ++r) {
        for (int c = tl.second; c <= br.second; ++c) printf("%c", field[r][c]);
        printf("\n");
    }
}
