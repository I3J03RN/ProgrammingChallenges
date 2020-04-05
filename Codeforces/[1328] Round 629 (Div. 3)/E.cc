#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef complex<int> ci;
typedef complex<double> cd;
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
#define ins insert
//#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))
#define ROFI(a, b) for (auto(a) = (b).rbegin(); (a) != (b).rend(); ++(a))
#define CEIL(a, b) ((a) + (b)-1) / (b)
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

template <typename t>
ostream& operator<<(ostream& o, const vector<t>& v) {
    for (auto& ts : v) o << ts << ' ';
    o << endl;
    return o;
}

class SparseTable {
   public:
    SparseTable() {}
    SparseTable(vi& A) : A(A) {
        st.assign(SZ(A) + 1, vi(log2(SZ(A)) + 1));
        F0R (i, SZ(A))
            st.at(i).at(0) = i;
        FOR (j, 1, SZ(st.at(0)))
            for (int i = 0; i + (1 << j) <= SZ(A); ++i) {
                if (A.at(st.at(i).at(j - 1)) <
                    A.at(st.at(i + (1 << (j - 1))).at(j - 1)))
                    st.at(i).at(j) = st.at(i).at(j - 1);
                else
                    st.at(i).at(j) = st.at(i + (1 << (j - 1))).at(j - 1);
            }
    }
    int rmq(int a, int b) {
        int j = 31 - __builtin_clz(b - a + 1);
        if (A.at(st.at(a).at(j)) < A.at(st.at(b - (1 << j) + 1).at(j)))
            return st.at(a).at(j);
        return st.at(b - (1 << j) + 1).at(j);
    }

   private:
    vi A;
    vvi st;
};

class LookUpTable {
   public:
    LookUpTable(int n, int val) : table(n, vi(n)) {
        vi vs(n, 0);
        FOR (i, 1, n) {
            vs.at(i) = vs.at(i - 1) + (val & 1 ? 1 : -1);
            val >>= 1;
        }

        F0R (i, n)
            table.at(i).at(i) = i;
        FOR (j, 1, n)
            for (int l = 0, r = j; r < n; ++l, ++r)
                if (vs.at(table.at(l).at(l)) < vs.at(table.at(l + 1).at(r)))
                    table.at(l).at(r) = table.at(r).at(l) = table.at(l).at(l);
                else
                    table.at(l).at(r) = table.at(r).at(l) =
                        table.at(l + 1).at(r);
    }
    int rmq(int a, int b) { return table.at(a).at(b); }

   private:
    vvi table;
};

class LCA {
   public:
    LCA(vvi& adj) {
        first.assign(SZ(adj), -1);
        height.assign(SZ(adj), -1);
        dfs(adj);
        blockSize = (int)ceil(log2(SZ(eulertour))) >> 1;
        int cnt = 0;
        ii m = mp(numeric_limits<int>::max(), -1);
        for (int i : eulertour) {
            ckmin(m, mp(height.at(i), i));
            if (++cnt == blockSize) {
                blocks.pb(m.fi);
                blockIndex.pb(m.se);
                cnt = 0;
                m = mp(numeric_limits<int>::max(), -1);
            }
        }
        if (cnt) {
            blocks.pb(m.fi);
            blockIndex.pb(m.se);
        }
        // for (int i : blocks) cout << i << ' ';
        // cout << endl;

        blockST = SparseTable(blocks);
        lookUpTables.reserve(1 << (blockSize - 1));
        F0R (i, 1 << (blockSize - 1))
            lookUpTables.eb(blockSize, i);

        for (int i = 0; i < SZ(blocks); ++i) {
            int val = 0;
            int start = i * blockSize;
            for (int j = 1, last = height.at(eulertour.at(start));
                 j < blockSize; ++j) {
                if (start + j < SZ(eulertour)) {
                    val |= height.at(eulertour.at(start + j)) > last << (j - 1);
                    last = height.at(eulertour.at(start + j));
                } else
                    val |= 1 << (j - 1);
            }
            lutIndeces.pb(val);
        }
    }

    int lca(int a, int b) {
        int l = min(first.at(a), first.at(b)),
            r = max(first.at(a), first.at(b));
        int blockL = l / blockSize;
        int blockR = r / blockSize;
        // cout << "rmq for: " << l << '.at(' << blockL << ") -- " << r << '['
        // << blockR << "]" << endl;
        if (blockL == blockR)
            return eulertour[blockSize * blockL +
                             lookUpTables.at(lutIndeces.at(blockL))
                                 .rmq(l % blockSize, r % blockSize)];

        int minl = eulertour.at(blockSize * blockL +
                                lookUpTables.at(lutIndeces.at(blockL))
                                    .rmq(l % blockSize, blockSize - 1));
        int minr = eulertour.at(
            blockSize * blockR +
            lookUpTables.at(lutIndeces.at(blockR)).rmq(0, r % blockSize));
        int minm = -1;
        if (blockL + 1 < blockR)
            minm = blockIndex.at(blockST.rmq(blockL + 1, blockR - 1));
        // cout << minl << ' ' << minm << ' ' << minr << endl;
        vii list = {
            mp(height.at(minl), minl), mp(height.at(minr), minr),
            mp(minm == -1 ? numeric_limits<int>::max() : height.at(minm),
               minm)};
        sort(ALL(list));
        return list.ft.se;
    };

    vi eulertour;
    vi first;
    vi height;
    int blockSize;
    vi blocks;
    vi blockIndex;
    vi lutIndeces;
    SparseTable blockST;
    vector<LookUpTable> lookUpTables;

    void dfs(vvi& adj, int v = 0, int h = 0) {
        eulertour.pb(v);
        first.at(v) = SZ(eulertour) - 1;
        height.at(v) = h;
        for (int u : adj.at(v))
            if (first.at(u) == -1) {
                dfs(adj, u, h + 1);
                eulertour.pb(v);
            }
    }
};

void dfs(vvi& adj, vi& parent, int v = 0, int p = -1) {
    parent.at(v) = p;
    for (int u : adj.at(v))
        if (u != p) dfs(adj, parent, u, v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vvi adj(n);
    FOR (i, 1, n) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj.at(a).pb(b);
        adj.at(b).pb(a);
    }

    LCA lca(adj);
    vi parent(n);
    dfs(adj, parent);

    while (m--) {
        int k;
        cin >> k;
        vi q(k);
        F0R (i, k) {
            cin >> q.at(i);
            --q.at(i);
        }
        sort(ALL(q),
             [&](int a, int b) { return lca.height.at(a) > lca.height.at(b); });
        bool possible = true;
        int p = q[0];
        for (int node : q) {
            int r = lca.lca(node, p);
            if (node == r || parent.at(node) == r) p = parent.at(node);

            if (p != parent.at(node)) {
                possible = false;
                break;
            }
        }
        cout << (possible ? "YES" : "NO") << endl;
    }

    return 0;
}
