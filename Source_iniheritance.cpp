#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <cstddef>

class DynamicIntArray {
protected:
    int* data;
    size_t size;

public:
    explicit DynamicIntArray(size_t initialSize = 0) : size(initialSize) {
        if (size == 0) {
            data = nullptr;
        }
        else {
            data = new int[size](); // инициализация нулями
        }
    }

    ~DynamicIntArray() {
        delete[] data;
    }

    // Конструктор копирования
    DynamicIntArray(const DynamicIntArray& other) : size(other.size) {
        if (size == 0) {
            data = nullptr;
        }
        else {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i != size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    int get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива!");
        }
        return data[index];
    }

    void set(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива!");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100]!");
        }
        data[index] = value;
    }

    size_t getSize() const {
        return size;
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100]!");
        }

        int* newData = new int[size + 1];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = value;
        delete[] data;
        data = newData;
        ++size;
    }

    void add(const DynamicIntArray& other) {
        for (size_t i = 0; i < size; ++i) {
            int otherValue = (i < other.size) ? other.data[i] : 0;
            data[i] += otherValue;
        }
    }

    void subtract(const DynamicIntArray& other) {
        for (size_t i = 0; i < size; ++i) {
            int otherValue = (i < other.size) ? other.data[i] : 0;
            data[i] -= otherValue;
        }
    }
};

// Производный класс с методами статистики
class StatDynamicIntArray : public DynamicIntArray {
public:
    using DynamicIntArray::DynamicIntArray; // Наследуем конструкторы

    double mean() const {
        if (size == 0) {
            throw std::runtime_error("Невозможно вычислить среднее: массив пуст.");
        }
        long long sum = 0;
        for (size_t i = 0; i < size; ++i) {
            sum += data[i];
        }
        return static_cast<double>(sum) / size;
    }

    double median() const {
        if (size == 0) {
            throw std::runtime_error("Невозможно вычислить медиану: массив пуст.");
        }
        std::vector<int> copy(data, data + size);
        std::sort(copy.begin(), copy.end());
        size_t n = size;
        if (n % 2 == 0) {
            return (copy[n / 2 - 1] + copy[n / 2]) / 2.0;
        }
        else {
            return static_cast<double>(copy[n / 2]);
        }
    }

    int minValue() const {
        if (size == 0) {
            throw std::runtime_error("Массив пуст.");
        }
        return *std::min_element(data, data + size);
    }

    int maxValue() const {
        if (size == 0) {
            throw std::runtime_error("Массив пуст.");
        }
        return *std::max_element(data, data + size);
    }
};

// Пример использования
int main() {
    try {
        StatDynamicIntArray arr(4);
        arr.set(0, 10);
        arr.set(1, -20);
        arr.set(2, 30);
        arr.set(3, 0);

        std::cout << "Массив: ";
        arr.print();

        std::cout << "Среднее: " << arr.mean() << std::endl;
        std::cout << "Медиана: " << arr.median() << std::endl;
        std::cout << "Минимум: " << arr.minValue() << std::endl;
        std::cout << "Максимум: " << arr.maxValue() << std::endl;

        // Проверка с чётным количеством
        StatDynamicIntArray arr2;
        arr2.pushBack(4);
        arr2.pushBack(2);
        arr2.pushBack(1);
        arr2.pushBack(3);
        std::cout << "\nВторой массив: ";
        arr2.print();
        std::cout << "Медиана (чётное): " << arr2.median() << std::endl; // 2.5

        // Проверка на пустой массив
        StatDynamicIntArray empty;
        // std::cout << empty.mean(); // выбросит исключение
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}