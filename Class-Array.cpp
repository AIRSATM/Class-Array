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
        // 1. Если размеры массивов не совпадают, они точно не равны
        if (length != other.length)
            return false;
    
        // 2. Создаём копию массивов, чтобы не изменять оригинальные данные
        Array temp1 = *this;
        Array temp2 = other;
    
        // 3. Сортируем оба массива
        sort(temp1.arr, temp1.arr + temp1.length);
        sort(temp2.arr, temp2.arr + temp2.length);
    
        // 4. Сравниваем отсортированные массивы поэлементно
        for (int i = 0; i < length; ++i)
        {
            if (temp1.arr[i] != temp2.arr[i])
                return false;
        }
        // 5. Если все элементы совпали, возвращаем true
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

    // Сортировка Шелла
    void ShellSort(){
        for(gap = length/2; gap > 0; gap/2){ //Берем шаг массива
            for(i = gap; i < length; i++){
                int temp = arr[i];
                int j = i;
                while(j >= gap && arr[j - gap] > temp){
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }
    void heapify(int *arr, int n, int i){
        int base = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        if (left < n && arr[left] > arr[base])
            base = left;
        if (right < n && arr[right] > arr[base])
            base = right;
        if (base != i){
            swap(arr[i],arr[base]);
            heapify(arr,n,base);
        }
    }
    void HeapSort(){
        for(int i = length/2 - 1; i >= 0; i--)
            heapify(arr,length,i);
        for(int i = length - 1; i >= 0; i--){
            swap(arr[0],swap[i]);
            heapify(arr,i,0);
        }
    }
    void HoarSort(){
        quickSort(0,n-1);
    }
    void quickSort(int low, int high){
        if (low < high){
            int pivot = arr[(low + high)/2];
            int i = low, j = high;
            while(i <= j){
                if(arr[i]<pivot) i++;
                if(arr[j]>pivot) j--;
                if(i <= j){
                    swap(arr[i],arr[j]);
                    i++;
                    j--;
                }
                quickSort(low,j);
                quickSort(i,high);
            }
        }
    }
    void BitSort(){
        for(int bit = 0; bit < 32; bit++){
            int* temp = new int[length];
            int index0 = 0;
            for(int i=0;i < length;i++)
                if (((arr[i] >> bit)&1) == 0) temp[index0++] = arr[i];
            for(int i=0;i < length;i++)
                if (((arr[i] >> bit)&1) == 1) temp[index0++] = arr[i];
            for(int i=0;i < length;i++){
                arr[i] = temp[i];
            }
            delete[] temp;
        }
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

    cout << "\nТест сортировок на a1:\n";
    cout << "a1 (перед сортировками): " << a1 << endl;
    
    // Shellsort
    a1.ShellSort();
    cout << "a1 после Shell_sort: " << a1 << endl;

    // Снова сделаем a1 неупорядоченным для демонстрации других сортировок
    a1 = Array(10, 1, 100);
    cout << "a1 (снова случайный): " << a1 << endl;

    // Heapsort
    a1.HeapSort();
    cout << "a1 после Heapsort: " << a1 << endl;

    // Снова делаем a1 неупорядоченным
    a1 = Array(10, 1, 100);
    cout << "a1 (снова случайный): " << a1 << endl;

    // Быстрая сортировка
    a1.HoarSort();
    cout << "a1 после Hoar_sort: " << a1 << endl;

    // Снова делаем a1 неупорядоченным
    a1 = Array(10, 1, 100);
    cout << "a1 (снова случайный): " << a1 << endl;

    // Bitsort
    a1.BitSort();
    cout << "a1 после Bit_sort: " << a1 << endl;
    return 0;
}
