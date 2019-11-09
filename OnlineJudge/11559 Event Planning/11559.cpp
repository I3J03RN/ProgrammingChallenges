#include <algorithm>
#include <cstdio>

typedef long long ll;

using namespace std;

int main() {
    int N, H, W;
    ll B;
    while (scanf("%d %lld %d %d", &N, &B, &H, &W) != EOF) {
        ll minPrice = B + 1;
        while (H--) {
            ll pricePP;
            scanf("%lld", &pricePP);
            for (int i = 0; i < W; ++i) {
                int beds;
                scanf("%d", &beds);
                if (beds >= N) {
                    minPrice = min(pricePP * N, minPrice);
                }
            }
        }
        if (minPrice < B)
            printf("%lld\n", minPrice);
        else
            printf("stay home\n");
    }
    return 0;
}
