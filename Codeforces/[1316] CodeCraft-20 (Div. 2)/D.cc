#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const int label[4] = {'U', 'L', 'D', 'R'};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

char field[1010][1010];
ii dests[1010][1010];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(field, 0, sizeof(field));

    int n;
    cin >> n;

    queue<ii> Xs;
    queue<ii> infs;

    F0R (r, n) {
        F0R (c, n) {
            int rr, cc;
            cin >> rr >> cc;
            rr--;
            cc--;
            if (r == rr && c == cc) Xs.push(mp(r, c));
            if (rr == -2 && cc == -2) infs.push(mp(r, c));
            dests[r][c] = mp(rr == -2 ? -1 : rr, cc == -2 ? -1 : cc);
        }
    }
    while (!Xs.empty()) {
        ii start = Xs.ft;
        Xs.pop();
        field[start.fi][start.se] = 'X';
        queue<ii> q;
        q.push(start);
        while (!q.empty()) {
            auto [r, c] = q.ft;
            q.pop();
            F0R (i, 4) {
                if (r + yd[i] >= 0 && r + yd[i] < n && c + xd[i] >= 0 &&
                    c + xd[i] < n && dests[r + yd[i]][c + xd[i]] == start &&
                    field[r + yd[i]][c + xd[i]] == 0) {
                    field[r + yd[i]][c + xd[i]] = label[i];
                    q.push(mp(r + yd[i], c + xd[i]));
                }
            }
        }
    }
    while (!infs.empty()) {
        ii start = infs.ft;
        auto [r, c] = start;
        infs.pop();
        if (field[start.fi][start.se]) continue;
        int partner = -1;
        F0R (i, 4)
            if (r + yd[i] >= 0 && r + yd[i] < n && c + xd[i] >= 0 &&
                c + xd[i] < n && dests[r + yd[i]][c + xd[i]] == mp(-1, -1))
                partner = i;

        field[start.fi][start.se] = label[(partner + 2) % 4];

        if (partner == -1) {
            cout << "INVALID\n";
            return 0;
        }
        queue<ii> q;
        q.push(start);

        while (!q.empty()) {
            auto [r, c] = q.ft;
            q.pop();
            F0R (i, 4) {
                if (r + yd[i] >= 0 && r + yd[i] < n && c + xd[i] >= 0 &&
                    c + xd[i] < n &&
                    dests[r + yd[i]][c + xd[i]] == mp(-1, -1) &&
                    field[r + yd[i]][c + xd[i]] == 0) {
                    field[r + yd[i]][c + xd[i]] = label[i];
                    q.push(mp(r + yd[i], c + xd[i]));
                }
            }
        }
    }

    F0R (r, n)
        F0R (c, n)
            if (field[r][c] == 0) {
                cout << "INVALID\n";
                return 0;
            }

    cout << "VALID\n";
    F0R (r, n) {
        F0R (c, n)
            cout << field[r][c];
        cout << endl;
    }

    return 0;
}
