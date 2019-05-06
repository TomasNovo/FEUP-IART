
#include "node.h"
#include "algorithms.h"

int main()
{
	Node* currNode = new Node();

	minimax(currNode, 0, 2);

	return 0;
}