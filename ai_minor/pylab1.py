import random

"""
Напиши программу, которая принимает на вход время начала и время окончания 
какого-либо события и выводит продолжительность этого события в часах и 
минутах
"""
def task1() -> None:
    start_time = input("Введите время начала (HH:MM): ")
    end_time = input("Введите время окончания (HH:MM): ")

    # Разбиваем время на часы и минуты
    start_hours, start_minutes = map(int, start_time.split(':'))
    end_hours, end_minutes = map(int, end_time.split(':'))

    start_total_minutes = start_hours * 60 + start_minutes
    end_total_minutes = end_hours * 60 + end_minutes

    # Если время окончания меньше времени начала, добавляем 24 часа (1440 минут)
    if end_total_minutes < start_total_minutes:
        end_total_minutes += 1440  # 24 * 60

    duration_minutes = end_total_minutes - start_total_minutes

    hours = duration_minutes // 60
    minutes = duration_minutes % 60

    print(f"Продолжительность события: {hours} часов и {minutes} минут.")


"""
Напиши программу, которая запрашивает у пользователя два числа и операцию 
(сложение, вычитание, умножение или деление), а затем выводит результат. 
Запрашивает до тех пор, пока не будет введено слово Stop. 
"""
def task2() -> None:
    while True:
        operation = input("Введите операцию (+, -, *, /) или 'Stop' для выхода: ").strip().lower()
        
        if operation == 'stop':
            print("Выход из программы.")
            break
        
        try:
            num1 = float(input("Введите первое число: "))
            num2 = float(input("Введите второе число: "))
        except ValueError:
            print("Пожалуйста, введите корректные числа.")
            continue

        if operation == '+':
            result = num1 + num2
            print(f"Результат: {result}")
        elif operation == '-':
            result = num1 - num2
            print(f"Результат: {result}")
        elif operation == '*':
            result = num1 * num2
            print(f"Результат: {result}")
        elif operation == '/':
            if num2 == 0:
                print("Ошибка: деление на ноль.")
            else:
                result = num1 / num2
                print(f"Результат: {result}")
        else:
            print("Неизвестная операция. Пожалуйста, выберите одну из следующих: сложение, вычитание, умножение, деление.")


"""
Напиши программу, которая запрашивает у пользователя число и выводит 
сообщение о том, является ли оно четным или нечетным. Запрашивает до тех 
пор, пока не будет введено слово Stop.
"""
def task3() -> None:
    while True:
        user_input = input("Введите число (или 'Stop' для выхода): ").strip()
        
        if user_input.lower() == 'stop':
            print("Выход из программы.")
            break
        
        try:
            number = int(user_input)
        except ValueError:
            print("Пожалуйста, введите корректное целое число.")
            continue

        if number % 2 == 0:
            print(f"{number} является четным числом.")
        else:
            print(f"{number} является нечетным числом.")


def is_prime(n: int) -> bool:
    """Проверяет, является ли число простым."""
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True


"""
Напиши программу, которая запрашивает у пользователя целые числа в цикле, 
пока пользователь не введет слово Stop. После этого программа выводит сумму 
введенных чисел.
"""
def task4() -> None:
    total_sum = 0 

    while True:
        user_input = input("Введите целое число (или 'Stop' для выхода): ").strip()
        
        if user_input.lower() == 'stop':
            break 
        
        try:
            number = int(user_input)
            total_sum += number
        except ValueError:
            print("Пожалуйста, введите корректное целое число.")
    
    print(f"Сумма введенных чисел: {total_sum}")


def factorial(n: int):
    """Вычисляет факториал числа n."""
    if n < 0:
        return None
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result


"""
Напиши программу, которая запрашивает у пользователя число и проверяет, 
является ли оно простым (не имеет делителей кроме 1 и самого себя). 
Запрашивает до тех пор, пока не будет введено слово Stop. 
"""
def task5() -> None:
    while True:
        user_input = input("Введите число (или 'Stop' для выхода): ").strip()
        
        if user_input.lower() == 'stop':
            print("Выход из программы.")
            break
        
        try:
            number = int(user_input)
        except ValueError:
            print("Пожалуйста, введите корректное целое число.")
            continue

        if is_prime(number):
            print(f"{number} является простым числом.")
        else:
            print(f"{number} не является простым числом.")


"""
Напиши программу, которая запрашивает у пользователя число и выводит его 
факториал. Запрашивает до тех пор, пока не будет введено слово Stop. 
"""
def task6() -> None:
    while True:
        user_input = input("Введите целое число (или 'Stop' для выхода): ").strip()
        
        if user_input.lower() == 'stop':
            print("Выход из программы.")
            break
        
        try:
            number = int(user_input)
        except ValueError:
            print("Пожалуйста, введите корректное целое число.")
            continue

        fact = factorial(number)
        if fact is not None:
            print(f"Факториал числа {number} равен {fact}.")
        else:
            print("Факториал отрицательных чисел не определен.")


"""
Напиши программу, которая генерирует случайное число от 1 до 100, а затем 
предлагает пользователю угадать это число. Программа должна давать подсказки 
("слишком большое" или "слишком маленькое") и завершаться, когда число 
угадано. 
"""
def task7() -> None:
    secret_number = random.randint(1, 100)
    attempts = 0 

    print("Я загадал число от 1 до 100. Попробуйте угадать его!")

    while True:
        user_input = input("Введите ваше предположение (или 'Stop' для выхода): ").strip()

        if user_input.lower() == 'stop':
            print("Выход из игры.")
            break

        try:
            guess = int(user_input)
        except ValueError:
            print("Пожалуйста, введите корректное целое число.")
            continue

        attempts += 1  # Увеличиваем счетчик попыток

        if guess < secret_number:
            print("Слишком маленькое число. Попробуйте еще раз.")
        elif guess > secret_number:
            print("Слишком большое число. Попробуйте еще раз.")
        else:
            print(f"Поздравляю! Вы угадали число {secret_number} за {attempts} попыток.")
            break


"""
Напиши программу, которая запрашивает у пользователя количество исходных 
единиц измерения (например, метры) и преобразует их в другие единицы 
измерения (например, футы, дюймы, ярды). 
"""
def task8() -> None:
    user_input = input("Введите количество метров: ").strip()

    try:
        meters = float(user_input)
    except ValueError:
        print("Пожалуйста, введите корректное число.")
        return

    feet = meters * 3.28084  # 1 метр = 3.28084 фута
    inches = meters * 39.3701  # 1 метр = 39.3701 дюйма
    yards = meters * 1.09361  # 1 метр = 1.09361 ярда

    print(f"{meters} метров равно:")
    print(f"{feet:.2f} футов")
    print(f"{inches:.2f} дюймов")
    print(f"{yards:.2f} ярдов")


"""
Напиши программу, которая запрашивает у пользователя строку, разбивает её на 
слова, а затем находит и выводит самое длинное слово в этой строке. 
"""
def task9() -> None:
    user_input = input("Введите строку: ").strip()

    words = user_input.split()

    if not words:
        print("Вы не ввели ни одного слова.")
        return

    longest_word = max(words, key=len)

    print(f"Самое длинное слово: '{longest_word}' (длина: {len(longest_word)})")


if __name__ == '__main__':
    # task1()
    # task2()
    # task3()
    task4()
    # task5()
    # task6()
    # task7()
    # task8()
    # task9()