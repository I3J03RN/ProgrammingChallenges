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

bool asteroids[100][100] = {{0}};
char buffer[110];

int h = 0, w;
ii laser = {19, 23};

ii getSteps(int r, int c) {
    int g = gcd<int, int>(abs(laser.second - c), abs(laser.first - r));
    return ii((r - laser.first) / g, (c - laser.second) / g);
}

int main() {
    int num = 0;
    for (; fgets(buffer, 100, stdin); ++h) {
        w = strlen(buffer) - 1;
        for (int i = 0; i < w; ++i) {
            asteroids[h][i] = (buffer[i] == '#');
            if (asteroids[h][i]) num++;
        }
    }
    printf("height: %d, width: %d\n", h, w);
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) printf("%c", asteroids[r][c] ? '#' : '.');
        printf("\n");
    }
    int number = 1;
    vii steps;
    for (int i = 0; i < 36; ++i)
        for (int j = 0; j < 36; ++j) {
            if (i == laser.first && laser.second == j) continue;
            ii s = getSteps(i, j);
            if (find(steps.begin(), steps.end(), s) == steps.end())
                steps.push_back(s);
        }
    sort(steps.begin(), steps.end(), [](const ii& a, const ii& b) -> bool {
        return arg(complex<double>(a.first, a.second)) <
               arg(complex<double>(b.first, b.second));
    });
    reverse(steps.begin(), steps.end());
    for (ii i : steps) {
        printf("%d %d\n", i.first, i.second);
    }
    while (1) {
        for (ii s : steps)
            for (int tr = laser.first + s.first, tc = laser.second + s.second;
                 0 <= tr && tr < 36 && 0 <= tc && tc < 36;
                 tr += s.first, tc += s.second) {
                //  printf("%d %d\n", tr, tc);
                if (asteroids[tr][tc]) {
                    asteroids[tr][tc] = false;
                    printf("%d: %d\n", number++, tc * 100 + tr);
                    if (number == num) return 0;
                    break;
                }
            }
    }
}
