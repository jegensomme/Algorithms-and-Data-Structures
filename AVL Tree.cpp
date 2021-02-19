#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

class AVLTree;

class avl_node
{
public:
	int elem;
	int level;
	avl_node() : left(0), right(0), elem(0), level(1) {}
	friend class AVL_Tree;
private:
	avl_node *left;
	avl_node *right;
};

class AVL_Tree
{
public:
	AVL_Tree() : Head(0){}
	~AVL_Tree();
	void InOrder();
	void InsertNode(int elem);
	void DeleteNode(int elem);
	avl_node* GetNode(int elem);
private:
	avl_node *Head;
	void Destroy(avl_node *Root);
	void InOrder(avl_node *Node);
	int GetLevel(avl_node *Node);
	int GetBalance(avl_node *Node);
	void UpdateLevel(avl_node *Node);
	avl_node* Balance(avl_node *Node);
	avl_node* RotateRight(avl_node *Node);
	avl_node* RotateLeft(avl_node *Node);
	avl_node* RotateRightLeft(avl_node *Node);
	avl_node* RotateLeftRight(avl_node *Node);
	avl_node* InsertNode(avl_node *Node, int elem);
	avl_node* DeleteNode(avl_node *Node, int elem);
	avl_node* Minimum(avl_node *Node);
	avl_node* DeleteMin(avl_node *Node);
};

void AVL_Tree::Destroy(avl_node *Root)
{
	if (Root)
	{
		Destroy(Root->left);
		Destroy(Root->right);

		delete Root;
	}
}

AVL_Tree::~AVL_Tree()
{
	Destroy(Head);
}

void AVL_Tree::InOrder()
{
	InOrder(Head);
}

void AVL_Tree::InOrder(avl_node *Node)
{
	if (!Node)
        return;

	InOrder(Node->left);
	cout << Node->elem << " ";
	InOrder(Node->right);
}

int AVL_Tree::GetLevel(avl_node *Node)
{
	if (Node)
		return Node->level;
	else
		return 0;
}

int AVL_Tree::GetBalance(avl_node *Node)
{
	return (GetLevel(Node->right) - GetLevel(Node->left));
}

void AVL_Tree::UpdateLevel(avl_node *Node)
{
	int lleft = GetLevel(Node->left);
	int lright = GetLevel(Node->right);

	if (lleft > lright)
        Node->level = lleft;
	else
        Node->level = lright;

	Node->level++;
}

avl_node* AVL_Tree::Balance(avl_node *Node)
{
	UpdateLevel(Node);

	if (GetBalance(Node) == 2)
	{
		if (GetBalance(Node->right) < 0)
			return RotateRightLeft(Node);
		else
			return RotateLeft(Node);
	}
	if (GetBalance(Node) == -2)
	{
		if (GetBalance(Node->left) > 0)
			return RotateLeftRight(Node);
		else
			return RotateRight(Node);
	}

	return Node;
}

avl_node* AVL_Tree::RotateRight(avl_node *Node)
{
	avl_node *Temp = Node->left;
	Node->left = Temp->right;
	Temp->right = Node;
	UpdateLevel(Node);
	UpdateLevel(Temp);

	return Temp;
}

avl_node* AVL_Tree::RotateLeft(avl_node *Node)
{
	avl_node *Temp = Node->right;
	Node->right = Temp->left;
	Temp->left = Node;
	UpdateLevel(Node);
	UpdateLevel(Temp);

	return Temp;
}

avl_node* AVL_Tree::RotateRightLeft(avl_node *Node)
{
	Node->right = RotateRight(Node->right);

	return RotateLeft(Node);
}

avl_node* AVL_Tree::RotateLeftRight(avl_node *Node)
{
	Node->left = RotateLeft(Node->left);

	return RotateRight(Node);
}

void AVL_Tree::InsertNode(int elem)
{
	Head = InsertNode(Head, elem);
}

avl_node* AVL_Tree::InsertNode(avl_node *Node, int elem)
{
	if (!Node)
	{
		avl_node *Temp = new avl_node;
		Temp->elem = elem;
		return Temp;
	}

	if (elem < Node->elem)
		Node->left = InsertNode(Node->left, elem);
	else
		Node->right = InsertNode(Node->right, elem);

	return Balance(Node);
}

void AVL_Tree::DeleteNode(int elem)
{
	Head = DeleteNode(Head, elem);
}

avl_node* AVL_Tree::DeleteNode(avl_node *Node, int elem)
{
	if (!Node)
        return 0;
	else
	{
		if (elem < Node->elem)
            Node->left = DeleteNode(Node->left, elem);
		else
		{
			if (elem > Node->elem)
                Node->right = DeleteNode(Node->right, elem);
			else
			{
				avl_node *Right = Node->right;
				avl_node *Left = Node->left;
				delete Node;

				if (!Right)
                    return Left;

				avl_node *Min = Minimum(Right);
				Min->right = DeleteMin(Right);
				Min->left = Left;

				return Balance(Min);
			}

		}

		return Balance(Node);
	}
}

avl_node* AVL_Tree::Minimum(avl_node *Node)
{
	if (!Node->left)
        return Node;
	else
        return Minimum(Node->left);
}

avl_node* AVL_Tree::DeleteMin(avl_node *Node)
{
	if (!Node->left)
        return Node->right;

	Node->left = DeleteMin(Node->left);

	return Balance(Node);
}

avl_node* AVL_Tree::GetNode(int elem)
{
	avl_node *Node = Head;

	while (Node)
	{
		if (elem == Node->elem)
            return Node;
		else
		{
			if (elem < Node->elem)
                Node = Node->left;
			else
                Node = Node->right;
		}
	}

	return 0;
}

enum nodeColor {black, red};

class RB_Tree;

class rb_node
{
public:
	nodeColor color;
	int elem;
	rb_node() : left(0), right(0), parent(0), elem(0), color(black) {}
	rb_node(rb_node *left, rb_node *right, rb_node *parent, nodeColor color, int elem)
		: left(left), right(right), parent(parent), elem(elem), color(color) {}
	friend class RB_Tree;
private:

	rb_node *left;
	rb_node *right;
	rb_node *parent;
};

class RB_Tree
{
public:
	RB_Tree() : Head(0) {}
	~RB_Tree();
	void Destroy(rb_node *Root);
	void InOrder();
	void InOrder(rb_node *Node);
	void RotateLeft(rb_node *Node);
	void RotateRight(rb_node *Node);
	rb_node* InsertNode(int elem);
	void FixInsertion(rb_node *Node);
	rb_node* GetNode(int elem);
	void DeleteNode(int elem);
	rb_node* DeleteNode(rb_node *Node, int elem);
	void FixDelete(rb_node *Node);
	rb_node* Minimum(rb_node *Node);
	rb_node* DeleteMin(rb_node *Node);
	void FixNil(rb_node *Node);
private:
	rb_node *Head;
	rb_node Nil;
};

void RB_Tree::Destroy(rb_node *Root)
{
	if (Root != 0)
	{
		Destroy(Root->left);
		Destroy(Root->right);
		delete Root;
	}
}

RB_Tree::~RB_Tree()
{
	Destroy(Head);
}

void RB_Tree::InOrder()
{
	InOrder(Head);
}

void RB_Tree::InOrder(rb_node *Node)
{
	if (!Node)
		return;

	InOrder(Node->left);

	cout << Node->elem;

	if (Node->color == black)
		cout << "(b) ";
	else
		cout << "(r) ";

	InOrder(Node->right);
}

void RB_Tree::RotateLeft(rb_node *Node)
{
	rb_node *Right = Node->right;
	Node->right = Right->left;

	if (Right->left)
		Right->left->parent = Node;
	if (Right)
		Right->parent = Node->parent;
	if (Node->parent)
	{
		if (Node == Node->parent->left)
			Node->parent->left = Right;
		else
			Node->parent->right = Right;
	}
	else
		Head = Right;

	Right->left = Node;

	if (Node)
		Node->parent = Right;
}

void RB_Tree::RotateRight(rb_node *Node)
{
	rb_node *Left = Node->left;

	if (Left)
		Node->left = Left->right;
	if (Left->right)
		Left->right->parent = Node;
	if (Left)
		Left->parent = Node->parent;
	if (Node->parent)
	{
		if (Node == Node->parent->right)
			Node->parent->right = Left;
		else
			Node->parent->left = Left;
	}
	else
		Head = Left;

	Left->right = Node;

	if (Node)
		Node->parent = Left;
}

rb_node* RB_Tree::InsertNode(int elem)
{
	rb_node *Node = Head;
	rb_node *Parent = 0;
	rb_node *Temp;

	while (Node)
	{
		if (elem == Node->elem)
			return Node;

		Parent = Node;

		if (elem < Node->elem)
			Node = Node->left;
		else
			Node = Node->right;
	}

	Temp = new rb_node;
	Temp->elem = elem;
	Temp->parent = Parent;
	Temp->left = 0;
	Temp->right = 0;
	Temp->color = red;

	if (Parent)
	{
		if (elem < Parent->elem)
			Parent->left = Temp;
		else
			Parent->right = Temp;
	}
	else
		Head = Temp;

	FixInsertion(Temp);

	return Temp;
}

void RB_Tree::FixInsertion(rb_node *Node)
{
	while (Node != Head && Node->parent->color == red)
	{
		if (Node->parent == Node->parent->parent->left)
		{
			rb_node *Uncle = Node->parent->parent->right;

			if (!Uncle)
				Uncle = &Nil;

			if (Uncle->color == red)
			{
				Node->parent->color = black;
				Uncle->color = black;
				Node->parent->parent->color = red;
				Node = Node->parent->parent;
			}
			else
			{
				if (Node == Node->parent->right)
				{
					Node = Node->parent;
					RotateLeft(Node);
				}

				Node->parent->color = black;
				Node->parent->parent->color = red;
				RotateRight(Node->parent->parent);
			}
		}
		else
		{
			rb_node *Uncle = Node->parent->parent->left;

			if (!Uncle)
				Uncle = &Nil;
			if (Uncle->color == red)
			{
				Node->parent->color = black;
				Uncle->color = black;
				Node->parent->parent->color = red;
				Node = Node->parent->parent;
			}
			else
			{
				if (Node == Node->parent->left)
				{
					Node = Node->parent;
					RotateRight(Node);
				}
				Node->parent->color = black;
				Node->parent->parent->color = red;
				RotateLeft(Node->parent->parent);
			}
		}
	}

	Head->color = black;
}

rb_node* RB_Tree::GetNode(int elem)
{
	rb_node *Node = Head;

	while (Node)
	{
		if (elem == Node->elem)
			return Node;
		else
		{
			if (elem < Node->elem)
				Node = Node->left;
			else
				Node = Node->right;
		}
	}

	return 0;
}

void RB_Tree::DeleteNode(int elem)
{
	rb_node *Node = GetNode(elem);
	rb_node *Temp1;
	rb_node *Temp2;

	if (Node == 0)
		return;

	if (!Node->left || !Node->right)
		Temp2 = Node;
	else
	{
		Temp2 = Node->right;

		while (Temp2->left)
			Temp2 = Temp2->left;
	}

	if (Temp2->left)
		Temp1 = Temp2->left;
	else
	{
		if (Temp2->right)
			Temp1 = Temp2->right;
		else
            Temp1 = new rb_node(0, 0, Temp2->parent, black, 0);;
	}

	if (Temp1)
		Temp1->parent = Temp2->parent;
	if (!Temp2->parent || Temp2 == Head)
		Head = Temp1;
	else
	{
		if (Temp2 == Temp2->parent->left)
			Temp2->parent->left = Temp1;
		else
			Temp2->parent->right = Temp1;
	}

	if (Temp2 != Node)
		Node->elem = Temp2->elem;
	if (Temp2->color == black)
		FixDelete(Temp1);
	if (Temp1 != NULL && !Temp1->elem)
	{
		if (Temp1 == Temp1->parent->left)
			Temp1->parent->left = 0;
		else
			Temp1->parent->right = 0;

		delete Temp1;
	}
}

rb_node* RB_Tree::DeleteNode(rb_node *Node, int elem)
{
	if (!Node)
		return 0;
	else
	{
		if (elem < Node->elem)
			Node->left = DeleteNode(Node->left, elem);
		else
		{
			if (elem > Node->elem)
				Node->right = DeleteNode(Node->right, elem);
			else
			{
				rb_node *Right = Node->right;
				rb_node *Left = Node->left;
				delete Node;

				if (!Right)
				{
					FixDelete(Left);

					return Left;
				}

				rb_node *Min = Minimum(Right);
				Min->right = DeleteMin(Right);
				Min->left = Left;
				FixDelete(Min);

				return Min;
			}

		}

		FixDelete(Node);

		return Node;
	}
}

void RB_Tree::FixDelete(rb_node *Node)
{
	while (Node != Head && Node->color == black)
	{
		if (Node == Node->parent->left)
		{
			rb_node *Brother = Node->parent->right;

			if (Brother->color == red)
			{
				Brother->color = black;
				Node->parent->color = red;
				RotateLeft(Node->parent);
				Brother = Node->parent->right;
			}
			if (!Brother->left)
				Brother->left = &Nil;
			if (!Brother->right)
				Brother->right = &Nil;
			if ((!Brother->left && !Brother->right) || (Brother->left->color == black && Brother->right->color == black))
			{
				Brother->color = red;
				Node = Node->parent;
			}
			else
			{
				if (Brother->right->color == black)
				{
					Brother->left->color = black;
					Brother->color = red;
					RotateRight(Brother);
					Brother = Node->parent->right;
				}

				Brother->color = Node->parent->color;
				Node->parent->color = black;
				Brother->right->color = black;
				RotateLeft(Node->parent);
				Node = Head;
			}
		}
		else
		{
			rb_node *Brother = Node->parent->left;
			if (Brother->color == red)
			{
				Brother->color = black;
				Node->parent->color = red;
				RotateLeft(Node->parent);
				Brother = Node->parent->left;
			}
			if (Brother->left == NULL)
			{
				Brother->left = &Nil;
			}
			if (Brother->right == NULL)
			{
				Brother->right = &Nil;
			}
			if ((!Brother->left && !Brother->right) || (Brother->left->color == black && Brother->right->color == black))
			{
				Brother->color = red;
				Node = Node->parent;
			}
			else
			{
				if (Brother->left->color == black)
				{
					Brother->right->color = black;
					Brother->color = red;
					RotateLeft(Brother);
					Brother = Node->parent->left;
				}

				Brother->color = Node->parent->color;
				Node->parent->color = black;
				Brother->right->color = black;
				RotateRight(Node->parent);
				Node = Head;
			}
		}
	}

	FixNil(Head);
	Node->color = black;
}

void RB_Tree::FixNil(rb_node *Node)
{
	if (!Node)
		return;
	if (Node->right == &Nil)
		Node->right = 0;
	if (Node->left == &Nil)
		Node->left = 0;

	FixNil(Node->left);
	FixNil(Node->right);
}

rb_node* RB_Tree::Minimum(rb_node *Node)
{
	if (!Node->left)
		return Node;
	else
		return Minimum(Node->left);
}

rb_node* RB_Tree::DeleteMin(rb_node *Node)
{
	if (!Node->left)
		return Node->right;

	Node->left = DeleteMin(Node->left);

	return Node;
}

int main()
{
    srand(time(0));

    int elem;
    int N;
    cout << "Enter number of elements" << endl;
    cin >> N;
    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "AVL Tree:" << endl << endl;

	AVL_Tree Tree1;
	for (int i = 0; i < N; i++)
        Tree1.InsertNode(1 + rand() % 300);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree1.InOrder();
	cout << " ---> In-Order"  << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want to insert: " << endl;
	cin >> elem;

	Tree1.InsertNode(elem);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree1.InOrder();
	cout << " ---> In-Order"  << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want: " << endl;
	cin >> elem;

	avl_node *Node1 = Tree1.GetNode(elem);
	if (Node1)
        cout << "Element is " << Node1->elem << endl << endl;
    else
        cout << "Element does not exist" << endl << endl;

    cout << "Enter element you want to delete: " << endl;
	cin >> elem;

	Tree1.DeleteNode(elem);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree1.InOrder();
	cout << " ---> In-Order"  << endl << endl;
////////////////////////////////////////////////////////

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "RB Tree:" << endl << endl;

    RB_Tree Tree2;
    for (int i = 0; i < N; i++)
        Tree2.InsertNode(1 + rand() % 300);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree2.InOrder();
	cout << " ---> In-Order"  << endl << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want to insert: " << endl;
	cin >> elem;

	Tree2.InsertNode(elem);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree2.InOrder();
	cout << " ---> In-Order"  << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Enter element you want: " << endl;
	cin >> elem;

	rb_node *Node2 = Tree2.GetNode(elem);
	if (Node2)
        cout << "Element is " << Node2->elem << endl << endl;
    else
        cout << "Element does not exist" << endl << endl;

    cout << "Enter element you want to delete: " << endl;
	cin >> elem;

	Tree2.DeleteNode(elem);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    Tree2.InOrder();
	cout << " ---> In-Order"  << endl << endl;
}
