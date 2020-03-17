#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

vvi pyramid;

char buffer[10000];

constexpr bool debug = false;

int main() {
    int t, cur = 0;
    while (scanf("%d", &t) != EOF) {
        if (cur == pyramid.size()) {
            pyramid.emplace_back();
            cur = 0;
        }
        pyramid.back().push_back(t);
        cur++;
    }

    viii edges;
    int counter = 0;
    for (int lvl = 1; lvl < pyramid.size(); ++lvl) {
        for (int i = 0; i < lvl; ++i, ++counter) {
            edges.emplace_back(counter, counter + lvl, pyramid[lvl - 1][i]);
            edges.emplace_back(counter, counter + lvl + 1, pyramid[lvl - 1][i]);
        }
    }
    int numVals = (pyramid.size() * (pyramid.size() + 1)) / 2;
    for (int i = 0; i < pyramid.size(); ++i, ++counter)
        edges.emplace_back(counter, numVals, pyramid.back().at(i));
    numVals++;

    if constexpr (debug)
        for (auto [from, to, dist] : edges)
            cout << from << " --> " << to << ": " << dist << '\n';

    vi dist(numVals, 0);
    for (int it = 1; it < dist.size(); ++it)
        for (auto [from, to, d] : edges)
            dist[to] = max(dist[to], dist[from] + d);
    cout << dist.back() << endl;
}
