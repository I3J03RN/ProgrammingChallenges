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
#define ft front()
#define bk back()
//#define endl '\n'
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
#define dout \
    if (DEBUG) std::cerr
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
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '{';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "}");
    return o;
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}

// to, cost, time
vector<vector<tuple<int, ll, ll>>> adj;
vector<ll> ecoins;
vector<ll> etime;

// state: current city, coins, cost
struct state {
    state(int city, ll coins, ll time) : city(city), coins(coins), time(time) {}
    int city;
    ll coins, time;
    friend bool operator<(const state& a, const state& b) {
        return a.time > b.time;
    }
};

const ll inf = 1e16;
void djikstra(vector<ll>& distprime, int start, ll startcoins) {
    distprime.assign(SZ(adj), inf);
    ckmin(startcoins, 50LL * SZ(adj));
    // city, coins -> time
    map<pair<int, ll>, ll> dist;
    dist[mp(start, startcoins)] = 0;
    priority_queue<state> q;
    q.emplace(start, startcoins, 0);
    distprime[start] = 0;
    while (!q.empty()) {
        int city = q.top().city;
        ll coins = q.top().coins;
        ll time = q.top().time;
        dout << dvar(city) << dvar(coins) << dvar(time) << endl;
        q.pop();
        if (dist[mp(city, coins)] < time) continue;
        for (auto [ucity, ucost, utime] : adj[city]) {
            if (ucost > coins) continue;
            ll ncoins = coins - ucost;
            ll ntime = time + utime;
            auto it = dist.find(mp(ucity, ncoins));
            if (it == dist.end() || it->second > ntime) {
                ckmin(distprime[ucity], ntime);
                dist[mp(ucity, ncoins)] = ntime;
                q.emplace(ucity, ncoins, ntime);
            }
        }
        coins += ecoins[city];
        ckmin(coins, 50LL * SZ(adj));
        time += etime[city];
        auto it = dist.find(mp(city, coins));
        if (it == dist.end() || it->second > time) {
            dist[mp(city, coins)] = time;
            q.emplace(city, coins, time);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    ll s;
    cin >> n >> m >> s;
    adj.assign(n, vector<tuple<int, ll, ll>>());
    ecoins.assign(n, 0);
    etime.assign(n, 0);
    F0R (i, m) {
        int a, b;
        ll cost, time;
        cin >> a >> b >> cost >> time;
        --a;
        --b;
        adj[a].eb(b, cost, time);
        adj[b].eb(a, cost, time);
    }
    F0R (i, n)
        cin >> ecoins[i] >> etime[i];
    vector<ll> dist;
    djikstra(dist, 0, s);
    FOR (i, 1, n)
        cout << dist[i] << endl;

    return 0;
}
