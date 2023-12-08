#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

// Структура для узла бинарного дерева выражения
struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Проверка синтаксической правильности идентификаторов переменных
bool isValidIdentifier(const string& id) {
    for (char c : id) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

// Построение выражения в инфиксной форме со скобками
string infixExpression(Node* root) {
    if (!root) {
        return "";
    }

    if (root->left == nullptr && root->right == nullptr) {
        return root->value;
    }

    string leftExp = infixExpression(root->left);
    string rightExp = infixExpression(root->right);

    return "(" + leftExp + " " + root->value + " " + rightExp + ")";
}

// Вычисление значения выражения
double evaluateExpression(Node* root, const vector<pair<string, double>>& variables) {
    if (!root) {
        return 0.0;
    }

    if (root->left == nullptr && root->right == nullptr) {
        // Поиск значения переменной в векторе пар "идентификатор переменной - значение переменной"
        for (const auto& var : variables) {
            if (var.first == root->value) {
                return var.second;
            }
        }
        return 0.0; // Возвращаем 0.0, если значение переменной не найдено
    }

    // Рекурсивно вычисляем значения левого и правого поддеревьев
    double leftValue = evaluateExpression(root->left, variables);
    double rightValue = evaluateExpression(root->right, variables);

    // Выполняем операции или функции в узле
    if (root->value == "+") {
        return leftValue + rightValue;
    }
    else if (root->value == "-") {
        return leftValue - rightValue;
    }
    else if (root->value == "*") {
        return leftValue * rightValue;
    }
    else if (root->value == "/") {
        return leftValue / rightValue;
    }
    else if (root->value == "SIN") {
        return sin(leftValue);
    }
    else if (root->value == "COS") {
        return cos(leftValue);
    }
    else if (root->value == "TG") {
        return tan(leftValue);
    }
    else if (root->value == "CTG") {
        return 1.0 / tan(leftValue);
    }
    else if (root->value == "LOG") {
        return log(leftValue);
    }
    else if (root->value == "EXP") {
        return exp(leftValue);
    }

    return 0.0; // Возвращаем 0.0 для неправильных операций
}

int main() {

    system("chcp 1251");
    // Создание бинарного дерева выражения
    Node* root = new Node("-");
    root->left = new Node("*");
    root->left->left = new Node("+");
    root->left->left->left = new Node("a1");
    root->left->left->right = new Node("bar");
    root->left->right = new Node("c");
    root->right = new Node("-");
    root->right->left = new Node("SIN");
    root->right->left->left = new Node("dors");
    root->right->right = new Node("e");

    // Вектор пар "идентификатор переменной - значение переменной"
    vector<pair<string, double>> variables = {
        {"a1", 5.0},
        {"bar", 10.0},
        {"c", 3.0},
        {"dors", 1.0},
        {"e", 2.0}
    };

    // Проверка синтаксической правильности идентификаторов переменных
    for (const auto& var : variables) {
        if (!isValidIdentifier(var.first)) {
            cout << "Ошибка: Идентификатор '" << var.first << "' содержит недопустимые символы!" << endl;
            return 1;
        }
    }

    // Вывод инфиксного выражения
    cout << "Инфиксное выражение: " << infixExpression(root) << endl;

    // Вычисление значения выражения
    double result = evaluateExpression(root, variables);
    cout << "Значение выражения: " << result << endl;

    // Освобождение памяти, выделенной для узлов дерева
    delete root->left->left->right;
    delete root->left->left;
    delete root->left;

    return 0;
}
//
//    -
//   / \
//   *  -
//  / \ / \
//  + c SIN e
//  / \   |
//a1  bar dors
