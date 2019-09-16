#include <algorithm>
#include <cstdint>
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
          weight(0),
          out(forward_list<edge*>()),
          in(forward_list<edge*>()),
          pred(nullptr) {}

    uint id;
    int weight;
    forward_list<edge*> out;
    forward_list<edge*> in;
    edge* pred;

   private:
    static uint idCounter;
};

uint vertex::idCounter = 0;

struct edge {
    edge(uint capacity, uint64_t cost, vertex* startVertex, vertex* endVertex)
        : capacity(capacity),
          flow(0),
          cost(cost),
          startVertex(startVertex),
          endVertex(endVertex) {
        if (startVertex != nullptr) startVertex->out.push_front(this);
        if (endVertex != nullptr) endVertex->in.push_front(this);
    }

    uint capacity;
    uint flow;
    uint64_t cost;
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

struct queue_entry {
    vertex* v;
    uint64_t cost;
};

uint augment(vertex& start, vertex& end, size_t numberVertices) {
    edge dummy = {1337, 0, nullptr, nullptr};
    vector<uint64_t> cost(numberVertices);
    auto cmp = [](queue_entry& a, queue_entry& b) {
        return greater<uint64_t>()(a.cost, b.cost);
    };

    priority_queue<queue_entry, vector<queue_entry>, decltype(cmp)> q(cmp);
    q.push({&start, 0});
    start.pred = &dummy;
    while (!q.empty()) {
        auto current = q.top();
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

void calculateWeight(vector<vertex>& vertices) {
    // vertex for potential calculation
    vertex q;
    forward_list<edge> tmpEdges;
    for (vertex& v : vertices) {
        tmpEdges.push_front(edge(0, 0, &q, &v));
    }

    // Bellman Ford
    vector<uint64_t> a(vertices.size());
    vector<uint64_t> b(vertices.size());
    for (uint64_t i = 1; i < vertices.size(); ++i) {
        for (uint v = 0; v < vertices.size(); ++v) {
            for (edge* in : vertices[v].in) {
                b[v] = min(
                    a[v], a[(&vertices[0] - in->startVertex) / sizeof(vertex)] +
                              in->cost);
            }
            for (edge* out : vertices[v].out) {
                b[v] = min(a[v],
                           a[(&vertices[0] - out->endVertex) / sizeof(vertex)] +
                               in->cost);
            }
        }
        swap(a, b);
    }

    for (uint64_t i = 0; i < vertices.size(); ++i) {
        vertices[i].weight = a[i];
        vertices[i].in.pop_front();
    }
}

uint maxFlowMinCost(vector<vertex>& vertices, vertex& start, vertex& end) {
    calculateWeight(vertices);
    uint maxFlowValue = 0;
    uint augmentingValue = augment(start, end, vertices.size());

    while (augmentingValue > 0) {
        for (vertex& v : vertices) {
            v.pred = nullptr;
        }
        maxFlowValue += augmentingValue;
        augmentingValue = augment(start, end, vertices.size());
    }

    return maxFlowValue;
}

int main() {
    while (true) {
        uint numberVertices, numberEdges;
        cin >> numberVertices >> numberEdges;
        if (std::cin.eof()) break;

        vector<vertex> vertices(numberVertices + numberEdges);
        forward_list<edge> edges;

        for (uint i = 0; i < numberEdges; ++i) {
            uint a, b;
            uint64_t cost;
            cin >> a >> b >> cost;
            a--;
            b--;
            edges.emplace_front(0, 2 * cost, &vertices[a], &vertices[b]);
            edges.emplace_front(0, cost, &vertices[b],
                                &vertices[numberVertices + i]);
            edges.emplace_front(0, cost, &vertices[numberVertices + i],
                                &vertices[a]);
        }

        uint data, linkCapacity;
        cin >> data >> linkCapacity;

        int64_t cost = maxFlowMinCost(vertices, vertices.front(),
                                      vertices[numberVertices - 1]);
        if (cost < 0) {
            cout << "Impossible.\n";
        } else {
            cout << (cost / 2) << "\n";
        }
    }
    return 0;
}
