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

const ll NUMBER_OF_CARDS = 119315717514047LL;
const ll SHUFFLE_ITERATIONS = 101741582076661LL;
const ll RELEVANT_CARD = 2020LL;

enum shuffleType { REV, CUT, INC };

class Shuffle {
   public:
    Shuffle(shuffleType type, ll amount) : type{type}, amount{amount} {}

    const shuffleType type;
    const ll amount;
};

vector<Shuffle> shuffles;
vector<ll> positions;

char buffer[1000];

void nextPos() {
    ll position = positions.back();
    for (Shuffle s : shuffles) {
        switch (s.type) {
            case REV:
                position = NUMBER_OF_CARDS - 1 - position;
                break;
            case CUT:
                if (position < s.amount)
                    position = NUMBER_OF_CARDS - (s.amount - position);
                else
                    position -= s.amount;
                break;
            case INC:
                position = (position * s.amount) % NUMBER_OF_CARDS;
                break;
        }
    }
    positions.push_back(position);
}

int main() {
    while (scanf(" %100s", buffer) != EOF) {
        // for (int i : cards) cout << " " << i;
        // cout << endl;
        if (strcmp(buffer, "cut") == 0) {
            ll n;
            scanf("%lld", &n);
            if (n < 0) n += NUMBER_OF_CARDS;
            shuffles.emplace_back(CUT, n);
        } else {
            scanf(" %100s", buffer);
            if (strcmp(buffer, "into") == 0) {
                shuffles.emplace_back(REV, 0);
                scanf(" %*s %*s");
            } else {
                ll n;
                scanf(" %*100s %lld", &n);
                shuffles.emplace_back(INC, n);
            }
        }
    }
    positions.push_back(RELEVANT_CARD - 1);
    do {
        nextPos();
        if (positions.size() <= 1000) cout << positions.back() << '\n';
    } while (positions.back() != RELEVANT_CARD - 1);
    printf("iterations: %lu\n", positions.size());
}
