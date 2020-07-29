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

template <class T>
int sign(T a) {
    return (a > 0) - (0 > a);
}
// invariants:
//   - no leading zeroes
using vll = vector<ll>;
using vit = vll::iterator;
struct bigint {
    int signum;
    static const ll base = 1e9;
    vll mag;
    bigint() : signum(0), mag() {}
    bigint(ll val) : signum(sign(val)), mag() {
        val = abs(val);
        while (val) {
            mag.pb(val % base);
            val /= base;
        }
    }
    bigint(string s) {
        if (s.empty() || s == "0")
            signum = 0;
        else {
            signum = s[0] == '-' ? -1 : 1;
            for (int i = SZ(s) - 1, j = 0, b = 1; ~i && isdigit(s[i]); --i) {
                if (!j) mag.pb(0);
                mag.bk += (s[i] - '0') * b;
                ++j;
                b *= 10;
                if (b == base) j = 0, b = 1;
            }
        }
    }
    size_t size() const { return mag.size(); }
    void trim() {
        while (!mag.empty() && !mag.bk) mag.pop_back();
        if (mag.empty()) signum = 0;
    }
    ll val(int index) { return index < SZ(mag) ? mag[index] : 0; }
    friend bigint operator-(bigint a) {
        a.signum *= -1;
        return a;
    }
    friend bigint operator+(bigint& a, bigint& b) {
        if (!a.signum) return b;
        if (!b.signum) return a;
        if (a.signum != b.signum) {
            if (b.signum < 0) {
                b.signum *= -1;
                bigint out = a - b;
                b.signum *= -1;
                return out;
            }
            return b + a;
        }
        if (SZ(a) < SZ(b)) return b + a;
        bigint out;
        out.signum = a.signum;
        out.mag = add(a.mag, b.mag);
        return out;
    }
    static vll add(vll& a, vll& b) {
        assert(SZ(a) >= SZ(b));
        vll out = a;
        out.pb(0);
        for (int i = 0, c = 0; i < SZ(b) || c; ++i) {
            out[i] += (i < SZ(b) ? b[i] : 0) + c;
            c = out[i] > base;
            out[i] %= base;
        }
        if (out.bk == 0) out.pop_back();
        return out;
    }
    friend bigint operator-(bigint& a, bigint& b) {
        if (!a.signum) return -b;
        if (!b.signum) return a;
        if (a.signum != b.signum) {
            a.signum *= -1;
            bigint out = a + b;
            out.signum = a.signum *= -1;
            return out;
        }
        if (a < b) return -(b - a);
        bigint out = a;
        for (int i = 0, c = 0; i < SZ(b) || c; ++i) {
            ll sub = b.val(i) + c;
            if (sub > out.val(i)) {
                c = 1;
                out.mag[i] += base - sub;
            } else {
                c = 0;
                out.mag[i] -= sub;
            }
        }
        out.trim();
        return out;
    }
    friend bigint operator*(bigint& a, bigint& b) {
        if (!a.signum || !b.signum) return bigint();
        bigint out;
        out.mag = karat_mult(ALL(a.mag), ALL(b.mag));
        out.signum = a.signum * b.signum;
        return out;
    }
    // karatsuba multiplication
    // a = a1 * B^m + a0
    // b = b1 * B^m + b0
    // z2 = a1 * b1
    // z1 = a1 * b0 + a0 * b1
    // z0 = a0 * b0
    // a * b = z2 * B^2m + z1 B^m + z0
    static vll karat_mult(vit ab, vit ae, vit bb, vit be) {
        if (distance(ab, ae) < distance(bb, be)) {
            swap(ab, bb);
            swap(ae, be);
        }
        if (distance(bb, be) <= 1) return small_mult(ab, ae, bb, be);
        auto split = distance(ab, ae) / 2;

        vit amid = ab + split, bmid = bb + min(split, distance(bb, be));
        vll z0 = karat_mult(ab, amid, bb, bmid),
            z2 = karat_mult(amid, ae, bmid, be),
            z11 = karat_mult(amid, ae, bb, bmid),
            z12 = karat_mult(ab, amid, bmid, be);
        vll z1 = SZ(z11) < SZ(z12) ? add(z12, z11) : add(z11, z12);
        vll out(2 * split + SZ(z2) + 1);
        auto add = [&](vll& v, int offset) {
            for (int i = 0, c = 0; i < SZ(v) || c; ++i) {
                out[i + offset] += (i < SZ(v) ? v[i] : 0) + c;
                c = out[i + offset] > base;
                out[i + offset] %= base;
            }
        };
        // maybe wrong offsets
        add(z0, 0);
        add(z1, split);
        add(z2, split * 2);
        while (!out.empty() && !out.bk) out.pop_back();
        return out;
    }
    // second range represents an array of length one or zero
    static vll small_mult(vit ab, vit ae, vit bb, vit be) {
        assert(distance(bb, be) <= 1);
        if (bb == be) return vll();
        ll fac = *bb;
        vll out(distance(ab, ae));
        ll c = 0;
        for (int i = 0; ab != ae || c; ++i) {
            if (i == SZ(out)) out.pb(0);
            out[i] = (ab != ae ? *ab : 0) * fac + c;
            c = out[i] / base;
            out[i] %= base;
            if (ab != ae) ++ab;
        }
        return out;
    }
    friend bool operator<(bigint& a, bigint& b) {
        if (a.signum != b.signum) return a.signum < b.signum;
        if (!a.signum) return false;  // both zero
        int cmp = sign(SZ(a) - SZ(b));
        for (int i = SZ(a) - 1; !cmp && ~i; --i)
            cmp = sign(a.mag[i] - b.mag[i]);
        return a.signum > 0 ? cmp < 0 : cmp > 0;
    }
    friend string to_string(bigint& bi) {
        if (!bi.signum) return "0";
        stringstream ss;
        ss << bi.signum * bi.mag.bk;
        R0F (i, SZ(bi) - 2)
            ss << setfill('0') << setw(9) << bi.mag[i];
        return ss.str();
    }
    friend ostream& operator<<(ostream& o, bigint& bi) {
        return o << to_string(bi);
    }
    void printmags() {
        for (ll l : mag) cout << l << endl;
    }
};

vector<bigint> der(1000, 0);

int main() {
    der[0] = 1;
    FOR (i, 2, 1000) {
        bigint b = i - 1;
        bigint tmp = der[i - 1] + der[i - 2];
        der[i] = b * tmp;
    }
    int i;
    while (cin >> i, ~i) {
        cout << der[i] << endl;
    }
}
