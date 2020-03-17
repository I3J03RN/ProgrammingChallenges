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

char prog[] =
    "A,B,B,A,B,C,A,C,B,C\n"
    "L,4,L,6,L,8,L,12\n"
    "L,8,R,12,L,12\n"
    "R,12,L,6,L,6,L,8\n"
    "n\n";

int newlines = -6;
const int maxl = 52;

int input = 2;  // 1;
int pc = 0;
int relativeBase = 0;

vector<vector<char>> field(1);

bool isScaffolding(int r, int c) {
    if (0 <= r && r < field.size()) {
        if (0 <= c && c < field[r].size())
            if (field[r][c] == '#' || field[r][c] == '<' ||
                field[r][c] == '>' || field[r][c] == 'v' || field[r][c] == '^')
                return true;
    }
    return false;
}

bool isIntersection(int r, int c) {
    return isScaffolding(r, c) && isScaffolding(r - 1, c) &&
           isScaffolding(r + 1, c) && isScaffolding(r, c - 1) &&
           isScaffolding(r, c + 1);
}

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }

    IntCodeInterpreter part1(
        programm,
        [](ll count) -> ll {
            assert(false);
            return 0;
        },
        [](ll out) -> void {
            char c = (char)out;
            if (c == '\n')
                field.push_back(vector<char>());
            else
                field.back().push_back(c);
        });
    part1.run();
    ll sum = 0;
    for (int r = 0; r < field.size(); ++r) {
        for (int c = 0; c < field[r].size(); ++c)
            if (isIntersection(r, c)) sum += r * c;
    }
    printf("part 1: %lld\n", sum);

    IntCodeInterpreter part2(
        programm, [](ll count) -> ll { return (ll)prog[count]; },
        [](ll out) -> void {
            if (out > 127) printf("part 2: %lld\n", out);
        });
    part2.modifyMemory(0) = 2;
    part2.run();
}
