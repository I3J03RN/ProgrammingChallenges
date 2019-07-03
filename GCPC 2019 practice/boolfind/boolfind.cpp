#include <iostream>
#include <string>

using namespace std;

int main() {
    int l = 1, r;
    cin >> r;

    while (l != r) {
        int mid = (l + r + 1) / 2;
        cout << "? " << mid << "\n";
        string response;
        cin >> response;
        if (response == "giraffe")
            r = mid - 1;
        else
            l = mid;
    }

    cout << "! " << l;

    return 0;
}
