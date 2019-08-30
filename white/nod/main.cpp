#include <iostream>

using namespace std;

long nod(long max, long min) {
    long d = max % min;
    if (d == 0) {
        return min;
    }
    return nod(min, d);
}

int main()
{
    long a, b;
    cin >> a >> b;

    long result;
    result = a > b ? nod(a, b) : nod(b, a);

    cout << result << endl;

    return 0;
}
