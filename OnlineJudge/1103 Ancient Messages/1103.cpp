#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

char map[200][210];

char buffer[210];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int H, W;

void printMap() {
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) printf("%c", map[i][j]);
        printf("\n");
    }
}

char flood(int x, int y, char find, char replace) {
    if (x < 0 || x >= W || y < 0 || y >= H) return 0;
    if (map[y][x] == find) {
        map[y][x] = replace;
        char rets[4];
        for (int d = 0; d < 4; d++) {
            rets[d] = flood(x + dx[d], y + dy[d], find, replace);
        }
        char ret = -2;
        char last = -1;
        for (int i = 0; i < 4; ++i) {
            if (rets[i] != -1 && ret != rets[i]) {
                last = ret;
                ret = rets[i];
            }
        }
        if (ret == -2) {
            ret = -1;
            last = -2;
        }
        if (last != -2) ret = 0;
        return ret;
    }
    return map[y][x] == replace ? -1 : map[y][x];
}

char glyphId = 'A';

int main() {
    int casenr = 1;
    while (scanf("%d %d", &H, &W), H) {
        glyphId = 'A';
        fgets(buffer, 200, stdin);
        for (int i = 0; i < H; ++i) {
            fgets(buffer, 200, stdin);
            for (int j = 0; j < W; ++j) {
                char c[2];
                c[0] = buffer[j];
                c[1] = 0;
                int t;
                sscanf(c, "%x", &t);
                for (int k = 0; k < 4; ++k)
                    map[i][(j << 2) | k] = (1 << (3 - k)) & t ? '1' : '0';
            }
        }
        W *= 4;
        // printMap();
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j)
                if (map[i][j] == '1') flood(j, i, '1', glyphId++);
        }
        // printMap();
        int numGlyghs = glyphId - 'A';
        vector<int> g(numGlyghs, 0);

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j)
                if (map[i][j] == '0') {
                    char in = flood(j, i, '0', '.');
                    // printf("%c: \n", in);
                    // printMap();
                    if (in) g[in - 'A']++;
                }
        }
        // printMap();

        vector<char> result;
        result.reserve(numGlyghs);

        char names[] = {'W', 'A', 'K', 'J', 'S', 'D'};

        for (int i : g) {
            result.push_back(names[i]);
        }

        sort(result.begin(), result.end());
        printf("Case %d: ", casenr++);
        for (char c : result) {
            printf("%c", c);
        }
        printf("\n");
    }
}
