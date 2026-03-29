#include <iostream>
#include <conio.h>  // Для _getch() в Visual Studio
using namespace std;

void sortRangeAsc(int arr[], int n, int N1, int N2)
{
    // Проверка границ
    if (N1 < 0) N1 = 0;
    if (N2 >= n) N2 = n - 1;
    if (N1 >= N2) return;

    // Сортировка пузырьком только в заданном диапазоне
    for (int i = N1; i <= N2; i++)
    {
        for (int j = N1; j < N2 - (i - N1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()  // main должен возвращать int
{
    // Устанавливаем русскую кодировку
    system("chcp 1251 > nul");

    int mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(mas) / sizeof(int);
    int N1 = 3, N2 = 8; // Пример интервала

    // Очистка экрана (вместо clrscr)
    system("cls");

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    // Вызываем функцию сортировки
    sortRangeAsc(mas, n, N1, N2);

    cout << "После сортировки интервала [" << N1 << ", " << N2 << "] по возрастанию: ";
    for (int i = 0; i < n; i++)  // i объявлена здесь
        cout << mas[i] << ' ';
    cout << endl;

    cout << "\nНажмите любую клавишу для выхода...";
    _getch();  // В Visual Studio используется _getch()

    return 0;
}