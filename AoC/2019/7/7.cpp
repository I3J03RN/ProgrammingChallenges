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

vector<ll> mem;
array<vector<ll>, 5> programms;

array<deque<ll>, 5> qs;

array<int, 5> pcs;

ll getArg(int add, bool immediate, int amp) {
    return programms[amp][immediate ? add : programms[amp][add]];
}

ll& write(int add, int amp) { return programms[amp][programms[amp][add]]; }

void memdump(int amp) {
    for (ll l : programms[amp]) printf("%lld, ", l);
    printf("\n");
}

bool eval(int amp) {
    vector<ll>& programm = programms[amp];
    int& pc = pcs[amp];
    array<int, 3> params;
    while (1) {
        int op = programm[pc] % 100;
        for (int i = 0, t = programm[pc] / 100; i < 3; ++i, t /= 10)
            params[i] = t % 10;
        switch (op) {
            case 1:
                write(pc + 3, amp) = getArg(pc + 1, params[0], amp) +
                                     getArg(pc + 2, params[1], amp);
                pc += 4;
                break;
            case 2:
                write(pc + 3, amp) = getArg(pc + 1, params[0], amp) *
                                     getArg(pc + 2, params[1], amp);
                pc += 4;
                break;
            case 3:
                if (qs[amp].empty()) {
                    // printf("amp %d waits\n", amp);
                    return false;
                }
                write(pc + 1, amp) = qs[amp].front();
                qs[amp].pop_front();
                pc += 2;
                break;
            case 4:
                // printf("amp %d prod output\n", amp);
                qs[(amp + 1) % 5].push_back(getArg(pc + 1, params[0], amp));
                pc += 2;
                break;
            case 5:
                if (getArg(pc + 1, params[0], amp))
                    pc = getArg(pc + 2, params[1], amp);
                else
                    pc += 3;
                break;
            case 6:
                if (!getArg(pc + 1, params[0], amp))
                    pc = getArg(pc + 2, params[1], amp);
                else
                    pc += 3;
                break;
            case 7:
                write(pc + 3, amp) = getArg(pc + 1, params[0], amp) <
                                             getArg(pc + 2, params[1], amp)
                                         ? 1
                                         : 0;
                pc += 4;
                break;
            case 8:
                // printf("dest %d\n", pc + 3);
                write(pc + 3, amp) = getArg(pc + 1, params[0], amp) ==
                                             getArg(pc + 2, params[1], amp)
                                         ? 1
                                         : 0;
                pc += 4;
                break;
            case 99:
                return true;
            default:
                printf("error op code %d not valid!\n", op);
                return true;
        }
        // memdump();
    }
    printf("error end reached!\n");
    return true;
}

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        mem.push_back(t);
        if (scanf(",") == EOF) break;
    }
    // memdump();
    array<int, 5> phases{5, 6, 7, 8, 9};
    ll m = -1;
    do {
        bitset<5> fin;
        fin.reset();
        for (int i = 0; i < 5; ++i) {
            qs[i].push_back(phases[i]);
            pcs[i] = 0;
            programms[i] = mem;
        }
        qs[0].push_back(0);
        while (!fin.all())
            for (int i = 0; i < 5; ++i)
                if (!fin.test(i)) fin[i] = eval(i);
        printf("value %lld\n", qs[0].front());
        m = max(m, qs[0].front());
        qs[0].pop_front();
        for (int i = 0; i < 5; ++i)
            if (qs[i].size() != 0) printf("hmm\n");
    } while (next_permutation(phases.begin(), phases.end()));
    printf("%lld\n", m);
}
