/************************************************************************************************************************************************************
 * @file Binary_Search_tree.cpp
 * @brief Binary search tree is a kind of Binary tree, where a node can contain o to maximum of two child nodes, where
 * the left_child should contain value lesser than root, and the right_child should contain bigger than root.
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>

template <typename T>
struct BST {
    T value;
    BST *left_child = nullptr;
    BST *right_child = nullptr;
};


template <typename T>
void print(BST<T> *root) {
    if (root != nullptr) {
        std::cout << root->value << " "; 
        std::cout << (root->left_child ? root->left_child->value : 0) << " ";
        std::cout << (root->right_child ? root->right_child->value : 0);
        std::cout << std::endl;
        print(root->left_child); print(root->right_child); 
    } else {      
        return;
    }
}

void pause() {
    std::string str;
    getline(std::cin, str);
    return ;
}

template <typename T>
void find(const T &val, const BST<T> *root) {
    auto curr = root;
    while(curr) {
        if(val == curr->value) {
            std::cout << val << " found" << curr << std::endl;
            return;
        } else {
            curr = val < curr->value ? curr->left_child : curr->right_child;
        }
    }

    std::cout << val << " not found" << std::endl;
} 

/*
int main() {
    BST<int> *root = new BST<int>({80});
    int a[10] = {80, 13, 89, 67, 34, 25, 90, 12, 35};

    for (int n : a) {
        bool repeat = false;
        auto curr = root;
        decltype(curr) prev = nullptr;
        while(curr != nullptr) {
            if(n < curr->value) {
                prev = curr;
                curr = curr->left_child;
            } else if (n > curr->value) {
                prev = curr;
                curr = curr->right_child;
            } else {
                repeat = true;
                break;
            }
        }

        if (!repeat) {
            auto *p = new BST<int>({n});
            if (n < prev->value) {    
                prev->left_child = p;
            } else {
                prev->right_child = p;    
            }
        }
    } 

    print(root);
    find(89, root);
    find(94, root);
    find(156, root);
    find(12, root);
    find(34, root);

    return 0;

}

*/