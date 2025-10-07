#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint> // Для uint64_t

// Функция для сложения двух больших чисел
std::vector<uint64_t> add(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
    std::vector<uint64_t> result(std::max(a.size(), b.size()) + 1, 0);
    uint64_t carry = 0;
    for (size_t i = 0; i < result.size(); ++i) {
        uint64_t sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];

        // Проверка на переполнение
        if (i < a.size() && sum < a[i]) {
            carry = 1; // Было переполнение
        } else if (i < b.size() && sum < b[i]) {
            carry = 1; // Было переполнение
        } else {
            carry = 0; // Переполнения не было
        }

        result[i] = sum; // Записываем сумму
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

// Функция для вычитания двух больших чисел
std::vector<uint64_t> subtract(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
    std::vector<uint64_t> result(a.size(), 0);
    uint64_t borrow = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        uint64_t diff = a[i] - borrow;
        if (i < b.size()) diff -= b[i];
        borrow = (diff > a[i]) ? 1 : 0;
        result[i] = diff & 0xFFFFFFFFFFFFFFFF; // Оставляем только 64 бита
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

// Функция для умножения двух больших чисел с использованием алгоритма Карацубы
std::vector<uint64_t> karatsuba(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
    size_t n = std::max(a.size(), b.size());
    if (n <= 4) {
        // Базовый случай: используем обычное умножение
        std::vector<uint64_t> result(2 * n, 0);
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < b.size(); ++j) {
                uint64_t product = a[i] * b[j];
                result[i + j] += product & 0xFFFFFFFFFFFFFFFF;
                if (result[i + j] < product) { // Обработка переполнения
                    result[i + j + 1] += 1;
                }
            }
        }
        // Обработка переносов
        for (size_t i = 0; i < result.size() - 1; ++i) {
            if (result[i] >> 63) { // Проверяем старший бит
                result[i + 1] += 1;
                result[i] &= 0x7FFFFFFFFFFFFFFF; // Сбрасываем старший бит
            }
        }
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        return result;
    }

    // Разделяем числа на две части
    size_t half = n / 2;
    std::vector<uint64_t> a_low(a.begin(), a.begin() + std::min(half, a.size()));
    std::vector<uint64_t> a_high(a.begin() + std::min(half, a.size()), a.end());
    std::vector<uint64_t> b_low(b.begin(), b.begin() + std::min(half, b.size()));
    std::vector<uint64_t> b_high(b.begin() + std::min(half, b.size()), b.end());

    // Рекурсивно вычисляем произведения
    std::vector<uint64_t> z0 = karatsuba(a_low, b_low);
    std::vector<uint64_t> z2 = karatsuba(a_high, b_high);
    std::vector<uint64_t> z1 = karatsuba(add(a_low, a_high), add(b_low, b_high));
    z1 = subtract(z1, z0);
    z1 = subtract(z1, z2);

    // Собираем результат
    std::vector<uint64_t> result(2 * n, 0);
    for (size_t i = 0; i < z0.size(); ++i) {
        result[i] += z0[i];
    }
    for (size_t i = 0; i < z1.size(); ++i) {
        result[i + half] += z1[i];
    }
    for (size_t i = 0; i < z2.size(); ++i) {
        result[i + 2 * half] += z2[i];
    }

    // Обработка переносов
    for (size_t i = 0; i < result.size() - 1; ++i) {
        if (result[i] >> 63) { // Проверяем старший бит
            result[i + 1] += 1;
            result[i] &= 0x7FFFFFFFFFFFFFFF; // Сбрасываем старший бит
        }
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

int main() {
    // Пример использования
    std::vector<uint64_t> a = {0x123456789ABCDEF0, 0x123456789ABCDEF0, 0x123456789ABCDEF0, 0x123456789ABCDEF0};
    std::vector<uint64_t> b = {0xFEDCBA9876543210, 0xFEDCBA9876543210, 0xFEDCBA9876543210, 0xFEDCBA9876543210};

    std::vector<uint64_t> result = karatsuba(a, b);

    std::cout << "Result: ";
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        std::cout << std::hex << *it;
    }
    std::cout << std::endl;

    return 0;
}