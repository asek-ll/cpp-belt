#include <iostream>

using namespace std;

long factorial(long x) {
    if (x <= 1) {
        return 1;
    }
    return factorial(x-1) * x;
}

int main()
{
    long x;
    cin >> x;

    cout << factorial(x) << endl;
    return 0;
}
