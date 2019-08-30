#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s1, s2, s3;

    cin >> s1 >> s2 >> s3;

    cout << min(s1, min(s2, s3)) << endl;

    return 0;
}
