#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

struct ret {
    int l, r, amount, value;
};

class SegmentTree {
   private:
    vi l, r, amount, value;
    vi& A;
    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) + 1; }

    void build(int i, int L, int R) {
        if (L == R) {
            l[i] = 1;
            r[i] = 1;
            amount[i] = 1;
            value[i] = A[L];
        } else {
            int _l = left(i);
            int _r = right(i);
            int rl = (R + L) / 2;
            build(_l, L, rl);
            build(_r, rl + 1, R);

            l[i] = l[_l];
            r[i] = r[_r];
            if (A[rl] == A[rl + 1]) {
                int rlAmount = l[_r] + r[_l];
                if (amount[_r] > amount[_l]) {
                    if (rlAmount > amount[_r]) {
                        amount[i] = rlAmount;
                        value[i] = A[rl];
                    } else {
                        amount[i] = amount[_r];
                        value[i] = value[_r];
                    }
                } else {
                    if (rlAmount > amount[_l]) {
                        amount[i] = rlAmount;
                        value[i] = A[rl];
                    } else {
                        amount[i] = amount[_l];
                        value[i] = value[_l];
                    }
                }
                if (A[L] == A[rl]) l[i] += l[_r];
                if (A[R] == A[rl]) r[i] += r[_l];
            } else {
                if (amount[_r] > amount[_l]) {
                    amount[i] = amount[_r];
                    value[i] = value[_r];
                } else {
                    amount[i] = amount[_l];
                    value[i] = value[_l];
                }
            }
        }
        // printf("build: %d (%d - %d): %d %d %d %d\n", i, L, R, value[i],
        //        amount[i], l[i], r[i]);
    }

    ret rmq(int p, int L, int R, int i, int j) {
        // printf("rmq: %d (%d - %d): %d %d\n", p, L, R, i, j);
        if (i > R || j < L) return {-1};
        if (i <= L && R <= j) {
            return {l[p], r[p], amount[p], value[p]};
        }

        int rl = (L + R) / 2;
        ret _l = rmq(left(p), L, rl, i, j);
        ret _r = rmq(right(p), rl + 1, R, i, j);
        // printf("%d - l: %d %d %d %d\n", p, _l.l, _l.r, _l.amount, _l.value);
        // printf("%d - r: %d %d %d %d\n", p, _r.l, _r.r, _r.amount, _r.value);

        if (_l.l == -1) return _r;
        if (_r.l == -1) return _l;

        if (A[rl] == A[rl + 1]) {
            int ll, rr, a, v;
            ll = _l.l + (A[L] == A[rl] ? _r.l : 0);
            rr = _r.r + (A[R] == A[rl] ? _l.r : 0);

            if (_r.amount > _l.amount) {
                if (_r.l + _l.r > _r.amount) {
                    a = _r.l + _l.r;
                    v = A[rl];
                } else {
                    v = _r.value;
                    a = _r.amount;
                }
            } else {
                if (_r.l + _l.r > _l.amount) {
                    a = _r.l + _l.r;
                    v = A[rl];
                } else {
                    v = _l.value;
                    a = _l.amount;
                }
            }

            return {ll, rr, a, v};
        } else {
            int v, a;
            if (_r.amount > _l.amount) {
                v = _r.value;
                a = _r.amount;
            } else {
                v = _l.value;
                a = _l.amount;
            }
            return {_l.l, _r.r, a, v};
        }
    }

   public:
    SegmentTree(vi& _A)
        : A(_A),
          l(_A.size() * 4),
          r(_A.size() * 4),
          amount(_A.size() * 4),
          value(_A.size() * 4) {
        build(1, 0, A.size() - 1);
    }

    int rmq(int i, int j) { return rmq(1, 0, A.size() - 1, i, j).amount; }
};

int main() {
    int n, q;

    while (scanf("%d %d", &n, &q), n) {
        vi A(n);
        for (int i = 0; i < n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            A[i] = tmp;
        }
        SegmentTree st(A);
        while (q--) {
            int i, j;
            scanf("%d %d", &i, &j);
            printf("%d\n", st.rmq(--i, --j));
        }
    }
}
