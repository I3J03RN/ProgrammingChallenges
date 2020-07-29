#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).begin; ++(a))

vector<ll> A;

class SegmentTree {
   private:
    int inline left(int p) { return p << 1; }
    int inline right(int p) { return (p << 1) + 1; }
    vector<ll> Sum;
    ll build(int p, int L, int R) {
        if (L == R) return Sum[p] = A[R];
        return Sum[p] = build(left(p), L, (L + R) / 2) +
                        build(right(p), (L + R) / 2 + 1, R);
    };

   public:
    SegmentTree() : Sum(400400) {}
    void rebuild() { build(1, 0, A.size() - 1); }
};

int main() {
    SegmentTree segmentTree;
    A.reserve(100010);
    int T, N, Q, casenr = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &Q);
        A.clear();
        while (N--) {
            ll t;
            scanf("%lld", &t);
            A.push_back(t);
        }
        segmentTree.rebuild();
        printf("Case %d:\n", casenr++);
        while (Q--) {
            char type;
            int st, nd, x;
            scanf(" %c %d %d", &type, &st, &nd);
        }
    }
}
