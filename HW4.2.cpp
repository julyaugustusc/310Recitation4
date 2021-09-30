//
//  main.cpp
//  HW4.2
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
        int planeNumber;
    };
    
    
public:
    int kValue;
    node* root;
    BinarySearchTree()
    {
        root = NULL;
    }
    bool isEmpty() const { return root == NULL; }
    void INORDER_TREE_WALK(node*);
    void TREE_INSERT(int, int);
    void POST_ORDER_WALK(node*);
    void PRE_ORDER_WALK(node*);
    node* FIND_MAX(node*);
    void REMOVE_MAX(node*);
    node* FIND_MIN(node*);
    node* SUCCESSOR(int);
    node* PREDECESSOR(int);
    node* SEARCH(node*, int);
    void DELETE(int);
    void SHORTDELETE(int);
    
};

void BinarySearchTree::TREE_INSERT(int key, int planeNumber)
{
    // This implements the algorithm in page 261 of the textbook
    node* z = new node();
    z->key = key;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->planeNumber = planeNumber;
    
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
    
    
    //1.Both NULL, 2. Pred == NULL, Suc = too close, 3. Pred == NULL, Suc = ok,
    //4. Suc == NULL Pred = too close, 5. Suc == NULL Pred = ok, 6. Either too close = bad, 7. Otherwise
    if(PREDECESSOR(key) == NULL){
        if(SUCCESSOR(key) == NULL){
            cout << "Landing was accepted!" << endl;
        } else {
            if (SUCCESSOR(key)->key <= key + kValue){
                cout << "Landing is too close!" << endl;
                SHORTDELETE(key);
            } else {
                cout << "Landing was accepted!" << endl;
            }
        }
    } else {
        if(SUCCESSOR(key) == NULL){
            if(PREDECESSOR(key)->key >= key - kValue){
                cout << "Landing is too close!" << endl;
                SHORTDELETE(key);
            } else {
                cout << "Landing was accepted!" << endl;
            }
        } else {
            if ((PREDECESSOR(key)->key >= key - kValue)||(SUCCESSOR(key)->key <= key + kValue)){
                cout << "Landing is too close!" << endl;
                SHORTDELETE(key);
            } else {
                cout << "Landing was accepted!" << endl;
            }
        }
    }
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
        if (x->left) INORDER_TREE_WALK(x->left);
        cout << " " << x->key << ", " << x->planeNumber << endl;
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

BinarySearchTree::node* BinarySearchTree::PREDECESSOR(int key){
    node* x = NULL;
    node* y = NULL;
    
    if (SEARCH(root, key) == NULL){
        return NULL;
    } else {
        x = SEARCH(root, key);
        
        if (x->left != NULL){
            return FIND_MAX(x->left);
        } else {
            y = x->parent;
            while (y != NULL && x == y->left){
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
        cout << "Landing successfully deleted" << endl;
    }
}

void BinarySearchTree::SHORTDELETE(int key){
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
    }
}

int main() {
    BinarySearchTree bst;
    int key, planeNumber;
    
    char input = 'i';                // initialized to a dummy value
    
    cout << "Please insert the value for K (Buffer Landing Time):" << endl;
    cin >> bst.kValue;
    
    do {
        cout << "\nPlane Landing Example\n";
        cout << "-----------------------" << endl;
        cout << "a: Request Landing" << endl;
        cout << "b: Withdraw Landing Request" << endl;
        cout << "c: List Landing times" << endl;
        cout << "q: Exit" << endl;
        cin >> input;
        cin.ignore();
        
        switch (input) {
            case 'a':
                cout << endl;
                cout << "Enter Landing time (int value): " << endl;
                cin >> key;
                cout << "Enter Flight number (int value): " << endl;
                cin >> planeNumber;
                bst.TREE_INSERT(key, planeNumber);
                break;
                
            case 'b':
                cout << endl;
                cout << "Enter the landing request time to be deleted: " << endl;
                cin >> key;
                bst.DELETE(key);
                break;
                
            case 'c':
                cout << endl;
                cout << "Landing time and flight numbers: " << endl;
                cout << "-------------------------------" << endl;
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

