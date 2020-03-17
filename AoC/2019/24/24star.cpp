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

const int mid = 300;

int up = 1, down = -1;

class BugField;

vector<BugField> A(mid * 2 + 1);
vector<BugField> B(mid * 2 + 1);

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

BugField& getEntry(vector<BugField>& v, int index) { return v.at(index + mid); }

class BugField {
   public:
    int level = 0;
    int count() {
        int sum = 0;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
                if (r != rows / 2 || c != columns / 2)
                    sum += field[r][c] ? 1 : 0;
        return sum;
    }
    void print() {
        printf("Depth: %d\n", level);
        for (int r = 0; r < rows; ++r, putchar('\n'))
            for (int c = 0; c < columns; ++c)
                if (r == rows / 2 && c == columns / 2)
                    putchar('?');
                else
                    putchar(field[r][c] ? '#' : '.');
    }
    void update() {
        array<array<int, columns>, rows> counts;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c) counts[r][c] = 0;

        // bug count in this field
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
                if (r != rows / 2 || c != columns / 2)
                    for (int i = 0; i < 4; ++i)
                        if (isBug(r + dr[i], c + dc[i])) counts[r][c]++;
        // first row
        if (getEntry(A, level - 1).field[rows / 2 - 1][columns / 2])
            for (int c = 0; c < columns; ++c) counts[0][c]++;
        // last row
        if (getEntry(A, level - 1).field[rows / 2 + 1][columns / 2])
            for (int c = 0; c < columns; ++c) counts[rows - 1][c]++;
        // leftmost column
        if (getEntry(A, level - 1).field[rows / 2][columns / 2 - 1])
            for (int r = 0; r < rows; ++r) counts[r][0]++;
        // rightmost column
        if (getEntry(A, level - 1).field[rows / 2][columns / 2 + 1])
            for (int r = 0; r < rows; ++r) counts[r][columns - 1]++;

        // above inner grid
        for (int c = 0; c < columns; ++c)
            if (getEntry(A, level + 1).field[0][c])
                counts[rows / 2 - 1][columns / 2]++;
        // below inner grid
        for (int c = 0; c < columns; ++c)
            if (getEntry(A, level + 1).field[rows - 1][c])
                counts[rows / 2 + 1][columns / 2]++;
        // left of inner grid
        for (int r = 0; r < rows; ++r)
            if (getEntry(A, level + 1).field[r][0])
                counts[rows / 2][columns / 2 - 1]++;
        // right of inner grid
        for (int r = 0; r < rows; ++r)
            if (getEntry(A, level + 1).field[r][columns - 1])
                counts[rows / 2][columns / 2 + 1]++;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
                if (r != rows / 2 || c != columns / 2) {
                    if (field[r][c])
                        getEntry(B, level).field[r][c] = counts[r][c] == 1;
                    else
                        getEntry(B, level).field[r][c] =
                            counts[r][c] == 1 || counts[r][c] == 2;
                }
    }

    bool isBug(int r, int c) {
        return (r != rows / 2 || c != columns / 2) && 0 <= r && r < rows &&
               0 <= c && c < columns && field[r][c];
    }
    array<array<bool, columns>, rows> field;
};

char field[10][10];

void nextMinute(int minute) {
    for (int i = down; i <= up; ++i) getEntry(A, i).update();
    A.swap(B);
    if (getEntry(A, down).count() > 0) down--;
    if (getEntry(A, up).count() > 0) up++;
    printf("After %d minutes:\n", minute);
    for (int i = down; i <= up; ++i) getEntry(A, i).print();
}

int main() {
    for (int r = 0; r < rows; ++r) fgets(field[r], 9, stdin);
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            getEntry(A, 0).field[r][c] = field[r][c] == '#';

    for (int i = -mid; i <= mid; ++i) {
        getEntry(A, i).level = i;
        getEntry(B, i).level = i;
    }
    printf("Initial state:\n");
    getEntry(A, 0).print();

    for (int i = 1; i <= 200; ++i) {
        nextMinute(i);
    }
    int bugs = 0;
    for (int i = down; i <= up; ++i) {
        bugs += getEntry(A, i).count();
    }
    printf("bugs: %d\n", bugs);
}
