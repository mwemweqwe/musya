#include <iostream>
using namespace std;

typedef int Item;

struct tree
{
    Item inf;
    tree* left;
    tree* right;
    tree* parent;
};

//Создание нового узла
tree* node(Item x) {
    tree* n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

// Вставка узла в дерево бинарного поиска
tree* insert(tree* root, Item x) {
    if (root == NULL) {
        return node(x);
    }

    tree* current = root;
    tree* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (x < current->inf) {
            current = current->left;
        }
        else if (x > current->inf) {
            current = current->right;
        }
        else {
            return root;
        }
    }

    tree* newNode = node(x);
    newNode->parent = parent;

    if (x < parent->inf) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return root;
}

// Проверка, является ли узел листом
bool isLeaf(tree* node) {
    return (node != NULL && node->left == NULL && node->right == NULL);
}

// Вывод всех четных листьев (прямой обход)
void printEvenLeaves(tree* tr, bool& found) {
    if (tr) {
        // Сначала проверяем левое поддерево
        printEvenLeaves(tr->left, found);

        // Проверяем текущий узел: если это лист И значение четное
        if (isLeaf(tr) && tr->inf % 2 == 0) {
            cout << tr->inf << " ";
            found = true;
        }

        // Затем проверяем правое поддерево
        printEvenLeaves(tr->right, found);
    }
}

// Функция для вывода бинарного дерева только числами (горизонтально)
void printBinaryTree(tree* root, int level = 0) {
    if (root == NULL) {
        return;
    }

    // Выводим правое поддерево (с отступами)
    if (root->right != NULL) {
        printBinaryTree(root->right, level + 1);
    }

    // Выводим текущий узел с отступами
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << root->inf << endl;

    // Выводим левое поддерево
    if (root->left != NULL) {
        printBinaryTree(root->left, level + 1);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    tree* root = NULL;
    int n, x;

    cout << "Введите количество элементов: ";
    cin >> n;

    if (n == 0) {
        cout << "Список пуст!" << endl;
        return 0;
    }

    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        root = insert(root, x);
    }

    cout << "\nПостроенное бинарное дерево:" << endl;
    printBinaryTree(root);
    cout << endl;

    cout << "Четные листья: ";
    bool found = false;
    printEvenLeaves(root, found);

    if (!found) {
        cout << "Четных листьев нет!";
    }
    cout << endl;
    return 0;
}