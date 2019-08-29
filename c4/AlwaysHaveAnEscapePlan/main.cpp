#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

struct edge;

struct vertex {
    vertex()
        : id(idCounter++), out(list<edge*>()), in(list<edge*>()), pred(NULL) {}

    uint id;
    list<edge*> out;
    list<edge*> in;
    edge* pred;

   private:
    static uint idCounter;
};

uint vertex::idCounter = 0;

ostream& operator<<(ostream& out, const edge& e);

struct edge {
    edge(uint capacity, vertex* startVertex, vertex* endVertex)
        : capacity(capacity),
          flow(0),
          startVertex(startVertex),
          endVertex(endVertex) {
        if (startVertex != NULL) startVertex->out.push_front(this);
        if (endVertex != NULL) endVertex->in.push_front(this);
        // cout << *this << endl;
    }

    uint capacity;
    uint flow;
    vertex* startVertex;
    vertex* endVertex;
};

ostream& operator<<(ostream& out, const edge& e) {
    if (e.startVertex != NULL)
        out << e.startVertex->id;
    else
        out << "NONE";

    out << " --" << e.flow << "/" << e.capacity << "--> ";

    if (e.endVertex != NULL)
        out << e.endVertex->id;
    else
        out << "NONE";

    return out;
}

ostream& operator<<(ostream& out, const vertex& v) {
    out << v.id << ", pred: ";
    if (v.pred != NULL)
        out << *(v.pred) << "\n";
    else
        out << "none\n";
    out << "in:\n";
    for (list<edge*>::const_iterator e = v.in.begin(); e != v.in.end(); ++e) {
        out << "  " << **e << "\n";
    }
    out << "out:\n";
    for (list<edge*>::const_iterator e = v.out.begin(); e != v.out.end(); ++e) {
        out << "  " << **e << "\n";
    }
    return out;
}

uint setAugmentPath(vertex& start, vertex& end) {
    vertex* current = &end;
    uint minValue = end.pred->startVertex == current
                        ? end.pred->flow
                        : end.pred->capacity - end.pred->flow;
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

uint augment(vertex& start, vertex& end) {
    edge dummy(1337, NULL, NULL);

    queue<vertex*> q;
    q.push(&start);
    start.pred = &dummy;
    while (!q.empty()) {
        vertex* current = q.front();
        q.pop();
        for (list<edge*>::iterator it = current->out.begin();
             it != current->out.end(); ++it) {
            edge* e = *it;
            if (e->endVertex->pred == NULL && e->capacity > e->flow) {
                if (e->endVertex == &end) {
                    end.pred = e;
                    return setAugmentPath(start, end);
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
                    return setAugmentPath(start, end);
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
    uint augmentingValue = augment(start, end);

    while (augmentingValue > 0) {
        for (vector<vertex>::iterator it = vertices.begin();
             it != vertices.end(); ++it) {
            (*it).pred = NULL;
        }
        maxFlowValue += augmentingValue;
        augmentingValue = augment(start, end);
    }

    return maxFlowValue;
}

int main() {
    uint n;
    cin >> n;
    while (n--) {
        uint numberOfRooms;
        cin >> numberOfRooms;
        vector<vertex> rooms;
        rooms.reserve(numberOfRooms * 2);
        for (uint i = 0; i < numberOfRooms * 2; ++i) {
            rooms.push_back(vertex());
        }
        uint numberOfSafeRooms;
        cin >> numberOfSafeRooms;
        vector<uint> safeRooms;
        safeRooms.reserve(numberOfSafeRooms);

        for (uint i = 0; i < numberOfSafeRooms; ++i) {
            uint tmp;
            cin >> tmp;
            safeRooms.push_back(tmp);
        }

        list<edge*> corridors;

        uint numberOfCorridors;
        cin >> numberOfCorridors;
        while (numberOfCorridors--) {
            uint a, b;
            cin >> a >> b;
            a = (a - 1) * 2;
            b = (b == 1 ? 0 : b * 2 - 3);
            // cout << a << ", " << b << "\n";
            corridors.push_front(new edge(1, &rooms[a], &rooms[b]));
        }
        for (vector<uint>::iterator safeRoom = safeRooms.begin();
             safeRoom != safeRooms.end(); ++safeRoom) {
            uint safeRoomIndex = (*safeRoom - 1) * 2;
            // cout << safeRoomIndex << "\n";
            corridors.push_front(
                new edge(1, &rooms[safeRoomIndex], &rooms.back()));
        }
        for (uint i = 0; i < numberOfRooms - 1; ++i) {
            uint a = i * 2 + 1;
            uint b = a + 1;
            corridors.push_front(new edge(1, &rooms[a], &rooms[b]));
        }

        // for (vector<vertex>::iterator v = rooms.begin(); v != rooms.end();
        // ++v) cout << *v << "\n";

        uint d;
        cin >> d;

        uint max = maxFlow(rooms, rooms.front(), rooms.back());

        if (max >= d) {
            cout << "safe\n";
        } else {
            cout << "unsafe\n";
        }
        for (list<edge*>::iterator e = corridors.begin(); e != corridors.end();
             ++e)
            delete *e;
        // cout << max << "/" << d << "\n";
    }
    return 0;
}
