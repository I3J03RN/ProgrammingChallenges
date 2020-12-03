#include <bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
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

int adj[210][210];

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  F0R(i, n) F0R(j, n) adj[i][j] = 10000000;

  viii edges(m);

  F0R(i, m) {
    int a, b, l;
    cin >> a >> b >> l;
    a--; b--;

    adj[a][b] = min(adj[a][b], l);
    adj[b][a] = min(adj[b][a], l);

    edges.pb(mt(a, b, l));
  }

  F0R(i, n)
    adj[i][i] = 0;

  FOR(k, 0, n)
    FOR(i, 0, n)
      FOR(j, 0, n)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);



  vi bests(200);
  double bestVal = 10000000000.0;
  F0R(i, n) {

    double bestL = 0;
    for(auto [a, b, l] : edges) {

      int maxL = max(adj[i][a], adj[i][b]);
      int minL = min(adj[i][a], adj[i][b]);

      //cout << "[" << a << ", " << b << ", " << l << "], d(" << adj[i][a] << ", " << adj[i][b] << ")    ";

      l -= maxL - minL;
      if(l < 0)
        l = 0;

      //cout << "Len: " << l << ", best?: " << maxL + l/2.0 << endl;

      bestL = max(bestL, maxL + l/2.0);
    }


    if(bestL < bestVal) {
      //cout << "Best is " << bestL << endl;
      bestVal = bestL;
      bests.clear();
      bests.pb(i);
    } else if(abs(bestL - bestVal) < 1e-6) {
      bests.pb(i); //FIXME: EPSILON
    }
  }

  cout << fixed << setprecision(9) << bestVal << endl;
  for(int r : bests)
    cout << r + 1 << endl;
}
