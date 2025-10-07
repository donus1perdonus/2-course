#include <iostream>

template <typename T>
class MyIterator {
public:
    MyIterator(T* ptr) : ptr_(ptr) {}

    // Префиксный инкремент
    MyIterator& operator++() {
        ++ptr_; // Увеличиваем указатель на следующий элемент
        return *this; // Возвращаем ссылку на текущий объект
    }

    // Постфиксный инкремент
    MyIterator operator++(int) {
        MyIterator temp = *this; // Сохраняем текущее состояние
        ++ptr_; // Увеличиваем указатель на следующий элемент
        return temp; // Возвращаем старое состояние
    }

    // Оператор разыменования
    T& operator*() {
        return *ptr_;
    }

    // Оператор сравнения
    bool operator!=(const MyIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    T* ptr_; // Указатель на текущий элемент
};

template <typename T>
class IndexIterator {
public:
    IndexIterator(T* ptr) : ptr_(ptr) {}

    // Оператор индексирования
    T& operator[](size_t index) {
        return ptr_[index];
    }

private:
    T* ptr_; // Указатель на массив
};

template <typename T>
class MyContainer {
public:
    MyContainer(T* data, size_t size) : data_(data), size_(size) {}

    MyIterator<T> begin() {
        return MyIterator<T>(data_);
    }

    MyIterator<T> end() {
        return MyIterator<T>(data_ + size_);
    }

    IndexIterator<T> index_begin() {
        return IndexIterator<T>(data_);
    }

    IndexIterator<T> index_end() {
        return IndexIterator<T>(data_ + size_);
    }

private:
    T* data_;
    size_t size_;
};

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    MyContainer<int> container(arr, 5);

    // Используем обычный итератор
    for (MyIterator<int> it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " "; // Вывод: 1 2 3 4 5
    }
    std::cout << std::endl;

    // Используем индексный итератор
    IndexIterator<int> indexIt = container.index_begin();
    for (size_t i = 0; i < 5; ++i) {
        std::cout << indexIt[i] << " "; // Вывод: 1 2 3 4 5
    }
    std::cout << std::endl;

    return 0;
}