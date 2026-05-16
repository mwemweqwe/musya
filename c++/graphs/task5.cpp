#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;


//Сначала запомни порядок обхода графа с помощью BFS, 
// затем обходи транспонированный граф в обратном порядке — 
// каждый такой обход даст одну сильно связную компоненту

//Внутри одной сильно связной компоненты каждая вершина может
//"добраться" до каждой другой(и наоборот), перемещаясь только по 
//стрелкам(ориентированным рёбрам).
struct Graph {
    int V; // Количество вершин в графе
    vector<list<int>> adj; // Список смежности
    vector<list<int>> adjRev; // Список смежности для транспонированного графа

    // Конструктор
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        adjRev.resize(V);
    }

    // Добавление ориентированного ребра
    void addEdge(int u, int v) {
        adj[u].push_back(v);      // Добавляем в исходный граф
        adjRev[v].push_back(u);   // Добавляем в транспонированный граф
    }

    // BFS для обхода графа
    void BFS(int start, vector<bool>& visited, vector<int>& component) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            component.push_back(v);

            // Перебираем всех соседей
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // BFS на транспонированном графе
    void BFSOnTranspose(int start, vector<bool>& visited, vector<int>& component) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            component.push_back(v);

            // Используем транспонированный граф
            for (int neighbor : adjRev[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Первый проход: заполняем порядок завершения (используем BFS, но порядок не сохраняется,
    // поэтому используем стек для эмуляции порядка)
    void fillOrder(int start, vector<bool>& visited, stack<int>& Stack) {
        queue<int> q;
        vector<int> order;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            order.push_back(v);

            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Добавляем вершины в стек в обратном порядке
        for (int i = order.size() - 1; i >= 0; i--) {
            Stack.push(order[i]);
        }
    }

    // Основная функция для поиска SCC
    vector<vector<int>> findSCCs() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        // Шаг 1: Заполняем порядок вершин (имитируем порядок завершения DFS)
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, Stack);
            }
        }

        // Шаг 2: Обходим транспонированный граф в порядке из стека
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                vector<int> component;
                BFSOnTranspose(v, visited, component);
                sccs.push_back(component);
            }
        }

        return sccs;
    }

    // Вывод графа
    void printGraph() {
        cout << "\nИсходный граф (список смежности):\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int x : adj[i]) {
                cout << x << " ";
            }
            cout << endl;
        }

        cout << "\nТранспонированный граф (список смежности):\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int x : adjRev[i]) {
                cout << x << " ";
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

    g.printGraph();

    // Находим все сильно связные компоненты
    vector<vector<int>> sccs = g.findSCCs();

    // Выводим результат
    cout << "РЕЗУЛЬТАТ: СИЛЬНО СВЯЗНЫЕ КОМПОНЕНТЫ\n";

    if (sccs.empty()) {
        cout << "Компоненты не найдены.\n";
    }
    else {
        cout << "Найдено " << sccs.size() << " сильно связных компонент(ы):\n\n";
        for (size_t i = 0; i < sccs.size(); i++) {
            cout << "SCC " << i + 1 << ": { ";
            for (int vertex : sccs[i]) {
                cout << vertex << " ";
            }
            cout << "}\n";
        }
    }

    return 0;
}