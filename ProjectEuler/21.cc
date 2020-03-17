#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

int sumDivs(int number) {
    if (number == 1) return 1;
    int sum = 0;
    int until = sqrt(number);
    for (int i = 1; i <= until; ++i)
        if (number % i == 0) {
            if (number / i == i)
                sum += i;
            else
                sum += i + number / i;
        }
    return sum - number;
}

int main() {
    int sum = 0;
    for (int n = 1; n < 10000; ++n) {
        int divsum = sumDivs(n);
        if (divsum != n && n == sumDivs(divsum)) sum += n;
    }
    cout << sum << endl;
}
