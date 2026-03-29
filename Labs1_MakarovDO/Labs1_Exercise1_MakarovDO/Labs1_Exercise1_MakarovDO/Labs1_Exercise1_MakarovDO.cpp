#include <iostream>
using namespace std;

int power(int x, int n) {
    int i, p = 1;
    for (i = 1; i <= n; i++)  // исправлено условие, чтобы степень считалась правильно
        p *= x;
    return p;
}

int main() {
    int i, k;
    int base;
    cout << "Vvedite osnovanie: ";
    cin >> base;
    for (i = 0; i < 10; i++) {
        k = power(base, i);
        cout << "i = " << i << ", k = " << k << endl;
    }
    return 0;
}