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

char field[1000][1000];

int rows, columns;

unordered_map<string, pair<ii, ii>> portals;

ii operator+(ii a, ii b) { return {a.first + b.first, a.second + b.second}; }

ii operator-(ii a, ii b) { return {a.first - b.first, a.second - b.second}; }

template <typename a, typename b>
ostream& operator<<(ostream& out, pair<a, b> i) {
    out << "(" << i.first << ", " << i.second << ')';
    return out;
}

char& getEntry(ii pos) { return field[pos.first][pos.second]; }

ii dirs[] = {make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0),
             make_pair(0, -1)};

string getPortalName(ii pos) {
    if (isupper(getEntry(pos - make_pair(1, 0))))
        return {getEntry(pos - make_pair(1, 0)), getEntry(pos)};
    if (isupper(getEntry(pos + make_pair(1, 0))))
        return {getEntry(pos), getEntry(pos + make_pair(1, 0))};
    if (isupper(getEntry(pos - make_pair(0, 1))))
        return {getEntry(pos - make_pair(0, 1)), getEntry(pos)};

    return {getEntry(pos), getEntry(pos + make_pair(0, 1))};
}

bool isOuter(ii i) {
    return i.first == 2 || i.second == 2 || i.first == rows - 3 ||
           i.second == columns - 3;
}

int main() {
    while (fgets(field[rows], 1000, stdin)) rows++;
    columns = strlen(field[0]);
    columns--;  // adjust for newlines
    // for (int r = 0; r < rows; ++r, printf("\n"))
    //     for (int c = 0; c < columns; ++c) printf("%c",
    //     field[r][c]);
    for (char a = 'A'; a <= 'Z'; ++a)
        for (char b = 'A'; b <= 'Z'; ++b)
            portals[{a, b}] = make_pair(make_pair(-1, -1), make_pair(-1, -1));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c) {
            ii i = {r, c};
            if (getEntry(i) == '.') {
                for (ii d : dirs) {
                    if (isupper(getEntry(i + d))) {
                        string portal = getPortalName(i + d);
                        auto& p = portals.find(portal)->second;
                        if (isOuter(i))
                            p.second = i;
                        else
                            p.first = i;
                    }
                }
            }
        }
    for (auto it = portals.begin(); it != portals.end(); ++it)
        if (it->second.second != make_pair(-1, -1) ||
            it->second.first != make_pair(-1, -1))
            cout << it->first << ": " << it->second.first << " --> "
                 << it->second.second << endl;

    ii start = portals.find("AA")->second.second;
    ii goal = portals.find("ZZ")->second.second;
    queue<tuple<ii, int, int>> q;
    q.push(make_tuple(start, 0, 0));
    set<pair<ii, int>> visited;
    visited.insert(make_pair(start, 0));
    while (!q.empty()) {
        auto [pos, dist, lvl] = q.front();
        q.pop();
        // cout << pos;
        // printf(": %d\n", dist);
        if (pos == goal && lvl == 0) {
            printf("part 2: %d\n", dist);
            break;
        }
        for (ii d : dirs) {
            if (isupper(getEntry(pos + d))) {
                auto portal = portals.find(getPortalName(pos + d))->second;
                if (isOuter(pos)) {
                    if (lvl > 0) {
                        ii to = portal.first;
                        if (to != make_pair(-1, -1) &&
                            visited.find(make_pair(to, lvl - 1)) ==
                                visited.end()) {
                            visited.insert(make_pair(to, lvl - 1));
                            q.push(make_tuple(to, dist + 1, lvl - 1));
                        }
                    }
                } else {
                    ii to = portal.second;
                    if (to != make_pair(-1, -1) &&
                        visited.find(make_pair(to, lvl + 1)) == visited.end()) {
                        visited.insert(make_pair(to, lvl + 1));
                        q.push(make_tuple(to, dist + 1, lvl + 1));
                    }
                }
            } else if (getEntry(pos + d) == '.') {
                if (visited.find(make_pair(pos + d, lvl)) == visited.end()) {
                    q.push(make_tuple(pos + d, dist + 1, lvl));
                    visited.insert(make_pair(pos + d, lvl));
                }
            }
        }
    }
}
