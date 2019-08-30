#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    long x;
    vector<bool> binary_digits;

    cin >> x;

    while(x > 0) {
        binary_digits.push_back(x % 2);
        x /= 2;
    }

    reverse(begin(binary_digits), end(binary_digits));

    for(const auto d: binary_digits) {
        cout << (d ? 1 : 0);
    }
    cout << endl;


    return 0;
}
