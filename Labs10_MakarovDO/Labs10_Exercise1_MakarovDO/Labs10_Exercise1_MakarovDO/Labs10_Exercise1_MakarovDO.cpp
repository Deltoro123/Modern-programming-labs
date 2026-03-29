#include <iostream>
using namespace std;

// Узел односвязного списка
struct Node {
    int data;
    Node* next;
};

// Создание первого элемента
Node* first(int d) {
    Node* pv = new Node;
    pv->data = d;
    pv->next = nullptr;
    return pv;
}

// Добавление в конец списка
void add(Node** pend, int d) {
    Node* pv = new Node;
    pv->data = d;
    pv->next = nullptr;
    (*pend)->next = pv;
    *pend = pv;
}

// Поиск элемента по ключу (значению)
Node* find(Node* pbeg, int key) {
    Node* pv = pbeg;
    while (pv) {
        if (pv->data == key)
            return pv;
        pv = pv->next;
    }
    return nullptr;
}

// Удаление элемента по ключу
bool remove(Node** pbeg, Node** pend, int key) {
    Node* pkey = find(*pbeg, key);
    if (!pkey) return false;   // элемент не найден

    // Если удаляемый элемент – первый
    if (pkey == *pbeg) {
        *pbeg = pkey->next;
        if (*pbeg == nullptr)  // список стал пустым
            *pend = nullptr;
        delete pkey;
        return true;
    }

    // Ищем предыдущий узел
    Node* prev = *pbeg;
    while (prev->next != pkey)
        prev = prev->next;

    prev->next = pkey->next;
    if (pkey == *pend)         // если удаляли последний
        *pend = prev;
    delete pkey;
    return true;
}

// Вставка элемента после элемента с заданным ключом
Node* insert(Node* pbeg, Node** pend, int key, int d) {
    Node* pkey = find(pbeg, key);
    if (!pkey) return nullptr; // ключ не найден

    Node* pv = new Node;
    pv->data = d;
    pv->next = pkey->next;
    pkey->next = pv;

    if (pkey == *pend)         // если вставляем после последнего
        *pend = pv;
    return pv;
}

// Вывод списка
void print(Node* pbeg) {
    Node* pv = pbeg;
    while (pv) {
        cout << pv->data << " ";
        pv = pv->next;
    }
    cout << endl;
}

int main() {
    // Формирование первого элемента
    Node* pbeg = first(1);
    Node* pend = pbeg;          // пока один элемент

    // Добавляем 2,3,4,5
    for (int i = 2; i <= 5; ++i)
        add(&pend, i);

    // Вставка 200 после 2
    insert(pbeg, &pend, 2, 200);

    // Удаление 5
    if (!remove(&pbeg, &pend, 5))
        cout << "Элемент 5 не найден\n";

    // Вывод списка
    print(pbeg);   // ожидаемый результат: 1 2 200 3 4

    // Освобождение памяти (необязательно для примера)
    return 0;
}