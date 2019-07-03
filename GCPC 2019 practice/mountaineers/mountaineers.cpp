#include <algorithm>
#include <iostream>

using namespace std;

int rows, columns;

int** mountain = nullptr;
int** a = nullptr;
int** b = nullptr;

int numHeights = 0;

int solve(int startx, int starty, int endx, int endy) {
    for (int i = 0; i < rows; ++i) {
        for (int c = 0; c < columns; ++c) {
            a[i][c] = -1;
        }
    }

    // init
    a[startx][starty] = mountain[startx][starty];

    while (true) {
        bool change = false;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                int candidates[5];
                candidates[0] = a[r][c];
                candidates[1] = r > 0 ? a[r - 1][c] : -1;
                candidates[2] = r + 1 < rows ? a[r + 1][c] : -1;
                candidates[3] = c > 0 ? a[r][c - 1] : -1;
                candidates[4] = c + 1 < columns ? a[r][c + 1] : -1;

                int realmin = -1;
                for (int i = 0; i < 5; ++i) {
                    if (candidates[i] > 0) {
                        realmin = realmin == -1 ? candidates[i]
                                                : min(realmin, candidates[i]);
                    }
                }
                if (realmin != -1) realmin = max(mountain[r][c], realmin);
                b[r][c] = realmin;
                if (realmin != a[r][c]) change = true;
            }
        }

        swap(a, b);

        if (!change) break;
    }

    return a[endx][endy];
}

int main() {
    int q;

    cin >> rows >> columns >> q;

    mountain = new int*[rows];
    a = new int*[rows];
    b = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        mountain[i] = new int[columns];
        a[i] = new int[columns];
        b[i] = new int[columns];
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            int f;
            cin >> f;
            mountain[r][c] = f;
        }
    }

    while (q--) {
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        cout << solve(startx - 1, starty - 1, endx - 1, endy - 1) << "\n";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] mountain[i];
        delete[] a[i];
        delete[] b[i];
    }
    delete[] a;
    delete[] b;
    delete[] mountain;

    return 0;
}
