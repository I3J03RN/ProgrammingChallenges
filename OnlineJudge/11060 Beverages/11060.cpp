#include <cstdio>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<vi> adj(200);
vector<string> bevs(200);
unordered_map<string, int> bevindex;

int main() {
    int N, M, casenr = 1;
    char buffer[100];
    char buffer2[100];
    while (scanf("%d", &N) != EOF) {
        bevindex.clear();
        vi in(N, 0);
        for (int i = 0; i < N; ++i) {
            adj[i].clear();
            scanf(" %s", buffer);
            bevs[i] = string(buffer);
            bevindex[bevs[i]] = i;
        }
        scanf("%d", &M);
        for (int i = 0; i < M; ++i) {
            scanf(" %s %s", buffer, buffer2);
            adj[bevindex[buffer]].push_back(bevindex[buffer2]);
            in[bevindex[buffer2]]++;
        }
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < N; ++i)
            if (in[i] == 0) q.push(i);

        printf("Case #%d: Dilbert should drink beverages in this order:",
               casenr++);
        while (!q.empty()) {
            int i = q.top();
            q.pop();
            printf(" %s", bevs[i].c_str());
            for (int j : adj[i]) {
                if (--in[j] == 0) q.push(j);
            }
        }

        printf(".\n\n");
    }
}
