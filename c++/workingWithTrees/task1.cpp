#include <iostream>
using namespace std;

typedef int Item;

struct tree
{
    Item inf;        // значение узла
    tree* left;      // указатель на левого потомка
    tree* right;     // указатель на правого потомка
    tree* parent;    // указатель на родителя
};

//Создание нового узла
tree* node(Item x) {
    tree* n = new tree;     // выделяем память под новый узел указатель n
    n->inf = x;              // кладём значение x
    n->parent = NULL;        // пока нет родителя
    n->right = NULL;         // правого потомка нет
    n->left = NULL;          // левого потомка нет
    return n;                // возвращаем указатель на новый узел 
}

// Вставка узла в дерево 
tree* insert(tree* root, Item x) {
    if (root == NULL) {
        return node(x);               // создаём узел и делаем его корнем
    }

    tree* current = root;             // начинаем с корня
    tree* parent = NULL;

    while (current != NULL) {         // ищем место для вставки
        parent = current;             // запоминаем родителя
        if (x < current->inf) {       // если x меньше, идём влево
            current = current->left;
        }
        else if (x > current->inf) { // если x больше, идём вправо
            current = current->right;
        }
        else {                       // если x уже есть
            return root;               // ничего не вставляем 
        }
    }

    tree* newNode = node(x);          // создаём новый узел
    newNode->parent = parent;         // привязываем родителя

    if (x < parent->inf) {            // если x меньше родителя
        parent->left = newNode;       // вставляем слева
    }
    else {                          // если больше
        parent->right = newNode;      // вставляем справа
    }

    return root; //Возвращаем корень, чтобы вызывающий код мог его использовать
}

// Поиск узла по значению
tree* findNode(tree* root, Item x) {
    tree* current = root;
    while (current != NULL) {                // пока не дошли до конца
        if (x == current->inf) {
            return current;                  // возвращаем указатель на узел
        }
        else if (x < current->inf) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

// Вычисление высоты узла 
int getHeight(tree* node) {
    if (node == NULL) {
        return -1;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return max(leftHeight, rightHeight) + 1;
}


