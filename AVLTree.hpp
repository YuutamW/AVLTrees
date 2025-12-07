#pragma once
#include <iostream>
#include <string>

/*Introduction:
    AVL tree Data structures are a sub catagory of binary search trees. what are the main differences?
    -The Definition of AVL Trees:
        An AVL tree is a self balancing binary search tree that ensures efficient operations
        O(log(n)) where n = number of nodes in the tree. in other words, an AVL tree is a family of Binary Search Trees
        of which their height is O(Log(n)), for example: if a BST has in total 6 nodes & it's height is O(log(6)) <= 3, 
        it is considered an AVL tree IF AND ONLY IF the height difference between each node is at most 1.
        one such AVLTree could look something like this: a 7 Node "perfect tree/whole tree" with height of 2.
            BST with 7 nodes, height of 2:
                h:0    6
                     /   \
              h:1   3     8
                   / \   / \
             h:2  2   4 7   9
    -Properties and charictaristics:
        *Self-balancing:
         It automatically rebalances itself after insertions and deletions to maintain a balanced structure
        *Balance factor:
         For any node, the difference between the height of its left subtree and its right subtree is at most one (i.e., -1, 0, or 1). 
        *Logarithmic time complexity:
         This balance ensures that search, insertion, and deletion operations all have a time complexity of \(O(\log n)\),
         making them very efficient. 
        *Named after inventors:
         The name "AVL" comes from its inventors, Georgy Adelson-Velsky and Evgenii Landis. 

         the tree keeps balancing itself to be at the right height. 
         here is a simplified table of cases:
         CASE:     CONIDTION:                       ROTATE:
         LL         Node: BF>1,LeftChild:BF>=0      Right
         RR         Node:BF<-1,RightChild:BF<=0     Left
         LR         Node: BF>1,LeftChild:BF<0       Left+Right
         RL         Node:BF<-1,RightChild:BF>0      Right+Left
        -----------In this file ill demonstrate an example of a class of AVL tree---------------------
        in a main file ill implement usages.
*/

class AVLTree
{
private:
    /* data */
    struct Node
    {
        Node *LeftSon;
        Node *RightSon;
        int Key;
        __int8 BF;    //balanceFactor,int8 bcoz it will be a very small range(-2,-1,0,1,2), we dont need more than one byte of mem.
        Node(int k=0): LeftSon(nullptr),RightSon(nullptr),Key(k),BF(0) {}
    };
    Node *Root;
    int height = -1;
    //rightBalance: Balance tree/subtree given to Right
    void rightBalance(Node*& node, bool &taller); 
    //leftBalance: Balance tree/subtree given to Left
    void leftBalance(Node*& node, bool &taller); 
    //rotateRight: Rotate given tree/subtree to the right
    void rotateRight(Node*& node);
    //rotateLeft: Rotate given tree/subtree to the left
    void rotateLeft(Node*& node);

    /*private helpers:*/
    
    void destroyTree(Node *root);
    int* getArrOfKeys();
    // Node& createNode(Node *LS=nullptr, Node *RS=nullptr,int K = 0, __int8 = 0);
    std::string tree2String(int *arrOfKeysInOrder , int *arrOfKeysPostOrder);
    void addNodeToTree(Node *&root, int key ,bool &taller);
    void removeNodeFromTree();

    int getHeight(Node *node);
    int balanceFactorOfNode(Node* root);
    inline int getBF(Node *root) { return (root) ? root->BF : 0 ;}
    
public:
    AVLTree();
    AVLTree(int k);
    ~AVLTree();
    void insertNode(int key);
    void deleteNode(int key);
    void printTree();

};

