#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calcBribes(vector<int>& counts, int ours) {
    sort(counts.begin(), counts.end());
    int bribes = 0;
    while (counts[counts.size() - 1] >= ours) {
        counts[counts.size() - 1]--;
        ours++;
        bribes++;
        for (int i = counts.size() - 1; i > 0; --i) {
            if (counts[i] < counts[i - 1])
                swap(counts[i - 1], counts[i]);
                else
            break;
        }
    }
    return bribes;
}


int main() {
    int districts, parties;

    cin >> districts >> parties;
    int toWin = districts / 2 + 1;  

    int districtsWon = 0;
    int bribedVoters = 0;

    vector<int> votes;
    vector<int> bribes;
    votes.reserve(parties);
    bribes.reserve(parties);
    while (districts--) {
        int ourPartie;
        cin >> ourPartie;
        for (int i = 1; i < parties; ++i) {
            int opposingPartie;
            cin >> opposingPartie;
            if (opposingPartie >= ourPartie) {
                votes.push_back(opposingPartie);
            }
        }
        if (votes.size() > 0) {
            bribes.push_back(calcBribes(votes, ourPartie));
        } else 
            districtsWon++;
        if (districtsWon >= toWin) break;
        votes.clear();
    }

    if (districtsWon < toWin) {
        sort(bribes.begin(), bribes.end());
        int index = 0;
        while (districtsWon < toWin) {
            bribedVoters += bribes[index++];
            districtsWon++;
        }
    }

    cout << bribedVoters << '\n';
}