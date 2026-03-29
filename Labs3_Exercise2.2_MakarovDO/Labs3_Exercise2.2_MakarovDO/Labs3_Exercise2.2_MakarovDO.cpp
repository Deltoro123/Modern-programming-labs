#include <iostream>
#include <conio.h>  // Для _getch() в Visual Studio
using namespace std;

// Функция для разделения массива (Hoare partition)
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // Опорный элемент
    int i = low - 1;       // Индекс меньшего элемента

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            // Меняем местами arr[i] и arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Ставим опорный элемент на место
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Рекурсивная быстрая сортировка
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // Индекс разделения

        quickSort(arr, low, pi - 1);  // Левая часть
        quickSort(arr, pi + 1, high); // Правая часть
    }
}

int main()  // Изменено с void на int
{
    int mas[] = { 2,5,-8,1,-4,6,3,-5,-9,13,0,4,9 };
    int n = sizeof(mas) / sizeof(int);

    // Очистка экрана (для Windows)
    system("cls");  // Вместо clrscr()

    // Установка русской кодировки
    system("chcp 1251 > nul");

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;

    quickSort(mas, 0, n - 1);

    cout << "После быстрой сортировки: ";
    for (int i = 0; i < n; i++)  // i объявлена здесь
        cout << mas[i] << ' ';
    cout << endl;

    cout << "Нажмите любую клавишу для выхода...";
    _getch();  // В Visual Studio используется _getch() вместо getch()

    return 0;  // Возвращаем 0
}