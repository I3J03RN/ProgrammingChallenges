#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <utility>
#include <string>

using namespace std;

int calcRepScore(string& str) {
    // cout << str << endl;
    int size = 1;
    for (int i = 1; i < str.size(); ++i) {
         if ((str[i % size] != str[i])
          ||     (str.size() % size != 0)) {
              if (str[0] == str[i] && str.size() % i == 0) size = i; else
            size = i + 1;
         }
    }

    return size;    
}

int main() {
    int n;
    cin >> n;

    int* a = new int[n];
    int* b = new int[n];

    for (unsigned int i = 0; i < n; ++i) {
        string in;
        cin >>  in;
        a[i] = calcRepScore(in);
        // cout << a[i] << endl;
    }

    for (unsigned int i = 0; i < n; ++i) {
        string in;
        cin >>  in;
        b[i] = calcRepScore(in);
        // cout << b[i] << endl;
    }

    sort(a, a + n);
    sort(b, b + n);

    int total = 0;

    for (int i = 0; i < n; ++i) {
        int diff = a[i] - b[i];
        total += diff * diff; 
    }

    cout << total << '\n';

    delete[] a;
    delete[] b;

    return 0;

}
