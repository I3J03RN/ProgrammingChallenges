#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int T, ca = 1;
    scanf("%d", &T);
    while (T--) {
        int c[3];
        scanf("%d %d %d", c, c + 1, c + 2);
        sort(c, c + 3);
        printf("Case %d: %d\n", ca++, c[1]);
    }
    return 0;
}
