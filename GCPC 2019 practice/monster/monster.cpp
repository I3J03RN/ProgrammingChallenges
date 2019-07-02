#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int fibs[] = {0,     1,     1,      2,      3,      5,      8,     13,
              21,    34,    55,     89,     144,    233,    377,   610,
              987,   1597,  2584,   4181,   6765,   10946,  17711, 28657,
              46368, 75025, 121393, 196418, 317811, 514229, 832040};

int isfib(int n) {
    for (int i = 1; i < 31; ++i) {
        if (fibs[i] == n) return i;
    }
    return 0;
}

struct entry {
    int index, fibindex;
};

std::ostream& operator<<(std::ostream& str, const entry& e) {
    return str << "i: " << e.index << ", f:" << e.fibindex;
}

int main() {
    int n;
    cin >> n;

    vector<entry> entries;

    for (int i = 1; i <= n; ++i) {
        int number;
        cin >> number;
        int fibsi = isfib(number);
        if (fibsi) {
            entries.push_back({i, fibsi});
        }
    }

    sort(entries.begin(), entries.end(), [](const entry& a, const entry& b) {
        return a.fibindex < b.fibindex;
    });

    // for (const entry& e : entries) {
    //     cout << e << "\n";
    // }

    for (int i = 0; i < entries.size(); ++i) {
        entry& a = entries[i];
        for (int j = i + 1; j < entries.size(); ++j) {
            entry& b = entries[j];
            if ((1 == b.fibindex || 2 == b.fibindex) &&
                b.fibindex == a.fibindex) {
                cout << a.index << " " << b.index << "\n";
                return 0;
            } else if (b.fibindex == 1 + a.fibindex) {
                cout << a.index << " " << b.index << "\n";
                return 0;
            } else
                break;
        }
    }

    cout << "impossible\n";
    return 0;
}
