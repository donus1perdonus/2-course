#include <iostream>
#include <time.h>

void QuickSort(int a[], int left, int right)
{
    if (left > right) return;

    int p = a[(left + right) / 2], i = left, j = right;

    while (i <= j)
    {
        while (a[i] < p) i++;
        while (a[j] > p) j--;

        if (i <= j)
        {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }
    
    QuickSort(a, left, j);
    QuickSort(a, i, right);
}

int main()
{
    srand(time(0));
    const int N = 10;
    int a[N];
    std::cout << "Исходный массив: " << std::endl;
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 16;
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    QuickSort(a, 0, N - 1);

    std::cout << "Отсортированный массив: " << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}