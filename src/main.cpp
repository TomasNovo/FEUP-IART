#include <iostream>
#include <string>
#include <vector>
#include <time.h> 

#include "node.h"
#include "mapLoader.h"
#include "interface.h"
#include "algorithms.h"
#include "macros.h"

using namespace std;


template<class T>
void printSet(const T& tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}


void printSet(const multiset<Node*, sortF>& tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}



void agent()
{
	Node* rootNode = initiateMap("map.txt");

	vector<Node*> rootRow;
	rootRow.push_back(rootNode);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;
	
	clock_t time = clock();

	for (int i = 0; i < 1; i++)
	{
		// result = breadth(rootRow, 0);
		// result = breadth2(tree, rootRow, 0);
		// result = depth(rootNode, 0, 12);
		result = greedy(tree, rootNode, 0);
		// result = aStar(rootNode, 0);
		// result = aStar2(rootNode, 0);
	}

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";

	printf("\nFinished in %f seconds.\n", deltaTime);
}



int main()
{	
	int input = menu();

	if (input == 1)
		play();
	else if (input == 2)
		agent();

	return 0;
}