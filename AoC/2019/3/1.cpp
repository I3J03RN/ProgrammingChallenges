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

map<ii, int> visited;

char buffer[10010];

int mindist = numeric_limits<int>::max();

void test(ii p, int steps) {
    auto it = visited.find(p);
    if (it != visited.end()) {
        printf("found crossing: %d %d, %d\n", p.first, p.second,
               steps + it->second);
        mindist = min(mindist, steps + it->second);
    }
}

void a(ii p, int steps) {
    if (visited.find(p) == visited.end()) {
        visited[p] = steps;
    }
}

int main() {
    ii cords = {0, 0};
    int steps = 0;
    fgets(buffer, 10000, stdin);
    char* p = strtok(buffer, ",");
    do {
        char c;
        int l;
        sscanf(p, "%c%d", &c, &l);
        // printf("%c: %d\n", c, l);
        switch (c) {
            case 'D':
                FOR(i, 0, l) {
                    cords.second--;
                    steps++;
                    a(cords, steps);
                }
                break;
            case 'U':
                FOR(i, 0, l) {
                    cords.second++;
                    steps++;
                    a(cords, steps);
                }
                break;
            case 'R':
                FOR(i, 0, l) {
                    cords.first++;
                    steps++;
                    a(cords, steps);
                }
                break;
            case 'L':
                FOR(i, 0, l) {
                    cords.first--;
                    steps++;
                    a(cords, steps);
                }
                break;
        }
    } while ((p = strtok(NULL, ",")));
    printf("NEXT\n");
    cords = {0, 0};
    steps = 0;
    fgets(buffer, 10000, stdin);
    p = strtok(buffer, ",");
    do {
        char c;
        int l;
        sscanf(p, "%c%d", &c, &l);
        // printf("%c: %d\n", c, l);
        switch (c) {
            case 'D':
                FOR(i, 0, l) {
                    cords.second--;
                    steps++;
                    test(cords, steps);
                }
                break;
            case 'U':
                FOR(i, 0, l) {
                    cords.second++;
                    steps++;
                    test(cords, steps);
                }
                break;
            case 'R':
                FOR(i, 0, l) {
                    cords.first++;
                    steps++;
                    test(cords, steps);
                }
                break;
            case 'L':
                FOR(i, 0, l) {
                    cords.first--;
                    steps++;
                    test(cords, steps);
                }
                break;
        }
    } while ((p = strtok(NULL, ",")));
    printf("min: %d\n", mindist);
}
