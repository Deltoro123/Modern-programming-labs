#include <iostream>
#include <functional>
using namespace std;

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

    // Удаление элемента по ключу (используется функция сравнения)
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

    // Поиск элемента (возвращает указатель на данные или nullptr)
    T* find(const T& key, function<bool(const T&, const T&)> cmp = [](const T& a, const T& b) { return a == b; }) {
        Node* curr = head;
        while (curr) {
            if (cmp(curr->data, key))
                return &(curr->data);
            curr = curr->next;
        }
        return nullptr;
    }

    // Вывод списка с помощью функции печати элемента
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

// Пример использования для целых чисел
static void example_int() {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print([](int x) { cout << x << " "; });   // 5 10 20

    list.remove(10);
    list.print([](int x) { cout << x << " "; });   // 5 20
}

int main() {
    example_int();
    return 0;
}