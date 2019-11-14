#include <cstdio>
#include <limits>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int V, E;
vector<vii> adj(1100);

const int INF = 10000000;

int main() {
    int c;
    scanf("%d", &c);
    while (c--) {
        scanf("%d %d", &V, &E);
        for (int i = 0; i < V; ++i) {
            adj[i].clear();
        }
        while (E--) {
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            adj[a].push_back({b, w});
        }
        vector<int> dist(V, INF);
        dist[0] = 0;
        for (int i = 0; i < V - 1; ++i) {
            for (int v = 0; v < V; ++v) {
                for (ii u : adj[v])
                    dist[u.first] = min(dist[u.first], dist[v] + u.second);
            }
        }
        bool relaxable = false;
        for (int v = 0; v < V; ++v) {
            for (ii u : adj[v]) {
                if (dist[v] + u.second < dist[u.first]) {
                    relaxable = true;
                    goto end;
                }
            }
        }
    end:
        if (relaxable) {
            printf("possible\n");

        } else
            printf("not possible\n");
    }
}
