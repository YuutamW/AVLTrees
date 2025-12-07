#include "AVLTree.hpp"

#pragma region private funcs

void AVLTree::rightBalance(Node *&node, bool &taller)
{
    if(!node || !node->RightSon) return;
    Node *rs = node->RightSon;  //the right child
    Node *ls;                   //the "grandchild" (inner child)

    switch (rs->BF)
    {
        //Case RR: the straight line to the right case
    case 1:
        node->BF = 0;
        rs->BF = 0;
        rotateLeft(node);
        taller = false;     //the tree height has shrunk back to normal
        break;
    //Case: Right-neutral ( usually happens in deletion)
    case 0:
        node->BF = 1;   //parent becomes slightly Right heavy
        rs->BF = -1;    //child becomes lsightly left heavy
        rotateLeft(node);
        taller = true;
        break;
    //CASE RL: the zig-zag case
    case -1:
        ls = rs->LeftSon;   //the grandchild that will jump up to become the new root
        //we must update BF based on what the Grandchild's BF was:
        switch (ls->BF)
        {
        case 1: //grandchild was leaning right
            node->BF = -1;    //orig parent becomes left heavy
            rs->BF = 0;     //Right child becomes balanced
            break;
        case 0: //grandchild was balanced
            node->BF = 0;   //so will the orig node's BF
            rs->BF = 0;     //and the right son's BF
            break;
        case -1:    //grandChild was leaning left
            node->BF = 0;   //orig parent becomes balanced
            rs->BF = 1; //right child becomes right heavy
            break;
        }
        ls->BF = 0; //the grandchild becomes the new balanced root
        rotateRight(node->RightSon);    //1.rotate child right
        rotateLeft(node);              //2.rotate parent left
        taller = false;
        break;
    }
}

void AVLTree::leftBalance(Node *&node, bool &taller)
{
    Node *ls = node->LeftSon;
    Node *rs = nullptr;
    switch (ls->BF)
    {
    case -1:    //case of left left heavy
        node->BF = 0;
        ls->BF = 0;
        rotateRight(node);
        taller = false;
        break;
    case 0: //left neutral - deletion edge case
        node->BF = -1;
        ls->BF = 1;
        rotateRight(node);
        taller = true;
        break;
    //case Lr: left right - zigzag
    case 1:
        rs = ls->RightSon;
        //update BF based on the grandchild's BF
        switch (rs->BF)
        {
        case -1:    //grandChild was leaning left
            node->BF = 1;
            ls->BF = 0;
            break;
        case 0: //GC was balanced
            node->BF = 0;
            ls->BF = 0;
            break;
        case 1: //GC was leaning right
            node->BF = 0;
            ls->BF = -1;
            break;
        }
        rs->BF = 0; //GC becomes new balanced root
        rotateLeft(node->LeftSon);  //1.rotate child left
        rotateRight(node);          //2.rotate parent right
        taller = false;
        break;
    }
}

/*Rotation logic summery:
let's say for example that a subtree is right heavy. we will want to rotate the tree to the left.
Before rotation:
            A   (node)
            \
              B (temp)
              /
            Y
we will rotate to the left and it will be like this:
        B(node)
        /
       A
        \
         Y
         */
void AVLTree::rotateLeft(Node *&node)
{
    if(!node || !node->RightSon) return;
    //1)identification: 'node' is A. temp is B(future root)
    Node *temp = node->RightSon;
    //2)handover: A takes B's left child(Y) as it new right child
    node->RightSon = temp->LeftSon;
    //3)lift: B takes A as its new left child
    temp->LeftSon = node;
    //4)update parrent: the pointer coming from above now points to B
    node = temp;
}
void AVLTree::rotateRight(Node *&node)
{
    if(!node || !node->LeftSon) return;
    //1)id: 'node' is A, temp is B(furute root)
    Node *temp = node->LeftSon;
    //2)handover: A takes B's Right son(Y) as it's new left child
    node->LeftSon = temp->RightSon;
    //3) Lift:B takes A as its new Right son
    temp->RightSon = node;
    //4)update: node becomes B for linking B to parrent of node
    node = temp;    
}



/*DestroyTree-Summery: 
stdrd implementation of deleting a BST recursively, no consideration of BF because we wont need it after the tree is dead.
*/
void AVLTree::destroyTree(Node *root)
{
    if(root == nullptr) return;
    destroyTree(root->LeftSon);
    destroyTree(root->RightSon);
    delete root;
}

// AVLTree::Node &AVLTree::createNode(Node *LS, Node *RS, int K, __int8 t){}

void AVLTree::addNodeToTree(Node *&root, int key ,bool &taller)
{
   //1. found insertion spot:
   if(!root){
    root = new Node(key);
    //a new node increases height from 0 to 1
    taller = true;
    return;
   }
   //2.duplicate check:
   if(key == root->Key){taller = false; /*no change.*/ return;}
   //3.recursive insertion
   if(key > root->Key)
   {
        addNodeToTree(root->RightSon,key,taller);
        //BACKTRACKING: did the right subtree grow?
        if(taller)
        {
            switch (root->BF)
            {
            case -1: //was left heavy added to right -> now balanced
                root->BF = 0;
                taller = false; //growth absorberd. stop alerting parents.
                break;
            case 0: //was balanced add to right-> now Right heavy
                root->BF = 1;
                taller = true;  //I grew Taller alert my parents.
                break;
            case 1: //was Right heavy added to right - > now critical (+2)
                rightBalance(root,taller);  //fix it.
                // NOTE: rightBalance will set taller = flase automatically
                break;
            }
        }
   }
   else //key < root->key (Insert to LEFT)
   {
        addNodeToTree(root->LeftSon, key , taller);
        //BACKTRACKING: did the left subtree grow?
        if (taller)
        {
            switch (root->BF)
            {
            case 1:  // Was Right heavy, added to Left -> Now Balanced
                root->BF = 0;
                taller = false; // Growth absorbed.
                break;

            case 0:  // Was Balanced, added to Left -> Now Left heavy
                root->BF = -1;
                taller = true;  // I grew taller. Alert my parent.
                break;

            case -1: // Was Left heavy, added to Left -> Now CRITICAL (-2)
                leftBalance(root, taller); // Fix it. will update taller.
                break;
            }
        }
   }
}

int AVLTree::getHeight(Node *node)
{
    if(!node) return -1;
    int leftH = getHeight(node->LeftSon);
    int rightH = getHeight(node->RightSon);
    //return max height of children + 1 for current node:
    return ((leftH > rightH) ? leftH : rightH) + 1;
}

int AVLTree::balanceFactorOfNode(Node *root)
{
    if(!root) return 0;
    return  getHeight(root->RightSon) - getHeight(root->LeftSon);
}

#pragma endregion

#pragma region public funcs

    #pragma region cnstrctrs/dstrctrs

    AVLTree::AVLTree()
    {
        Root = nullptr;
    }

    AVLTree::AVLTree(int k)
    {
        insertNode(k);
    }

    AVLTree::~AVLTree()
    {
        if(Root != nullptr)
        destroyTree(Root);
    }


    #pragma endregion

    void AVLTree::insertNode(int key)
    {
        bool taller = false;
        addNodeToTree(Root, key , taller);
    }

    void AVLTree::deleteNode(int key)
    {
    }

    void AVLTree::printTree()
    {
    }

#pragma endregion