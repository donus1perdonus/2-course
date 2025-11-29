#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <sort.h>

template <typename T>
class HeapSort : public Sort<T>
{
public:
    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override
    {
        int n = data.size();

        // Построение кучи (перегруппировка массива)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(data, n, i, comparator);

        // Один за другим извлекаем элементы из кучи
        for (int i = n - 1; i > 0; i--)
        {
            std::swap(data[0], data[i]); // Перемещаем текущий корень в конец
            heapify(data, i, 0, comparator); // Вызываем heapify на уменьшенной куче
        }
    }

private:

    void heapify(std::vector<T>& data, int n, int i, std::function<bool(const T&, const T&)> comparator)
    {
        int largest = i; // Инициализируем корень как наибольший
        int left = 2 * i + 1; // левый = 2*i + 1
        int right = 2 * i + 2; // правый = 2*i + 2

        // Если левый дочерний элемент больше корня
        if (left < n && comparator(data[left], data[largest]))
            largest = left;

        // Если правый дочерний элемент больше, чем наибольший до сих пор
        if (right < n && comparator(data[right], data[largest]))
            largest = right;

        // Если наибольший не корень
        if (largest != i)
        {
            std::swap(data[i], data[largest]); // Меняем местами

            // Рекурсивно heapify затронутое поддерево
            heapify(data, n, largest, comparator);
        }
    }
};

#endif //HEAP_SORT_H