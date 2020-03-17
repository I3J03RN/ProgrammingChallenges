#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

const int rows = 20;
const int columns = 20;

int field[rows][columns];

int test(int r, int c) {
    int ret = 0;

    // down
    int prod = 1;
    for (int i = 0; i < 4; ++i) prod *= field[r + i][c];
    ret = max(ret, prod);
    // down right
    prod = 1;
    for (int i = 0; i < 4; ++i) prod *= field[r + i][c + i];
    ret = max(ret, prod);
    // down left
    if (c - 3 >= 0) {
        prod = 1;
        for (int i = 0; i < 4; ++i) prod *= field[r + i][c - i];
        ret = max(ret, prod);
    }
    // right
    prod = 1;
    for (int i = 0; i < 4; ++i) prod *= field[r][c + i];
    ret = max(ret, prod);

    return ret;
}

int main() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c) scanf("%d", field[r] + c);

    int maxprod = 0;
    for (int r = 0; r + 4 <= rows; ++r)
        for (int c = 0; c + 4 <= columns; ++c)
            maxprod = max(maxprod, test(r, c));

    cout << maxprod << endl;
}
