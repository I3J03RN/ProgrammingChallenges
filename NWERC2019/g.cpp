#include <cstdio>
typedef long long ll;

ll binom[510][510];

int n, k;
void calcBinom() {
  for (int i = 0; i < n; ++i) {
    binom[i][0] = 1; 
    binom[i][i] = 1;
  }
  for (int i = 2; i < n; ++i)
    for (int j = 1; j < i; ++j) {
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j -1];
    }
}

double values[510];
double table[510][510];

int main() {
  scanf("%d %d", &n, &k);
  calcBinom();
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j <= i; ++j)
  //     printf("%d ", binom[i][j]);
  //   printf("\n");
  // }

  for (int i = 0; i < n; ++i)
    scanf("%lf", values + i);
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int c = 0; c <= n - k; ++c) {
      sum += values[(i - c + n) % n];
      table[i][c] = sum;
    }
 }
  // for (int c = 0; c <= n - k; ++c) {
  //   for (int i = 0; i < n; i++)
  //     printf("%5.5lf ", table[i][c]);
  //   printf("\n");
  // }
  if (k == 1) {
    for (int i = 0; i < n; ++i)
      printf("%lf", 1.0 / (double)n);
  } else {
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    double count = 0;
    for (int c = 0; c <= n - k; ++c) {
      sum += binom[n - c - 2][k - 2] * table[i][c];
      count += binom[n - c - 2][k - 2];
    }
    if (n == k)
      printf("%.10lf ", values[i]);
    else 
      printf("%.10lf ", k * (sum / count / (double)n));
  }
  }
    
}
