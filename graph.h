#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef _GRAPH_H_
#define _GRAPH_H_


enum STATE {UNVISITED, OPEN, CLOSED};

struct Node
{
	float x;
	float y;

	vector<int> adj;
	STATE state;

	int index;
	Node* prev;
	float f;
	float g;
	float h;
};

const int size = 10;
class heap
{

public:

	heap();
	~heap();

void insert(Node*);
Node* remove();
void heapSort();

void heapUp(int);
void heapDown(int);
void swap(Node*& num1, Node*&  num2);
void Update(Node* Nei);
bool empty();
void print();


private:

Node* array[size];
int len;


};


class Graph
{
public:

	Graph();
	~Graph();

	void loadMap(string file);
	void nodeList();
	void findPath(int start, int goal);
	void reconstructPath(int goal);
	void displayGraph();


	float distance(Node* i, Node* j);



private:

	vector<Node*> nodes;
	int num_nodes;
	heap* myHeap;

};







#endif