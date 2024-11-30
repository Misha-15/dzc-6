#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <vector>

class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;

    void ensureCapacity(size_t newCapacity) {
        if (newCapacity > capacity) {
            int* newData = new int[newCapacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

public:
    //конструкторы и деструктор
    Vector() : data(nullptr), size(0), capacity(0) {}

    explicit Vector(size_t initialCapacity) : size(0), capacity(initialCapacity) {
        data = new int[capacity];
    }

    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }

    ~Vector() {
        delete[] data;
    }

    //перегрузка оператора присваивания
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    //вставка элемента
    void Insert(size_t index, int value) {
        if (index > size) throw std::out_of_range("Index out of bounds");
        ensureCapacity(size + 1);
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    //удаление элемента по индексу
    void RemoveAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    //удаление элементов по значению
    void RemoveByValue(int value, bool removeAll = true) {
        size_t i = 0;
        while (i < size) {
            if (data[i] == value) {
                RemoveAt(i);
                if (!removeAll) break;
            }
            else {
                ++i;
            }
        }
    }

    //удаление первого элемента
    void PopFront() {
        RemoveAt(0);
    }

    //удаление последнего элемента
    void PopBack() {
        if (size == 0) throw std::out_of_range("Vector is empty");
        --size;
    }

    //подгонка capacity под size
    void TrimToSize() {
        ensureCapacity(size);
    }

    //поиск первого вхождения
    int IndexOf(int value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    //поиск последнего вхождения
    int LastIndexOf(int value) const {
        for (size_t i = size; i-- > 0; ) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    //реверс массива
    void Reverse() {
        std::reverse(data, data + size);
    }

    // сртировка по возрастанию
    void SortAsc() {
        std::sort(data, data + size);
    }

    //сортировка по убыванию
    void SortDesc() {
        std::sort(data, data + size, std::greater<int>());
    }

    //перемешивание
    void Shuffle() {
        std::srand(std::time(nullptr));
        std::random_shuffle(data, data + size);
    }

    //заполнение случайными числами
    void RandomFill(size_t count, int minVal, int maxVal) {
        ensureCapacity(size + count);
        for (size_t i = 0; i < count; ++i) {
            data[size++] = minVal + std::rand() % (maxVal - minVal + 1);
        }
    }

    //сравнение массивов
    bool Equals(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    //получение элемента по индексу
    int GetElementAt(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    //клонирование массива
    Vector Clone() const {
        return Vector(*this);
    }

    //перегрузка оператора 
    int& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    //перегрузка оператора 
    bool operator==(const Vector& other) const {
        return Equals(other);
    }

    //перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "[";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i];
            if (i < vec.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        int value;
        while (is >> value) {
            vec.Insert(vec.size, value);
        }
        return is;
    }
};

int main() {
    Vector vec;
    vec.RandomFill(5, 1, 10);
    std::cout << "Initial vector: " << vec << std::"/n";

    vec.Insert(2, 42);
    std::cout << "After Insert: " << vec << std::"/n";

    vec.RemoveAt(3);
    std::cout << "After RemoveAt: " << vec << std::"/n";

    vec.Reverse();
    std::cout << "After Reverse: " << vec << std::"/n";

    vec.SortAsc();
    std::cout << "After SortAsc: " << vec << std::"/n";

    return 0;
}
