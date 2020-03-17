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

vector<ll> base = {0, 1, 0, -1};

vector<ll> numbers;
vector<ll> result;
vector<ll> sums;

int offset;

void phase() {
    ll sum = 0;
    for (int i = numbers.size() - 1; i >= offset; --i) {
        // if ((i & 65535) == 0) printf("%d\n", i);
        sum += numbers[i];
        ll mysum = sums[i] = sum;
        int j = i + i + 1;
        int c = 0;
        while (j < numbers.size()) {
            if (c < 2)
                mysum -= sums[j];
            else
                mysum += sums[j];
            c = (c + 1) & 3;
            j += i + 1;
        }
        result[i] = abs(mysum) % 10;
    }
}

int main() {
    char c;
    while (scanf("%c", &c) != EOF)
        if (c == '\n')
            break;
        else
            numbers.push_back(c - '0');

    // for (ll l : numbers) printf("%lld\n", l);

    int len = numbers.size();

    for (int i = 1; i < 10000; ++i) {
        numbers.insert(numbers.end(), numbers.begin(), numbers.begin() + len);
    }

    for (int i = 0; i < 7; ++i) {
        offset *= 10;
        offset += numbers[i];
    }

    sums.assign(numbers.size(), 0);
    result.assign(numbers.size(), 0);
    for (int i = 0; i < 100; ++i) {
        // printf("Phase %d:\n", i + 1);
        phase();
        swap(result, numbers);
        // for (ll l : numbers) printf("%lld", l);
        // printf("\n");
    }
    for (int i = 0; i < 8; ++i) printf("%lld", numbers[offset + i]);
    printf("\n");
}
