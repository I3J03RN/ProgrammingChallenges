#include <cstring>
#include <deque>
#include <iostream>

using namespace std;

bool visited[10][10][10][10];

struct config {
    union {
        struct {
            short _1;
            short _2;
            short _3;
            short _4;
        };
        long full;
    };

    void setVisited() { visited[_1][_2][_3][_4] = true; }
    bool getVisited() { return visited[_1][_2][_3][_4]; }
};

ostream& operator<<(ostream& os, const config& config) {
    os << config._1 << ", " << config._2 << ", " << config._3 << ", "
       << config._4;
    return os;
}

struct bfsstate {
    config _config;
    int _depth;
};

ostream& operator<<(ostream& os, const bfsstate& bfsstate) {
    os << "config: " << bfsstate._config << ", depth: " << bfsstate._depth;
    return os;
}

int main() {
    int numberofproblems;
    cin >> numberofproblems;
    // cout << numberofproblems << "\n";
    while (numberofproblems--) {
        config init, end;
        cin >> init._1 >> init._2 >> init._3 >> init._4;
        cin >> end._1 >> end._2 >> end._3 >> end._4;

        // cout << "start: " << init << "\nend: " << end << "\n";
        memset(visited, false, 10000);

        int numberForbidden;
        cin >> numberForbidden;
        // cout << numberForbidden << "\n";
        while (numberForbidden--) {
            config forbidden;
            cin >> forbidden._1 >> forbidden._2 >> forbidden._3 >> forbidden._4;
            // cout << "forbidden: " << forbidden << "\n";
            forbidden.setVisited();
        }

        init.setVisited();

        deque<bfsstate> bfsqueue;

        bfsqueue.push_back({init, 0});

        bool found = false;
        while (!bfsqueue.empty()) {
            bfsstate current = bfsqueue.front();
            // cout << current << "\n";
            bfsqueue.pop_front();
            if (current._config.full == end.full) {
                cout << current._depth << "\n";
                found = true;
                break;
            }
            config newConfig = current._config;
            newConfig._1 = newConfig._1 == 9 ? 0 : newConfig._1 + 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._1 = current._config._1;
            newConfig._1 = newConfig._1 == 0 ? 9 : newConfig._1 - 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._1 = current._config._1;

            newConfig._2 = newConfig._2 == 9 ? 0 : newConfig._2 + 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._2 = current._config._2;
            newConfig._2 = newConfig._2 == 0 ? 9 : newConfig._2 - 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._2 = current._config._2;

            newConfig._3 = newConfig._3 == 9 ? 0 : newConfig._3 + 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }

            newConfig._3 = current._config._3;
            newConfig._3 = newConfig._3 == 0 ? 9 : newConfig._3 - 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._3 = current._config._3;

            newConfig._4 = newConfig._4 == 9 ? 0 : newConfig._4 + 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
            newConfig._4 = current._config._4;
            newConfig._4 = newConfig._4 == 0 ? 9 : newConfig._4 - 1;
            if (!newConfig.getVisited()) {
                bfsqueue.push_back({newConfig, current._depth + 1});
                newConfig.setVisited();
            }
        }
        if (!found) {
            cout << "-1\n";
        }
    }

    return 0;
}
