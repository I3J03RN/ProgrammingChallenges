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

vector<ll> programm;

int input = 5;  // 1
int pc = 0;

ll getArg(int add, bool immediate) {
    return programm[immediate ? add : programm[add]];
}

ll& write(int add) { return programm[programm[add]]; }

void memdump() {
    for (ll l : programm) printf("%lld, ", l);
    printf("\n");
}

void eval() {
    array<int, 3> params;
    while (1) {
        int op = programm[pc] % 100;
        for (int i = 0, t = programm[pc] / 100; i < 3; ++i, t /= 10)
            params[i] = t % 10;
        switch (op) {
            case 1:
                write(pc + 3) =
                    getArg(pc + 1, params[0]) + getArg(pc + 2, params[1]);
                pc += 4;
                break;
            case 2:
                write(pc + 3) =
                    getArg(pc + 1, params[0]) * getArg(pc + 2, params[1]);
                pc += 4;
                break;
            case 3:
                write(pc + 1) = input;
                pc += 2;
                break;
            case 4:
                printf("%lld\n", getArg(pc + 1, params[0]));
                pc += 2;
                break;
            case 5:
                if (getArg(pc + 1, params[0]))
                    pc = getArg(pc + 2, params[1]);
                else
                    pc += 3;
                break;
            case 6:
                if (!getArg(pc + 1, params[0]))
                    pc = getArg(pc + 2, params[1]);
                else
                    pc += 3;
                break;
            case 7:
                write(pc + 3) =
                    getArg(pc + 1, params[0]) < getArg(pc + 2, params[1]) ? 1
                                                                          : 0;
                pc += 4;
                break;
            case 8:
                // printf("dest %d\n", pc + 3);
                write(pc + 3) =
                    getArg(pc + 1, params[0]) == getArg(pc + 2, params[1]) ? 1
                                                                           : 0;
                pc += 4;
                break;
            case 99:
                return;
            default:
                printf("error op code %d not valid!\n", op);
                return;
        }
        // memdump();
    }
}

int main() {
    while (1) {
        ll t;
        scanf("%lld", &t);
        programm.push_back(t);
        if (scanf(",") == EOF) break;
    }
    // memdump();
    eval();
}
