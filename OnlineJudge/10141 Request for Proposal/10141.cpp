#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int rfp = 1;
    int n, p;
    while (scanf("%d %d", &n, &p), n != 0 && p != 0) {
        while (getchar() != '\n')
            ;
        string dummy;
        while (n--) {
            getline(cin, dummy);
            // cout << dummy << endl;
        }
        int bestRq = -1;
        double bestPrice;
        string bestName;
        while (p--) {
            int rq;
            double price;
            string name;
            getline(cin, name);
            scanf("%lf %d", &price, &rq);
            while (getchar() != '\n')
                ;
            if (rq > bestRq) {
                bestRq = rq;
                bestPrice = price;
                bestName = name;
            } else if (rq == bestRq) {
                if (price < bestPrice) {
                    bestRq = rq;
                    bestPrice = price;
                    bestName = name;
                }
            }
            while (rq--) getline(cin, dummy);
        }
        if (rfp > 1) printf("\n");
        printf("RFP #%d\n%s\n", rfp++, bestName.c_str());
    }
}
