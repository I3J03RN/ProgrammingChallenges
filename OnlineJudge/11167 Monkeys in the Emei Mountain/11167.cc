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
#define SZ(x) (int)(x).size()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
  return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
  return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
  template <class C>
  static char test(typename C::const_iterator*);
  template <class C>
  static int test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
  static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o, const C& c) {
  o << '[';
  for (auto it = c.begin(); it != c.end();)
      o << *it << (++it != c.end() ? ", " : "");
  return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
  return o << '(' << p.fi << "," << p.se << ')';
}

struct edge {
  edge(int from, int to, ll capacity, ll flow = 0)
      : mfrom(from), mto(to), mcapacity(capacity), mflow(flow) {}
  int mfrom, mto;
  ll mcapacity, mflow;
  int other(int v) { return v == mfrom ? mto : mfrom; }
  ll capacity(int v) { return v == mfrom ? mcapacity : 0; }
  ll flow(int v) { return v == mfrom ? mflow : -mflow; }
  void adjust(int v, ll amount) {
    mflow += v == mfrom ? amount : -amount;
  }
};
vector<edge> edges;
vvi adj;
void addEdge(int from, int to, ll c, ll f = 0) {
  edges.eb(from, to, c, f);
  adj[from].pb(SZ(edges) - 1);
  adj[to].pb(SZ(edges) - 1);
}

vi dist, ptr;
const ll inf = 1e16;
bool dinic_bfs(int s, int t) {
  dist.assign(SZ(adj), SZ(adj));
  queue<int> q;
  q.push(s);
  dist[s] = 0;
  while (SZ(q)) {
    int v = q.front(); q.pop();
    for (int i : adj[v]) {
      edge& e = edges[i];
      if (dist[e.other(v)] == SZ(adj) && e.flow(v) < e.capacity(v)) {
        dist[e.other(v)] = dist[v] + 1;
        q.push(e.other(v));
      }
    }
  }
  return dist[t] < SZ(adj);
}
ll dinic_dfs(int v, int t, ll available) {
  if (v == t || !available) return available;
  ll pushed = 0;
  for (; ptr[v] < SZ(adj[v]); ++ptr[v]) {
    edge& e = edges[adj[v][ptr[v]]];
    if (dist[v] + 1 != dist[e.other(v)] || e.flow(v) >= e.capacity(v))
      continue;
    ll wasPushed =
        dinic_dfs(e.other(v), t,
                  min(available - pushed, e.capacity(v) - e.flow(v)));
    pushed += wasPushed;
    e.adjust(v, wasPushed);
    if (pushed == available) return pushed;
  }
  return pushed;
}
ll maxflow(int s, int t) {
  dist.assign(SZ(adj), 0);
  ll f = 0;
  while (1) {
    if (!dinic_bfs(s, t)) return f;
    ptr.assign(SZ(adj), 0);
    f += dinic_dfs(s, t, inf);
  }
}

const int offset = 50001;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m, casenr = 1;
  while (cin >> n, n) {
    cin >> m;
    adj.clear(); edges.clear(); adj.resize(offset + 2 + n);
    int source = offset + n;
    int target = source + 1;

    vector<bool> connected(offset);
    int sum = 0;
    F0R (i, n) {
      int v, a, b;
      cin >> v >> a >> b;
      sum += v;
      addEdge(offset + i, target, v);
      FOR (j, a, b) {
        if (!connected[j]) {
          connected[j] = 1;
          addEdge(source, j, m);
        }
        addEdge(j, offset + i, 1);
      }
    }

    ll mf = maxflow(source, target);
    // for (edge& e : edges) {
    //   dout << dvar(e.mfrom) << dvar(e.mto) << dvar(e.mflow) << dvar(e.mcapacity) << endl;
    // }

    cout << "Case " << casenr++ << ": ";
    if (mf == sum) {
      cout << "Yes" << endl;

      vvii out(n);
      for (edge& e : edges) {
        int j = e.mto - offset;
        int t = e.mfrom;
        if (0 <= j && j < n && e.mflow == 1) {
          if (out[j].empty() || out[j].back().se < t) {
            out[j].eb(t, t + 1);
          } else {
            out[j].back().se = t + 1;
          }
        }
      }

      F0R (i, n) {
        cout << SZ(out[i]);
        for (auto& p : out[i]) cout << ' ' << p;
        cout << endl;
      }
      
    } else {
      cout << "No" << endl;
    }
    
  }

  return 0;
}
