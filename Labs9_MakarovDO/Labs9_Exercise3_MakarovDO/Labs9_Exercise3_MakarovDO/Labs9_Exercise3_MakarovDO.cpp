#include <iostream>
using namespace std;

// Шаблон класса стек
template <class T>
class TStack
{
protected:
    int numItem;     // количество элементов
    T* item;         // указатель на массив
    size_t capacity; // вместимость
public:
    TStack(size_t size = 10) : numItem(0), capacity(size)
    {
        item = new T[size];
    }

    ~TStack()
    {
        delete[] item;
    }

    void push(T t)
    {
        if (numItem < capacity)
            item[numItem++] = t;
        else
            cerr << "Stack overflow!" << endl;
    }

    T pop()
    {
        if (numItem > 0)
            return item[--numItem];
        else
        {
            cerr << "Stack underflow!" << endl;
            return T(); // возвращаем значение по умолчанию
        }
    }

    bool empty() const
    {
        return numItem == 0;
    }

    T top() const
    {
        if (numItem > 0)
            return item[numItem - 1];
        else
        {
            cerr << "Stack empty!" << endl;
            return T();
        }
    }
};

// Функция сортировки поезда с использованием стека
bool sortTrain(int wagons[], size_t n)
{
    TStack<int> stack(n); // стек-тупик
    int expected = 1;     // ожидаемый номер

    cout << "\nПроцесс сортировки:\n";

    for (size_t i = 0; i < n; ++i)
    {
        int v = wagons[i];

        // Пока наверху стека нужный вагон, выталкиваем
        while (!stack.empty() && stack.top() == expected)
        {
            cout << "Вагон " << stack.pop() << " выехал на выход\n";
            ++expected;
        }

        if (v == expected)
        {
            cout << "Вагон " << v << " сразу отправлен на выход\n";
            ++expected;
        }
        else if (v > expected)
        {
            cout << "Вагон " << v << " заехал в тупик\n";
            stack.push(v);
        }
        else // v < expected
        {
            cout << "Ошибка: вагон " << v
                << " нельзя ни отправить, ни задвинуть в тупик!\n";
            return false;
        }
    }

    // Выталкиваем остатки из стека
    while (!stack.empty())
    {
        int v = stack.pop();
        if (v == expected)
        {
            cout << "Вагон " << v << " выехал на выход\n";
            ++expected;
        }
        else
        {
            cout << "Ошибка: в тупике остались неподходящие вагоны!\n";
            return false;
        }
    }

    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t n;
    cout << "Введите количество вагонов: ";
    cin >> n;

    int* wagons = new int[n];
    cout << "Введите номера вагонов (от 1 до " << n << "): ";
    for (size_t i = 0; i < n; ++i)
        cin >> wagons[i];

    if (sortTrain(wagons, n))
        cout << "\nСортировка выполнена успешно!\n";
    else
        cout << "\nСортировка невозможна!\n";

    delete[] wagons;
    return 0;
}