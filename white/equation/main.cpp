#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    if	(a == 0.0) {
        if (b != 0.0) {
            cout << -c/b;
        }
    } else {

        double d = b*b - 4 * a * c;

        if (d == 0.0) {
            cout << (-b / (2 * a));
        } if (d > 0) {
            double sqrtd = sqrt(d);
            cout << ((-b - sqrtd) / (2 * a)) << ' ' << ((-b + sqrtd) / (2 * a));
        }

    }

    cout << endl;

    return 0;
}
