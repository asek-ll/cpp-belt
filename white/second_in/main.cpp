#include <iostream>

using namespace std;

int main()
{
    string input;
    cin >> input;

    int out = -2;

    for(size_t i = 0; i < input.length(); ++i){
        if (input[i] == 'f') {
            if (out == -1) {
                out = int(i);
                break;
            } else {
                out = -1;
            }
        }

    }

    cout << out << endl;

    return 0;
}
