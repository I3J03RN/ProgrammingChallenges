#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bitset<1100000> A;
int N;

const int FLIP = 1;
const int SET = 2;
const int RESET = 3;
const int DEEP = 4;

class SegmentTree {
   private:
    vi pi, nupdate;

    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }
    int build(int p, int L, int R) {
        if (L == R) return pi[p] = A[L];
        return pi[p] = build(left(p), L, (L + R) / 2) +
                       build(right(p), (L + R) / 2 + 1, R);
    }
    int rmq(int p, int L, int R, int i, int j) {
        // printf("rmq (%d - %d)\n", L, R);
        if (j < L || i > R) return -1;

        if (nupdate[p]) update(p, L, R);
        if (i <= L && R <= j) return pi[p];

        int l = rmq(left(p), L, (L + R) / 2, i, j);
        int r = rmq(right(p), (L + R) / 2 + 1, R, i, j);
        if (l == -1) return r;
        if (r == -1) return l;
        return r + l;
    }
    void lazyUpdate(int p, int L, int R, int i, int j, int type) {
        if (j < L || i > R) return;

        if (i <= L && R <= j) {
            setUpdate(p, L, R, type);
            // printf("setUp: %d-%d, %d\n", L, R, nupdate[p]);
        } else if (L != R) {
            setUpdate(p, L, R, DEEP);
            lazyUpdate(left(p), L, (L + R) / 2, i, j, type);
            lazyUpdate(right(p), (L + R) / 2 + 1, R, i, j, type);
        }
    }
    void setUpdate(int p, int L, int R, int type) {
        if (nupdate[p] == 0) {
            nupdate[p] = type;
        } else {
            if (type == FLIP) {
                if (nupdate[p] == FLIP)
                    nupdate[p] = 0;
                else if (nupdate[p] == SET)
                    nupdate[p] = RESET;
                else if (nupdate[p] == RESET)
                    nupdate[p] = SET;
                else {
                    // nupdate[p] == DEEP
                    update(p, L, R);
                    nupdate[p] = FLIP;
                }
            } else if (type == SET)
                nupdate[p] = SET;
            else if (type == RESET)
                nupdate[p] = RESET;
            else {
                // type == DEEP
                if (nupdate[p]) update(p, L, R);
                nupdate[p] = DEEP;
            }
        }
    }
    void update(int p, int L, int R) {
        if (nupdate[p] == 0) return;
        // printf("up: %d %d\n", L, R);

        if (nupdate[p] == DEEP) {
            update(left(p), L, (R + L) / 2);
            update(right(p), (R + L) / 2 + 1, R);
            pi[p] = pi[left(p)] + pi[right(p)];
        } else {
            if (nupdate[p] == FLIP) pi[p] = R - L + 1 - pi[p];
            if (nupdate[p] == SET) pi[p] = R - L + 1;
            if (nupdate[p] == RESET) pi[p] = 0;
            if (L != R) {
                setUpdate(left(p), L, (R + L) / 2, nupdate[p]);
                setUpdate(right(p), (R + L) / 2 + 1, R, nupdate[p]);
                // printf("setUp: %d-%d, %d\n", L, (R + L) / 2,
                // nupdate[left(p)]); printf("setUp: %d-%d, %d\n", (R + L) / 2 +
                // 1, R, nupdate[right(p)]);
            }
        }

        nupdate[p] = 0;
    }

   public:
    SegmentTree() : pi(N * 4), nupdate(N * 4, 0) { build(1, 0, N - 1); }
    int rmq(int i, int j) { return rmq(1, 0, N - 1, i, j); }
    void lazyUpdate(int i, int j, int type) {
        lazyUpdate(1, 0, N - 1, i, j, type);
    }
};

void printA() {
    printf("Bitset: ");
    for (int i = 0; i < N; ++i) {
        printf("%c", A[i] ? '1' : '0');
    }
    printf("\n");
}

int main() {
    int T;
    char s[100];
    scanf("%d", &T);
    for (int c = 1; c <= T; ++c) {
        printf("Case %d:\n", c);
        N = 0;
        int M;
        scanf("%d", &M);
        int i = 0;
        while (M--) {
            int T;
            scanf("%d", &T);
            scanf(" %[01]", s);
            int len = strlen(s);
            N += len * T;
            while (T--) {
                for (int j = 0; j < len; ++j) {
                    A[i++] = s[j] == '1';
                }
            }
        }
        SegmentTree st;
        // printA();
        int Q;
        scanf("%d", &Q);
        int q = 1;
        int ul, uu = -1;
        while (Q--) {
            int a, b;
            scanf(" %[FISE] %d %d", s, &a, &b);
            if (s[0] == 'S') {
                printf("Q%d: %d\n", q++, st.rmq(a, b));
            } else {
                if (s[0] == 'F') {
                    // printf("F");
                    st.lazyUpdate(a, b, SET);
                }
                if (s[0] == 'E') {
                    // printf("E");
                    st.lazyUpdate(a, b, RESET);
                }
                if (s[0] == 'I') {
                    // printf("I");
                    st.lazyUpdate(a, b, FLIP);
                }
                // printf(" %d %d\n", a, b);
                // printA();
            }
        }
    }
}
