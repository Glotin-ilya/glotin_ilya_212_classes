#include <iostream>

class DynamicIntArray {
private:
    int* data;
    size_t size;

public:

    explicit DynamicIntArray(size_t initialSize = 0) : size(initialSize) {
        if (size == 0) {
            data = nullptr;
        }
        else {
            data = new int[size]();
        }
    }

    
    ~DynamicIntArray() {
        delete[] data; 
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


int main() {
    try {
        
        DynamicIntArray arr1(3);
        arr1.set(0, 10);
        arr1.set(1, -50);
        arr1.set(2, 100);
        std::cout << "arr1: ";
        arr1.print(); // [10, -50, 100]

        
        DynamicIntArray arr2 = arr1;
        std::cout << "arr2 (копия): ";
        arr2.print(); // [10, -50, 100]

        arr1.pushBack(42);
        std::cout << "arr1 после pushBack(42): ";
        arr1.print(); // [10, -50, 100, 42]

        DynamicIntArray arr3(2);
        arr3.set(0, 5);
        arr3.set(1, -10);
        std::cout << "arr3: ";
        arr3.print(); // [5, -10]


        arr1.add(arr3);
        std::cout << "arr1 после add(arr3): ";
        arr1.print(); // [15, -60, 100, 42] последние элементы = 0

        
        arr1.subtract(arr3);
        std::cout << "arr1 после subtract(arr3): ";
        arr1.print(); // [10, -50, 100, 42]

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
