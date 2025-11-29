#include <sort_strategy.h>

int main()
{
    std::vector<int> data = {5, 6, 1, 45, 678, 93, 123, 22, 1, 4, 11};

    SortContext<int> context;

    auto * strategy = new QuickSort<int>; 

    context.set_strategy(strategy);

    context.sort(data, [](const int& a, const int& b) { return a < b; });

    for (const auto& value : data) 
    {
        std::cout << value << " ";
    }

    delete strategy;

    return 0;
}