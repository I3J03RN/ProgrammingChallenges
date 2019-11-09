#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int months, records;
    double downPayment, loan;

    while (scanf("%d %lf %lf %d", &months, &downPayment, &loan, &records),
           months >= 0) {
        vector<int> startMonth(records);
        vector<double> rate(records);
        for (int i = 0; i < records; ++i)
            scanf("%d %lf", &startMonth[i], &rate[i]);
        int index = 0;
        double apply = 1 - rate[0];
        double price = loan + downPayment;
        // printf("price: %lf\n", price);
        double monthly = loan / months;
        for (int m = 0; m <= months; m++) {
            if (index < records && startMonth[index] == m)
                apply = 1 - rate[index++];

            price *= apply;
            if (m != 0) loan -= monthly;
            if (m == months) loan = 0;
            //            printf("month: %d, price: %lf, loan: %lf\n", m, price,
            //            loan);
            if (loan < price) {
                printf("%d month%s\n", m, m == 1 ? "" : "s");
                break;
            }
        }
    }

    return 0;
}
