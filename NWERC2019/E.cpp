#include <cstdio>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;



int main() {
  int t[8];
  int target1, target2, target;
  int value[4];
  scanf("%d.%d %d.%d %d.%d %d.%d %d.%d", t , t + 1, t + 2, t + 3, t + 4, t + 5, t + 6, t + 7, &target1, &target2);
  for (int i =0; i< 4; ++i) {
    value[i] = t[i << 1] * 100 + t[(i << 1) + 1];
  }
  sort(value, value + 4);
  target = target1 * 100 + target2;
  if ((value[0] + value[1] +value[2]) > target * 3) {
    printf("impossible\n");
  } else if ((value[1] + value[2] + value[3]) <= target * 3) {
    printf("infinite\n");
  } else {
    int v = 3 * target - (value[1] + value[2]);
    printf("%d.%02d\n", v / 100, v % 100 );
  }
}
