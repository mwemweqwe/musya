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

    int vertex;
    cout << "\nВведите вершину: ";
    cin >> vertex;

    // ОТВЕТ НА ЗАДАЧУ
    cout << "\nКоличество вершин, смежных с " << vertex << ": " << g.countAdjacent(vertex) << endl;

    return 0;
}