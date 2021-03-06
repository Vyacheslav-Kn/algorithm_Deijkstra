#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

struct graph {
	int size_num;			// number of edges
	int edge_num;			// number of verges
	int** a;
};

graph* read(const char* path) {

	graph* graph1 = new graph;

	ifstream infile(path);
	if (!infile) {
		cout << "Reading error!" << endl;
		return NULL;
	}

	char ch[2];
	infile >> ch[0];
	ch[1] = '\0';
	graph1->edge_num = atoi(ch);
	cout << "Number of verges: " << graph1->edge_num << endl;

	infile.seekg(4, ios::beg);
	infile >> ch[0];
	ch[1] = '\0';
	graph1->size_num = atoi(ch);
	cout << "Number of edges:  " << graph1->size_num << endl;

	int check = graph1->size_num*graph1->edge_num;
	char* sh = new char[2];
	int* mas = new int[graph1->size_num*graph1->edge_num]; int k = 0;
	infile.seekg(8, ios::beg);

	char* buf = new char[check];
	while (!infile.eof()) {
		infile.getline(buf, check);
		for (int i = 0; i < graph1->size_num; i++) {
			sh[0] = buf[i * 2];
			sh[1] = '\0';
			int num = atoi(sh);
			mas[k] = num; k++;
		}
	}

	graph1->a = new int*[graph1->edge_num];
	for (int i = 0; i < graph1->edge_num; i++) {
		graph1->a[i] = new int[graph1->size_num];
	}

	int l = 0;
	for (int i = 0; i < graph1->edge_num; i++)
	{
		for (int j = 0; j < graph1->size_num; j++)
			graph1->a[i][j] = mas[l++];
	}

	return graph1;

}


void clear_memory(graph* graph) {

	for (int i = 0; i < graph->edge_num; i++) { delete[] graph->a[i]; }
	delete[] graph->a;

	cout << "Memory is clear!" << endl;
}


void graph_show(graph* graph) {
	cout << "           ";
	for (int s = 0; s < graph->size_num; s++) { cout << s + 1 << " "; }
	cout << endl;
	for (int i = 0; i < graph->edge_num; i++) {
		cout << "Verge " << i + 1 << " :  ";
		for (int j = 0; j < graph->size_num; j++) {
			cout << graph->a[i][j] << " ";
		}
		cout << endl;
	}
}


void algoritm_Dijkstra(int** matr_ed, int n, int yzel) {

	int temp = 0;
	int minindex = 0, min = 0;

	int* d = new int[n];
	int* v = new int[n];

	for (int i = 0; i < n; i++)
	{
		d[i] = 1000;
		v[i] = 1;
	}

	cout << "Input starting edge: " << yzel << endl;
	d[yzel - 1] = 0;

	for (int i = 0; i < n; i++) {
		minindex = 1000;
		min = 1000;
		for (int i = 0; i < n; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 1000)
		{
			for (int i = 0; i < n; i++)
			{
				if (matr_ed[minindex][i] > 0)
				{
					temp = min + matr_ed[minindex][i];
					if (temp < d[i])
						d[i] = temp;
				}
			}
			v[minindex] = 0;
		}
	}

	for (int i = 0; i < n; i++) { cout << d[i] << " "; }
	cout << endl;

	delete[] d;
	delete[] v;
}


int** step_to_Dijkstra(graph* graph) {

	int** mas = new int*[graph->size_num];
	for (int i = 0; i < graph->size_num; i++) {
		mas[i] = new int[graph->size_num];
	}

	for (int i = 0; i < graph->size_num; i++) {
		for (int j = 0; j < graph->size_num; j++) {
			mas[i][j] = 0;
		}
	}
		int p[2]; int k = 0;

		for (int i = 0; i < graph->edge_num; i++)
		{
			for (int j = 0; j < graph->size_num; j++) {
				if (graph->a[i][j] != 0) {
					p[k] = j;
					k++;
				}
			}
			int l1 = p[0]; int l2 = p[1];
			mas[l1][l2] = 1 + rand() % 10;
			mas[l2][l1] = mas[l1][l2];
			cout << "Verge price " << l1 + 1 << l2 + 1 << " (" << l2 + 1 << l1 + 1 << ") : " << mas[l1][l2];
			cout << endl;
			k = 0;
		}

	return mas;
}


void test(const char* path, int yzel) {

	int n = 0; int** prev = new int*;

	graph* gr = read(path);
	n = gr->size_num;
	graph_show(gr);
	prev = step_to_Dijkstra(gr);
	algoritm_Dijkstra(prev, n, yzel);
	clear_memory(gr);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Test 1: " << endl;
	test("graf1.txt", 1);
	cout << endl;
	cout << "Test 2: " << endl;
	test("graf2.txt", 2);
	cout << endl;
	cout << "Test 3: " << endl;
	test("graf3.txt", 3);
	cout << endl;
	cout << "Test 4: " << endl;
	test("graf4.txt", 4);
	cout << endl;
	cout << "Test 5: " << endl;
	test("graf5.txt", 5);
	cout << endl;

	system("pause");
	return 0;
}
