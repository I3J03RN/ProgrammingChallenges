#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define pf push_front
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define SZ(x) (x).size()
#define ft front
#define bk back
#define ins insert
#define MID(a, b) (a + b) / 2
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) for (auto(a) = 0; (a) < (b); ++(a))
#define R0F(a, b) for (auto(a) = (b); (a) >= 0; --(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))
#define ROFI(a, b) for (auto(a) = (b).rbegin(); (a) != (b).rend(); ++(a))
#define TRAV(a, b) for (auto&(a) : (b))
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

typedef tuple<int, int, double> iid;

class unionFind {
   public:
    unionFind(int size) : _size(size), data(size, -1) {}
    int find(int toFind) {
        int root = toFind;
        while (data[root] >= 0) root = data[root];
        while (toFind != root) {
            int tmp = data[toFind];
            data[toFind] = root;
            toFind = tmp;
        }
        return root;
    }
    void join(int a, int b) {
        if (data[a] < data[b]) {
            data[a] += data[b];
            data[b] = a;
        } else {
            data[b] += data[a];
            data[a] = b;
        }
        _size--;
    }
    int size() { return _size; }

   private:
    int _size;
    vi data;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc;
    cin >> tc;

    while (tc--) {
        int numRevTrans;
        cin >> numRevTrans;
        vii sensors;
        while (1) {
            int x, y;
            cin >> x;
            if (x == -1) break;
            cin >> y;
            sensors.eb(x, y);
        }
        vector<iid> edges;
        edges.reserve(SZ(sensors) * (SZ(sensors) - 1) / 2);
        F0R (a, SZ(sensors))
            FOR (b, a + 1, SZ(sensors)) {
                double dx = sensors[a].fi - sensors[b].fi;
                double dy = sensors[a].se - sensors[b].se;
                edges.eb(a, b, dx * dx + dy * dy);
            }

        sort(ALL(edges),
             [](iid& a, iid& b) -> bool { return get<2>(a) < get<2>(b); });

        unionFind uf(SZ(sensors));
        F0R (i, SZ(edges)) {
            int a = uf.find(get<0>(edges[i]));
            int b = uf.find(get<1>(edges[i]));
            if (a != b) {
                uf.join(a, b);
                if (uf.size() <= numRevTrans) {
                    cout << (int)ceil(sqrt(get<2>(edges[i]))) << endl;
                    break;
                }
            }
        }
    }

    return 0;
}
