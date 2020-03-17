#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

const int numMoveableField = 10000;

int coordIndexC;
map<ii, int> coordIndex;
vii coords(numMoveableField);

int getIndex(ii i) {
    auto it = coordIndex.find(i);
    if (it != coordIndex.end()) return it->second;
    coordIndex[i] = coordIndexC;
    coords[coordIndexC] = i;
    return coordIndexC++;
}

vvi adj(numMoveableField);
vector<char> special(numMoveableField, 0);

int numKeys = 0;

char buffer[1000];
char field[1000][1000];
char field2[1000][1000];

int n = 0, m;

vi startIndece;
array<int, 26> keys;
array<int, 26> doors;

array<array<int, 50>, 50> dists;

void insertEdge(int a, int b) { adj[a].push_back(b); }

ii operator+(ii a, ii b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

char& getField(ii i) { return field[i.first][i.second]; }

array<ii, 4> dirs = {make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0),
                     make_pair(0, -1)};

void buildAdjP(ii i) {
    int myIndex = getIndex(i);
    for (ii d : dirs)
        if (getField(i + d) != '#') insertEdge(myIndex, getIndex(i + d));
}

void buildAdj() {
    for (int r = 1; r < n; ++r) {
        for (int c = 1; c < m; ++c) {
            ii i = make_pair(r, c);
            char cur = getField(i);
            if (cur == '@') {
                special[getIndex(i)] = '@';
                startIndece.push_back(getIndex(i));
            }
            if ('A' <= cur && cur <= 'Z') {
                doors[cur - 'A'] = getIndex(i);
                special[getIndex(i)] = cur;
            }
            if ('a' <= cur && cur <= 'z') {
                keys[cur - 'a'] = getIndex(i);
                numKeys = max(numKeys, cur - 'a' + 1);
                // printf("i for %c: %d\n", cur, getIndex(i));
                special[getIndex(i)] = cur;
            }
            if (cur != '#') buildAdjP(i);
        }
    }
}

vi visited(numMoveableField, 0);

void calcDists(int start, int index) {
    queue<ii> q;
    fill(visited.begin(), visited.end(), 0);
    q.push({start, 0});
    visited[start] = 1;
    while (!q.empty()) {
        int v = q.front().first;
        int s = q.front().second;
        q.pop();
        char c = special[v];
        if ('a' <= c && c <= 'z') dists[index][c - 'a'] = s;
        if (c == '@')
            dists[index][find(startIndece.begin(), startIndece.end(), v) -
                         startIndece.begin() + 26] = s;
        s += 1;
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = 1;
                q.push({u, s});
            }
        }
    }
}

array<int, 26> preqs;

bool dfs(int v, int pre) {
    visited[v] = 1;
    bool ret = islower(special[v]);
    for (int u : adj[v]) {
        if (visited[u]) continue;
        char c = special[u];
        if (isupper(c)) {
            ret |= dfs(u, pre | 1 << (c - 'A'));
        } else if (islower(c)) {
            printf("%c: ", c);
            preqs[c - 'a'] = pre;
            for (int i = 0; i < numKeys; ++i)
                if (pre & (1 << i)) printf("%c ", 'A' + i);
            printf("\n");
            ret |= dfs(u, pre);
        } else
            ret |= dfs(u, pre);
    }
    if (ret)
        field2[coords[v].first][coords[v].second] =
            field[coords[v].first][coords[v].second];
    return ret;
}

map<ii, int> states;

int solve() {
    assert(startIndece.size() <= 4);
    // index, seen, dist
    auto cmp = [](const iii a, const iii b) -> bool {
        return get<2>(a) > get<2>(b);
    };
    priority_queue<iii, vector<iii>, decltype(cmp)> q(cmp);
    int start = 0;
    for (int i = 0; i < startIndece.size(); ++i) start |= (26 + i) << (i << 3);

    q.push({start, 0, 0});
    states[{start, 0}] = 0;
    while (!q.empty()) {
        auto [v, seen, dist] = q.top();
        q.pop();

        if (states[{v, seen}] != dist) continue;
        if (seen == (1 << numKeys) - 1) return dist;

        for (int i = 0, c = 1; i < numKeys; ++i, c <<= 1) {
            if ((seen & preqs[i]) == preqs[i] && !(c & seen)) {
                for (int j = 0; j < startIndece.size(); ++j) {
                    int node = (v >> (j << 3)) & 0xFF;
                    if (dists[node][i] != -1) {
                        int newi =
                            (i << (j << 3)) | (v & ~(0x000000FF << (j << 3)));
                        auto it = states.find({newi, seen | c});
                        if (it == states.end()) {
                            q.push({newi, seen | c, dist + dists[node][i]});
                            states[{newi, seen | c}] = dist + dists[node][i];
                        } else {
                            if (dist + dists[node][i] < it->second) {
                                q.push({newi, seen | c, dist + dists[node][i]});
                                states[{newi, seen | c}] =
                                    dist + dists[node][i];
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return -1;
};

int main() {
    while (1) {
        fgets(field[n++], 900, stdin);
        if (field[n - 1][0] == '\n') break;
    }
    n--;
    m = strlen(field[0]) - 1;
    memset(field2, ' ', sizeof(field2));
    buildAdj();
    // memset(field2, ' ', sizeof(field2));
    for (int startIndex : startIndece) dfs(startIndex, 0);
    for (auto& arr : dists) fill(arr.begin(), arr.end(), -1);

    for (char c = 'a'; c < 'a' + numKeys; ++c)
        calcDists(keys[c - 'a'], c - 'a');
    for (int i = 0; i < startIndece.size(); ++i)
        calcDists(startIndece[i], i + 26);
    printf("    ");
    for (char c = 'a'; c <= 'z'; ++c) printf("   %c", c);
    for (int i : startIndece) printf("   @");
    printf("\n");
    for (int r = 0; r < 26 + startIndece.size(); ++r) {
        auto& arr = dists[r];
        if (r < 26)
            printf("   %c", 'a' + r);
        else
            printf("   @");
        for (int c = 0; c < 26 + startIndece.size(); ++c) printf("%4d", arr[c]);
        printf("\n");
    }
    for (int r = 0; r < n; ++r, printf("\n"))
        for (int c = 0; c < m; ++c) printf("%c", field2[r][c]);

    printf("%d\n", solve());
}
