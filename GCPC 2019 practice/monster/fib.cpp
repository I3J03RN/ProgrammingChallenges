#include <iostream>

using namespace std;

int main() {
    int fib1 = 0, fib2 = 1;
    cout << fib1 << endl;
    cout << fib2 << endl;

    while (true) {
        int next = fib1 + fib2;
        if (next > 1000000) break;
        cout << next << endl;
        fib1 = fib2;
        fib2 = next;
    }
    return 0;
}
