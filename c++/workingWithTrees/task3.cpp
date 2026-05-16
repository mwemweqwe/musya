#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef int Item;

struct tree
{
    Item inf;
    tree* left;
    tree* right;
    tree* parent;
};

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

// Сбор всех листьев в вектор
void collectLeaves(tree* tr, vector<tree*>& leaves) {
    if (tr) {
        collectLeaves(tr->left, leaves);
        if (isLeaf(tr)) {
            leaves.push_back(tr);
        }
        collectLeaves(tr->right, leaves);
    }
}

// Нахождение среднего по значению листа
tree* findMiddleLeaf(tree* root) {
    vector<tree*> leaves;
    collectLeaves(root, leaves);

    if (leaves.empty()) {
        return NULL;
    }

    sort(leaves.begin(), leaves.end(), [](tree* a, tree* b) {
        return a->inf < b->inf;
        });

    int middleIndex = leaves.size() / 2;
    return leaves[middleIndex];
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

// Функция для удаления узла с переподключением детей
tree* deleteNodeWithReconnect(tree* root, tree* target) {
    if (target == NULL) return root;

    tree* parent = target->parent;
    tree* leftChild = target->left;
    tree* rightChild = target->right;

    // Если удаляем корень
    if (parent == NULL) {
        // Если есть левый и правый потомки
        if (leftChild != NULL && rightChild != NULL) {
            // Ищем самый правый узел в левом поддереве
            tree* maxLeft = leftChild;
            while (maxLeft->right != NULL) {
                maxLeft = maxLeft->right;
            }
            maxLeft->right = rightChild;
            rightChild->parent = maxLeft;
            root = leftChild;
            leftChild->parent = NULL;
        }
        // Если есть только левый потомок
        else if (leftChild != NULL) {
            root = leftChild;
            leftChild->parent = NULL;
        }
        // Если есть только правый потомок
        else if (rightChild != NULL) {
            root = rightChild;
            rightChild->parent = NULL;
        }
        // Если нет потомков
        else {
            root = NULL;
        }
        delete target;
        return root;
    }

    // Определяем, кем был удаляемый узел для своего родителя
    bool isLeftChild = (parent->left == target);

    // Случай 1: удаляемый узел - лист
    if (leftChild == NULL && rightChild == NULL) {
        if (isLeftChild) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        delete target;
    }
    // Случай 2: удаляемый узел имеет только левого потомка
    else if (leftChild != NULL && rightChild == NULL) {
        if (isLeftChild) {
            parent->left = leftChild;
        }
        else {
            parent->right = leftChild;
        }
        leftChild->parent = parent;
        delete target;
    }
    // Случай 3: удаляемый узел имеет только правого потомка
    else if (leftChild == NULL && rightChild != NULL) {
        if (isLeftChild) {
            parent->left = rightChild;
        }
        else {
            parent->right = rightChild;
        }
        rightChild->parent = parent;
        delete target;
    }
    // Случай 4: удаляемый узел имеет двух потомков
    else {
        // Подключаем левое поддерево к самому правому узлу правого поддерева
        tree* rightmostLeft = rightChild;
        while (rightmostLeft->left != NULL) {
            rightmostLeft = rightmostLeft->left;
        }
        rightmostLeft->left = leftChild;
        leftChild->parent = rightmostLeft;

        // Подключаем правое поддерево к родителю
        if (isLeftChild) {
            parent->left = rightChild;
        }
        else {
            parent->right = rightChild;
        }
        rightChild->parent = parent;

        delete target;
    }

    return root;
}

// Освобождение памяти
void deleteTree(tree* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
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

    // Вывод построенного дерева
    cout << "\nПостроенное бинарное дерево:" << endl;
    printBinaryTree(root);
    cout << endl;

    // Находим средний по значению лист
    tree* middleLeaf = findMiddleLeaf(root);

    if (middleLeaf == NULL) {
        cout << "В дереве нет листьев!" << endl;
        deleteTree(root);
        return 0;
    }

    cout << "Средний по значению лист: " << middleLeaf->inf << endl;

    // Находим "деда" (родителя родителя)
    tree* grandparent = NULL;
    if (middleLeaf->parent != NULL) {
        grandparent = middleLeaf->parent->parent;
    }

    if (grandparent == NULL) {
        cout << "У среднего листа нет деда (глубина меньше 2)!" << endl;
    }
    else {
        cout << "Дед среднего листа: " << grandparent->inf << endl;

        // Вывод дерева до удаления
        cout << "\nДерево ДО удаления деда:" << endl;
        printBinaryTree(root);
        cout << endl;

        cout << "Удаляем деда с переподключением его детей..." << endl;
        root = deleteNodeWithReconnect(root, grandparent);
        cout << "Дед успешно удален, его дети переподключены!" << endl;

        // Вывод дерева после удаления
        cout << "\nДерево ПОСЛЕ удаления деда:" << endl;
        printBinaryTree(root);
        cout << endl;
    }

    deleteTree(root);

    return 0;
}