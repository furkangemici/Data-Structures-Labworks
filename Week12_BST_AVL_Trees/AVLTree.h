#pragma once
#include <iostream>
#include <algorithm>
#include "AVLNode.h"

class AVLTree {
private:
    AVLNode* root;

    // D���m y�ksekli�ini al
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    // Denge fakt�r�n� hesapla
    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Sa� rotasyon
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Rotasyonu uygula
        x->right = y;
        y->left = T2;

        // Y�kseklikleri g�ncelle
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Sol rotasyon
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Rotasyonu uygula
        y->left = x;
        x->right = T2;

        // Y�kseklikleri g�ncelle
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // AVL a�ac�na eleman ekleme
    AVLNode* insertNode(AVLNode* node, int value) {
        if (!node) {
            return new AVLNode(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }
        else {
            return node; // Ayn� eleman tekrar eklenemez
        }

        // Y�ksekli�i g�ncelle
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

        // Denge fakt�r�n� kontrol et
        int balance = getBalanceFactor(node);

        // Sol-Sol durumu
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Sa�-Sa� durumu
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Sol-Sa� durumu
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Sa�-Sol durumu
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // InOrder traversal
    void inOrderTraversal(AVLNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    // PreOrder traversal
    void preOrderTraversal(AVLNode* node) {
        if (node) {
            std::cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    // PostOrder traversal
    void postOrderTraversal(AVLNode* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

    // D���m denge fakt�rlerini yazd�r
    void printBalanceFactors(AVLNode* node) {
        if (node) {
            printBalanceFactors(node->left);
            std::cout << "Node: " << node->data
                << ", Left Height: " << getHeight(node->left)
                << ", Right Height: " << getHeight(node->right)
                << ", Balance Factor: " << getBalanceFactor(node)
                << std::endl;
            printBalanceFactors(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Eleman ekleme
    void insert(int value) {
        root = insertNode(root, value);
    }

    // Dengeli AVL a�ac�n� g�ster (InOrder traversal)
    void showBalancedTree() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    // PreOrder Traversal
    void preOrder() {
        preOrderTraversal(root);
        std::cout << std::endl;
    }

    // InOrder Traversal
    void inOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    // PostOrder Traversal
    void postOrder() {
        postOrderTraversal(root);
        std::cout << std::endl;
    }

    // D���m denge fakt�rlerini yazd�r
    void printBalanceFactors() {
        printBalanceFactors(root);
    }
};
