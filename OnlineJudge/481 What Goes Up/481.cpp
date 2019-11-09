#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    const int N = 1000000;
    vi A;
    vii L;
    vi P;
    A.reserve(N);
    L.reserve(N);
    P.reserve(N);

    int list = 0;
    int value;
    int listEnd = 0;
    for (int i = 0; scanf("%d", &value) != EOF; i++) {
        A.push_back(value);
        list = lower_bound(
                   L.begin(), L.begin() + listEnd, value,
                   [](const ii& a, int b) -> bool { return a.first < b; }) -
               L.begin();
        if (list == L.size()) {
            L.push_back({value, i});
            listEnd++;
        } else {
            L[list] = {value, i};
        }
        P.push_back(list ? L[list - 1].second : -1);
    }
    stack<int> p;
    for (int x = L.back().second; x != -1; x = P[x]) p.push(A[x]);
    printf("%ld\n-\n", L.size());
    for (; !p.empty(); p.pop()) printf("%d\n", p.top());
}
