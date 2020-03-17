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

char buffer[1000];

const int NOC = 10007;

vi cards;
vi tmp(NOC);

void dealInc(int n) {
    // printf("deal w/ inc %d\n", n);
    int counter = 0;
    for (int i = 0; i < NOC; ++i, counter = (counter + n) % NOC)
        tmp[counter] = cards[i];
    cards.swap(tmp);
}

void dealNewStack() { reverse(cards.begin(), cards.end()); }

void cut(int n) {
    if (n < 0) n = NOC + n;
    tmp.clear();
    tmp.insert(tmp.end(), cards.begin() + n, cards.end());
    tmp.insert(tmp.end(), cards.begin(), cards.begin() + n);
    cards.swap(tmp);
}

int main() {
    for (int i = 0; i < NOC; ++i) cards.push_back(i);
    assert(cards.size() == NOC);
    assert(tmp.size() == NOC);
    while (scanf(" %100s", buffer) != EOF) {
        // for (int i : cards) cout << " " << i;
        // cout << endl;
        if (strcmp(buffer, "cut") == 0) {
            int n;
            scanf("%d", &n);
            cut(n);
        } else {
            scanf(" %100s", buffer);
            if (strcmp(buffer, "into") == 0) {
                dealNewStack();
                scanf(" %*s %*s");
            } else {
                int n;
                scanf(" %*100s %d", &n);
                dealInc(n);
            }
        }
    }
    if (cards.size() < 100) {
        cout << "Result:";
        for (int i : cards) cout << " " << i;
        cout << endl;
    }
    printf("part 1: %ld\n",
           find(cards.begin(), cards.end(), 2019) - cards.begin());
}
