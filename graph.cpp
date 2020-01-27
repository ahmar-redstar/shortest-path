#include "graph.h"
#include<fstream>
#include <stack>
#include <sstream>

Graph::Graph()
{
	myHeap = new heap;
}

Graph::~Graph()
{
	delete myHeap;
}
void Graph ::nodeList()
{
	for(int i = 0; i < num_nodes; i++)
	{
		
		nodes[i]-> f = 100000;
		nodes[i]-> g = 100000;
		nodes[i]-> h = 100000;
		nodes[i]->prev = NULL;
		nodes[i]->state = UNVISITED;
		nodes[i]-> index = i;
	}


}



void Graph::loadMap(string file)
{
	//string file;
	string line;
	fstream infile;
	int num;
	Node* newNode;

	cout << "Enter file Name\n";


	cin >> file;

	infile.open(file, ios::in);
	infile >> num_nodes;






	for (int i = 0; i < num_nodes; i++)
	{

		istringstream ss;

		getline(infile, line);

		ss.str(line);
		if(line.empty())
		{
			i--;
			continue;
		}

		else
		{
			newNode = new Node;
			ss >> newNode -> x;
			ss >> newNode-> y;

			nodes.push_back(newNode);

		}

	}

	for( int i = 0; i < num_nodes; i++)
	{
		istringstream ss;

		getline(infile, line);

		ss.str(line);

		if (line .empty())
		{
			i--;
		}
		else
		{
			while ( ss >> num)
			{
				nodes[i] -> adj.push_back(num);

			}
		}

	}

	if (infile.fail())
	{
		cout << "Could not open\n" <<endl;
	}


}

void Graph::displayGraph()
{
	nodeList();

	for (int i= 0; i < num_nodes; i++)
	{

		cout << "Node:" << nodes[i] ->index << " (";
		cout << nodes[i]->x;
		cout << " , ";
		cout << nodes[i]->y;

		cout << ")\t Connects To:\t" ;

		for(int j = 0; j < nodes[i]->adj.size(); j++)
		{
			cout << nodes[i]->adj[j]; 
			cout << " ";

		}

		cout << endl;
	}



}



void Graph::findPath(int start, int goal)
{


	nodeList();

	heap h;

	float tenetive_g;
	float tenetive_h;
	Node* current;
	int neighbor;


	nodes[start]->g = 0;
	nodes[start]->h = distance(nodes[start], nodes[goal]);
	nodes[start]->f = nodes[start]->h + nodes[start]->g;

	h.insert(nodes[start]);

	//h.heapUp(start);

	while (!h.empty())
	{
		
		current = h.remove();

		if(current == nodes[goal])
		{
			
			reconstructPath(goal);
			return;

		}

		current->state = CLOSED;
		for(int j = 0; j < current->adj.size(); j++)
		{
			int neighbor = current-> adj[j];
			if(nodes[neighbor]->state == CLOSED)
			{
				continue;
			}
			
			/*
				else{
			h.insert(nodes[neighbor]);
			}

			
			for(int i = 0; i < num_nodes; i++)
			{

			insert(nodes);


			h.remove();
			}*/

			tenetive_g = current->g + distance(current, nodes[neighbor]);
			//tenetive_h = distance(neighbor, nodes[neighbor]);

			if ((tenetive_g < nodes[neighbor]->g )|| (nodes[neighbor]->state == UNVISITED))
			{

				nodes[neighbor]->g = tenetive_g;
				nodes[neighbor]->h = distance (nodes[neighbor], nodes[goal]);
				nodes[neighbor]->f = tenetive_g + nodes[neighbor]->h;
				nodes[neighbor]->prev = current;

			}

			if (nodes[neighbor]->state == UNVISITED)
			{


				h.insert(nodes[neighbor]);
				nodes[neighbor]->state = OPEN;
			}

			else 
			{
				h.Update(nodes[neighbor]);
			}
		}


	}

	cout << "Path not found"<< endl;

}

void Graph::reconstructPath(int goal)
{
	Node* curr = nodes[goal];
	stack<Node*> st;


	//float dist = 0;
	while (curr!= NULL)

	{
		st.push(curr);
		curr = curr ->prev;
	}


	while(!st.empty())
	{
		
		cout << "Nodes: " << st.top()->index << " (";
		cout << st.top()->x << " , " << st.top()->y << ") ";
		st.pop();
		cout << endl;

	}

	cout << endl << "Distance: " << nodes[goal]->g << endl;

}

float Graph::distance(Node* i, Node* j)
{
	float x = i->x - j->x;
	float y = i-> y - j->y;
	float sum = x*x + y*y;

	return sqrt(sum);

}


heap::heap()
{
	len = 0;
}
heap::~heap()
{

}
bool heap::empty()
{
	if(len <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void heap::insert(Node* val)
{
	if (len > size)
	{
		cout << "Overflow ";
		exit(0);
	}
	array[len] = val;

	heapUp(len);
	len++;
}

void heap::heapUp(int i_child)
{
	if(i_child <= 0)
		return;
	int i_parent = (i_child-1)/2;
	if(array[i_parent] > array [i_child])
	{
		swap(array[i_parent], array[i_child]);
		heapUp(i_parent);
	}
}

Node* heap::remove()
{

	Node* root = array[0];
	swap(array[0], array[len-1]);
	len--;
	heapDown(0);
	return root;

}

void heap::heapDown(int i_parent)
{
	int i_left = 2* i_parent +1;
	int i_right = 2* i_parent +2;
	int i_max;

	if(i_left < len)
	{
		int i_max = i_left;

		if( len > i_right  && array[i_left]->f > array[i_right]->f)
		{
			int i_max = i_right;
		}

		if(array[i_parent]-> f > array[i_max]-> f)
		{
			swap(array[i_parent], array[i_max]);
			heapDown(i_max);
		}
	}
}

void heap::swap(Node*&  a, Node*& b)
{
	Node* temp;

	temp = a;
	a = b;
	b = temp;

}

void heap::heapSort()
{
	int size = len;
	for (int i = 0; i<size; i++)
	{
		cout << remove() << endl;
	}
	len = size;
}

void heap::Update(Node* Nei)
{
	
	
	for(int i = 0; i< size; i ++)
	{
		if(array[i] == Nei)
		{
			heapUp(i);
			heapDown(i);
		}
	}

	

}

void heap::print()
{
	for (int i = 0; i <size; i++)
	{
		cout << array[i];
	}
}