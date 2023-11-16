#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;

using namespace std;

// Функция для вычисления расстояния между двумя городами
int distance(vector<vector<int>>& graph, int src, int dest) {
    return graph[src][dest];
}

// Функция для вычисления длины пути
int calculatePathLength(vector<int>& path, vector<vector<int>>& graph) {
    int length = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        length += distance(graph, path[i], path[i + 1]);
    }
    return length;
}

// Функция для перебора всех возможных путей
void tsp(vector<vector<int>>& graph, vector<int>& path, vector<bool>& visited, int& minLength) {
    if (path.size() == graph.size()) {
        // Путь завершен, вычисляем его длину
        int currentLength = calculatePathLength(path, graph);
        // Обновляем минимальную длину, если текущая длина меньше
        minLength = min(minLength, currentLength);
        return;
    }

    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            // Посещаем город, добавляем его к пути
            visited[i] = true;
            path.push_back(i);
            tsp(graph, path, visited, minLength);
            // Отменяем посещение текущего города перед возвратом (backtracking)
            visited[i] = false;
            path.pop_back();
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    // Пример графа с расстояниями между городами
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = graph.size();
    vector<int> path;
    vector<bool> visited(n, false);
    int minLength = INF;

    // Начинаем с первого города (можно выбрать любой другой)
    path.push_back(0);
    visited[0] = true;

    // Вызываем функцию для поиска оптимального пути
    tsp(graph, path, visited, minLength);

    // Выводим результат
    cout << "Минимальная длина пути: " << minLength << endl;

    return 0;
}
