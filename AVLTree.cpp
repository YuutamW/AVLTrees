#include "AVLTree.hpp"

#pragma region private funcs

AVLTree::Node &AVLTree::rightBalance(Node *&node, bool &taller)
{
    Node *rs = node->RightSon; //right subtree of root
    Node *ls;                  //left subtree ofright subtree

    switch (rs->BF)
    {
    case 1:
        node->BF = rs->BF = 0;
        *node = rotateLeft(node);
        break;
    case 0:
        std::cout<<"Error! tree is already balanced!"<<std::endl;
    case -1:
        ls = rs->LeftSon;
        switch (ls->BF)
        {
        case 1:
            node->BF = -1;
            rs->BF = 0;
            break;
        case 0:
            std::cout<<"Error! tree is already balanced!"<<std::endl;
            break;
        case -1:
            node->BF = 0;
            rs->BF = 1;
            break;
        }
        ls->BF = 0;
        *node->RightSon = rotateRight(rs);
        *node = rotateLeft(node);
        taller = false;
        break;
    }
    return *node;
}

AVLTree::Node &AVLTree::leftBalance(Node *&node, bool &taller)
{
    // TODO: insert return statement here
}

AVLTree::Node &AVLTree::rotateRight(Node *&node)
{
    // TODO: insert return statement here
}

AVLTree::Node &AVLTree::rotateLeft(Node *&node)
{
    // TODO: insert return statement here
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

void AVLTree::addNodeToTree(Node *&root, int key ,bool taller)
{
    if(!root)
    {
        root = new Node(key);
        taller = true;
        return;
    }
    else if(root->Key == key)
    {
        std::cout<<"ERROR! Duplicate Key in Tree!"<<std::endl;
        return;
    }
    else if(key > root->Key)
    {
        addNodeToTree(root->LeftSon,key,taller);
        if(taller)  //left subtree is taller
        {
            switch (root->BF)
            {
            case -1:    //node was left heavy
                *root = leftBalance(root,taller);
                break;
            case 0: //node is now left heavy
                root->BF = -1;
                break;
            case 1: //node now has balanced height
                root->BF = 0;
                taller = false;
                break; 
            }
        }
    }else {
        addNodeToTree(root->RightSon, key , taller);
        if(taller)  //right sub tree is taller
        {
            switch (root->BF)
            {
                case 1: //node was right high
                    *root = rightBalance(root,taller);
                    break;
                case 0: //node is now right high
                    root->BF = 1;
                    break;
                case -1:    //node now has balanced height
                    root->BF = 0;
                    taller = false;
                    break;
            }
        }
    }
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
        addNodeToTree(Root,k,false);
    }

    AVLTree::~AVLTree()
    {
        if(Root != nullptr)
        destroyTree(Root);
    }


    #pragma endregion

    void AVLTree::insertNode(int key)
    {

    }

    void AVLTree::deleteNode(int key)
    {
    }

    void AVLTree::printTree()
    {
    }

#pragma endregion