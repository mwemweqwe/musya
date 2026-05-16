#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Graph {
    int V; //вершины
    vector<list<int>> adj; //список смежности

    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    //метод для добавления ребра из вершины u в вершину v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // МЕТОД ДЛЯ ПОДСЧЁТА СМЕЖНЫХ ВЕРШИН
    int countAdjacent(int vertex) {
        return adj[vertex].size();
    }

    // МЕТОД ДЛЯ ВСТАВКИ РЕБРА (С ПРОВЕРКОЙ)
    void insertEdge(int A, int B) {
        // Проверка: существует ли уже такое ребро?
        for (int neighbor : adj[A]) {
            if (neighbor == B) {
                cout << "Ребро " << A << " -> " << B << " уже существует!" << endl;
                return;
            }
        }

        // Добавляем ребро
        adj[A].push_back(B);
        cout << "Ребро " << A << " -> " << B << " успешно вставлено!" << endl;
    }

    // МЕТОД ДЛЯ ВЫВОДА ГРАФА
    void printGraph() {
        cout << "\nСписок смежности:\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    int V, E;
    cout << "Введите количество вершин: ";
    cin >> V;
    cout << "Введите количество рёбер: ";
    cin >> E;

    Graph g(V);

    cout << "Введите " << E << " рёбер (формат: from to):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Выводим начальный граф
    g.printGraph();

    // ВСТАВКА НОВОГО РЕБРА
    int A, B;
    cout << "\nВведите ребро для вставки (формат: A B): ";
    cin >> A >> B;

    g.insertEdge(A, B);

    // Выводим обновлённый граф
    g.printGraph();

    return 0;
}