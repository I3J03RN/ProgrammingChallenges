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

char a[100];
char b[100];

unordered_map<string, int> orbits;
unordered_set<string> in0;

vvi adj(100000, vi());
// vi in(100000, 0);
vi visited(100000, 0);
int indexCounter = 0;

int getIndex(string a) {
    auto it = orbits.find(a);
    if (it == orbits.end())
        return orbits[a] = indexCounter++;
    else
        return it->second;
}

int main() {
    int y;
    int s;
    int totalOrbits = 0;
    while (scanf(" %3s)%3s", a, b) != EOF) {
        int i1 = getIndex(string(a));
        int i2 = getIndex(string(b));
        if (string(b) == "YOU") y = i2;
        if (string(b) == "SAN") s = i2;
        adj[i1].push_back(i2);
        adj[i2].push_back(i1);
        // in[i2] += 1;
    }
    // for (int i = 0; i < indexCounter; ++i) printf("%d\n", in[i]);
    queue<ii> q;
    // for (int i = 0; i < indexCounter; ++i)
    //     if (in[i] == 0) q.push({i, 0});
    q.push({y, 0});
    visited[y] = 1;
    while (!q.empty()) {
        ii v = q.front();
        q.pop();
        if (v.first == s) {
            printf("%d\n", v.second - 2);
        }
        // totalOrbits += v.second;
        for (int u : adj[v.first])
            if (visited[u] == 0) {
                q.push({u, v.second + 1});
                visited[u] = 1;
            }
    }

    printf("%d\n", totalOrbits);
}
