#include <cstdio>

char buffer[10010];

int main() {
    while (fgets(buffer, 10000, stdin)) printf("%s", buffer);
}
