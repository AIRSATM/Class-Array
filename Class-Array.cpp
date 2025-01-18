#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

class Array
{
    int *arr;      // Указатель на динамический массив
    int length;    // Длина массива

public:
    // Конструктор 1
    // len – число элементов в массиве
    // mode = 1 – неупорядоченный массив
    // mode = 2 – массив, упорядоченный по возрастанию
    // mode = 3 – массив, упорядоченный по убыванию
    // range – случайные числа (при mode = 1)
    Array(int len = 1, int mode = 1, int range = 10)
    {
        length = len;
        arr = new int[length];

        if (mode == 1)
        {
            // NoSort массив
            for (int i = 0; i < length; i++)
                arr[i] = rand() % range;
        }
        else
        {
            // Заполнение массива случайными числами
            for (int i = 0; i < length; ++i)
                arr[i] = rand() % range;
            // Sort в зависимости от режима
            if (mode == 2)
                sort(arr, arr + length); // Возрастающая
            else if (mode == 3)
                sort(arr, arr + length, greater<int>()); // Убывающая
        }
    }

    // Конструктор 2: создание массива из существующего массива
    Array(int *inputArr, int len)
    {
        length = len;
        arr = new int[length];
        for (int i = 0; i < length; ++i)
            arr[i] = inputArr[i];
    }

    // Конструктор копирования
    Array(const Array &other)
    {
        length = other.length;
        arr = new int[length];
        for (int i = 0; i < length; ++i)
            arr[i] = other.arr[i];
    }

    // Деструктор
    ~Array()
    {
        delete[] arr;
    }

    // Оператор присваивания
    Array& operator=(const Array &other)
    {
        if (this == &other)
            return *this; // Самоприсваивание
        delete[] arr; // Очистка существующего массива
        length = other.length;
        arr = new int[length];
        for (int i = 0; i < length; ++i)
            arr[i] = other.arr[i];
        return *this;
    }

    // Оператор индексирования []
    int& operator[](int i)
    {
        if (i < 0 || i >= length)
        {
            cout << "Индекс вне границ массива!" << endl;
            exit(1);
        }
        return arr[i];
    }

    // Проверка на упорядоченность по неубыванию
    bool isSorted()
    {
        for (int i = 1; i < length; ++i)
            if (arr[i] < arr[i - 1])
                return false;
        return true;
    }

    // Оператор равенства
    bool operator==(const Array &other)
    {
        if (length != other.length)
            return false;
        // Используем unordered_map для подсчёта элементов
        unordered_map<int, int> countMap;
        for (int i = 0; i < length; ++i)
            countMap[arr[i]]++;
        for (int i = 0; i < other.length; i++)
        {
            if (countMap.find(other.arr[i]) == countMap.end())
                return false;
            countMap[other.arr[i]]--;
            if (countMap[other.arr[i]] < 0)
                return false;
        }
        return true;
    }

    // Перегрузка оператора ввода >>
    friend istream& operator>>(istream &in, Array &a)
    {
        cout << "Enter " << a.length << " numbers arr:\n";
        for(int i = 0; i < a.length; i++)
            in >> a.arr[i];
        return in;
    }

    // Перегрузка оператора вывода <<
    friend ostream& operator<<(ostream &out, const Array &a)
    {
        for(int i = 0; i < a.length; i++)
            out << a.arr[i] << " ";
        return out;
    }

    // Геттер для получения длины массива
    int getLength() const
    {
        return length;
    }
};

// Главная функция для демонстрации использования класса Array
int main()
{
    srand(time(0));
    // Создание неупорядоченного массива с 10 элементами, диапазон 100
    Array a1(10, 1, 100);
    cout << "NoSort массив a1: " << a1 << endl;

    // Создание массива, Sort по возрастанию
    Array a2(10, 2, 100);
    cout << "Sort массив a2 (по возрастанию): " << a2 << endl;

    // Создание массива, Sort по убыванию
    Array a3(10, 3, 100);
    cout << "Sort массив a3 (по убыванию): " << a3 << endl;

    // Конструктор копирования
    Array a4 = a1;
    cout << "Копия a1 (a4): " << a4 << endl;

    // Оператор =
    Array a5;
    a5 = a2;
    cout << "a2 = a5: " << a5 << endl;

    // оператор[]
    cout << "a1[3] = " << a1[3] << endl;
    a1[3] = 500;
    cout << "a1 после установки a1[3] = 500: " << a1 << endl;

    // Проверка на isSorted
    cout << "a1 отсортирован? " << (a1.isSorted() ? "Да" : "Нет") << endl;
    cout << "a2 отсортирован? " << (a2.isSorted() ? "Да" : "Нет") << endl;

    // оператор >>
    Array a6(5);
    cin >> a6;
    cout << "Введённый массив a6: " << a6 << endl;

    // Проверка оператора ==
    Array a7 = a1;
    cout << "a7 (копия a1): " << a7 << endl;
    cout << "a1 == a7? " << (a1 == a7 ? "Да" : "Нет") << endl;
    cout << "a1 == a2? " << (a1 == a2 ? "Да" : "Нет") << endl;

    return 0;
}
