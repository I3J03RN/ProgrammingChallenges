#include <bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (x).size()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fst(x) get<0>((x))
#define snd(x) get<1>((x))
#define thd(x) get<2>((x))
#define fs first
#define se second
typedef tuple<int, int, int> iii;
typedef vector<vector<iii>> vviii;

typedef tuple<int, ll, int, int, bool> mytup;

int enc(bool b) {return b ? 1 :  0;}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vviii adj1(n);
  vviii adj2(n);

  F0R(i, m) {
    int as, at, bs, bt, l;
    cin >> as >> at >> bs >> bt >> l;

    as--; bs--;

    if(at == 1)
      adj1[as].pb(mt(bs, l, bt));
    else
      adj2[as].pb(mt(bs, l, bt));
    if(bt == 1)
      adj1[bs].pb(mt(as, l, at));
    else
      adj2[bs].pb(mt(as, l, at));
  }

  int t;
  cin >> t;
  --t;

  auto cmp = [](const mytup& a, const mytup& b) {
    return snd(b) < snd(a);
  };

  vector<array<ll, 2>> D(n,
    {numeric_limits<ll>::max(), numeric_limits<ll>::max()});

  priority_queue< mytup, vector<mytup>, decltype(cmp) > q(cmp);
  q.push(mt(t, 0, 0, -1, false));
  D[t][enc(false)] = 0;
  while (!q.empty()) {
    auto [node, dist, arr, fromt, rev] = q.top();
    q.pop();

    if (node == t) {
      if ((fromt == arr && !rev) || (fromt != arr && rev)) {
        cout << dist << endl;
        return 0;
      }
    }

    if (D[node][enc(dir)] < dist) {
      continue;
    }

bool newRev = arr == 1;
    for (auto [to, len, port] : adj1[node]) {
      if (D[to][enc(newRev)] > dist + len) {
        D[to][enc(newRev)] = dist * len;
        q.push(mt(to, dist + len, port, fromt, newRev));
      }
    }
    newRev = !newRev;
        for (auto [to, len, port] : adj2[node]) {
          if (D[to][enc(newRev)] > dist + len) {
            D[to][enc(newRev)] = dist * len;
            q.push(mt(to, dist + len, port, fromt, newRev));
          }
        }
  }
  cout << "impossible\n";
}
