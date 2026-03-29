#include <iostream>
#include <cstring>
#include <clocale> // для setlocale
using namespace std;

template <class T>
T getmax(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

// Специализация для const char* (обычная перегрузка)
const char* getmax(const char* s1, const char* s2)
{
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

template <class T>
T getmax(T t[], size_t size)
{
    T retval = t[0];
    for (size_t i = 1; i < size; ++i)
        if (t[i] > retval) retval = t[i];
    return retval;
}

int main()
{
    setlocale(LC_ALL, "Russian"); // устанавливаем русскую локаль

    int i1 = 3, i2 = 5;
    const char* s1 = "строка1";
    const char* s2 = "строка2";

    cout << "max int = " << getmax(i1, i2) << endl;
    cout << "max str = " << getmax(s1, s2) << endl;

    return 0;
}