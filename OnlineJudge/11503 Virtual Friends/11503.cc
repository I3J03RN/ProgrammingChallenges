#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
#define ge(a, b) get<(b)>((a))
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

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
    int size(int a) { return -data[a]; }
    int size() { return _size; }

   private:
    vi data;
    int _size;
};

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        unordered_map<string, int> m;
        int cnt = 0;
        unionFind uf(n * 2);
        while (n--) {
            string s1, s2;
            cin >> s1 >> s2;
            if (m.count(s1) == 0) m[s1] = cnt++;
            if (m.count(s2) == 0) m[s2] = cnt++;
            int i1 = uf.find(m[s1]);
            int i2 = uf.find(m[s2]);
            if (i1 != i2) uf.join(i1, i2);
            cout << uf.size(uf.find(i1)) << endl;
        }
    }

    return 0;
}
