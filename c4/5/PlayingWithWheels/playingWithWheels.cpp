#include <cstring>
#include <deque>
#include <iostream>

using namespace std;

struct config {
    union {
        struct {
            uint8_t _1;
            uint8_t _2;
            uint8_t _3;
            uint8_t _4;
        };
        uint32_t full;
    };

    int getTen() { return _1 * 1000 + _2 * 100 + _3 * 10 + _4; }
};

struct bfsstate {
    config _config;
    int _depth;
};

bool visited[10000] = {false};

int main() {
    int numberofproblems;
    while (cin >> numberofproblems) {
        cin;
        config init, end;
        cin >> init._1 >> init._2 >> init._3 >> init._4;
        cin >> end._1 >> end._2 >> end._3 >> end._4;

        memset(visited, false, sizeof visited);

        int numberForbidden;
        cin >> numberForbidden;
        while (numberForbidden--) {
            config forbidden;
            cin >> forbidden._1 >> forbidden._2 >> forbidden._3 >> forbidden._4;
            visited[forbidden.getTen()] = true;
        }

        deque<bfsstate> bfsqueue;

        bfsqueue.push_back({init, 0});

        bool found = false;
        while (!bfsqueue.empty()) {
            bfsstate current = bfsqueue.front();
            if (current._config.full == end.full) {
                cout << current._depth << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "-1\n";
        }
    }

    return 0;
}
