#include <cmath>
#include <forward_list>
#include <iostream>
#include <queue>

#define getIndex(x) (x - 'A')
#define getId(x) (char)(x + 'A')

using namespace std;

struct Planet {
    uint8_t index;
    bool end;
    double value;
    forward_list<Planet*> dests;
};

ostream& operator<<(ostream& os, const Planet& planet) {
    string dests = "";
    for (Planet* p : planet.dests) {
        dests += getId(p->index);
        dests += ", ";
    }
    os << "Planet: " << getId(planet.index) << ", value: " << planet.value
       << ", end: " << planet.end << ", dests: " << dests;
    return os;
}

uint32_t findEnd(Planet& planet) {
    uint8_t visited[26] = {0};
    queue<Planet*> bfsqueue;
    Planet* current = nullptr;
    bfsqueue.push(&planet);
    visited[planet.index] = 1;
    while (!bfsqueue.empty()) {
        current = bfsqueue.front();
        bfsqueue.pop();
        if (current->end) return visited[current->index];
        for (Planet* p : current->dests) {
            if (visited[p->index] == 0) {
                visited[p->index] = visited[current->index] + 1;
                bfsqueue.push(p);
            }
        }
    }
    return 0;
}

int main() {
    Planet planets[26];
    for (char c = 0; c < 26; ++c) {
        planets[(uint32_t)c].index = c;
    }
    uint32_t n;
    while (cin >> n) {
        // cout << "---------------\n";
        auto cmp = [](Planet* a, Planet* b) -> bool {
            return a->value < b->value;
        };
        std::priority_queue<Planet*, vector<Planet*>, decltype(cmp)> prioQueue(
            cmp);
        while (n--) {
            char identifier;
            double value;
            string dests;
            cin >> identifier >> value >> dests;
            Planet* planet = planets + getIndex(identifier);
            planet->value = value;
            planet->dests.clear();
            planet->end = false;
            for (char c : dests) {
                if (c == '*')
                    planet->end = true;
                else
                    planet->dests.push_front(planets + getIndex(c));
            }
            prioQueue.push(planet);

            // cout << *planet << "\n";
        }
        // cout << "max: " << *prioQueue.top() << "\n";
        Planet* maxPlanet = prioQueue.top();
        prioQueue.pop();
        double maxValue = maxPlanet->value * pow(.95, findEnd(*maxPlanet));
        while (!prioQueue.empty()) {
            Planet* p = prioQueue.top();
            prioQueue.pop();
            uint32_t hops = findEnd(*p);
            double newValue = p->value * pow(.95, hops);
            if (newValue > maxValue) {
                maxValue = newValue;
                maxPlanet = p;
            }
            if (maxValue > prioQueue.top()->value) break;
        }
        cout << "Import from " << getId(maxPlanet->index) << "\n";
    }
    return 0;
}
