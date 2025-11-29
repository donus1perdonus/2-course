import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

# Функция для вычисления евклидова расстояния
def euclidean_distance(point1, point2):
    return np.sqrt(np.sum((point1 - point2) ** 2))

# Реализация алгоритма KNN
class KNN:
    def __init__(self, k=5):
        self.k = k

    def fit(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X):
        predictions = [self._predict(x) for x in X]
        return np.array(predictions)

    def _predict(self, x):
        # Вычисляем расстояния до всех точек в обучающем наборе
        distances = [euclidean_distance(x, x_train) for x_train in self.X_train]
        # Сортируем расстояния и выбираем k ближайших
        k_indices = np.argsort(distances)[:self.k]
        # Получаем метки классов ближайших соседей
        k_nearest_labels = [self.y_train[i] for i in k_indices]
        # Возвращаем наиболее частую метку
        most_common = Counter(k_nearest_labels).most_common(1)
        return most_common[0][0]

# 1. Сформировать случайные данные для первого класса
# np.random.seed(0)  # Для воспроизводимости
class_1 = np.random.rand(50, 2) + np.array([0, 0])  # Смещение для первого класса

# 2. Сформировать случайные данные для второго класса
class_2 = np.random.rand(50, 2) + np.array([1, 1])  # Смещение для второго класса

scale = 2
# 3. Сформировать случайные тестовые данные
test_data = np.random.rand(10, 2) * scale  # 10 случайных точек

# Объединяем данные классов и метки
X = np.vstack((class_1, class_2))
y = np.array([0] * 50 + [1] * 50)  # Метки классов: 0 для первого класса, 1 для второго

# 4. Методом KNN классифицировать тестовые данные
k = 5
knn = KNN(k=k)
knn.fit(X, y)
predictions = knn.predict(test_data)

# 5. Вывести на первом графике данные первого класса, второго класса и тестовые данные
plt.figure(figsize=(12, 6))

# Данные первого класса
plt.scatter(class_1[:, 0], class_1[:, 1], color='blue', label='Класс 1')
# Данные второго класса
plt.scatter(class_2[:, 0], class_2[:, 1], color='red', label='Класс 2')
# Тестовые данные
plt.scatter(test_data[:, 0], test_data[:, 1], color='green', label='Тестовые данные', marker='x')

plt.title('Данные классов и тестовые данные')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid()
plt.show()

# 6. Вывести на графике результаты алгоритма KNN
plt.figure(figsize=(12, 6))

# Данные первого класса
plt.scatter(class_1[:, 0], class_1[:, 1], color='blue', label='Класс 1')
# Данные второго класса
plt.scatter(class_2[:, 0], class_2[:, 1], color='red', label='Класс 2')

# Отображаем предсказанные классы для тестовых данных
for i, point in enumerate(test_data):
    plt.scatter(point[0], point[1], color='green' if predictions[i] == 0 else 'orange', marker='x')
    plt.text(point[0], point[1], f'Pred: {predictions[i]}', fontsize=9, ha='right')

plt.title('Результаты классификации KNN')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid()
plt.show()