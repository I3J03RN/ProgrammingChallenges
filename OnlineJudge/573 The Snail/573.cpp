#include <cstdio>

using namespace std;

int main() {
    int H, U, D, F;
    while (scanf("%d %d %d %d", &H, &U, &D, &F), H != 0) {
        int day = 1;
        double height = 0;
        double climbing = U;
        double fatigue = U * ((double)F / 100.0);

        while (1) {
            height += climbing;
            if (height > H) {
                printf("success on day %d\n", day);
                break;
            }
            climbing -= fatigue;
            if (climbing < 0) climbing = 0;
            height -= D;
            if (height < 0) {
                printf("failure on day %d\n", day);
                break;
            }
            day++;
        }
    }
}
