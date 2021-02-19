#include <iostream>
#include <chrono>
#include <ctime>
#include <windows.h>

using namespace std;

struct l_item

{
	int elem;
	l_item *Pred, *Next;

};

class DL_list
{
public:
	void Create(int N)
	{
		l_item *Curr = 0, *Next = 0;

		for (int i = 0; i < N; i++)
		{
			Curr = new l_item;

			Curr->Next = Next;

			if (Next)
				Next->Pred = Curr;

			Next = Curr;
		}
		Curr->Pred = 0;

		Beg = Curr;
	}

	void Init(int N)
	{
		l_item *Curr = Beg;

		for (int i = 0; i < N; i++)
		{
			Curr->elem = i;
			Curr = Curr->Next;
		}
	}

	l_item* InsItem(int num, int elem, int N)
	{
		l_item *Item = new l_item;

		if (!num || !Beg)
		{
			Beg->Pred = Item;
			Item->Pred = 0;
			Item->Next = Beg;
			Beg = Item;

			Item->elem = elem;

			return Item;
		}

		l_item *PredItem = Beg;

		if (num == N)
		{
			while (PredItem->Next && (num--))
				PredItem = PredItem->Next;

			Item->Pred = PredItem;
			Item->Next = 0;
			PredItem->Next = Item;

			Item->elem = elem;

			return Item;
		}
		else
		{
			num--;
			while (PredItem->Next && (num--))
				PredItem = PredItem->Next;

			Item->Pred = PredItem;
			PredItem->Next->Pred = Item;
			Item->Next = PredItem->Next;
			PredItem->Next = Item;

			Item->elem = elem;

			return Item;
		}
	}

	l_item* Item(int num)
	{
		l_item *Temp = Beg;

		while (Temp && (num--))
			Temp = Temp->Next;

		return Temp;
	}

	void DelItem(int num, int N)
	{
		if (num >= N)
			return;

		l_item *Item = Beg;

		if (!num)
		{
			Item = Beg->Next;
			delete Beg;
			Beg = Item;
			Beg->Pred = 0;

			return;
		}

		if (num < N - 1)
		{

			while (Item && (--num))
				Item = Item->Next;

			l_item *DelItem = Item->Next;
			Item->Next = DelItem->Next;
			Item->Next->Pred = Item;

			delete DelItem;
		}
		else
		{
			while (Item && (--num))
				Item = Item->Next;

			l_item *DelItem = Item->Next;
			Item->Next = DelItem->Next;

			delete DelItem;
		}
	}

	void Output()
	{
		l_item *Curr = Beg;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		while (Curr)
		{
			cout << Curr->elem << " ";
			Curr = Curr->Next;
		}
		cout << "--> List" << endl;
	}

private:
	l_item * Beg;
};



class D_Array
{
public:
	void Create(int N)
	{
		ArrPoint = new int[N];
	}

	void Init(int N)
	{
		for (int i = 0; i < N; i++)
			ArrPoint[i] = i;
	}

	void InsItem(int N, int num, int elem)
	{
		int *Res = new int[N + 1], curr = 0;

		for (int i = 0; i < N + 1; i++)
			if (num == i)
				Res[i] = elem;
			else
			{
				Res[i] = ArrPoint[curr];
				curr++;
			}

		delete[] ArrPoint;

		ArrPoint = Res;
	}

	int Item(int num)
	{
		return ArrPoint[num];
	}

	void DelItem_Array(int N, int num)
	{
		int *Res = new int[N];
		int curr = 0;
		for (int i = 0; i < N + 1; i++)
		{
			if (i != num)
			{
				Res[curr] = ArrPoint[i];
				curr++;
			}
		}
		delete[] ArrPoint;

		ArrPoint = Res;
	}

	void Output(int N)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int i = 0; i < N; i++)
			cout << ArrPoint[i] << " ";
		cout << "--> Array" << endl;
	}

private:
	int *ArrPoint;
};

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int N, num, elem;
	cout << "Enter N: " << endl;
	cin >> N;

	cout << endl;

	//Создание

	D_Array Array;

	auto begin = std::chrono::steady_clock::now();
	Array.Create(N);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	Array.Init(N);
	Array.Output(N);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms.count() << " ns" << endl;

	cout << endl;

	DL_list List;

	auto begin1 = std::chrono::steady_clock::now();
	List.Create(N);
	auto end1 = std::chrono::steady_clock::now();
	auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);

	List.Init(N);
	List.Output();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms1.count() << " ns" << endl;

	cout << endl;

	//Вставка нового элемента

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter number of element you want to insert:" << endl;
	cin >> num;
	cout << "Enter element:" << endl;
	cin >> elem;

	cout << endl;

	auto begin2 = std::chrono::steady_clock::now();
	Array.InsItem(N, num, elem);
	auto end2 = std::chrono::steady_clock::now();
	auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);

	Array.Output(N + 1);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms2.count() << " ns" << endl;


	cout << endl;

	auto begin3 = std::chrono::steady_clock::now();
	List.InsItem(num, elem, N);
	auto end3 = std::chrono::steady_clock::now();
	auto elapsed_ms3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - begin3);

	List.Output();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms3.count() << " ns" << endl;

	cout << endl;

	//Получение элемента

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter number of element you want:" << endl;
	cin >> num;

	cout << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	auto begin4 = std::chrono::steady_clock::now();
	cout << "The element of array is " << Array.Item(num) << endl;
	auto end4 = std::chrono::steady_clock::now();
	auto elapsed_ms4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - begin4);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms4.count() << " ns" << endl;

	cout << endl;

	auto begin5 = std::chrono::steady_clock::now();
	cout << "The element of list is " << List.Item(num)->elem << endl;
	auto end5 = std::chrono::steady_clock::now();
	auto elapsed_ms5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end5 - begin5);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms5.count() << " ns" << endl;

	cout << endl;

	//Удаление элемента из массива

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter the number you want to delete:" << endl;
	cin >> num;

	cout << endl;

	auto begin6 = std::chrono::steady_clock::now();
	Array.DelItem_Array(N, num);
	auto end6 = std::chrono::steady_clock::now();
	auto elapsed_ms6 = std::chrono::duration_cast<std::chrono::nanoseconds>(end6 - begin6);

	Array.Output(N);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms6.count() << " ns" << endl;

	cout << endl;

	auto begin7 = std::chrono::steady_clock::now();
	List.DelItem(num, N + 1);
	auto end7 = std::chrono::steady_clock::now();
	auto elapsed_ms7 = std::chrono::duration_cast<std::chrono::nanoseconds>(end7 - begin7);

	List.Output();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Work time: " << elapsed_ms7.count() << " ns" << endl;









}
