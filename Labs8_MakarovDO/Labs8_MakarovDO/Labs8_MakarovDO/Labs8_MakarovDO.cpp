
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <clocale>
using namespace std;

// -----------------------------------------------------------------
// 1. Класс Stroka (аналог лабораторной работы 6) с перегрузкой << и >>
// -----------------------------------------------------------------
class Stroka {
private:
    char* str;      // указатель на динамическую память для строки
    int length;     // длина строки

public:
    // Конструкторы
    Stroka();
    Stroka(const char*);
    Stroka(const Stroka&);
    Stroka(int size);

    // Деструктор
    ~Stroka();

    // Операторы
    Stroka& operator=(const Stroka&);
    Stroka operator+(const Stroka&) const;
    bool operator==(const Stroka&) const;

    // Методы
    int dllina() const;
    void vvod();          // ввод с клавиатуры (через cin)
    void vyvod() const;   // вывод на экран (через cout)

    // Дружественные операторы для работы с потоками
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);

    // Статические методы для работы со строками (собственные реализации)
    static int str_len(const char* s);
    static void str_cpy(char* dest, const char* src);
    static void str_cat(char* dest, const char* src);
    static int str_cmp(const char* s1, const char* s2);
};

// ---------- Реализация статических методов ----------
int Stroka::str_len(const char* s) {
    int len = 0;
    if (s != nullptr) {
        while (s[len] != '\0') len++;
    }
    return len;
}

void Stroka::str_cpy(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr) return;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void Stroka::str_cat(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr) return;
    int dest_len = str_len(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

int Stroka::str_cmp(const char* s1, const char* s2) {
    if (s1 == nullptr || s2 == nullptr) {
        return (s1 == nullptr && s2 == nullptr) ? 0 : -1;
    }
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

// ---------- Конструкторы ----------
Stroka::Stroka() {
    length = 0;
    str = new char[1];
    str[0] = '\0';
}

Stroka::Stroka(const char* s) {
    if (s != nullptr) {
        length = str_len(s);
        str = new char[length + 1];
        str_cpy(str, s);
    }
    else {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }
}

Stroka::Stroka(const Stroka& other) {
    length = other.length;
    str = new char[length + 1];
    str_cpy(str, other.str);
}

Stroka::Stroka(int size) {
    if (size <= 0) {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }
    else {
        length = 0;
        str = new char[size + 1];
        str[0] = '\0';
    }
}

// ---------- Деструктор ----------
Stroka::~Stroka() {
    delete[] str;
}

// ---------- Операторы ----------
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        str_cpy(str, other.str);
    }
    return *this;
}

Stroka Stroka::operator+(const Stroka& other) const {
    Stroka result;
    delete[] result.str;
    result.length = length + other.length;
    result.str = new char[result.length + 1];
    str_cpy(result.str, str);
    str_cat(result.str, other.str);
    return result;
}

bool Stroka::operator==(const Stroka& other) const {
    return (str_cmp(str, other.str) == 0);
}

// ---------- Методы ----------
int Stroka::dllina() const {
    return length;
}

void Stroka::vvod() {
    char buffer[1000];
    cin >> buffer;
    delete[] str;
    length = str_len(buffer);
    str = new char[length + 1];
    str_cpy(str, buffer);
}

void Stroka::vyvod() const {
    cout << str;
}

// ---------- Перегрузка операторов потоков ----------
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& is, Stroka& s) {
    char buffer[1000];
    is >> buffer;
    delete[] s.str;
    s.length = Stroka::str_len(buffer);
    s.str = new char[s.length + 1];
    Stroka::str_cpy(s.str, buffer);
    return is;
}

// -----------------------------------------------------------------
// 2. Демонстрация форматирования вывода (страница 22)
// -----------------------------------------------------------------
void demoFormatting() {
    cout << "\n--- Форматирование вывода ---\n";
    double pi = 3.1415926535;
    int num = 12345;

    cout << "Без форматирования: " << pi << endl;
    cout << fixed << setprecision(2);
    cout << "fixed + setprecision(2): " << pi << endl;
    cout << "Ширина 10, заполнитель '*': " << setw(10) << setfill('*') << num << endl;
    cout.unsetf(ios::fixed);       // сброс флага fixed
    cout << "После сброса fixed: " << pi << endl;
}

// -----------------------------------------------------------------
// 3. Демонстрация состояния потока (страница 23)
// -----------------------------------------------------------------
void demoStreamState() {
    cout << "\n--- Состояние потока ---\n";
    ifstream file("nonexistent.txt");
    if (file.fail()) {
        cout << "Ошибка открытия файла (fail() == true).\n";
        file.clear();
        cout << "После clear() состояние: " << (file.good() ? "good" : "bad") << endl;
    }

    // Демонстрация eof()
    ofstream test("test.txt");
    test << "Hello";
    test.close();
    ifstream fin("test.txt");
    char ch;
    while (fin.get(ch)) {}
    if (fin.eof()) cout << "Достигнут конец файла (eof() == true).\n";
    fin.close();
    remove("test.txt");
}

// -----------------------------------------------------------------
// 4. Демонстрация манипуляторов (страница 24)
// -----------------------------------------------------------------
void demoManipulators() {
    cout << "\n--- Манипуляторы ---\n";
    int val = 255;
    cout << "Десятичное: " << dec << val << endl;
    cout << "Шестнадцатеричное: " << hex << val << endl;
    cout << "Восьмеричное: " << oct << val << endl;
    cout << "Снова десятичное: " << dec << val << endl;
    cout << "endl (перевод строки + сброс буфера)" << endl;
}

// -----------------------------------------------------------------
// 5. Программа-шифратор с файловыми потоками
// -----------------------------------------------------------------
void encryptFile(const string& inFile, const string& outFile, const string& key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Ошибка: не удалось открыть " << inFile << endl;
        return;
    }
    if (!out.is_open()) {
        cerr << "Ошибка: не удалось создать " << outFile << endl;
        return;
    }

    char ch;
    size_t keyLen = key.length();
    size_t i = 0;
    while (in.get(ch)) {
        ch ^= key[i % keyLen];
        out.put(ch);
        i++;
    }
    in.close();
    out.close();
    cout << "Файл " << inFile << " зашифрован в " << outFile << endl;
}

void cipherProgram() {
    cout << "\n--- Программа-шифратор файлов ---\n";
    string input, output, key;
    cout << "Входной файл: "; cin >> input;
    cout << "Выходной файл: "; cin >> output;
    cout << "Ключ: "; cin >> key;

    encryptFile(input, output, key);
    // Проверка: повторное шифрование должно вернуть исходник
    string check = "check_temp.txt";
    encryptFile(output, check, key);

    // Сравнение исходного и проверочного
    ifstream orig(input, ios::binary);
    ifstream chk(check, ios::binary);
    bool same = true;
    char o, c;
    while (orig.get(o) && chk.get(c)) if (o != c) { same = false; break; }
    if (orig.get(o) || chk.get(c)) same = false;
    orig.close(); chk.close();

    if (same)
        cout << "Проверка успешна: повторное шифрование восстановило исходный файл.\n";
    else
        cout << "Ошибка: файлы не совпадают!\n";
    remove(check.c_str());
}

// -----------------------------------------------------------------
// 6. Изменение состояния потоков (setf/unsetf, flags, clear)
// -----------------------------------------------------------------
void demoStreamFlags() {
    cout << "\n--- Изменение состояния потоков ---\n";

    // Сохраняем исходные флаги
    ios::fmtflags old = cout.flags();

    cout.setf(ios::showpos | ios::left);
    cout << "Установлены showpos и left:\n";
    cout << setw(10) << 123 << endl;
    cout << setw(10) << -456 << endl;

    cout.flags(old);
    cout << "После восстановления:\n";
    cout << setw(10) << 123 << endl;
    cout << setw(10) << -456 << endl;

    // Демонстрация ввода с ошибкой
    cout << "\nВведите число: ";
    int x;
    cin >> x;
    if (cin.fail()) {
        cout << "Ошибка ввода! cin.fail() == true\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "После clear() и ignore() введите число: ";
        cin >> x;
        cout << "Вы ввели: " << x << endl;
    }
    else {
        cout << "Вы ввели: " << x << endl;
    }
}

// -----------------------------------------------------------------
// 7. Собственная программа: форматирование таблицы
// -----------------------------------------------------------------
void myTableDemo() {
    cout << "\n--- Собственная программа: таблица с форматированием ---\n";

    struct Product {
        const char* name;
        double price;
        int qty;
    } items[] = {
        {"Молоко", 58.50, 10},
        {"Хлеб", 35.20, 5},
        {"Масло", 120.90, 3}
    };

    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrec = cout.precision();
    char oldFill = cout.fill();

    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(2);
    cout.fill('.');

    cout << left << setw(15) << "Наименование"
        << right << setw(10) << "Цена"
        << right << setw(12) << "Количество" << endl;
    cout << setfill('-') << setw(37) << "" << setfill('.') << endl;

    for (int i = 0; i < 3; ++i) {
        cout << left << setw(15) << items[i].name
            << right << setw(10) << items[i].price
            << right << setw(12) << items[i].qty << endl;
    }

    cout.flags(oldFlags);
    cout.precision(oldPrec);
    cout.fill(oldFill);
}

// -----------------------------------------------------------------
// Главная функция с меню
// -----------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        cout << "\n========================================";
        cout << "\nЛабораторная работа 8\n";
        cout << "1. Класс Stroka с операторами << и >>\n";
        cout << "2. Форматирование вывода (стр. 22)\n";
        cout << "3. Состояние потока (стр. 23)\n";
        cout << "4. Манипуляторы (стр. 24)\n";
        cout << "5. Программа-шифратор (файловые потоки)\n";
        cout << "6. Изменение состояния потоков\n";
        cout << "7. Собственная программа (таблица)\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\n--- Демонстрация Stroka ---\n";
            Stroka s1("Привет");
            Stroka s2;
            cout << "Введите строку: ";
            cin >> s2;
            cout << "s1 = " << s1 << ", длина = " << s1.dllina() << endl;
            cout << "s2 = " << s2 << ", длина = " << s2.dllina() << endl;
            Stroka s3 = s1 + s2;
            cout << "s1 + s2 = " << s3 << endl;
            break;
        }
        case 2: demoFormatting(); break;
        case 3: demoStreamState(); break;
        case 4: demoManipulators(); break;
        case 5: cipherProgram(); break;
        case 6: demoStreamFlags(); break;
        case 7: myTableDemo(); break;
        case 0: cout << "Выход.\n"; break;
        default: cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}