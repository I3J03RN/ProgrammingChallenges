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
#define ALL(a) (a).begin(), (a).end()

const int MIN = 245182;
const int MAX = 790572;

array<int, 6> test;

bool test2() {
    for (int i = 0; i < 10; ++i) {
        if (count(test.begin(), test.end(), i) == 2) return true;
    }
    return false;
}

int main() {
    int count = 0;
    for (int num = MIN; num <= MAX; ++num) {
        int conv = num;
        for (int i = 0; i < 6; ++i) {
            test[i] = conv % 10;
            conv /= 10;
        }
        reverse(test.begin(), test.end());
        if (is_sorted(test.begin(), test.end()) &&
            test2()) {  // adjacent_find(test.begin(), test.end()) !=
                        // test.end()) {
            printf("found: %d\n", num);
            count++;
        }
    }
    printf("count: %d\n", count);
}
