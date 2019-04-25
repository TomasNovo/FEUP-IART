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


int main()
{


	menu();
	
	return 0;
}