#include <cstdio>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi price(1100);
vector<vi> cost(110, vi(1100));
vector<vii> adj(1100);

struct node {
    int city;
    int fuel;
    int cost;
};

int N, M;

int dji(int s, int e, int c) {
    for (int i = 0; i <= c; i++) {
        cost[i].assign(N, numeric_limits<int>::max());
    }

    auto cmp = [](const node& a, const node& b) -> bool {
        return a.cost > b.cost;
    };
    priority_queue<node, vector<node>, decltype(cmp)> q(cmp);
    q.push({s, 0, 0});
    cost[0][s] = 0;
    while (!q.empty()) {
        node n = q.top();
        q.pop();
        // printf("city: %d, fuel: %d, price: %d\n", n.city, n.fuel, n.cost);
        if (n.city == e) return n.cost;
        if (cost[n.fuel][n.city] < n.cost) continue;
        // printf("-city: %d, fuel: %d, price: %d\n", n.city, n.fuel, n.cost);
        if (n.fuel + 1 <= c &&
            cost[n.fuel + 1][n.city] > n.cost + price[n.city]) {
            cost[n.fuel + 1][n.city] = n.cost + price[n.city];
            q.push({n.city, n.fuel + 1, n.cost + price[n.city]});
        }
        for (ii v : adj[n.city]) {
            if (v.second <= n.fuel &&
                cost[n.fuel - v.second][v.first] > n.cost) {
                cost[n.fuel - v.second][v.first] = n.cost;
                q.push({v.first, n.fuel - v.second, n.cost});
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        price[i] = t;
    }
    while (M--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    // for (ii i : adj[159]) {
    //     printf("159 -- %d: %d\n", i.first, i.second);
    // }
    // for (ii i : adj[264]) {
    //     printf("264 -- %d: %d\n", i.first, i.second);
    // }

    int q;
    scanf("%d", &q);
    while (q--) {
        int capacity, start, end;
        scanf("%d %d %d", &capacity, &start, &end);
        int result = dji(start, end, capacity);
        if (result == -1)
            printf("impossible\n");
        else
            printf("%d\n", result);
    }
}
