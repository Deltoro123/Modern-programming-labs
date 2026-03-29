#include <iostream>
#include <clocale>  // Для setlocale
#include <windows.h> // Для SetConsoleCP и SetConsoleOutputCP (только для Windows)
using namespace std;

int main()
{
    // Способ 1: Установка локали
    setlocale(LC_ALL, "Russian");

    // Способ 2: Для Windows также можно установить кодировку консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(mas) / sizeof(int);

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    // Сортировка выбором
    for (int i = 0; i < n - 1; i++)
    {
        int imin = i;
        for (int j = i + 1; j < n; j++)
        {
            if (mas[j] < mas[imin])
                imin = j;
        }
        int t = mas[i];
        mas[i] = mas[imin];
        mas[imin] = t;
    }

    cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    system("pause");
    return 0;
}