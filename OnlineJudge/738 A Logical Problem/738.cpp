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
string input;

const int mxN = 200;

vector<string> board;
bool ok(int r, int c) {
    return 0 <= r && r < mxN && 0 <= c && c < mxN;
}

array<int, 4> dr{0, 1, 0, -1};
array<int, 4> dc{1, 0, -1, 0};

array<char, 4> valid{'-', '|', '-', '|'};

bool dfs(int r, int c, int from = -1) {
    dout << dvar(r) << dvar(c) << dvar(board[r][c]) << endl;
    if (isalpha(board[r][c]) && board[r][c] != 'o') return '1' == input[board[r][c] - 'A'];
    switch(board[r][c]) {
        case '?':
	    F0R (i, 4) {
		int rr = r + dr[i], cc = c + dc[i];
		if (ok(rr, cc) && valid[i] == board[rr][cc]) return dfs(rr, cc, i);
	    }
        case '+':
        	F0R (i, 4) {
        	    int rr = r + dr[i], cc = c + dc[i];
        	    if (i != (from + 2) % 4 && ok(rr, cc) && valid[i] == board[rr][cc]) {
        		return dfs(rr, cc, i);
        	    }
        	}
        case '-': case '|': return dfs(r + dr[from], c + dc[from], from);
        case 'o': return !dfs(r + dr[from], c + dc[from], from);
        case ')': return dfs(r - 1, c - 3, from) && dfs(r + 1, c - 3, from);
        case '>': return dfs(r - 1, c - 3, from) || dfs(r + 1, c - 3, from);
    }	    
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
	string in;
        board.assign(mxN, "");
	F0R (i, mxN + 1) {
	    if (!getline(cin, in)) return 0;
	    if (!in.empty() && in[0] == '*') break;
	    board[i] = in;
	}
	for (auto& s : board) s.resize(mxN, ' ');
	F0R (i, 12) dout << board[i] << endl;
	int r = -1, c = -1;
	F0R (rr, mxN) {
	    F0R (cc, mxN) {
		if (board[rr][cc] == '?') {
		    r = rr;
		    c = cc;
		}
	    }
	}
	assert(~r && ~c);
	while (1) {
	    getline(cin, input);
	    if (!input.empty() && input[0] == '*') break;
	    cout << dfs(r, c) << endl;
	}
	cout << endl;
	
    }

    return 0;
}
