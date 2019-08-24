#include <cmath>
#include <iostream>
#include <limits>
#include <set>

using namespace std;

int main() {
    uint64_t m, n;

    cin >> m >> n;
    while (true) {
        if (m % n == 0) {
            cout << "minimum volume: " << n << " liter(s)\n"
                 << m << " liter(s) not needed\n"
                 << n << " liter(s) poured 1 times\n";
        } else {
            uint64_t remainder = n % m;
            uint64_t times = ceil((double)m / (double)remainder);
            uint64_t diff = remainder - ((remainder * times) % m);
            uint64_t back = (remainder - 1) / diff;

            uint64_t pourN = 1 + times * back;
            uint64_t withdrawM = (pourN * n) / m;
            uint64_t minLitersNM = (pourN * n) % m;
            cout << remainder << endl;
            cout << times << endl;
            cout << diff << endl;
            cout << back << endl;

            cout << pourN << endl;
            cout << withdrawM << endl;
            cout << minLitersNM << endl << endl;

            remainder = m % n;
            times = ceil((double)n / (double)remainder);
            diff = remainder - ((remainder * times) % n);
            back = (remainder - 1) / diff;

            uint64_t pourM = 1 + times * back;
            uint64_t withdrawN = (pourN * n) / m;
            uint64_t minLitersMN = (pourN * n) % m;
            cout << remainder << endl;
            cout << times << endl;
            cout << diff << endl;
            cout << back << endl;

            cout << pourM << endl;
            cout << withdrawN << endl;
            cout << minLitersMN << endl << endl;

            bool mPoured;

            if (minLitersNM < minLitersMN) {
                mPoured = false;
            } else if (minLitersNM > minLitersMN) {
                mPoured = true;
            } else {
                mPoured = pourM + withdrawM < pourN + withdrawM;
            }

            cout << "mPoured: " << mPoured << endl;

            if (mPoured) {
                cout << "minimum volume: " << minLitersMN << " liter(s)\n"
                     << m << " liter(s) poured " << pourM << " times\n"
                     << n << " liter(s) withdrawn " << withdrawN << " times\n";
            } else {
                cout << "minimum volume: " << minLitersNM << " liter(s)\n"
                     << m << " liter(s) withdrawn " << withdrawM << " times\n"
                     << n << " liter(s) poured " << pourN << " times\n";
            }
        }

        cin >> m >> n;
        if (m == 0 && n == 0)
            break;
        else
            cout << '\n';
    }
}
