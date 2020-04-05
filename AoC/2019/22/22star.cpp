#include <bits/stdc++.h>
using namespace std;
typedef __int128_t ll;
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
#define endl '\n'
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

void print_it(__int128_t n) {
    if (n < 0) {
        cout << '-';
        n *= -1;
    }
    ll mod = 1e18;
    string s;
    do {
        unsigned long long digits = n % mod;
        string dStr = to_string(digits);
        if (digits != n)
            s = string(18 - dStr.length(), '0') + dStr + s;
        else
            s = dStr + s;
        n = (n - digits) / mod;
    } while (n);
    cout << s;
}

const ll NUMBER_OF_CARDS = 119315717514047LL;
const ll SHUFFLE_ITERATIONS = 101741582076661LL;
const ll RELEVANT_CARD = 2020LL;

ll binpow(ll a, ll b, ll p) {
    a %= p;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    // ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    ll offset = 0, increment = 1;
    while (cin >> s, cin) {
        if (s == "cut") {
            long long n;
            cin >> n;
            offset += increment * n % NUMBER_OF_CARDS;
            offset %= NUMBER_OF_CARDS;
        } else {
            cin >> s;
            if (s == "into") {
                increment *= -1;
                increment += NUMBER_OF_CARDS;
                increment %= NUMBER_OF_CARDS;
                offset += increment % NUMBER_OF_CARDS;
            } else {
                long long n;
                cin >> s >> n;
                increment = increment *
                            binpow(n, NUMBER_OF_CARDS - 2, NUMBER_OF_CARDS) %
                            NUMBER_OF_CARDS;
            }
        }
    }
    ll tmp = (1 - binpow(increment, SHUFFLE_ITERATIONS, NUMBER_OF_CARDS) +
              NUMBER_OF_CARDS) %
             NUMBER_OF_CARDS;
    offset = offset * tmp % NUMBER_OF_CARDS;
    offset = offset *
             binpow(1 - increment + NUMBER_OF_CARDS, NUMBER_OF_CARDS - 2,
                    NUMBER_OF_CARDS) %
             NUMBER_OF_CARDS;
    increment = binpow(increment, SHUFFLE_ITERATIONS, NUMBER_OF_CARDS);

    print_it((offset + (increment * RELEVANT_CARD % NUMBER_OF_CARDS)) %
             NUMBER_OF_CARDS);
    cout << endl;

    return 0;
}
