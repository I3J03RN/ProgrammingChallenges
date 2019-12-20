#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).begin; ++(a))

ll adj[100][100];
int n;
struct box {
    ll x, y, z;
};
box boxes[100];
int main() {
    int casenr = 1;

    while (scanf("%d", &n), n) {
        for (int i = 0; i < 3 * n; i += 3) {
            scanf("%lld %lld %lld", &boxes[i].x, &boxes[i].y, &boxes[i].z);
            boxes[i + 1] = {boxes[i].x, boxes[i].z, boxes[i].y};
            boxes[i + 2] = {boxes[i].y, boxes[i].z, boxes[i].x};
        }
        FOR(i, 0, 3 * n) {
            box b1 = boxes[i];
            FOR(j, 0, 3 * n) {
                box b2 = boxes[j];
                if ((b1.x > b2.y && b1.y > b2.x) ||
                    (b1.x > b2.x && b1.y > b2.y)) {
                    adj[i][j] = b2.z;
                } else
                    adj[i][j] = -1000000000;
            }
        }
        FOR(k, 0, n * 3)
        FOR(i, 0, n * 3)
        FOR(j, 0, n * 3)
        adj[i][j] = max(adj[i][j], adj[i][k] + adj[k][j]);

        ll maxv = -1000000000;
        FOR(i, 0, n * 3)
        FOR(j, 0, n * 3)
        maxv = max(maxv, boxes[i].z + adj[i][j]);

        printf("Case %d: maximum height = %lld\n", casenr++, maxv);
    }
}
