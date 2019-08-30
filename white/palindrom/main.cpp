#include <iostream>

using namespace std;

bool is_palindrom(const string& input) {
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] != input[input.size()-1-i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << is_palindrom("madam") << endl;
    cout << is_palindrom("gentleman") << endl;
    cout << is_palindrom("x") << endl;
    cout << is_palindrom("") << endl;
    return 0;
}
