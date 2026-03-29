#include <iostream>
#include <locale>
using namespace std;

// 1. Передача по значению (не работает, копии)
void obmen1(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// 2. Передача по указателю (работает)
void obmen2(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 3. Передача по ссылке (работает)
void obmen3(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main() {
    setlocale(LC_ALL, "ru");

    int a = 2, b = 5;

    cout << "до обмена: " << a << ", " << b << endl;

    obmen1(a, b);
    cout << "после обмена 1 (по значению): " << a << ", " << b << " (не изменились)" << endl;

    obmen2(&a, &b);
    cout << "после обмена 2 (по указателю): " << a << ", " << b << endl;

    obmen3(a, b);
    cout << "после обмена 3 (по ссылке): " << a << ", " << b << endl;

    return 0;
}