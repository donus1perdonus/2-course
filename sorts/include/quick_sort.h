#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <sort.h>

template <typename T>
class QuickSort :
    public Sort<T>
{

public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override 
    {
        quickSort(data, 0, data.size() - 1, comparator);
    }

private:

    void quickSort(std::vector<T>& data, int low, int high, std::function<bool(const T&, const T&)> comparator) 
    {
        if (low < high) {
            int pi = partition(data, low, high, comparator);
            quickSort(data, low, pi - 1, comparator);  // Рекурсивно сортируем элементы до и после разделителя
            quickSort(data, pi + 1, high, comparator);
        }
    }

    int partition(std::vector<T>& data, int low, int high, std::function<bool(const T&, const T&)> comparator) {
        T pivot = data[high]; // Выбираем последний элемент в качестве опорного
        int i = (low - 1); // Индекс меньшего элемента

        for (int j = low; j < high; j++) {
            // Если текущий элемент меньше или равен опорному
            if (comparator(data[j], pivot)) {
                i++; // Увеличиваем индекс меньшего элемента
                std::swap(data[i], data[j]); // Меняем местами
            }
        }
        std::swap(data[i + 1], data[high]); // Меняем опорный элемент с элементом на позиции i + 1
        return (i + 1);
    }

};

#endif //QUICK_SORT_H