from scipy.optimize import linprog
import numpy as np

def task1():
    # Коэффициенты целевой функции
    c = [1.5, 2, 1]  # Минимизировать: 1.5x + 2y + 1z

    # Ограничения (неравенства в виде Ax >= b)
    A = [
        [-12, -8, -3],   # - (12x + 8y + 3z) <= -60
        [-9, -10, -2],   # - (9x + 10y + 2z) <= -50
        [0, -15, -10]    # - (15y + 10z) <= -200 (в данном случае z)
    ]

    b = [-60, -50, -200]

    # Ограничения на неотрицательность
    x0_bounds = (0, None)  # x >= 0
    x1_bounds = (0, None)  # y >= 0
    x2_bounds = (0, None)  # z >= 0

    # Решение задачи линейного программирования
    res = linprog(c, A_ub=A, b_ub=b, bounds=[x0_bounds, x1_bounds, x2_bounds], method='highs')

    # Вывод результатов
    if res.success:
        print("Оптимальное решение найдено:")
        print(f"Количество яиц (x): {res.x[0]:.2f}")
        print(f"Количество молока (y): {res.x[1]:.2f}")
        print(f"Количество хлеба (z): {res.x[2]:.2f}")
        print(f"Минимальные затраты: {res.fun:.2f} долларов")
    else:
        print("Решение не найдено.")


def task2():
    # Коэффициенты целевой функции (прибыли)
    c = [-10, -15]  # Мы минимизируем -z, чтобы максимизировать z

    # Ограничения
    A = [
        [2, 1],  # 2x + y <= 40
        [1, 2]   # x + 2y <= 30
    ]
    b = [40, 30]  # Правая часть ограничений

    # Ограничения на неотрицательность
    x_bounds = (0, None)  # x >= 0
    y_bounds = (0, None)  # y >= 0

    # Решение задачи
    result = linprog(c, A_ub=A, b_ub=b, bounds=[x_bounds, y_bounds], method='highs')

    # Вывод результатов
    if result.success:
        print(f"Оптимальное количество продукта A (x): {result.x[0]}")
        print(f"Оптимальное количество продукта B (y): {result.x[1]}")
        print(f"Максимальная прибыль: {-result.fun}")
    else:
        print("Не удалось найти оптимальное решение.")


def task3():

    # Ввод целевой функции
    print("Введите коэффициенты целевой функции (например, для 10x + 15y введите '10 15'):")
    c = list(map(float, input().split()))
    
    # Ввод ограничений
    print("Введите количество ограничений:")
    m = int(input())
    
    A = []
    b = []
    
    for i in range(m):
        print(f"Введите коэффициенты для ограничения {i + 1} (например, для 2x + y <= 40 введите '2 1'):")
        A.append(list(map(float, input().split())))
        print(f"Введите правую часть для ограничения {i + 1}:")
        b.append(float(input()))
    
    # Преобразуем A и b в numpy массивы
    A = np.array(A)
    b = np.array(b)
    
    # Ограничения на неотрицательность
    x_bounds = [(0, None) for _ in range(len(c))]  # x >= 0 для всех переменных

    # Решение задачи
    result = linprog(c, A_ub=A, b_ub=b, bounds=x_bounds, method='highs')

    # Вывод результатов
    if result.success:
        print("Оптимальное решение найдено:")
        for i, val in enumerate(result.x):
            print(f"x[{i}] = {val}")
        print(f"Максимальная (или минимальная) цель: {-result.fun}")
    else:
        print("Не удалось найти оптимальное решение.")


if __name__ == '__main__':
    # task1()
    task2()
    task3()