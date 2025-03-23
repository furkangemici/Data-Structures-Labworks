#pragma once
#include <iostream>
#include <utility>
#include <string>
using namespace std;

class BSTCityNode {
private:
    pair<string, int> value; // �ehir ad� ve say�sal de�eri
    BSTCityNode* left;       // Sol alt d���m
    BSTCityNode* right;      // Sa� alt d���m

public:
    // Constructor
    BSTCityNode(pair<string, int> val) : value(val), left(nullptr), right(nullptr) {}

    // Getter ve Setter Metotlar�
    pair<string, int> getValue() { return value; }
    void setValue(pair<string, int> val) { value = val; }

    BSTCityNode* getLeft() { return left; }
    void setLeft(BSTCityNode* node) { left = node; }

    BSTCityNode* getRight() { return right; }
    void setRight(BSTCityNode* node) { right = node; }
};
