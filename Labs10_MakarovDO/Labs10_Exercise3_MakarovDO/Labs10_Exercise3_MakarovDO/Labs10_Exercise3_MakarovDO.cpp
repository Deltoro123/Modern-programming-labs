#include <iostream>
#include <string>
#include <functional>
#include <clocale>   // для setlocale
#include <windows.h> // для SetConsoleCP/SetConsoleOutputCP (альтернатива)
using namespace std;

// ========== Шаблон односвязного списка ==========
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr) {}
    ~SinglyLinkedList() { clear(); }

    // Добавление в конец
    void push_back(const T& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Добавление в начало
    void push_front(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        if (!tail) tail = head;
    }

    // Удаление элемента по ключу
    bool remove(const T& key, function<bool(const T&, const T&)> cmp = [](const T& a, const T& b) { return a == b; }) {
        if (!head) return false;

        // Если удаляем первый
        if (cmp(head->data, key)) {
            Node* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            return true;
        }

        Node* prev = head;
        Node* curr = head->next;
        while (curr) {
            if (cmp(curr->data, key)) {
                prev->next = curr->next;
                if (curr == tail) tail = prev;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // Поиск элемента
    T* find(const T& key, function<bool(const T&, const T&)> cmp = [](const T& a, const T& b) { return a == b; }) {
        Node* curr = head;
        while (curr) {
            if (cmp(curr->data, key))
                return &(curr->data);
            curr = curr->next;
        }
        return nullptr;
    }

    // Вывод списка
    void print(function<void(const T&)> printElem) const {
        Node* curr = head;
        while (curr) {
            printElem(curr->data);
            curr = curr->next;
        }
        cout << endl;
    }

    // Очистка списка
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    bool empty() const { return head == nullptr; }
};

// ========== Структура автобуса ==========
struct Bus {
    int number;
    string driver;
    int route;

    void print() const {
        cout << "Автобус " << number << ", водитель " << driver << ", маршрут " << route;
    }
};

// Сравнение по номеру автобуса
static bool compareByNumber(const Bus& a, const Bus& b) {
    return a.number == b.number;
}

// Меню
static void showMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Выезд автобуса из парка\n";
    cout << "2. Въезд автобуса в парк\n";
    cout << "3. Показать автобусы в парке\n";
    cout << "4. Показать автобусы на маршруте\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    // Настройка кодировки для корректного вывода в консоли Windows
    // Вариант 1: через setlocale
    setlocale(LC_ALL, "Russian");
    // Вариант 2: через WinAPI (раскомментировать если setlocale не помогает)
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    // Создание списков
    SinglyLinkedList<Bus> park;
    SinglyLinkedList<Bus> route;

    // Начальное наполнение парка
    park.push_back({ 101, "Иванов И.И.", 5 });
    park.push_back({ 102, "Петров П.П.", 8 });
    park.push_back({ 103, "Сидоров С.С.", 12 });
    park.push_back({ 104, "Кузнецов К.К.", 5 });

    cout << "Программа управления автобусным парком\n";

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: { // Выезд автобуса
            int num;
            cout << "Введите номер автобуса, выезжающего из парка: ";
            cin >> num;

            Bus temp;
            temp.number = num;
            Bus* found = park.find(temp, compareByNumber);
            if (found) {
                Bus busToMove = *found;
                park.remove(temp, compareByNumber);
                route.push_back(busToMove);
                cout << "Автобус " << num << " выехал на маршрут.\n";
            }
            else {
                cout << "Автобус с номером " << num << " не найден в парке.\n";
            }
            break;
        }
        case 2: { // Въезд автобуса
            int num;
            cout << "Введите номер автобуса, возвращающегося в парк: ";
            cin >> num;

            Bus temp;
            temp.number = num;
            Bus* found = route.find(temp, compareByNumber);
            if (found) {
                Bus busToMove = *found;
                route.remove(temp, compareByNumber);
                park.push_back(busToMove);
                cout << "Автобус " << num << " вернулся в парк.\n";
            }
            else {
                cout << "Автобус с номером " << num << " не найден на маршруте.\n";
            }
            break;
        }
        case 3: // Показать парк
            cout << "Автобусы в парке:\n";
            if (park.empty())
                cout << "Список пуст.\n";
            else
                park.print([](const Bus& b) { b.print(); cout << "\n"; });
            break;
        case 4: // Показать маршрут
            cout << "Автобусы на маршруте:\n";
            if (route.empty())
                cout << "Список пуст.\n";
            else
                route.print([](const Bus& b) { b.print(); cout << "\n"; });
            break;
        case 0:
            cout << "Завершение работы.\n";
            break;
        default:
            cout << "Неверный выбор. Повторите.\n";
        }
    } while (choice != 0);

    return 0;
}