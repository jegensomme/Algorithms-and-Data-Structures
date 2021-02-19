#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <vector>
#include <ctime>
#include <time.h>
#include <Windows.h>

using namespace std;

class MSTree;

class Graph
{
public:
	void Generate(int vert_num, bool mode, int edge_num);
	friend class MSTree;
private:
    int** tab;
	int vertex_num;
	void RandomGenerate(int edge_num);
	void ManualInput();
};

void Graph::Generate(int vert_num, bool mode, int edge_num)
{
    vertex_num = vert_num;

    if (!mode)
        RandomGenerate(edge_num);
    else
        ManualInput();
}

void Graph::RandomGenerate(int edge_num)
{
	srand(time(NULL));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("\nGraph generation...\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	tab = new int*[vertex_num];
	for (int i = 0; i < vertex_num; i++)
    {
        tab[i] = new int[vertex_num];
        for (int j = 0; j < vertex_num; j++)
            tab[i][j] = 0;
    }

    int point;
	for (int i = 0; i < vertex_num - 1; i++)
    {
        for (int j = 0; j < edge_num; j++)
        {
            point = i + 1 + rand() % (vertex_num - i - 1);
            if (!tab[i][point])
            {
                tab[i][point] = 1 + rand() % 200;
                tab[point][i] = tab[i][point];
            }
        }
    }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("Complete");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Graph::ManualInput()
{
    tab = new int*[vertex_num];
	for (int i = 0; i < vertex_num; i++)
    {
        tab[i] = new int[vertex_num];
        for (int j = 0; j < vertex_num; j++)
            tab[i][j] = 0;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("\n\nEnter the graph tab:\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 0; i < vertex_num; i++)
    {
        for (int j = i; j < vertex_num; j++)
        {
            printf("(%d, %d):", i, j);
            cin >> tab[i][j];
            tab[j][i] = tab[i][j];
        }
    }
}

class MSTree
{
public:
    MSTree(Graph gr) : graph(gr){}
	void Generate();
	void Output();
private:
    Graph graph;
	vector<int*> tree;
	vector<int> vertId;
	unsigned int alg_time;
	void CountEdges(vector<int*> &edges);
	void SortEdges(int left, int right, vector<int*> &vect);
	void BuildTree(vector<int*> edges);
};

void MSTree::Generate()
{
    vector<int*> edges;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("\n\nMinimum spanning tree generation...\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CountEdges(edges);
	if (edges.size())
    {
        alg_time = clock();
	    SortEdges(0, edges.size() - 1, edges);
        for (int i = 0; i < graph.vertex_num; i++)
		vertId.push_back(i);
        BuildTree(edges);
        alg_time = clock() - alg_time;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	    printf("Complete");
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	    printf("\n\nThe number of edges in the old tree: %d\n", edges.size());
    }
}

void MSTree::Output()
{
    if (!tree.size())
    {
        printf("\nThe graph has not edges\n");
        return;
    }
    for (int i = 0; i < graph.vertex_num; i++)
		if (vertId[i] != vertId[0])
        {
            printf("\nError! The tree is not built\n");
            return;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        printf("\nResult:\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        for (int i = 0; i < tree.size(); i++)
        printf("(%4d, %d) = %d\n", (int)tree[i][0], (int)tree[i][1], (int)tree[i][2]);
        printf("The number of edges in the spanning tree: %d\n", tree.size());
        printf("Algorithm runtime: %f second\n", alg_time / 1000.0);
}

void MSTree::CountEdges(vector<int*> &edges)
{
    int *edge;

    for (int i = 0; i < graph.vertex_num - 1; i++)
    {
		for (int j = i + 1; j < graph.vertex_num; j++)
		{
			if (graph.tab[i][j])
            {
				edge = new int[3];
				edge[0] = i;
                edge[1] = j;
				edge[2] = graph.tab[i][j];
				edges.push_back(edge);
			}
		}
	}
}

void MSTree::SortEdges(int left, int right, vector<int*> &edges)
{
    if (right == left)
        return;
    if (right - left == 1)
        {
            if (edges[right][2] < edges[left][2])
            {
                int *temp;
                temp = edges[right];
                edges[right] = edges[left];
                edges[left] = temp;
            }

            return;
        }

    int middle = (right + left) / 2;

    SortEdges(left, middle, edges);
    SortEdges(middle + 1, right, edges);

    vector<int*> buf;
    int lcur = left;
    int rcur = middle + 1;
    int cur = 0;

    for (int i = 0; i < right - left + 1; i++)
    {
        if (lcur <= middle && rcur <= right)
        {
            if (edges[lcur][2] > edges[rcur][2])
            {
                buf.push_back(edges[rcur]);
                rcur++;
            }
            else
            {
                buf.push_back(edges[lcur]);;
                lcur++;
            }
        }
        else
        {
            if (lcur > middle)
            {
                buf.push_back(edges[rcur]);
                rcur++;
            }
            else
            {
                buf.push_back(edges[lcur]);;
                lcur++;
            }
        }
        cur++;
    }

    for (int i = 0; i < cur; i++)
        edges[i + left] = buf[i];
}

void MSTree::BuildTree(vector<int*> edges)
{
    int *edge;
    int i = 0;

    while ((tree.size() != graph.vertex_num - 1) && (i < edges.size()))
    {
        edge = edges[i];

        if (vertId[edge[0]] != vertId[edge[1]])
        {
			tree.push_back(edge);

			int col1 = vertId[edge[0]], col2 = vertId[edge[1]];
            for (int j = 0; j < graph.vertex_num; j++)
                if (vertId[j] == col2)
                    vertId[j] = col1;
		}
		i++;
    }
}




int main()
{
    bool mode;
    cout << "Select the mode(0 - random, 1 - manual)" << endl;
    cin >> mode;

    int vertex_num;
    int edge_num = 5;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Enter the number of vertices:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cin >> vertex_num;
    Graph graph;
    graph.Generate(vertex_num, mode, edge_num);

	MSTree ms_tree(graph);
	ms_tree.Generate();
	ms_tree.Output();

	_getch();
}
