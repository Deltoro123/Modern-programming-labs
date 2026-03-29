#include <iostream>
#include <windows.h>  // Для SetConsoleCP и SetConsoleOutputCP
using namespace std;

// Функция сортировки пузырьком
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
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

int main()
{
    // Устанавливаем правильную кодировку для консоли
    SetConsoleCP(1251);        // Устанавливаем кодировку ввода
    SetConsoleOutputCP(1251);   // Устанавливаем кодировку вывода

    int mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(mas) / sizeof(int);

    // Очистка экрана (по желанию)
    system("cls");

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    bubbleSort(mas, n);

    cout << "После пузырьковой сортировки: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    system("pause");
    return 0;
}