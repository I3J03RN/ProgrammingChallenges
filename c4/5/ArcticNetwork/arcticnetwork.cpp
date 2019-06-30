#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

#define Log(x) cout << x << "\n";

using namespace std;

struct outpost {
    double x, y;
};

struct connection {
    int a, b;
    double weigth;
};

ostream& operator<<(ostream& os, const outpost& outpost) {
    os << "x: " << outpost.x << ", y: " << outpost.y;
    return os;
}

ostream& operator<<(ostream& os, const connection& connection) {
    os << "from " << connection.a << " to " << connection.b << " costs "
       << connection.weigth;
    return os;
}

bool cmp(const connection& a, const connection& b) {
    return a.weigth < b.weigth;
};

int find(int* parent, int node) {
    int root = node;
    while (parent[root] >= 0) root = parent[root];

    while (node != root) {
        int tmp = parent[node];
        parent[node] = root;
        node = tmp;
    }

    return root;
}

void join(int* parent, int a, int b) {
    int newSize = parent[a] + parent[b];
    if (parent[a] < parent[b]) {
        parent[b] = a;
        parent[a] = newSize;
    } else {
        parent[a] = b;
        parent[b] = newSize;
    }
}

int main() {
    int numberOfTestCases;

    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        int numOutposts, sateliteConnections;
        cin >> sateliteConnections >> numOutposts;

        outpost* outposts = new outpost[numOutposts];

        for (int i = 0; i < numOutposts; ++i) {
            double x, y;
            cin >> x >> y;
            outposts[i].x = x;
            outposts[i].y = y;
        }

        int numConnects = (numOutposts * (numOutposts - 1)) / 2;

        connection* connections = new connection[numConnects];

        for (int a = 0, index = 0; a < numOutposts; ++a) {
            for (int b = a + 1; b < numOutposts; ++index, ++b) {
                double distanceX = outposts[a].x - outposts[b].x;
                double distanceY = outposts[a].y - outposts[b].y;
                double distance = distanceX * distanceX + distanceY * distanceY;
                connections[index].a = a;
                connections[index].b = b;
                connections[index].weigth = distance;
            }
        }

        std::sort(connections, connections + numConnects, cmp);

        // for (int i = 0; i < numConnects; ++i) {
        //     cout << connections[i] << "\n";
        // }

        int* msts = new int[numOutposts];
        fill(msts, msts + numOutposts, -1);

        // for (int i = 0; i < numOutposts; ++i) cout << msts[i] << "\n";

        if (sateliteConnections < numOutposts) {
            for (int i = 0; i < numConnects; ++i) {
                connection& current = connections[i];
                int a = find(msts, current.a);
                int b = find(msts, current.b);
                if (a != b) {
                    join(msts, a, b);
                    numOutposts--;
                    if (sateliteConnections >= numOutposts) {
                        cout << setprecision(2) << fixed << sqrt(current.weigth)
                             << "\n";
                        break;
                    }
                }
            }
        } else {
            cout << "0.00\n";
        }

        delete[] outposts;
        delete[] connections;
        delete[] msts;
    }

    return 0;
}
