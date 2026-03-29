#include <iostream>
using namespace std;

// Шаблон пузырьковой сортировки
template <class T>
void Sort(T array[], size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = size - 1; i < j; --j)
            if (array[i] > array[j])
            {
                T tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
}

// Класс Money
class Money
{
    long dollars;
    int cents;
public:
    Money() : dollars(0), cents(0) {}
    Money(long d, int c) : dollars(d), cents(c) {}

    // Оператор сравнения для сортировки
    int operator>(const Money& amt) const
    {
        return (dollars > amt.dollars) ||
            ((dollars == amt.dollars) && (cents > amt.cents));
    }

    friend ostream& operator<<(ostream& os, const Money& amt);
};

ostream& operator<<(ostream& os, const Money& amt)
{
    os << amt.dollars << '.' << amt.cents;
    return os;
}

int main()
{
    Money mas[] = {
        Money(19, 10),
        Money(99, 99),
        Money(99, 95),
        Money(19, 95)
    };
    size_t size = sizeof(mas) / sizeof(mas[0]);

    Sort(mas, size);

    for (size_t i = 0; i < size; ++i)
        cout << "mas[" << i << "] = " << mas[i] << endl;

    return 0;
}