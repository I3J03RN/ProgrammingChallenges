#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

const double eps = 1e-6;

enum ptype { Fuel = 0, Goal, Leak, Gas, Mechanic };

string typeNames[] = {"Fuel", "Goal", "Leak", "Gas", "Mechanic"};

struct part {
    part(double dist, ptype type, double consumption)
        : dist(dist), type(type), consumption(consumption) {}
    double dist;
    ptype type;
    double consumption;
};

vector<part> route;

ostream& operator<<(ostream&, const part&);

bool test(double tankVol) {
    double fuel = tankVol;
    int leaks = 0;
    double consumption = 0;
    double last = 0;
    double dist = 0;
    for (auto& p : route) {
        dist = p.dist - last;
        last = p.dist;
        fuel -= (consumption / 100.0 + leaks) * dist;
        if (fuel < 0) return false;
        // cout << p << ": " << fuel << ", " << leaks << ", " << consumption
        //      << endl;

        switch (p.type) {
            case Fuel:
                consumption = p.consumption;
                break;
            case Goal:
                break;
            case Leak:
                leaks++;
                break;
            case Gas:
                fuel = tankVol;
                break;
            case Mechanic:
                leaks = 0;
                break;
        }
    }
    return true;
}

ostream& operator<<(ostream& o, const part& p) {
    o << p.dist << ' ' << typeNames[p.type];
    if (p.type == Fuel) o << ' ' << p.consumption;
    return o;
}

char buffer[1010];
char event[100];

int main() {
    while (1) {
        route.clear();
        while (1) {
            fgets(buffer, 1000, stdin);
            char* p = buffer;
            double d;
            int n;
            sscanf(p, "%lf %50s%n", &d, event, &n);
            p += n;
            if (strcmp(event, "Fuel") == 0) {
                double c;
                sscanf(p, "%*s %lf", &c);
                if (c == 0 && d == 0) return 0;
                route.emplace_back(d, Fuel, c);
            } else if (strcmp(event, "Goal") == 0) {
                route.emplace_back(d, Goal, 0);
                break;
            } else if (strcmp(event, "Leak") == 0)
                route.emplace_back(d, Leak, 0);
            else if (strcmp(event, "Gas") == 0)
                route.emplace_back(d, Gas, 0);
            else
                route.emplace_back(d, Mechanic, 0);
        }
        // for (auto& p : route) cout << p << endl;
        double l = 0.0, r = 2.0;
        while (!test(r)) r *= 2.0;
        while (abs(r - l) >= eps) {
            double mid = (l + r) / 2.0;
            // cout << mid << endl;
            if (test(mid))
                r = mid;
            else
                l = mid;
        }
        printf("%.03lf\n", l);
    }
}
