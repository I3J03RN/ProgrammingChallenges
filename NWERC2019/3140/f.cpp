#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;
typedef vector<int> vi;

vector<vi> adj(500000);
vi value(300000);
unordered_map<int, int> map;
int n;
int dfsn = 0;
struct solutionEntry {
  int p, q, r;
};
vector<solutionEntry> solution; 
vi dfs_num(500000, -1);
void dfs(int v, int from, int desc, int k) {
  dfs_num[v] = dfsn++;
  if (k == 2) {
    solution.push_back({from + 1, v + 1, value[desc - n]});
    from = v;
    k = 1;
  } else if (k == 1) {
    desc = v;
    k = 2;
  } else {
    from = v;
    k = 1;
  }
  
  for (int i : adj[v]) {
    if (dfs_num[i] == -1)
      dfs(i, from, desc, k);
  }
}
int main() {
  scanf("%d", &n);
  int index = n;
  solution.reserve(n);
  for (int i = 0; i < n; ++i) {
      int m;
      scanf ("%d", &m);
      while (m--) {
	int t;
	scanf("%d", &t);
	auto it = map.find(t);
	int nodeIndex;
	if (it == map.end()) {
	  nodeIndex = index++;
	  map[t] = nodeIndex;
	  value[nodeIndex - n] = t;
	} else {
	  nodeIndex = it->second;
	}
	adj[i].push_back(nodeIndex);
	adj[nodeIndex].push_back(i);
      }
    }
  dfs(0, 0, 0, 0);
  
  // printf("%d\n", solution.size());
  if (solution.size() == n - 1)
    for (solutionEntry s : solution) {
      printf("%d %d %d\n", s.p, s.q, s.r);
    }
  else
    printf("impossible\n");
}
