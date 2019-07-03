#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int rows, columns;

struct node {
    int x, y;
    int height;
};

int** mountain = nullptr;
int numHeights = 0;

int solve(int startx, int starty, int endx, int endy) {
    auto cmp = [](const node& a, const node& b) { return a.height < b.height; };
    priority_queue<node, vector<node>, decltype(cmp)> queue(cmp);

    while (queue.top().x != endx, queue.top().y != endy) {
    }

    return queue.top().height;
}

int main() {
    int q;

    cin >> rows >> columns >> q;

    mountain = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        mountain[i] = new int[columns];
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
    }
    delete[] mountain;

    return 0;
}
