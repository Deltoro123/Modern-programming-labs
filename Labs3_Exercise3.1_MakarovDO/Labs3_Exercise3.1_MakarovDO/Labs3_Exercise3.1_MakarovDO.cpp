#include <iostream>
#include <conio.h>  // Для _getch() в Visual Studio
using namespace std;

void specialSort(int arr[], int n)
{
    // Сначала сортируем весь массив по возрастанию (пузырьковая сортировка)
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

    // Создаем временный массив для нечетных чисел
    int* odd = new int[n];
    int oddCount = 0;

    // Собираем нечетные числа
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0) // если число нечетное
        {
            odd[oddCount] = arr[i];
            oddCount++;
        }
    }

    // Вставляем нечетные числа обратно в обратном порядке (по убыванию)
    int oddIndex = oddCount - 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            arr[i] = odd[oddIndex];
            oddIndex--;
        }
    }

    // Освобождаем память
    delete[] odd;
}

int main()  // main должен возвращать int, не void
{
    // Устанавливаем русскую кодировку для консоли
    system("chcp 1251 > nul");  // Для русского языка

    int mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(mas) / sizeof(int);

    // Очистка экрана (вместо clrscr)
    system("cls");

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    specialSort(mas, n);

    cout << "После спец. сортировки: ";
    for (int i = 0; i < n; i++)  // i объявлена здесь
        cout << mas[i] << ' ';
    cout << endl;

    cout << "\nНажмите любую клавишу для выхода...";
    _getch();  // В Visual Studio используется _getch() вместо getch()

    return 0;  // Возвращаем 0
}