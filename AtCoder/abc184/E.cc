// this line is here for a reason
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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
template <typename T>
bool ckmin(T& a, const T& b) { return a > b ? a = b, true : false; }
template <typename T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, true : false; }
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout if (DEBUG) cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int R, C; cin >> R >> C;
  vector<string> m(R); F0R (i, R) cin >> m[i];
  vvii letters(26);
  ii start, goal;
  F0R (r, R) {
    F0R (c, C) {
      if (m[r][c] == 'S') {
        start = {r, c};
      }
      if (m[r][c] == 'G') {
        goal = {r, c};
      }
      if ('a' <= m[r][c] && m[r][c] <= 'z') {
        letters[m[r][c] - 'a'].eb(r, c);
      }
    }
  }

  vvi dist(R, vi(C, 1e8));

  int dr[4] = {0, 0, 1, -1};
  int dc[4] = {1, -1, 0, 0};

  dist[start.fi][start.se] = 0;
  set<tuple<int, int, int>> q;
  q.emplace(0, start.fi, start.se);
  while (not q.empty()) {
    auto [d, r, c] = *q.begin(); q.erase(q.begin());
    if (dist[r][c] < d) continue;
    if ('a' <= m[r][c] && m[r][c] <= 'z') {
      char cr = m[r][c];

      for (auto [rr, cc] : letters[cr - 'a']) {
        if (ckmin(dist[rr][cc], d + 1)) {
          q.emplace(d + 1, rr, cc);
        }
      }

      letters[cr - 'a'].clear();
    }
      F0R (i, 4) {
        int rr = r + dr[i], cc = c + dc[i];
        if (min(rr, cc) < 0 || rr >= R || cc >= C || m[rr][cc] == '#') continue;
        if (ckmin(dist[rr][cc], d + 1)) {
          q.emplace(d + 1, rr, cc);
        }
      }
  }


  cout << (dist[goal.fi][goal.se] == 1e8 ? -1 : dist[goal.fi][goal.se]) << endl;


  
  return 0;
}
