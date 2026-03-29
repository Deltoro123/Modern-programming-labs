#include <iostream>      
#include <iomanip>       
#include <cstdlib>       
#include <ctime>         
#include <cmath>   
#include <windows.h>      // Для SetConsoleCP и SetConsoleOutputCP
#include <clocale>        // Для setlocale
using namespace std;

#define N 5  // размерность матрицы

// Прототипы функций
void findRowMax(float m[N][N], float rowMax[N]);
void findColMax(float m[N][N], float colMax[N]);
void findRowAvg(float m[N][N], float rowAvg[N]);
void findColAvg(float m[N][N], float colAvg[N]);
void findGroupSums(float m[N][N], float& upperSum, float& lowerSum);
float findClosestToAvg(float m[N][N], float totalAvg);
void printArray(float arr[N], const char* title);
void printResult(float value, const char* title);

int main()
{
    // Настройка кодировки для правильного отображения русского текста
    SetConsoleCP(1251);           // Ввод в консоли (если понадобится)
    SetConsoleOutputCP(1251);      // Вывод в консоль
    setlocale(LC_ALL, "Russian");  // Для потокового ввода-вывода

    float m[N][N];  // исходная матрица
    int i, j;

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(NULL)));

    // Заполнение матрицы случайными числами
    cout << "Исходная матрица " << N << "x" << N << ":\n";
    cout << fixed << setprecision(4);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            // Генерация чисел от 0 до 32.7 с одним знаком после запятой
            m[i][j] = (rand() % 327) / 10.0f;
            cout << setw(8) << m[i][j];
        }
        cout << endl;
    }
    cout << "\n";

    // Массивы для хранения результатов
    float rowMax[N];      // максимумы строк
    float colMax[N];      // максимумы столбцов
    float rowAvg[N];      // средние арифметические строк
    float colAvg[N];      // средние арифметические столбцов
    float upperSum, lowerSum;  // суммы верхней и нижней частей
    float totalAvg;       // общее среднее арифметическое
    float closestValue;   // элемент, ближайший к среднему

    // 1. Нахождение максимальных значений строк
    findRowMax(m, rowMax);
    printArray(rowMax, "Максимальные значения строк:");

    // 2. Нахождение максимальных значений столбцов
    findColMax(m, colMax);
    printArray(colMax, "Максимальные значения столбцов:");

    // 3. Нахождение средних арифметических строк
    findRowAvg(m, rowAvg);
    printArray(rowAvg, "Средние арифметические строк:");

    // 4. Нахождение средних арифметических столбцов
    findColAvg(m, colAvg);
    printArray(colAvg, "Средние арифметические столбцов:");

    // Вычисление общего среднего арифметического для последующего поиска
    totalAvg = 0;
    for (i = 0; i < N; i++)
        totalAvg += rowAvg[i];
    totalAvg /= N;

    // 5. Суммы нижне- и верхнегрупповых частей матрицы
    findGroupSums(m, upperSum, lowerSum);
    printResult(upperSum, "Сумма верхнегрупповой части (включая главную диагональ):");
    printResult(lowerSum, "Сумма нижнегрупповой части (включая главную диагональ):");

    // 6. Элемент, наиболее близкий по значению к среднеарифметическому
    closestValue = findClosestToAvg(m, totalAvg);
    printResult(closestValue, "Элемент, наиболее близкий к общему среднему арифметическому:");
    printResult(totalAvg, "Общее среднее арифметическое матрицы:");

    cout << "\nНажмите Enter для продолжения...";
    cin.ignore();  // Очищаем буфер ввода
    cin.get();     // Ожидание нажатия Enter
    return 0;      // Возвращаем 0 - успешное завершение
}

void findRowMax(float m[N][N], float rowMax[N])
{
    for (int i = 0; i < N; i++)
    {
        rowMax[i] = m[i][0];
        for (int j = 1; j < N; j++)
        {
            if (m[i][j] > rowMax[i])
                rowMax[i] = m[i][j];
        }
    }
}

void findColMax(float m[N][N], float colMax[N])
{
    for (int j = 0; j < N; j++)
    {
        colMax[j] = m[0][j];
        for (int i = 1; i < N; i++)
        {
            if (m[i][j] > colMax[j])
                colMax[j] = m[i][j];
        }
    }
}

void findRowAvg(float m[N][N], float rowAvg[N])
{
    for (int i = 0; i < N; i++)
    {
        float sum = 0;
        for (int j = 0; j < N; j++)
        {
            sum += m[i][j];
        }
        rowAvg[i] = sum / N;
    }
}

void findColAvg(float m[N][N], float colAvg[N])
{
    for (int j = 0; j < N; j++)
    {
        float sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += m[i][j];
        }
        colAvg[j] = sum / N;
    }
}

void findGroupSums(float m[N][N], float& upperSum, float& lowerSum)
{
    upperSum = 0;
    lowerSum = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i <= j)  // Верхнегрупповая часть (включая диагональ)
                upperSum += m[i][j];

            if (i >= j)  // Нижнегрупповая часть (включая диагональ)
                lowerSum += m[i][j];
        }
    }
}

float findClosestToAvg(float m[N][N], float target)
{
    float closest = m[0][0];
    float minDiff = fabs(m[0][0] - target);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            float diff = fabs(m[i][j] - target);
            if (diff < minDiff)
            {
                minDiff = diff;
                closest = m[i][j];
            }
        }
    }

    return closest;
}

void printArray(float arr[N], const char* title)
{
    cout << title << "\n";
    cout << fixed << setprecision(4);
    for (int i = 0; i < N; i++)
    {
        cout << setw(8) << arr[i];
    }
    cout << "\n\n";
}

void printResult(float value, const char* title)
{
    cout << title << " " << fixed << setprecision(4) << setw(8) << value << "\n";
}