#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

struct sensor {
    sensor(double x, double y) : x(x), y(y) {}
    double x, y;
};

struct connection {
    uint a, b;
    double distance;
};

class unionFind {
   public:
    unionFind(uint size) : _size(size) {
        data = new int[size];
        fill(data, data + size, -1);
    }
    ~unionFind() { delete[] data; }

    int find(int toFind) {
        int root = toFind;
        while (data[root] >= 0) root = data[root];

        while (toFind != root) {
            int tmp = data[toFind];
            data[toFind] = root;
            toFind = tmp;
        }

        return root;
    }

    void join(int a, int b) {
        if (data[a] < data[b]) {
            data[a] += data[b];
            data[b] = a;
        } else {
            data[b] += data[a];
            data[a] = b;
        }
        _size--;
    }

    uint size() { return _size; }

   private:
    int* data;
    uint _size;
};

int main() {
    uint n;
    cin >> n;

    while (n--) {
        uint numberRevTrans;
        cin >> numberRevTrans;
        vector<sensor> sensors;
        sensors.reserve(256);

        while (true) {
            int x, y;
            cin >> x;

            if (x == -1) break;

            cin >> y;
            sensors.emplace_back(x, y);
        }

        uint numberOfConnections = (sensors.size() * (sensors.size() - 1)) / 2;
        vector<connection> connections(numberOfConnections);
        for (uint a = 0, index = 0; a < sensors.size(); ++a) {
            for (uint b = a + 1; b < sensors.size(); ++b, ++index) {
                double distX = sensors[a].x - sensors[b].x;
                double distY = sensors[a].y - sensors[b].y;

                connections[index].a = a;
                connections[index].b = b;
                connections[index].distance = distX * distX + distY * distY;
            }
        }

        auto cmp = [](const connection& a, const connection& b) -> bool {
            return a.distance < b.distance;
        };
        sort(connections.begin(), connections.end(), cmp);

        unionFind unionFind(sensors.size());
        for (connection& c : connections) {
            int a = unionFind.find(c.a);
            int b = unionFind.find(c.b);

            if (a != b) {
                unionFind.join(a, b);
                if (unionFind.size() <= numberRevTrans) {
                    cout << ceil(sqrt(c.distance)) << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}
