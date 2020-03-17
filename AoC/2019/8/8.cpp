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

const int width = 25, height = 6;

char image[6][25];

int main() {
    memset(image, '2', sizeof(image));
    while (1) {
        for (int r = 0; r < height; ++r)
            for (int i = 0; i < width; ++i) {
                char c;
                if (scanf("%c", &c) == EOF) goto end;
                if (c == '0' && image[r][i] == '2')
                    image[r][i] = '0';
                else if (c == '1' && image[r][i] == '2')
                    image[r][i] = '1';
            }
    }
end:
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) printf("%c", image[r][c]);
        printf("\n");
    }
}
