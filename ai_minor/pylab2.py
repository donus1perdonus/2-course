"""
Напишите программу, которая запрашивает у пользователя список элементов и 
выводит список уникальных элементов (без повторений).
"""
def task1() -> None:
    user_input = input("Введите элементы, разделенные запятыми: ")
    
    elements = [element.strip() for element in user_input.split(',')]
    
    unique_elements = list(set(elements))
    
    print("Список уникальных элементов:", unique_elements)


"""
Напишите программу, которая запрашивает у пользователя список чисел через 
пробел и выводит количество четных и нечетных чисел в этом списке.
"""
def task2() -> None:
    user_input = input("Введите числа через пробел: ")
    
    numbers = list(map(int, user_input.split()))
    
    even_count = 0
    odd_count = 0
    
    for number in numbers:
        if number % 2 == 0:
            even_count += 1
        else:
            odd_count += 1
    
    print("Количество четных чисел:", even_count)
    print("Количество нечетных чисел:", odd_count)


"""
Напишите программу, которая запрашивает у пользователя список элементов и 
выводит наиболее часто встречающийся элемент. 
"""
def task3() -> None:
    user_input = input("Введите элементы, разделенные запятыми: ")
    
    elements = [element.strip() for element in user_input.split(',')]
    
    element_counts = {}
    
    for element in elements:
        if element in element_counts:
            element_counts[element] += 1
        else:
            element_counts[element] = 1
    
    most_common_element = None
    most_common_count = 0
    
    for element, count in element_counts.items():
        if count > most_common_count:
            most_common_count = count
            most_common_element = element
    
    if most_common_element is not None:
        print(f"Наиболее часто встречающийся элемент: '{most_common_element}' (встречается {most_common_count} раз)")
    else:
        print("Список пуст.")


"""
Напишите программу, которая запрашивает у пользователя два списка и выводит 
список элементов, которые встречаются в обоих списках. 
"""
def task4() -> None:
    first_input = input("Введите элементы первого списка, разделенные запятыми: ")
    first_list = [element.strip() for element in first_input.split(',')]
    
    second_input = input("Введите элементы второго списка, разделенные запятыми: ")
    second_list = [element.strip() for element in second_input.split(',')]
    
    common = list(set(first_list) & set(second_list))
    
    print("Элементы, которые встречаются в обоих списках:", common)


"""
Напишите программу, которая запрашивает у пользователя список элементов и 
удаляет из него все дубликаты, оставляя только уникальные элементы. 
"""
def task5() -> None:
    user_input = input("Введите элементы, разделенные запятыми: ")
    
    elements = [element.strip() for element in user_input.split(',')]
    
    unique_elements = list(set(elements))
    
    print("Список уникальных элементов:", unique_elements)


"""
Напишите программу, которая запрашивает у пользователя список слов и 
выводит только те слова, которые являются палиндромами (читаются одинаково 
как слева направо, так и справа налево). 
"""
def task6() -> None:
    user_input = input("Введите слова через пробел: ")
    
    words = user_input.split()
    
    palindromes = [word for word in words if word == word[::-1]]
    
    print("Палиндромы:", palindromes)


"""
Напишите программу, которая запрашивает у пользователя список кортежей 
(каждый кортеж состоит из двух элементов), затем сортирует список по второму 
элементу в каждом кортеже и выводит отсортированный список. 
"""
def task7() -> None:
    user_input = input("Введите кортежи в формате (a, b), разделенные запятыми: ")
    
    tuples_list = []
    # Убираем пробелы и разбиваем по запятой
    items = user_input.split('),')
    
    for item in items:
        item = item.strip().strip('()')
        if item:  # Проверяем, что строка не пустая
            parts = item.split(',')
            if len(parts) == 2:
                try:
                    a = int(parts[0].strip())
                    b = int(parts[1].strip())
                    tuples_list.append((a, b))
                except ValueError:
                    print(f"Ошибка преобразования: '{item}' не является корректным кортежем.")
            else:
                print(f"Ошибка: '{item}' не является корректным кортежем (должен содержать 2 значения).")

    # Сортируем кортежи по второму элементу
    sorted_tuples = sorted(tuples_list, key=lambda x: x[1])
    
    print("Отсортированный список кортежей:", sorted_tuples)


"""
Напишите программу, которая объединяет несколько словарей в один. 
Количество словарей и их содержимое запрашивается у пользователя. 
"""
def task8() -> None:
    # Запрашиваем у пользователя количество словарей
    num_dicts = int(input("Введите количество словарей, которые вы хотите объединить: "))
    
    merged_dict = {}
    
    for i in range(num_dicts):
        # Запрашиваем у пользователя ввод словаря в формате ключ: значение
        user_input = input(f"Введите элементы словаря {i + 1} в формате 'ключ: значение', разделенные запятыми: ")
        
        # Преобразуем ввод в словарь
        current_dict = {}
        for item in user_input.split(','):
            key, value = item.split(':')
            current_dict[key.strip()] = value.strip()
        
        # Объединяем текущий словарь с общим
        merged_dict.update(current_dict)
    
    # Выводим объединенный словарь
    print("Объединенный словарь:", merged_dict)


"""
Напишите программу, которая запрашивает у пользователя текст и выводит 
словарь, в котором ключами являются слова из текста, а значениями - количество 
их вхождений. 
"""
def task9() -> None:
    # Запрашиваем у пользователя ввод текста
    user_input = input("Введите текст: ")
    
    # Приводим текст к нижнему регистру и разбиваем его на слова
    words = user_input.lower().split()
    
    # Инициализируем пустой словарь для подсчета вхождений
    word_count = {}
    
    # Подсчитываем количество вхождений каждого слова
    for word in words:
        if word in word_count:
            word_count[word] += 1
        else:
            word_count[word] = 1
    
    # Выводим результат
    print("Словарь с количеством вхождений слов:", word_count)


if __name__ == '__main__':
    # task1()
    # task2()
    task3()
    # task4()
    # task5()
    # task6()
    # task7()
    # task8()
    # task9()