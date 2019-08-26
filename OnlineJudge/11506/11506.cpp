#include <algorithm>
#include <cstring>
#include <forward_list>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

struct edge;

struct vertex {
    vertex()
        : id(idCounter++),
          out(forward_list<edge*>()),
          in(forward_list<edge*>()),
          pred(nullptr) {}

    uint id;
    forward_list<edge*> out;
    forward_list<edge*> in;
    edge* pred;

   private:
    static uint idCounter;
};

uint vertex::idCounter = 0;

struct edge {
    edge(uint capacity, vertex* startVertex, vertex* endVertex)
        : capacity(capacity),
          flow(0),
          startVertex(startVertex),
          endVertex(endVertex) {
        if (startVertex != nullptr) startVertex->out.push_front(this);
        if (endVertex != nullptr) endVertex->in.push_front(this);
    }

    uint capacity;
    uint flow;
    vertex* startVertex;
    vertex* endVertex;
};

ostream& operator<<(ostream& out, const edge& e) {
    if (e.startVertex != nullptr)
        out << e.startVertex->id;
    else
        out << "NONE";

    out << " --" << e.flow << "/" << e.capacity << "--> ";

    if (e.endVertex != nullptr)
        out << e.endVertex->id;
    else
        out << "NONE";

    return out;
}

ostream& operator<<(ostream& out, const vertex& v) {
    out << v.id << ", pred: ";
    if (v.pred != nullptr)
        out << *v.pred << "\n";
    else
        out << "none\n";
    out << "in:\n";
    for (edge* e : v.in) {
        out << "  " << *e << "\n";
    }
    out << "out:\n";
    for (edge* e : v.out) {
        out << "  " << *e << "\n";
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
    edge dummy = {1337, nullptr, nullptr};

    queue<vertex*> q;
    q.push(&start);
    start.pred = &dummy;
    while (!q.empty()) {
        vertex* current = q.front();
        q.pop();
        for (edge* e : current->out) {
            if (e->endVertex->pred == nullptr && e->capacity > e->flow) {
                if (e->endVertex == &end) {
                    end.pred = e;
                    return setAugmentPath(start, end);
                } else {
                    q.push(e->endVertex);
                    e->endVertex->pred = e;
                }
            }
        }
        for (edge* e : current->in) {
            if (e->startVertex->pred == nullptr && e->flow > 0) {
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
        for (vertex& v : vertices) {
            v.pred = nullptr;
        }
        maxFlowValue += augmentingValue;
        augmentingValue = augment(start, end);
    }

    return maxFlowValue;
}

int main() {
    while (true) {
        uint pcs, wires;
        cin >> pcs >> wires;

        if (pcs == 0 && wires == 0) break;

        vector<vertex> vertices(pcs + (pcs - 2) * 2 + wires);
        uint wireOffset = pcs + (pcs - 2) * 2;

        forward_list<edge> edges;

        for (uint i = 2; i < pcs; ++i) {
            uint pc, cost;
            cin >> pc >> cost;

            uint inIndex = (pc - 2) * 3 + 1;
            uint dummyIndex = (pc - 2) * 3 + 2;
            uint outIndex = (pc - 2) * 3 + 3;

            edges.emplace_front(cost, &vertices[inIndex], &vertices[outIndex]);
            edges.emplace_front(cost, &vertices[outIndex],
                                &vertices[dummyIndex]);
            edges.emplace_front(cost, &vertices[dummyIndex],
                                &vertices[inIndex]);
        }

        for (uint i = 0; i < wires; ++i) {
            uint a, b, cost;
            cin >> a >> b >> cost;
            uint aOut, aIn, bOut, bIn;
            if (a == 1) {
                aOut = aIn = 0;
            } else if (a == pcs) {
                aOut = aIn = wireOffset - 1;
            } else {
                aIn = (a - 2) * 3 + 1;
                aOut = (a - 2) * 3 + 3;
            }
            if (b == 1) {
                bOut = bIn = 0;
            } else if (b == pcs) {
                bOut = bIn = wireOffset - 1;
            } else {
                bIn = (b - 2) * 3 + 1;
                bOut = (b - 2) * 3 + 3;
            }
            uint dummyIndex = wireOffset + i;

            edges.emplace_front(cost, &vertices[aOut], &vertices[bIn]);
            edges.emplace_front(cost, &vertices[bOut], &vertices[dummyIndex]);
            edges.emplace_front(cost, &vertices[dummyIndex], &vertices[aIn]);
        }
        cout << maxFlow(vertices, vertices[0], vertices[wireOffset - 1])
             << "\n";
    }
    return 0;
}
