#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

//сильно связные компоненты графа  Это группы вершин, где из каждой вершины можно добраться до любой другой внутри этой группы.
struct Graph {
    int V;
    vector<list<int>> adj;   // обычный граф
    vector<list<int>> revAdj; // обратный граф (все рёбра наоборот)

    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        revAdj.resize(V);
    }

    // Добавление ребра
    void addEdge(int from, int to) {
        adj[from].push_back(to);      // обычное ребро
        revAdj[to].push_back(from);   // обратное ребро (для алгоритма)
    }

    // ШАГ 1: Обычный DFS - запоминаем порядок выхода
    void dfs1(int v, vector<bool>& visited, stack<int>& st) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, visited, st);
            }
        }
        st.push(v); // запоминаем вершину после обработки
    }

    // ШАГ 2: DFS на обратном графе - находим одну компоненту
    //Ключевая идея : На обратном графе все вершины, которых мы можем
    //достичь из v — это те, кто может достичь v в прямом графе.Вместе 
    //они образуют сильную компоненту.
    void dfs2(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);

        for (int neighbor : revAdj[v]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, visited, component);
            }
        }
    }

    // Главная функция
    void findStrongComponents() {
        stack<int> st;
        vector<bool> visited(V, false);

        // ШАГ 1: Запускаем DFS на обычном графе
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs1(i, visited, st);
            }
        }

        // ШАГ 2: Запускаем DFS на обратном графе
        vector<bool> visitedRev(V, false);
        vector<vector<int>> allComponents;

        while (!st.empty()) {
            int v = st.top();
            st.pop();

            if (!visitedRev[v]) {
                vector<int> component;
                dfs2(v, visitedRev, component);
                allComponents.push_back(component);
            }
        }
        cout << "Найдено компонент: " << allComponents.size() << endl << endl;

        for (int i = 0; i < allComponents.size(); i++) {
            for (int vertex : allComponents[i]) {
                cout << vertex << " ";
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

    cout << "Введите " << E << " рёбер (from to):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findStrongComponents();

    return 0;
}