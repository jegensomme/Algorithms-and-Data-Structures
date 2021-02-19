#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <windows.h>
#include <ctime>

using namespace std;

struct t_item
{
    int elem;
    t_item *left = 0, *right = 0, *parent = 0;
};

t_item* T_InsertNode(t_item *&Root, int elem)
{
    t_item *Curr = Root;
    t_item *Node = new t_item;
    t_item *Parent;

    while (Curr)
    {
        Parent = Curr;

        if (elem > Curr->elem)
            Curr = Curr->right;
        else if (elem < Curr->elem)
            Curr = Curr->left;
        else if (elem == Curr->elem)
        {
            return 0;
        }
    }

    if (Parent->elem > elem)
        Parent->left = Node;
    else if (Parent->elem < elem)
             Parent->right = Node;

    Node->elem = elem;
    Node->parent = Parent;
    Node->left = 0;
    Node->right = 0;

    return Node;
}

t_item* T_Node(t_item *Root, int elem)
{
    t_item *Curr = Root;

    while (Curr)
    {
        if (elem > Curr->elem)
            Curr = Curr->right;
        else if (elem < Curr->elem)
            Curr = Curr->left;
        else if (elem == Curr->elem)
        {
            return Curr;
        }
    }

    if (!Curr)
        return 0;
}

void T_DelNode(t_item *&Root, int elem)
{
    t_item *Curr = Root;
    t_item *DelNode;

    DelNode = T_Node(Root, elem);

    if (!DelNode->left && !DelNode->right)
    {
        if (DelNode->elem > DelNode->parent->elem)
            DelNode->parent->right = 0;
        else
            DelNode->parent->left = 0;

        delete DelNode;

        return;
    }

    if (DelNode->left == 0 || DelNode->right == 0)
    {
        if (DelNode->elem > DelNode->parent->elem)
            if (DelNode->left == 0)
            {
                DelNode->parent->right = DelNode->right;
                DelNode->right->parent = DelNode->parent;
                delete DelNode;

                return;
            }
            else
            {
                DelNode->parent->right = DelNode->left;
                DelNode->left->parent = DelNode->parent;
                delete DelNode;

                return;

            }
        else
            if (DelNode->left == 0)
            {
                DelNode->parent->left = DelNode->right;
                DelNode->right->parent = DelNode->parent;
                delete DelNode;

                return;
            }
            else
            {
                DelNode->parent->left = DelNode->left;
                DelNode->left->parent = DelNode->parent;
                delete DelNode;

                return;

            }
    }

    t_item *Node = DelNode->right;

    while (Node->left)
        Node = Node->left;

    if (Node->right)
    {
        if (Node->elem > Node->parent->elem)
        {
            Node->parent->right = Node->right;
        }
        else
            Node->parent->left = Node->right;

        Node->right->parent = Node->parent;
    }
    else
        Node->parent->left = 0;

    DelNode->elem = Node->elem;
    DelNode = Node;

    delete DelNode;
}

void T_InOrder(t_item *Root)
{
    t_item *Curr = Root;

	if (Curr)
	{
	   T_InOrder(Curr->left);
	   cout << Curr->elem << " ";
	   T_InOrder(Curr->right);
	}
}

void T_PreOrder(t_item *Root)
{
    t_item *Curr = Root;

	if (Curr)
	{
       cout << Curr->elem << " ";
	   T_PreOrder(Curr->left);
	   T_PreOrder(Curr->right);
	}
}

void T_PostOrder(t_item *Root)
{
    t_item *Curr = Root;

	if (Curr)
	{
       T_PostOrder(Curr->left);
	   T_PostOrder(Curr->right);
       cout << Curr->elem << " ";
	}
}

void T_LevelOrder(t_item *Root)
{
	queue<t_item*> q;
	q.push(Root);

	while (!q.empty())
	{
		t_item *Curr = q.front();
		q.pop();

		cout << Curr->elem << " ";

		if (Curr->left != 0)
		{
			q.push(Curr->left);
		}
		if (Curr->right != 0)
		{
			q.push(Curr->right);
		}
	}
}

int main()
{
    srand(time(NULL));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int N, elem;
	cout << "Enter N: " << endl;
	cin >> N;

	cout << endl;

	t_item *Tree = new t_item;
	Tree->elem = 1 + rand() % 200;

	for (int i = 1; i < N; i++)
        while(!T_InsertNode(Tree, 1 + rand() % 200));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    T_InOrder(Tree);
	cout << " ---> In-Order"  << endl;
	T_PreOrder(Tree);
	cout << " ---> Pre-Order"  << endl;
	T_PostOrder(Tree);
	cout << " ---> Post-Order"  << endl;
	T_LevelOrder(Tree);
	cout << " ---> Level-Order"  << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want to insert: " << endl;
	cin >> elem;

	if (!T_InsertNode(Tree, elem))
        cout << "This element already exists" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    T_InOrder(Tree);
	cout << " ---> In-Order"  << endl;
	T_PreOrder(Tree);
	cout << " ---> Pre-Order"  << endl;
	T_PostOrder(Tree);
	cout << " ---> Post-Order"  << endl;
	T_LevelOrder(Tree);
	cout << " ---> Level-Order"  << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want: " << endl;
	cin >> elem;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	t_item *Node = T_Node(Tree, elem);
	if (Node)
	    cout << "Element is " << Node->elem << endl << endl;
    else
        cout << "Element does not exist " << endl << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter element you want to delete: " << endl;
	cin >> elem;

	T_DelNode(Tree, elem);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    T_InOrder(Tree);
	cout << " ---> In-Order"  << endl;
	T_PreOrder(Tree);
	cout << " ---> Pre-Order"  << endl;
	T_PostOrder(Tree);
	cout << " ---> Post-Order"  << endl;
	T_LevelOrder(Tree);
	cout << " ---> Level-Order"  << endl << endl;


}
