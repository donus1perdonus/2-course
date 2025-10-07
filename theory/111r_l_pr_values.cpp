#include <iostream>
#include <utility>

class MyClass {
public:
    int* data;

    // Конструктор
    MyClass(int value) : data(new int(value)) {}

    // Деструктор
    ~MyClass() {
        delete data;
    }

    // Конструктор копирования
    MyClass(const MyClass& other) : data(new int(*other.data)) {}

    // Оператор присваивания копированием
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    // Конструктор перемещения
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    // Оператор присваивания перемещением
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};



// Пример rvalue
int getValue() {
    return 42; // Возвращаемое значение является rvalue
}



// Шаблонная функция, которая принимает универсальную ссылку
template <typename T>
void print(T&& value) {
    std::cout << "Value: " << value << std::endl;
}

// Функция, которая передает аргумент в print с сохранением категории значения
template <typename T>
void forwardToPrint(T&& value) {
    print(std::forward<T>(value));
}



int main() {
    MyClass obj1(10);
    MyClass obj2 = std::move(obj1); // Перемещение
    MyClass obj3(20);
    obj3 = std::move(obj2); // Перемещение

    std::cout << "obj3.data: " << *obj3.data << std::endl;



    int x = 10; // 10 является prvalue
    int y = getValue(); // getValue() возвращает rvalue

    std::cout << "x: " << x << ", y: " << y << std::endl;



    int z = 10;
    forwardToPrint(z); // x является lvalue
    forwardToPrint(20); // 20 является rvalue

    return 0;
}
