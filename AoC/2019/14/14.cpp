#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

char buffer[1010];

vi inR(1000, 0);
vi rightAmount(1000, 0);
vi needed(1000, 0);

vvii adj(1000);

map<string, int> indexMap;
int indexCount = 0;

int getIndex(const string s) {
    auto it = indexMap.find(s);
    if (it == indexMap.end()) {
        indexMap[s] = indexCount++;
        return indexCount - 1;
    }
    return it->second;
}

char target[110];

ll oreAmount(ll fuel) {
    int fuelIndex = getIndex("FUEL");
    int oreIndex = getIndex("ORE");
    needed.assign(1000, 0);
    needed[fuelIndex] = fuel;
    vi in = inR;
    queue<int> q;
    q.push(fuelIndex);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == oreIndex) {
            return needed[oreIndex];
            break;
        }
        ll times = needed[cur] / rightAmount[cur];
        if (needed[cur] % rightAmount[cur] != 0) times++;
        for (ii v : adj[cur]) {
            needed[v.first] += times * v.second;
            if (v.first == oreIndex && needed[oreIndex] > 1000000000000L)
                return -1;
            if (!--in[v.first]) q.push(v.first);
        }
    }
    return -1;
}

int main() {
    while (1) {
        fgets(buffer, 1000, stdin);
        if (buffer[0] == '.') break;
        string line(buffer);
        int eq = line.find("=>");
        string part1 = line.substr(0, eq - 1);
        string part2 = line.substr(eq + 3);
        part2.pop_back();
        int amount, targetIndex;
        sscanf(part2.c_str(), "%d %100s", &amount, target);
        targetIndex = getIndex(target);
        rightAmount[targetIndex] = amount;
        regex re(",");
        regex_token_iterator<string::iterator> it(part1.begin(), part1.end(),
                                                  re, -1);
        regex_token_iterator<string::iterator> en;
        for (; it != en; it++) {
            sscanf((*it).str().c_str(), "%d %100s", &amount, target);
            int iindex = getIndex(target);
            inR[iindex]++;
            adj[targetIndex].push_back({iindex, amount});
        }
    }
    ll l = 1;
    ll r = 100000000;
    while (l != r) {
        ll lr = (l + r) / 2 + 1;
        if (oreAmount(lr) != -1)
            l = lr;
        else
            r = lr - 1;
    }
    printf("max: %lld\n", l);
}
