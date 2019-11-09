#include <cmath>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector<vector<vi>> A(200, vector<vi>(21, vi(801)));

int inline diff(const ii& i) { return i.first - i.second; }
int inline all(const ii& i) { return i.first + i.second; }
bool inline valid(int i) { return 0 <= i && i <= 800; }

int main() {
    int n, m, jury = 1;
    while (scanf("%d %d", &n, &m), n) {
        for (int i = 0; i < n; ++i)
            for (int j = 1; j <= m; ++j) A[i][j].assign(801, -1);

        vii pairs(n);
        for (int i = 0; i < n; ++i)
            scanf("%d %d", &pairs[i].first, &pairs[i].second);

        A[0][1][400 + diff(pairs[0])] = all(pairs[0]);
        for (int _n = 1; _n < n; ++_n) {
            A[_n][1][400 + diff(pairs[_n])] = all(pairs[_n]);
            for (int d = 380; d <= 420; ++d)
                A[_n][1][d] = max(A[_n - 1][1][d], A[_n][1][d]);
        }

        for (int _m = 2; _m <= m; ++_m) {
            for (int _n = _m - 1; _n < n; ++_n) {
                auto& a = A[_n][_m];
                for (int d = 400 - (20 * _m); d <= 400 + (20 * _m); ++d) {
                    if (valid(d - diff(pairs[_n])) &&
                        A[_n - 1][_m - 1][d - diff(pairs[_n])] != -1)
                        a[d] = max(A[_n - 1][_m][d],
                                   all(pairs[_n]) +
                                       A[_n - 1][_m - 1][d - diff(pairs[_n])]);
                    else
                        a[d] = A[_n - 1][_m][d];
                }
            }
        }

        // for (int _m = 1; _m <= m; ++_m) {
        //     for (int _n = 0; _n < n; ++_n) {
        //         for (int d = 400 - (20 * m); d <= 400 + (20 * m); ++d) {
        //             if (A[_n][_m][d] != -1)
        //                 printf("%d, %d, %d: %d\n", _n, _m, d - 400,
        //                        A[_n][_m][d]);
        //         }
        //         printf("\n");
        //     }
        //     printf("\n");
        //     printf("\n");
        // }

        int _diff = 0;
        auto& a = A[n - 1][m];
        for (;; _diff++) {
            if (a[400 + _diff] != -1 || a[400 - _diff] != -1) {
                if (a[400 - _diff] > a[400 + _diff]) {
                    _diff *= -1;
                }
                break;
            }
        }

        // printf("%d\n", _diff);
        // _diff = d - p
        // a = d + p = _diff + p + p
        int p = (_diff + a[400 + _diff]) / 2;
        printf(
            "Jury #%d\nBest jury has value %d for prosecution and value %d for "
            "defence:\n",
            jury++, p, a[400 + _diff] - p);

        stack<int> s;
        for (; m > 1; n--) {
            if (A[n - 2][m - 1][400 + _diff - diff(pairs[n - 1])] != -1 &&
                A[n - 2][m - 1][400 + _diff - diff(pairs[n - 1])] +
                        all(pairs[n - 1]) ==
                    A[n - 1][m][400 + _diff]) {
                s.push(n);
                m--;
                _diff -= diff(pairs[n - 1]);
            }
        }

        for (; n > 0; n--) {
            if (_diff == diff(pairs[n - 1]) &&
                A[n - 1][m][400 + _diff] == all(pairs[n - 1])) {
                s.push(n);
                m--;
                break;
            }
        }

        for (; !s.empty(); s.pop()) printf(" %d", s.top());

        printf("\n\n");
    }
}
