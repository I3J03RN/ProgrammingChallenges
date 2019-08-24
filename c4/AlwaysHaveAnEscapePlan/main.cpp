#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

struct vertex;

struct edge {
    uint capacity;
    uint flow;
    vertex* startVertex;
    vertex* endVertex;
};

struct vertex {
    vertex() : out(list<edge*>()), in(list<edge*>()), id(""), pred(NULL) {}

    string id;
    list<edge*> out;
    list<edge*> in;
    edge* pred;
};

// ostream& operator<<(ostream& out, const edge& e) {
//     out << e.startVertex->id << " --" << e.flow << "/" << e.capacity << "-->
//     "
//         << e.endVertex->id;
//     return out;
// }

// ostream& operator<<(ostream& out, const vertex& v) {
//     out << v.id << ", pred: ";
//     if (v.pred != NULL)
//         out << *v.pred << "\n";
//     else
//         out << "none\n";
//     out << "in:\n";
//     for (edge* e : v.in) {
//         out << "  " << *e << "\n";
//     }
//     out << "out:\n";
//     for (edge* e : v.out) {
//         out << "  " << *e << "\n";
//     }
//     return out;
// }

vertex vdummy;
edge dummy = {1337, 42, &vdummy, &vdummy};

uint setAugmentPath(vector<vertex>& vertices, vertex& start, vertex& end) {
    vertex* current = &end;
    uint minValue = end.pred->startVertex == current ? end.pred->flow : end.pred->capacity - end.pred->flow;
    while (current != &start) {
        if (current->pred->startVertex == current) {
            minValue = min(minValue, current->pred->flow);
            current = current->pred->endVertex;
        } else {
            minValue =
                min(minValue, current->pred->capacity - current->pred->flow);
            current = current->pred->startVertex;
        }
    }
    current = &end;
    while (current != &start) {
        if (current->pred->startVertex == current) {
            current->pred->flow -= minValue;
            current = current->pred->endVertex;
        } else {
            current->pred->flow += minValue;
            current = current->pred->startVertex;
        }
    }

    return minValue;
}

uint augment(vector<vertex>& vertices, vertex& start, vertex& end) {
    for (vector<vertex>::iterator v = vertices.begin(); v != vertices.end();
         ++v) {
        v->pred = NULL;
    }

    queue<vertex*> q;
    q.push(&start);
    start.pred = &dummy;
    while (!q.empty()) {
        vertex* current = q.front();
        // cout << "selected: " << *current << "-----------------\n";
        q.pop();
        for (list<edge*>::iterator it = current->out.begin();
             it != current->out.end(); ++it) {
            edge* e = *it;
            if (e->endVertex->pred == NULL && e->capacity > e->flow) {
                if (e->endVertex == &end) {
                    end.pred = e;
                    return setAugmentPath(vertices, start, end);
                } else {
                    q.push(e->endVertex);
                    e->endVertex->pred = e;
                }
            }
        }
        for (list<edge*>::iterator it = current->in.begin();
             it != current->in.end(); ++it) {
            edge* e = *it;
            if (e->startVertex->pred == NULL && e->flow > 0) {
                if (e->startVertex == &end) {
                    end.pred = e;
                    return setAugmentPath(vertices, start, end);
                } else {
                    q.push(e->startVertex);
                    e->startVertex->pred = e;
                }
            }
        }
    }

    return 0;
}

uint maxFlow(vector<vertex>& vertices, vertex& start, vertex& end) {
    uint maxFlowValue = 0;
    uint augmentingValue = augment(vertices, start, end);

    while (augmentingValue > 0) {
        // cout << "augmented by " << augmentingValue << "\n";
        // for (vertex& v : vertices) cout << v << "\n";
        maxFlowValue += augmentingValue;
        augmentingValue = augment(vertices, start, end);
    }

    return maxFlowValue;
}

int main() {
    uint n;
    cin >> n;
    while (n--) {
        uint numberOfRooms;
        cin >> numberOfRooms;
        vector<vertex> rooms(numberOfRooms * 2);
        // rooms.front().id = "start (1)";
        // for (uint i = 1; i < numberOfRooms * 2 - 1; ++i) {
        //     if ((i & 1) == 1) {
        //         rooms[i].id = "(" + to_string(i / 2 + 2) + ") in";
        //     } else {
        //         rooms[i].id = "(" + to_string(i / 2 + 1) + ") out";
        //     }
        // }
        // rooms.back().id = "sink (extra)";
        uint numberOfSafeRooms;
        cin >> numberOfSafeRooms;
        vector<uint> safeRooms;
        safeRooms.reserve(numberOfSafeRooms);
        
        for (uint i = 0; i < numberOfSafeRooms; ++i) {
            uint tmp;
            cin >> tmp;
            safeRooms.push_back(tmp);
        }

        list<edge> corridors;

        uint numberOfCorridors;
        cin >> numberOfCorridors;
        while (numberOfCorridors--) {
            uint a, b;
            cin >> a >> b;
            a = (a - 1) * 2;
            b = (b == 1 ? 0 : b * 2 - 3);
	    // cout << a << ", " << b << "\n";
            edge tmp = {1, 0, &rooms[a], &rooms[b]};
            corridors.push_front(tmp);
            rooms[a].out.push_front(&corridors.front());
            rooms[b].in.push_front(&corridors.front());
        }
        for (vector<uint>::iterator safeRoom = safeRooms.begin();
             safeRoom != safeRooms.end(); ++safeRoom) {
            uint safeRoomIndex = (*safeRoom - 1) * 2;
	    // cout << safeRoomIndex << "\n";
            edge tmp = {1, 0, &rooms[safeRoomIndex], &rooms.back()};
            corridors.push_front(tmp);
            rooms[safeRoomIndex].out.push_front(&corridors.front());
            rooms.back().in.push_front(&corridors.front());
        }
        for (uint i = 0; i < numberOfRooms - 1; ++i) {
            uint a = i * 2 + 1;
            uint b = a + 1;
            edge tmp = {1, 0, &rooms[a], &rooms[b]};
            corridors.push_front(tmp);
            rooms[a].out.push_front(&corridors.front());
            rooms[b].in.push_front(&corridors.front());
        }

        // for (vertex& v : rooms) cout << v << "\n";

        uint d;
        cin >> d;

        uint max = maxFlow(rooms, rooms.front(), rooms.back());

        if (max >= d) {
            cout << "safe\n";
        } else {
            cout << "unsafe\n";
        }
	// cout << max << "/" << d << "\n";
    }
    return 0;
}
