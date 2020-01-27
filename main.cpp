#include "graph.h"
#include<fstream>


int main()
{
	int pointA, pointB;
	Graph test;
	string file;
	test.loadMap(file);
	
	test.displayGraph();

	cout << "Pick point A: ";

	cin>> pointA;
	cout << "Pick B:";

	cin >> pointB;

	test.findPath(pointA, pointB);




	return 0;
}