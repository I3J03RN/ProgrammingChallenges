#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        int scarries;
        scanf("%d", &scarries);
        vector<int> speeds(scarries);
        for (int j = 0; j < scarries; ++j) {
            scanf("%d", &speeds[j]);
        }
        printf("Case %d: %d\n", i, *max_element(speeds.begin(), speeds.end()));
    }
}
