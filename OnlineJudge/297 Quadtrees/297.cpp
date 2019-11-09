#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> first(4098);
vector<char> second(4098);

void build(vector<char>& v, int vpos, string& s, int& spos) {
    v[vpos] = s[spos++];
    if (v[vpos] == 'p') {
        build(v, vpos * 4 + 1, s, spos);
        build(v, vpos * 4 + 2, s, spos);
        build(v, vpos * 4 + 3, s, spos);
        build(v, vpos * 4 + 4, s, spos);
    }
}

int count1(vector<char>& v, int pos, int p) {
    if (v[pos] == 'f') return p;
    if (v[pos] == 'e') return 0;
    return count1(v, pos * 4 + 1, p >> 2) + count1(v, pos * 4 + 2, p >> 2) +
           count1(v, pos * 4 + 3, p >> 2) + count1(v, pos * 4 + 4, p >> 2);
}

int count(int pos, int p) {
    if (first[pos] == 'f' || second[pos] == 'f') return p;

    if (first[pos] == 'e') return count1(second, pos, p);
    if (second[pos] == 'e') return count1(first, pos, p);

    return count(pos * 4 + 1, p >> 2) + count(pos * 4 + 2, p >> 2) +
           count(pos * 4 + 3, p >> 2) + count(pos * 4 + 4, p >> 2);
}

int main() {
    int N;
    cin >> N;
    while (getchar() != '\n')
        ;
    while (N--) {
        string firsts, seconds;
        getline(cin, firsts);
        getline(cin, seconds);

        int i = 0;
        build(first, 0, firsts, i);
        i = 0;
        build(second, 0, seconds, i);

        printf("There are %d black pixels.\n", count(0, 1024));
    }
}
