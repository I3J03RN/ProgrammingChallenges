#include <cmath>
#include <forward_list>
#include <iostream>
#include <queue>

#define getIndex(x) x - 'A'

using namespace std;

struct Planet {
    char id;
    bool end;
    float value;
    forward_list<Planet*> dests;
};

ostream& operator<<(ostream& os, const Planet& planet) {
    string dests = "";
    for (Planet* p : planet.dests) {
        dests += p->id;
        dests += ", ";
    }
    os << "Planet: " << planet.id << ", value: " << planet.value
       << ", end: " << planet.end << ", dests: " << dests;
    return os;
}

uint32_t findEnd(Planet& planet) {
    uint8_t visited[26] = {0};
    queue<Planet*> bfsqueue;
    Planet* current = nullptr;
    bfsqueue.push(&planet);
    visited[getIndex(planet.id)] = 1;
    while (!bfsqueue.empty()) {
        current = bfsqueue.front();
        bfsqueue.pop();
        if (current->end) return visited[getIndex(current->id)];
        for (Planet* p : current->dests) {
            if (visited[getIndex(p->id)] == 0) {
                visited[getIndex(p->id)] = visited[getIndex(current->id)] + 1;
                bfsqueue.push(p);
            }
        }
    }
    return 0;
}

int main() {
    Planet planets[26];
    for (char c = 'A'; c <= 'Z'; c++) {
        planets[getIndex(c)].id = c;
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
            float value;
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
        float maxValue = pow(maxPlanet->value, findEnd(*maxPlanet));
        while (!prioQueue.empty()) {
            Planet* p = prioQueue.top();
            prioQueue.pop();
            uint32_t hops = findEnd(*p);
            float newValue = pow(p->value, hops);
            if (newValue > maxValue) {
                maxValue = newValue;
                maxPlanet = p;
            }
            if (maxValue > prioQueue.top()->value) break;
        }
        cout << maxPlanet->id << "\n";
    }
    return 0;
}
