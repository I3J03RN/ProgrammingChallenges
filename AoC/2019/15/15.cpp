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

char field[10000][10000];
bool visited[10000][10000];
ii pos(5000, 5000);

ii tl = pos;
ii br = pos;

int dir = 0;

int pc = 0;
int relativeBase = 0;

int lastMov;

bool backtrack;

const bool animation = false;

void display() {
    printf("pos: %d, %d\n", pos.first, pos.second);
    for (int r = tl.first; r <= br.first; ++r) {
        for (int c = tl.second; c <= br.second; ++c)
            if (r == pos.first && c == pos.second)
                printf("D");
            else
                printf("%c", field[r][c]);
        printf("\n");
    }
}

char getField(int dir) {
    ii rel = {0, 0};
    switch (dir) {
        case 1:
            rel.first--;
            break;
        case 2:
            rel.first++;
            break;
        case 4:
            rel.second++;
            break;
        case 3:
            rel.second--;
            break;
        default:
            printf("unknown dir %d\n", dir);
            break;
    }
    return field[rel.first + pos.first][rel.second + pos.second];
}

int rev(int dir) {
    if (dir & 1)
        return dir + 1;
    else
        return dir - 1;
}

stack<ii> moves;

bool getInput() {
    while (!moves.empty()) {
        int next = moves.top().second;
        if (next == 5) {
            if (moves.top().first == -1) return true;
            lastMov = rev(moves.top().first);
            moves.pop();
            backtrack = true;
            return false;
        }
        moves.top().second++;
        if (getField(next) == ' ') {
            lastMov = next;
            backtrack = false;
            return false;
        }
    }
    printf("empty\n");
    return true;
}

void paint(ll in) { field[pos.first][pos.second] = in ? '#' : '.'; }

void move(ll status) {
    ii old = pos;
    switch (lastMov) {
        case 1:
            pos.first--;
            break;
        case 2:
            pos.first++;
            break;
        case 4:
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
    if (status == 0) {
        field[pos.first][pos.second] = '#';
        pos = old;
        if (animation) {
            this_thread::sleep_for(chrono::milliseconds(10));

            system("clear");
            display();
        }
        return;
    }
    if (!backtrack) {
        moves.push({lastMov, 1});
        if (animation) {
            this_thread::sleep_for(chrono::milliseconds(10));
            system("clear");
            display();
        }
    }
    if (status == 1)
        field[pos.first][pos.second] = '.';
    else
        field[pos.first][pos.second] = '*';
}

int main() {
    memset(field, ' ', sizeof(field));
    memset(visited, 0, sizeof(visited));
    field[5000][5000] = '$';
    moves.push({-1, 1});
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }

    IntCodeInterpreter mazeFinder(
        programm,
        [](ll count) -> ll {
            if (getInput()) return numeric_limits<ll>::min();
            return lastMov;
        },
        [](ll out) -> void { move(out); });
    mazeFinder.run();
    display();

    ii star;
    int minutes;
    queue<pair<ii, int>> q;
    ii movess[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    q.push({{5000, 5000}, 0});
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        if (field[c.first.first][c.first.second] == '*') {
            printf("part 1: %d\n", c.second);
            star = c.first;
        }
        for (ii i : movess)
            if (!visited[c.first.first + i.first][c.first.second + i.second] &&
                field[c.first.first + i.first][c.first.second + i.second] !=
                    '#') {
                q.push({{c.first.first + i.first, c.first.second + i.second},
                        c.second + 1});
                visited[c.first.first + i.first][c.first.second + i.second] =
                    true;
            }
    }
    memset(visited, 0, sizeof(visited));
    q.push({star, 0});
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        minutes = c.second;
        for (ii i : movess)
            if (!visited[c.first.first + i.first][c.first.second + i.second] &&
                field[c.first.first + i.first][c.first.second + i.second] !=
                    '#') {
                q.push({{c.first.first + i.first, c.first.second + i.second},
                        c.second + 1});
                visited[c.first.first + i.first][c.first.second + i.second] =
                    true;
            }
    }
    printf("part 2: %d\n", minutes);
}
