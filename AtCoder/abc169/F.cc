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
    o << '[';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "");
    return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}


struct mod {
  static const ll p = 998244353;
  ll val;
  mod() : val(0) {}
  mod(ll val) : val(val % p) { if (this->val < 0) this->val += p; }
  mod& operator+=(mod o) {
    val = (val + o.val) % p;
    return *this;
  }
  mod& operator-=(mod o) {
    val = (val - o.val + p) % p;
    return *this;
  }
  mod& operator*=(mod o) {
    val = val * o.val % p;
    return *this;
  }
  mod& operator/=(mod o) { return (*this) *= pow(o, p - 2); }
  mod& operator++() { return (*this) += 1; }
  mod operator++(int) { return ++(*this) - 1; }
  mod& operator--() { return (*this) -= 1; }
  mod operator--(int) { return --(*this) + 1; }
  mod friend operator+(mod a, mod b) { return a += b; }
  mod friend operator-(mod a, mod b) { return a -= b; }
  mod friend operator*(mod a, mod b) { return a *= b; }
  mod friend operator/(mod a, mod b) { return a /= b; }
  static mod pow(mod a, mod b) {
    mod res = 1;
    for (; b.val; b.val >>= 1, a = a * a)
      if (b.val & 1) res = res * a;
    return res;
  }
  friend istream& operator>>(istream& i, mod& m) {
    i >> m.val;
    m.val %= mod::p;
    if (m.val < 0) m.val += mod::p;
    return i;
  }
  friend ostream& operator<<(ostream& o, mod m) { return o << m.val; }
};

void solve() {
    int n, s;
    cin >> n >> s;
    vi as(n);
    F0R (i, n) cin >> as[i];
    vector<vector<mod>> dp(n, vector<mod>(s + 1, 1));
    dp[0][0] = 2;
    FOR (i, 1, n) {
	dp[i][0] = dp[i - 1][0] * 2;
    }
    FOR (ss, 1, s + 1) {
	if (as[0] == ss)
	    dp[0][ss] = 1ll;
	else
	    dp[0][ss] = 0ll;
	dout << dvar(ss) << dvar(dp[0][ss]) << endl;
	FOR (i, 1, n) {
	    dp[i][ss] = 2 * dp[i - 1][ss];
	    if (ss >= as[i]) {
		dp[i][ss] += dp[i - 1][ss - as[i]];
	    }
	}
    }
    cout << dp[n - 1][s] << endl;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    FOR (t, 1, tt + 1) {
	// cout << "Case #" << t << ": ";
	solve();
    }

    return 0;
}
