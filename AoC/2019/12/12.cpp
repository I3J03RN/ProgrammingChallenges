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

struct v3 {
    int x, y, z;
};

array<v3, 4> planets;
array<v3, 4> start;
array<v3, 4> velocity;

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void updateGravityPair(int i, int j) {
    velocity[i].x -= sgn(planets[i].x - planets[j].x);
    velocity[j].x += sgn(planets[i].x - planets[j].x);
    velocity[i].y -= sgn(planets[i].y - planets[j].y);
    velocity[j].y += sgn(planets[i].y - planets[j].y);
    velocity[i].z -= sgn(planets[i].z - planets[j].z);
    velocity[j].z += sgn(planets[i].z - planets[j].z);
}

void updateGravity() {
    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j) updateGravityPair(i, j);
}

void step() {
    for (int i = 0; i < 4; ++i) {
        planets[i].x += velocity[i].x;
        planets[i].y += velocity[i].y;
        planets[i].z += velocity[i].z;
    }
}

void prettyPrint() {
    for (int i = 0; i < 4; ++i) {
        printf("pos=<x=%3d, y=%3d, z=%3d>, vel=<x=%3d, y=%3d, z=%3d>\n",
               planets[i].x, planets[i].y, planets[i].z, velocity[i].x,
               velocity[i].y, velocity[i].z);
    }
}

ll calcEnergie() {
    ll sum = 0;
    for (int i = 0; i < 4; ++i)
        sum += ((ll)abs(planets[i].x) + abs(planets[i].y) +
                (ll)abs(planets[i].z)) *
               ((ll)abs(velocity[i].x) + abs(velocity[i].y) +
                (ll)abs(velocity[i].z));

    return sum;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        scanf("<x=%d, y=%d, z=%d>\n", &planets[i].x, &planets[i].y,
              &planets[i].z);
        velocity[i] = {0, 0, 0};
    }
    start = planets;

    // printf("step %d:\n", 0);
    // prettyPrint();
    ll minX = 0, minY = 0, minZ = 0;
    for (ll i = 1; !minX || !minY || !minZ; ++i) {
        updateGravity();
        step();
        if (!minX) {
            bool t = true;
            for (int i = 0; t && i < 4; ++i)
                if (planets[i].x != start[i].x || velocity[i].x) t = false;
            if (t) minX = i;
        }
        if (!minY) {
            bool t = true;
            for (int i = 0; t && i < 4; ++i)
                if (planets[i].y != start[i].y || velocity[i].y) t = false;
            if (t) minY = i;
        }
        if (!minZ) {
            bool t = true;
            for (int i = 0; t && i < 4; ++i)
                if (planets[i].z != start[i].z || velocity[i].z) t = false;
            if (t) minZ = i;
        }
        // printf("step %lld:\n", i);
        // prettyPrint();
    }
    printf("%lld\n", lcm(minX, lcm(minY, minZ)));
}
