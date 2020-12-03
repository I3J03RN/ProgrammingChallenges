#include <bits/stdc++.h>
using namespace std;
#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (x).size()
#define pb push_back
#define mp make_pair

int in[100000] = {};
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vvi adj(n);

  F0R(i, m) {
    int a, b;
    cin >> a >> b;
    a--; b--;

    in[b]++;
    adj[a].pb(b);
  }

  queue<ii> q;
  F0R(i, n)
    if(!in[i])
      q.push(mp(i, 0));

  int t = 0;
  while(!q.empty()) {
    auto [v, tt] = q.front();
    q.pop();

    if(t != tt) {
      cout << endl;
      t++;
    }

    cout << v + 1 << ' ';
    for(auto u : adj[v])
      if(--in[u] == 0)
        q.push(mp(u , tt + 1));
  }
  cout << endl;
}
