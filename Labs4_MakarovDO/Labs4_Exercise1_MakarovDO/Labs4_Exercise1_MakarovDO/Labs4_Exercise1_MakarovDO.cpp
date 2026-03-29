#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <clocale>  // для setlocale
#include <windows.h> // для SetConsoleCP и SetConsoleOutputCP
using namespace std;

int main() {
    // Устанавливаем русскую локаль
    setlocale(LC_ALL, "Russian");
    // Устанавливаем кодировку консоли на Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("cls");

    char str1[20] = "Hello";
    char str2[20] = "World";
    char str3[40];

    cout << "--- strlen ---" << endl;
    cout << "Длина str1 ('Hello'): " << strlen(str1) << endl;
    cout << "Длина str2 ('World'): " << strlen(str2) << endl;

    cout << "\n--- strcpy ---" << endl;
    strcpy(str3, str1);
    cout << "Копирование str1 в str3: " << str3 << endl;

    cout << "\n--- strcat ---" << endl;
    strcpy(str3, str1);
    strcat(str3, " ");
    strcat(str3, str2);
    cout << "Конкатенация str1 и str2: " << str3 << endl;

    cout << "\n--- strcmp ---" << endl;
    int result = strcmp(str1, str2);
    cout << "Сравнение 'Hello' и 'World': " << result << endl;
    if (result < 0) cout << "Результат < 0: str1 меньше str2" << endl;
    else if (result > 0) cout << "Результат > 0: str1 больше str2" << endl;
    else cout << "Результат = 0: строки равны" << endl;

    cout << "Сравнение 'Hello' и 'Hello': " << strcmp(str1, "Hello") << " (равны)" << endl;

    system("pause");
    return 0;
}