#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

char buffer[201];
char map[201][201];

int n, m;

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

int floodfill(int x, int y, char find, char replace) {
    if (x < 0 || x >= m || y < 0 || y >= n) return 0;
    if (map[y][x] == find) {
        map[y][x] = replace;
        int sum = 1;
        for (int i = 0; i < 8; ++i)
            sum += floodfill(x + dx[i], y + dy[i], find, replace);
        return sum;
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    fgets(buffer, 200, stdin);
    fgets(buffer, 200, stdin);

    while (T--) {
        for (int i = 0;; ++i) {
            fgets(buffer, 200, stdin);
            if (buffer[0] == 'L' || buffer[0] == 'W')
                strcpy(map[i], buffer);
            else {
                n = i;
                break;
            }
        }
        m = strlen(map[0]);

        while (buffer[0] != '\n') {
            int i, j;
            sscanf(buffer, "%d %d", &i, &j);
            printf("%d\n", floodfill(j - 1, i - 1, 'W', 'X'));
            floodfill(j - 1, i - 1, 'X', 'W');

            if (!fgets(buffer, 200, stdin)) break;
        }

        if (T) printf("\n");
    }
}
