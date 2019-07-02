#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long max = 0;
    while (n--) {
        long long i;
        cin >> i;
        if (i > max) max = i;
    }

    long long result = max * max * max;
    cout << result << "\n";
}
