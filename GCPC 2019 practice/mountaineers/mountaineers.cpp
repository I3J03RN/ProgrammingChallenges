#include <deque>
#include <forward_list>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

int rows, columns;

int** mountain = nullptr;

int numHeights = 0;

int* heights = nullptr;

bool reachable(int startx, int starty, int endx, int endy, int maxH) {
    if (mountain[startx][starty] > maxH || mountain[endx][endy] > maxH)
        return false;
    deque<pair<int, int>> queue;
    forward_list<pair<int, int>> visited;
    queue.push_back({startx, starty});
    visited.push_front({startx, starty});
    mountain[startx][starty] *= -1;
    bool found = false;
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop_front();

        if (current.first == endx && current.second == endy) {
            found = true;
            break;
        }

        if (current.first > 0) {
            if (mountain[current.first - 1][current.second] > 0 &&
                mountain[current.first - 1][current.second] <= maxH) {
                queue.push_back({current.first - 1, current.second});
                visited.push_front({current.first - 1, current.second});
                mountain[current.first - 1][current.second] *= -1;
            }
        }
        if (current.first < rows - 1) {
            if (mountain[current.first + 1][current.second] > 0 &&
                mountain[current.first + 1][current.second] <= maxH) {
                queue.push_back({current.first + 1, current.second});
                visited.push_front({current.first + 1, current.second});
                mountain[current.first + 1][current.second] *= -1;
            }
        }
        if (current.second > 0) {
            if (mountain[current.first][current.second - 1] > 0 &&
                mountain[current.first][current.second - 1] <= maxH) {
                queue.push_back({current.first, current.second - 1});
                visited.push_front({current.first, current.second - 1});
                mountain[current.first][current.second - 1] *= -1;
            }
        }
        if (current.second < columns - 1) {
            if (mountain[current.first][current.second + 1] > 0 &&
                mountain[current.first][current.second + 1] <= maxH) {
                queue.push_back({current.first, current.second + 1});
                visited.push_front({current.first, current.second + 1});
                mountain[current.first][current.second + 1] *= -1;
            }
        }
    }
    for (auto i : visited) {
        mountain[i.first][i.second] *= -1;
    }
    return found;
}

int solve(int startx, int starty, int endx, int endy) {
    int l = 0, r = numHeights - 1;
    while (l != r) {
        // cout << l << ", " << r << "\n";
        int mid = (r + l) / 2;
        // cout << mid << endl;
        if (reachable(startx, starty, endx, endy, heights[mid])) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return heights[l];
}

int main() {
    int q;

    cin >> rows >> columns >> q;

    mountain = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        mountain[i] = new int[columns];
    }

    set<int> hs;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            int f;
            cin >> f;
            mountain[r][c] = f;
            auto p = hs.insert(f);
            if (p.second) numHeights++;
        }
    }

    int index = 0;
    heights = new int[numHeights];
    for (int i : hs) {
        heights[index++] = i;
        // cout << i << endl;
    }

    // cout << "-------------------------------\n";

    while (q--) {
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        cout << solve(startx - 1, starty - 1, endx - 1, endy - 1) << "\n";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] mountain[i];
    }
    delete[] mountain;
    delete[] heights;

    return 0;
}
