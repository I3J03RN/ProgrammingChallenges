#include <cstdio>

using namespace std;

typedef long long ll;

int main() {
    int t;
    ll a, b;

    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld", &a, &b);
        if (a < b)
            printf("<\n");
        else if (a > b)
            printf(">\n");
        else
            printf("=\n");
    }

    return 0;
}
