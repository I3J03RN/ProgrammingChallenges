#include <cstdio>
#include <cstring>

using namespace std;

enum { px, py, pz, mx, my, mz } direction = px;

int main() {
    int L;
    while (scanf("%d", &L), L) {
        direction = px;
        L--;
        while (L--) {
            char in[10];
            scanf("%s", in);
            if (strcmp("+y", in) == 0) {
                switch (direction) {
                    case px:
                        direction = py;
                        break;
                    case mx:
                        direction = my;
                        break;
                    case py:
                        direction = mx;
                        break;
                    case my:
                        direction = px;
                        break;
                    default:
                        break;
                }
            } else if (strcmp("-y", in) == 0) {
                switch (direction) {
                    case px:
                        direction = my;
                        break;
                    case mx:
                        direction = py;
                        break;
                    case py:
                        direction = px;
                        break;
                    case my:
                        direction = mx;
                    default:
                        break;
                }
            } else if (strcmp("+z", in) == 0) {
                switch (direction) {
                    case px:
                        direction = pz;
                        break;
                    case mx:
                        direction = mz;
                        break;
                    case pz:
                        direction = mx;
                        break;
                    case mz:
                        direction = px;
                    default:
                        break;
                }
            } else if (strcmp("-z", in) == 0) {
                switch (direction) {
                    case px:
                        direction = mz;
                        break;
                    case mx:
                        direction = pz;
                        break;
                    case pz:
                        direction = px;
                        break;
                    case mz:
                        direction = mx;
                    default:
                        break;
                }
            }
        }
        switch (direction) {
            case px:
                printf("+x\n");
                break;
            case mx:
                printf("-x\n");
                break;
            case py:
                printf("+y\n");
                break;
            case my:
                printf("-y\n");
                break;
            case pz:
                printf("+z\n");
                break;
            case mz:
                printf("-z\n");
                break;
        }
    }
}
