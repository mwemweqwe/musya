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

