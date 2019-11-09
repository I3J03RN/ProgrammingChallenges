#include <cstdio>

using namespace std;

int main() {
    int cases, n, m;

    while (scanf("%d", &cases), cases) {
        scanf("%d %d", &n, &m);
        while (cases--) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (x == n || y == m)
                printf("divisa\n");
            else if (x > n) {
                if (y > m)
                    printf("NE\n");
                else
                    printf("SE\n");
            } else {
                if (y > m)
                    printf("NO\n");
                else
                    printf("SO\n");
            }
        }
    }

    return 0;
}
