import numpy as np

def get_neighbors_indices(array, row, col):
    rows, cols = array.shape
    
    neighbors = []
    
    for i in range(row - 1, row + 2):
        for j in range(col - 1, col + 2):
            if (i != row or j != col) and 0 <= i < rows and 0 <= j < cols:
                neighbors.append((i, j))
    
    return neighbors
def task1():
    array = np.array([[1, 2, 3],
                    [4, 5, 6],
                    [7, 8, 9]])

    row, col = 1, 1  # Индексы элемента 5
    neighbors = get_neighbors_indices(array, row, col)

    print("Индексы соседних элементов:", neighbors)


def find_nearest(array, value):
    idx = (np.abs(array - value)).argmin()
    return array[idx]
def task2():
    np.random.seed(42)  # Для воспроизводимости результата
    A = np.random.randint(0, 100, 10)  # Массив A из 10 случайных чисел от 0 до 100
    B = np.random.randint(0, 100, 10)  # Массив B из 10 случайных чисел от 0 до 100

    C = np.array([a + find_nearest(B, a) for a in A])

    print("Массив A:", A)
    print("Массив B:", B)
    print("Массив C:", C)


def task3():
    sales = np.array([
        [120, 340, 560, 230],  # Январь
        [150, 400, 600, 280],  # Февраль
        [180, 390, 630, 310],  # Март
        [170, 420, 670, 290],  # Апрель
        [200, 450, 710, 330],  # Май
        [220, 470, 750, 350],  # Июнь
    ])

    total_sales = np.sum(sales)
    print("1. Общий объем продаж за 6 месяцев:", total_sales)

    monthly_sales = np.sum(sales, axis=1)  # Сумма продаж по каждому месяцу
    best_month_index = np.argmax(monthly_sales)  # Индекс месяца с наибольшими продажами
    best_month = ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь"][best_month_index]
    print("2. Месяц с наибольшими продажами:", best_month)

    category_sales = np.sum(sales, axis=0)  # Сумма продаж по каждой категории
    best_category_index = np.argmax(category_sales)  # Индекс категории с наибольшими продажами
    best_category = ["Электроника", "Одежда", "Бытовая техника", "Мебель"][best_category_index]
    print("3. Категория с наибольшими продажами:", best_category)

    average_sales_per_category = np.mean(sales, axis=0)
    print("4. Средние объемы продаж по категориям:")
    for i, category in enumerate(["Электроника", "Одежда", "Бытовая техника", "Мебель"]):
        print(f"   {category}: {average_sales_per_category[i]:.2f}")

    january_sales = sales[0]  # Продажи в январе
    june_sales = sales[-1]    # Продажи в июне
    growth_percentage = ((june_sales - january_sales) / january_sales) * 100
    print("5. Рост продаж в июне по сравнению с январем (в процентах):")
    for i, category in enumerate(["Электроника", "Одежда", "Бытовая техника", "Мебель"]):
        print(f"   {category}: {growth_percentage[i]:.2f}%")


def task4():
    np.random.seed(42)  # Для воспроизводимости результата
    sales = np.random.randint(500, 1500, (3, 12))  # Данные о продажах (3 года, 12 месяцев)
    print("Данные о продажах:\n", sales)

    average_sales_per_year = np.mean(sales, axis=1)
    print("\n1. Средние продажи за каждый год:")
    for i, year in enumerate([2022, 2023, 2024]):
        print(f"   {year}: {average_sales_per_year[i]:.2f}")

    average_sales_per_month = np.mean(sales, axis=0)
    sales_diff = sales - average_sales_per_month
    max_diff_index = np.unravel_index(np.argmax(sales_diff), sales_diff.shape)
    year_with_max_diff = [2022, 2023, 2024][max_diff_index[0]]
    month_with_max_diff = ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", 
                        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"][max_diff_index[1]]
    print("\n2. Месяц с самым большим приростом продаж:")
    print(f"   Год: {year_with_max_diff}, Месяц: {month_with_max_diff}, Прирост: {sales_diff[max_diff_index]:.2f}")

    years = np.array([2022, 2023, 2024])
    months = np.arange(1, 13)  # Номера месяцев (1–12)
    X = np.vstack([np.tile(months, len(years)), np.repeat(years, len(months))]).T  # Признаки: месяц и год
    y = sales.flatten()  # Целевые значения: продажи
    X = np.hstack([X, np.ones((X.shape[0], 1))])
    coefficients, _, _, _ = np.linalg.lstsq(X, y, rcond=None)
    next_year = 2025
    predicted_sales = []
    for month in months:
        predicted_sales.append(coefficients[0] * month + coefficients[1] * next_year + coefficients[2])
    print("\n3. Предсказанные продажи на 2025 год:")
    for i, month in enumerate(["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", 
                            "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"]):
        print(f"   {month}: {predicted_sales[i]:.2f}")


def task5():
    np.random.seed(42)  # Для воспроизводимости результата
    temperatures = np.random.randint(-10, 36, size=365)  # Температуры за 365 дней
    print("Температуры за год:\n", temperatures)

    average_temperature = np.mean(temperatures)
    print("\n1. Средняя температура за год:", average_temperature)

    above_average_days = np.where(temperatures > average_temperature)[0]
    below_average_days = np.where(temperatures < average_temperature)[0]
    print("\n2. Дни с температурой выше средней:", above_average_days)
    print("   Дни с температурой ниже средней:", below_average_days)

    hottest_day = np.argmax(temperatures)
    hottest_temp = temperatures[hottest_day]
    coldest_day = np.argmin(temperatures)
    coldest_temp = temperatures[coldest_day]
    print("\n3. Самый жаркий день:")
    print(f"   День: {hottest_day}, Температура: {hottest_temp}°C")
    print("Самый холодный день:")
    print(f"   День: {coldest_day}, Температура: {coldest_temp}°C")

    cold_months = temperatures[temperatures < average_temperature]
    warm_months = temperatures[temperatures > average_temperature]
    normal_months = temperatures[(temperatures >= average_temperature - 5) & (temperatures <= average_temperature + 5)]
    print("\n4. Разделение данных:")
    print(f"   Холодные месяцы (ниже средней): {cold_months}")
    print(f"   Теплые месяцы (выше средней): {warm_months}")
    print(f"   Нормальные месяцы (в пределах ±5°C от средней): {normal_months}")


if __name__ == '__main__':
    task1()
    # task2()
    # task3()
    # task4()
    # task5()