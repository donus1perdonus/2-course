import numpy as np
from numpy import polyfit

x = np.array([10, 35, 60, 85, 110, 135])
y = np.array([11.2, 28.8, 43.2, 56.2, 67.8, 79.2])

"""
Линейная функция
"""
# Находим коэффициенты линейной функции
a, b = polyfit(x, y, 1)

"""
Степенная функция
"""
# Линейный ответив логарифмируем y для нахождения степенной зависимости
log_y = np.log(y)
# Находим линейную функцию для логарифмированных данных
beta, log_a = polyfit(x, log_y, 1)
a = np.exp(log_a)  # Возвращение к a

"""
Показательная функция
"""
# Показательная приходит из применения логарифма
log_y = np.log(y)
beta, a = polyfit(x, log_y, 1)
beta = np.exp(beta)  # Возвращение к β

"""
Квадратичная функция
"""
# Находим коэффициенты квадратичной функции
coeffs = np.polyfit(x, y, 2)
a, b, c = coeffs


import matplotlib.pyplot as plt
plt.figure()

# Линейная
plt.subplot(2, 2, 1)
plt.scatter(x, y, color="red", label="Экспериментальные точки")
plt.plot(x, a*x + b, label='Линейная')
plt.title('Линейная функция')
plt.legend()

# Степенная
plt.subplot(2, 2, 2)
plt.scatter(x, y, color="red", label="Экспериментальные точки")
plt.plot(x, beta * (x ** a), label='Степенная')
plt.title('Степенная функция')
plt.legend()

# Показательная
plt.subplot(2, 2, 3)
plt.scatter(x, y, color="red", label="Экспериментальные точки")
plt.plot(x, beta * np.exp(a * x), label='Показательная')
plt.title('Показательная функция')
plt.legend()

# Квадратичная
plt.subplot(2, 2, 4)
plt.scatter(x, y, color="red", label="Экспериментальные точки")
plt.plot(x, coeffs[0]*(x**2) + coeffs[1]*x + coeffs[2], label='Квадратичная')
plt.title('Квадратичная функция')
plt.legend()

plt.tight_layout()
plt.show()



plt.figure()
plt.scatter(x, y, color="red", label="Экспериментальные точки")
plt.plot(x, a*x + b, label='Линейная')
plt.plot(x, beta * (x ** a), label='Степенная')
plt.plot(x, beta * np.exp(a * x), label='Показательная')
plt.plot(x, coeffs[0]*(x**2) + coeffs[1]*x + coeffs[2], label='Квадратичная')
plt.title('Все функции')
plt.legend()
plt.show()



def calculate_s(y_observed, y_predicted):
    return np.sum((y_predicted - y_observed) ** 2)

# Ошибка для каждой функции
s_linear = calculate_s(y, a*x + b)
s_power = calculate_s(y, beta * (x ** a))
s_exponential = calculate_s(y, beta * np.exp(a * x))
s_quadratic = calculate_s(y, coeffs[0]*(x**2) + coeffs[1]*x + coeffs[2])

# Результаты
print(f"S (Линейная): {s_linear}")
print(f"S (Степенная): {s_power}")
print(f"S (Показательная): {s_exponential}")
print(f"S (Квадратичная): {s_quadratic}")