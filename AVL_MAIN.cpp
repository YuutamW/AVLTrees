#include "AVLTree.hpp"


int main()
{
    using namespace std;
    AVLTree Tree;
    cout<<"Tree Created"<<endl;
    string buffer;
    int choice , KEY;
    while (1)
    {
        cout<<"Choose option:1.insert 2.deletekey   3.exit"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Insert Key:"<<endl;
            cin>>KEY;
            Tree.insertNode(KEY);
            Tree.printTree();
            break;
        case 2: 
            cout<<"Insert Key to delete:"<<endl;
            cin>>KEY;
            Tree.deleteNode(KEY);
            Tree.printTree();
            break;
        case 3:
            cout<<"Exiting program:"<<endl;
            return 0;
        default:
            cout<<"ERROR: Incorrect input!"<<endl;
            continue;
        }
    }
    return 0;
}