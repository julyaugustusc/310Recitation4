//
//  main.cpp
//  HW4.1
//
//  Created by Augustus Crosby on 6/20/19.
//  Copyright © 2019 Augustus Crosby. All rights reserved.
//

#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
private:
    class node
    {
    public:
        node* left;
        node* right;
        node* parent;
        int key;
        string data;
    };
    
    
public:
    node* root;
    BinarySearchTree()
    {
        root = NULL;
    }
    bool isEmpty() const { return root == NULL; }
    void INORDER_TREE_WALK(node*);
    void TREE_INSERT(int);
    void POST_ORDER_WALK(node*);
    void PRE_ORDER_WALK(node*);
    node* FIND_MAX(node*);
    void REMOVE_MAX(node*);
    node* FIND_MIN(node*);
    node* SUCCESSOR(int);
    node* SEARCH(node*, int);
    void DELETE(int);
    
};

void BinarySearchTree::TREE_INSERT(int d)
{
    // This implements the algorithm in page 261 of the textbook
    node* z = new node();
    z->key = d;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    
    node* y = NULL;
    node* x = root;
    
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
        if (x->left) INORDER_TREE_WALK(x->left);
        cout << " " << x->key << " ";
        if (x->right) INORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::POST_ORDER_WALK(node* x){
    if (x != NULL)
    {
        if (x->left) POST_ORDER_WALK(x->left);
        if (x->right) POST_ORDER_WALK(x->right);
        cout << " " << x->key << " ";
    }
}

void BinarySearchTree::PRE_ORDER_WALK(node* x){
    if (x != NULL)
    {
        cout << " " << x->key << " ";
        if (x->left) POST_ORDER_WALK(x->left);
        if (x->right) POST_ORDER_WALK(x->right);
    }
}

BinarySearchTree::node* BinarySearchTree::FIND_MAX(node* x){
    while (x->right != NULL){
        x = x->right;
    }
    return x;
}

void BinarySearchTree::REMOVE_MAX(node* x){
    while (x->right->right != NULL){
        x = x->right;
    }
    delete(x->right);
    x->right = NULL;
}

BinarySearchTree::node* BinarySearchTree::FIND_MIN(node* x){
    while (x->left != NULL){
        x = x->left;
    }
    return x;
}

BinarySearchTree::node* BinarySearchTree::SUCCESSOR(int key){
    node* x = NULL;
    node* y = NULL;
    
    if (SEARCH(root, key) == NULL){
        return NULL;
    } else {
        x = SEARCH(root, key);
    
        if (x->right != NULL){
            return FIND_MIN(x->right);
        } else {
            y = x->parent;
            while (y != NULL && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }
    }
}

BinarySearchTree::node* BinarySearchTree::SEARCH(node* x, int key){
    if (x == NULL || key == x->key){
        return x;
    } else {
        if (key < x->key){
            if (x->left == NULL){
                return NULL;
            } else {
                return SEARCH(x->left, key);
            }
        } else {
            if (x->right == NULL){
                return NULL;
            } else {
                return SEARCH(x->right, key);
            }
        }
    }
}

void BinarySearchTree::DELETE(int key){
    node* x = NULL;
    node* y = NULL;
    node* z = NULL;
    
    if (SEARCH(root, key) == NULL){
        cout << "Value not found" << endl;
    } else {
        x = SEARCH(root, key);
    
        if (x->left == NULL || x->right == NULL){
            y = x;
        } else {
            y = SUCCESSOR(x->key);
        }
    
        if (y->left != NULL){
            z = y->left;
        } else {
            z = y->right;
        }
    
        if (z != NULL){
            z->parent = y->parent;
        }
    
        if (y->parent == NULL){
            root = z;
        } else {
            if (y == y->parent->left){
                y->parent->left = z;
            } else {
                y->parent->right = z;
            }
        }
    
        if (y != x){
            x->key = y->key;
        }
        cout << "Value successfully deleted" << endl;
    }
}

int main() {
    BinarySearchTree bst;
    int key;
    
    char input = 'i';                // initialized to a dummy value
    
    do {
        cout << "\nBinary Search Tree Example\n";
        cout << "-----------------------------" << endl;
        cout << "a: Insert\n";
        cout << "b: Post-Order Traversal\n";
        cout << "c: Pre-Order Traversal\n";
        cout << "d: Find Max\n";
        cout << "e: Remove Max\n";
        cout << "f: Successor\n";
        cout << "g: Delete a Node\n";
        cout << "h: In-Order Traversal\n";
        cout << "q: Exit\n";
        cin >> input;
        cin.ignore();
        
        switch (input) {
            case 'a':
                cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
                
            case 'b':
                cout << endl;
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POST_ORDER_WALK(bst.root);
                break;
                
            case 'c':
                cout << endl;
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PRE_ORDER_WALK(bst.root);
                break;
                
            case 'd':
                cout << endl;
                cout << " Find Max " << endl;
                cout << " --------" << endl;
                cout << bst.FIND_MAX(bst.root)->key << endl;
                break;
                
            case 'e':
                cout << endl;
                cout << " Remove Max " << endl;
                cout << " ----------" << endl;
                bst.REMOVE_MAX(bst.root);
                cout << "Max has been removed." << endl;
                break;
                
            case 'f':
                cout << " Enter key (int value) to find Successor: ";
                cin >> key;
                cout << endl;
                cout << " Successor " << endl;
                cout << " ---------" << endl;
                if (bst.SUCCESSOR(key) == NULL){
                     cout << "Value not found" << endl;
                } else {
                    cout << bst.SUCCESSOR(key)->key << endl;
                }
                break;
                
            case 'g':
                cout << " Enter key (int value) to be deleted: ";
                cin >> key;
                cout << endl;
                cout << " Delete Node " << endl;
                cout << " -----------" << endl;
                bst.DELETE(key);
                break;
                
            case 'h':
                cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
                
            case 'q':        // quit
                return 0;
                break;
                
            default:
                cout << "Invalid choice\n";
        }
    } while (input != 'q');
}
