#include <cstdio>
#include <cstring>
using namespace std;
char text[2200000];
char pattern[1100000];
int back[1100000];
int n, m;               // n = strlen(text); m = strlen(patter);
void kmpPreprocess() {  // use this once before the search
    for (int i = 0, j = -1; i <= m; ++i, ++j) {
        back[i] = j;  // negative one marks the beginning
        // backtrack until the beginning is reached or the chars are
        // equal again
        while (j >= 0 && pattern[i] != pattern[j]) j = back[j];
    }
}
int kmpSearch() {
    bool once = false;
    for (int i = 0, j = 0; i <= n; i++, j++) {
        if (j == m) {  // if j is equal to m the pattern is completely
                       // matched
            // printf("found match at: %d\n", i - j);
            if (once)
                return i - j;
            else
                once = true;
            j = back[j];
        }
        while (j >= 0 && text[i] != pattern[j]) j = back[j];
    }
    return -1;
}
int main() {
    while (1) {
        fgets(pattern, 1010000, stdin);
        if (strchr(pattern, '.')) break;
        m = strlen(pattern);
        m--;
        pattern[m] = 0;
        n = m << 1;
        strcpy(text, pattern);
        strcat(text, pattern);
        kmpPreprocess();
        printf("%d\n", m / kmpSearch());
    }
}
