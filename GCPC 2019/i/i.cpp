#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <utility>
#include <string>
#include <list>
#include <cmath>

using namespace std;

void addHideNodes(list<int>& solution, int min, int max) {
    // cout << "rec: " << min << ", " << max << '\n';
    if (min > max)
    return;
    int mid = (max + min) / 2;
// cout << mid << endl;
    addHideNodes(solution, min, mid - 1);
    addHideNodes(solution, mid + 1, max);
    solution.push_front(mid);

}

int main() {
    int nodes, height;
    cin >> nodes >> height;

    if (nodes > pow(2, height) - 1 || nodes < height) {
        cout << "impossible\n";
        return 0;
    }

    int restNodes = nodes - height;
    int hideable = 1;

    list<int> solution;

// cout << nodes << endl;
    solution.push_front(nodes--);

    while (nodes) {
        if (restNodes > 0) {
  //          cout << "hide: " << nodes << "\n";
            int hideNow = min(hideable, restNodes);
            addHideNodes(solution, nodes - hideNow, nodes - 1);
//cout << nodes << endl;
            solution.push_front(nodes--);
            nodes = nodes - hideNow;
            restNodes -= hideNow;

        } else {
    //        cout << "no hide\n";
//cout << nodes << endl;
            solution.push_front(nodes--);
        }
        hideable = (hideable + 1) * 2 - 1;

    }

for (int i : solution) {
    cout << i << " ";
}
cout << '\n';

}