import random
import matplotlib.pyplot as plt
import math

def generate_points(num_points=100, range_min=0, range_max=100):
    points = [(random.uniform(range_min, range_max), random.uniform(range_min, range_max)) for _ in range(num_points)]
    return points

def initialize_centroids(points, num_clusters):
    return random.sample(points, num_clusters)

def calculate_distance(point1, point2):
    return math.sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)

def assign_clusters(points, centroids):
    labels = []
    for point in points:
        distances = [calculate_distance(point, centroid) for centroid in centroids]
        labels.append(distances.index(min(distances)))
    return labels

def update_centroids(points, labels, num_clusters):
    new_centroids = []
    for k in range(num_clusters):
        cluster_points = [(points[i][0], points[i][1]) for i in range(len(points)) if labels[i] == k]
        if cluster_points:  
            avg_x = sum(point[0] for point in cluster_points) / len(cluster_points)
            avg_y = sum(point[1] for point in cluster_points) / len(cluster_points)
            new_centroids.append((avg_x, avg_y))
        else:
            new_centroids.append(random.choice(points))  
    return new_centroids

def k_means_clustering(points, num_clusters=3, tolerance=1e-4):
    centroids = initialize_centroids(points, num_clusters)
    iteration = 0
    
    while True:
        iteration += 1
        labels = assign_clusters(points, centroids)
        new_centroids = update_centroids(points, labels, num_clusters)
        
        plt.figure(figsize=(8, 6))
        for k in range(num_clusters):
            cluster_points = [points[j] for j in range(len(points)) if labels[j] == k]
            plt.scatter(*zip(*cluster_points), label=f'Кластер {k + 1}')
        plt.scatter(*zip(*new_centroids), c='red', marker='X', s=200, label='Центроиды')
        plt.title(f'Итерация {iteration}')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.legend()
        plt.grid()
        plt.show()
        
        if all(calculate_distance(centroids[i], new_centroids[i]) < tolerance for i in range(num_clusters)):
            break
        
        centroids = new_centroids

    return centroids

points = generate_points(num_points=100)

centroids = k_means_clustering(points, num_clusters=3)

print("Координаты центроидов кластеров:")
print(centroids)