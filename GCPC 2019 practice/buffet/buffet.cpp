#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

struct dish {
    int amount;
    double nom;
};

int main() {
    int numdishes, platespace;
    cin >> numdishes >> platespace;
    dish* dishes = new dish[numdishes];
    for (int i = 0; i < numdishes; ++i) {
        string trash;
        int amount;
        double nom;
        cin >> trash >> amount >> nom;
        dishes[i].amount = amount;
        dishes[i].nom = nom;
    }
    sort(dishes, dishes + numdishes,
         [](const dish& a, const dish& b) { return a.nom > b.nom; });

    int index = 0;
    double result = 0;
    while (platespace--) {
        result += dishes[index].nom;
        dishes[index].amount--;
        if (dishes[index].amount == 0) index++;
    }

    cout << result << "\n";

    return 0;
}
