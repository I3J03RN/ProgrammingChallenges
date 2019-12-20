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

int adj[60][60];
int N, P;
int availableIn[15];
int diff[15];

int cumdiffs[1 << 13];

void calcAdj() {
    for (int k = 0; k <= N; ++k)
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= N; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void calcCumdiffs() {
    cumdiffs[0] = 0;
    int h = 0;
    for (int i = 1; i <= (1 << P) - 1; ++i) {
        if (i & (1 << (h + 1))) h++;
        cumdiffs[i] = cumdiffs[i ^ (1 << h)] + diff[h];
    }
}

struct entry {
    int node, seen, cost;
};

int visited[15][1 << 13];

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int roads;
        scanf("%d %d", &N, &roads);
        for (int r = 0; r <= N; ++r)
            for (int c = 0; c <= N; ++c) adj[r][c] = r == c ? 0 : 1000000;
        while (roads--) {
            int a, b, c1, c2;
            scanf("%d %d %d.%d", &a, &b, &c1, &c2);
            int cost = c1 * 100 + c2;
            if (adj[a][b] > cost) adj[a][b] = adj[b][a] = c1 * 100 + c2;
        }
        scanf("%d", &P);
        for (int i = 0; i < P; ++i) {
            int avai, c1, c2;
            scanf("%d %d.%d", &avai, &c1, &c2);
            availableIn[i] = avai;
            diff[i] = c1 * 100 + c2;
        }
        calcAdj();
        // printf("Adj:\n");
        // for (int r = 0; r <= N; ++r, printf("\n"))
        //     for (int c = 0; c <= N; ++c) printf("%5d ", adj[r][c]);
        calcCumdiffs();
        // for (int i = 0; i <= (1 << P) - 1; ++i)
        //     cout << bitset<12>(i) << ": " << cumdiffs[i] << '\n';
        for (int r = 0; r <= P + 1; r++)
            for (int i = 0; i <= (1 << P) - 1; ++i) visited[r][i] = 1000000;
        auto cmp = [](const entry& a, const entry& b) -> bool {
            return a.cost > b.cost;
        };
        priority_queue<entry, vector<entry>, decltype(cmp)> q(cmp);
        q.push({0, 0, 0});
        visited[0][0] = 0;
        int bestSeen = 0;
        int bestCost = 0;
        while (!q.empty()) {
            int n = q.top().node;
            int seen = q.top().seen;
            int cost = q.top().cost;
            q.pop();
            if (n == P + 1) {
                bestSeen = seen;
                bestCost = cost;
                break;
            }
            if (visited[P + 1][seen] < cost) continue;
            int index = n == 0 ? 0 : availableIn[n - 1];

            for (int i = 0; i < P; ++i) {
                if (!(seen & (1 << i)) && cost + adj[index][availableIn[i]] <
                                              visited[i + 1][seen | (1 << i)]) {
                    q.push({i + 1, seen | (1 << i),
                            cost + adj[index][availableIn[i]]});
                    visited[i + 1][seen | (1 << i)] =
                        cost + adj[index][availableIn[i]];
                }
            }
            if (cost + cumdiffs[(1 << P) - 1] - cumdiffs[seen] + adj[index][0] <
                visited[P + 1][seen]) {
                visited[P + 1][seen] = cost + cumdiffs[(1 << P) - 1] -
                                       cumdiffs[seen] + adj[index][0];
                q.push({P + 1, seen, visited[P + 1][seen]});
            }
        }
        // cout << bitset<12>(bestSeen) << ": " << bestCost << '\n';
        int saved = cumdiffs[(1 << P) - 1] - bestCost;
        if (saved > 0) {
            int c1 = saved / 100;
            int c2 = saved % 100;
            printf("Daniel can save $%d.%02d\n", c1, c2);
        } else
            printf("Don't leave the house\n");
    }
}
