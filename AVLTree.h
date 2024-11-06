#pragma once

#include <iostream>

using namespace std;

// Структура для узла дерева
struct Node;
// Функция для создания нового узла
Node* createNode(int value);
// Функция для вставки элемента в бинарное дерево поиска
Node* insert(Node* root, int value);
int checkBalance(Node* root, bool& isBalanced);
void freeTree(Node* root);