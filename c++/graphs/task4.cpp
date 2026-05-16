#include <iostream>
#include <vector>
#include <list>
using namespace std;


//Цикл в графе — это замкнутый путь, где можно начать движение из одной вершины, пройти по рёбрам и вернуться в ту же вершину, не проходя дважды по одному ребру
//При обходе графа в глубину(DFS), если мы встретили уже посещённую вершину, и это не наш "родитель" по обходу — значит, мы нашли цикл.

struct Graph {
    int V;
    vector<list<int>> adj;
    vector<int> cycle;  // чтобы сохранить найденный цикл и потом вывести его на экран

    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    // Добавление ребра (неориентированный граф)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS для поиска цикла
    // v - текущая вершина
    // parent - откуда пришли
    // visited - посещённые вершины
    bool dfs(int v, int parent, vector<bool>& visited, vector<int>& path) {
        visited[v] = true; //Отмечаем текущую вершину как посещённую
        path.push_back(v); //Добавляем текущую вершину в путь

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {//Если сосед ещё не посещён
                if (dfs(neighbor, v, visited, path)) {
                    //Рекурсивно запускаем DFS от соседа(передаём neighbour как текущий, v как родителя)
                    return true;
                }
            }
            else if (neighbor != parent) {// Если сосед ПОСЕЩЁН и это НЕ родитель то нашли цикл
                cycle.clear();

                // Ищем в пути path позицию, где находится вершина neighbor
                auto it = find(path.begin(), path.end(), neighbor);
                for (; it != path.end(); ++it) {
                    cycle.push_back(*it); //Добавляем вершины из пути в цикл
                }
                cycle.push_back(neighbor);
                return true;
            }
        }

        path.pop_back(); //При возврате к родителю вершина больше не часть пути
        return false; //Сообщить родителю, что отсюда цикла нет
    }

    // Поиск и вывод цикла
    void findAndPrintCycle() {
        vector<bool> visited(V, false);
        vector<int> path;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, visited, path)) {
                    cout << "\nНайден цикл: ";
                    for (int i = 0; i < cycle.size(); i++) {
                        cout << cycle[i];
                        if (i < cycle.size() - 1) cout << " → ";
                    }
                    cout << endl;
                    return;
                }
            }
        }

        cout << "\nЦиклов не найдено!" << endl;
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

    cout << "Введите " << E << " рёбер (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findAndPrintCycle();

    return 0;
}