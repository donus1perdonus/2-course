#ifndef SORT_STRATEGY_H
#define SORT_STRATEGY_H

#include <chrono>
#include <iostream>
#include <iomanip>

#include <counting_sort.h>
#include <insertion_sort.h>
#include <selection_sort.h>
#include <Shell_sort.h>
#include <quick_sort.h>
#include <heap_sort.h>
#include <radix_sort.h>

template <typename T>
class SortContext 
{
private:

    Sort<T>* _strategy;

    std::chrono::high_resolution_clock::time_point start_time;

    long long elapsed_time; // Время в миллисекундах

public:

    SortContext()
    {
        _strategy = nullptr;
    }

    void set_strategy(Sort<T>* newStrategy) 
    {
        _strategy = newStrategy;
    }

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) 
    {
        start();

        if (_strategy) 
        {
            _strategy->sort(data, comparator);
        }
        else
        {
            throw std::logic_error("STRATEGY CONTEXT NOT SET!");
        }

        stop();
    }

private:

    void start() 
    {
        start_time = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::system_clock::to_time_t(start_time);
        auto local_time = std::localtime(&now);
        
        // Получаем миллисекунды
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(start_time.time_since_epoch()) % 1000;

        std::cout << "Start time: "
                  << std::setfill('0') << std::setw(2) << local_time->tm_hour << ":"
                  << std::setfill('0') << std::setw(2) << local_time->tm_min << ":"
                  << std::setfill('0') << std::setw(2) << local_time->tm_sec << ":"
                  << std::setfill('0') << std::setw(3) << milliseconds.count() << std::endl;
    }

    void stop() 
    {
        auto end_time = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        auto now = std::chrono::system_clock::to_time_t(end_time);
        auto local_time = std::localtime(&now);
        
        // Получаем миллисекунды
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time.time_since_epoch()) % 1000;

        std::cout << "Stop time: "
                  << std::setfill('0') << std::setw(2) << local_time->tm_hour << ":"
                  << std::setfill('0') << std::setw(2) << local_time->tm_min << ":"
                  << std::setfill('0') << std::setw(2) << local_time->tm_sec << ":"
                  << std::setfill('0') << std::setw(3) << milliseconds.count() << std::endl;

        std::cout << "Elapsed time: " << elapsed_time << " ms" << std::endl;
    }
};

#endif //SORT_STRATEGY_H