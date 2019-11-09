#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int UNVISITED = -1;

vector<vi> adj_list(3000);
vi dfs_num, dfs_low, S, visited;
int dfsCounter, numSCC;

void scc(int v) {
    dfs_num[v] = dfs_low[v] = dfsCounter++;
    S.push_back(v);
    visited[v] = 1;
    for (int j : adj_list[v]) {
        if (dfs_num[j] == UNVISITED) scc(j);
        if (visited[j]) dfs_low[v] = min(dfs_low[j], dfs_low[v]);
    }
    if (dfs_num[v] == dfs_low[v]) {
        numSCC++;
        while (1) {
            int u = S.back();
            S.pop_back();
            visited[u] = 0;
            if (u == v) break;
        }
    }
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M), N) {
        for (int i = 0; i < N; ++i) adj_list[i].clear();
        while (M--) {
            int a, b, p;
            scanf("%d %d %d", &a, &b, &p);
            a--;
            b--;
            adj_list[a].push_back(b);
            if (p == 2) adj_list[b].push_back(a);
        }
        dfs_num.assign(N, UNVISITED);
        dfs_low.assign(N, 0);
        visited.assign(N, 0);
        dfsCounter = numSCC = 0;
        for (int i = 0; i < N; ++i)
            if (dfs_num[i] == UNVISITED) scc(i);
        printf("%d\n", numSCC == 1 ? 1 : 0);
    }
}
