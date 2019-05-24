#include <chrono>

#include "node.h"
#include "algorithms.h"
#include "mapLoader.h"

int main()
{
	std::vector<char> chars = {'a', 'b', 'c', 'd'};
	Node* currNode = initiateMap(chars);

	auto begin = std::chrono::high_resolution_clock::now();

	Node* bestMove = minimax(currNode, 0, 2, 1);

	double deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() / (double)1e9;

	std::cout << "\nFinished in : " << deltaTime << " seconds.\n";

	std::cin.get();

	return 0;
}