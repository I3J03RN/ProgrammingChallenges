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

const int rows = 5, columns = 5;

bitset<2 << (rows * columns)> seen;

char A[10][10];
char B[10][10];

bool inline isBug(int r, int c) {
    return 0 <= r && r < rows && 0 <= c && c < columns && A[r][c] == '#';
}

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int countBugs(int r, int c) {
    int sum = 0;
    for (int i = 0; i < 4; ++i)
        if (isBug(r + dr[i], c + dc[i])) sum++;
    return sum;
}

int calcBioDiv() {
    int ret = 0;
    for (int r = rows - 1; r >= 0; --r)
        for (int c = columns - 1; c >= 0; --c, ret <<= 1)
            if (A[r][c] == '#') ret |= 1;
    return ret >> 1;
}

void nextMinute() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (A[r][c] == '#')
                B[r][c] = countBugs(r, c) == 1 ? '#' : '.';
            else {
                int bugs = countBugs(r, c);
                B[r][c] = 1 <= bugs && bugs <= 2 ? '#' : '.';
            }
    swap(A, B);
}

void printA() {
    for (int r = 0; r < rows; ++r, printf("\n"))
        for (int c = 0; c < columns; ++c) printf("%c", A[r][c]);
}

int main() {
    for (int r = 0; r < rows; ++r) fgets(A[r], 9, stdin);
    printf("Initial state:\n");
    printA();

    seen[calcBioDiv()] = true;

    while (1) {
        nextMinute();
        int bioDiv = calcBioDiv();
        if (seen.test(bioDiv)) {
            printf("Found first matching bioDiv %d:\n", bioDiv);
            printA();
            break;
        }
        seen.set(bioDiv);
    }
}
