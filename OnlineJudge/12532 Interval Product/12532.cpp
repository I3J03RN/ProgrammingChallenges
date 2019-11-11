#include <cstdio>
#include <vector>
using namespace std;
typedef vector<int> vi;
class FenwickTree {
   private:
    vi A;
    int n;
    int inline LSOne(int i) { return i & (-i); }
    int querry(int i) {
        int sum = 0;
        for (; i; i -= LSOne(i)) sum += A[i];
        return sum;
    }

   public:
    FenwickTree(int n) : A(n + 1, 0), n(n) {}
    void adjust(int i, int adjustBy) {
        for (; i <= n; i += LSOne(i)) A[i] += adjustBy;
    }
    int querry(int i, int j) { return querry(j) - querry(i - 1); }
};

int main() {
    int N, K;
    while (scanf("%d %d", &N, &K) != EOF) {
        vi A(N + 1);
        A.reserve(N);
        FenwickTree zeros(N), negatives(N);
        for (int i = 1; i <= N; ++i) {
            int t;
            scanf("%d", &t);
            A[i] = t;
            if (t == 0)
                zeros.adjust(i, 1);
            else if (t < 0)
                negatives.adjust(i, 1);
        }
        // printf("z: %d\n", zeros.querry(1, N));
        // printf("-: %d\n", negatives.querry(1, N));
        while (K--) {
            char type;
            int a, b;
            scanf(" %c %d %d", &type, &a, &b);
            // printf("%c: %d %d\n", type, a, b);
            if (type == 'C') {
                if (b == 0) {
                    if (A[a] < 0) {
                        negatives.adjust(a, -1);
                        zeros.adjust(a, 1);
                    } else if (A[a] > 0) {
                        zeros.adjust(a, 1);
                    }
                } else if (b < 0) {
                    if (A[a] > 0) {
                        negatives.adjust(a, 1);
                    } else if (A[a] == 0) {
                        negatives.adjust(a, 1);
                        zeros.adjust(a, -1);
                    }
                } else {
                    if (A[a] < 0) {
                        negatives.adjust(a, -1);
                    } else if (A[a] == 0) {
                        zeros.adjust(a, -1);
                    }
                }
                A[a] = b;
                // printf("z: %d\n", zeros.querry(1, N));
                // printf("-: %d\n", negatives.querry(1, N));
            } else {
                int neg = negatives.querry(a, b);
                int zero = zeros.querry(a, b);
                if (zero != 0) {
                    printf("0");
                } else if (neg & 1) {
                    printf("-");
                } else {
                    printf("+");
                }
            }
        }
        printf("\n");
    }
}
