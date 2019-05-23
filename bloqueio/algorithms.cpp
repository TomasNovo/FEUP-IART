#include "algorithms.h"

#include <cfloat>

#include "mapLoader.h"
#include "macros.h"


Node* minimax(Node* currNode, int maxCharacter, int characterIndex, int depth, double alpha, double beta, int heuristic)
{
	if (depth == 0 || currNode->finished())
		return currNode;

	Node* nextNode = NULL;
	Node* bestNode = NULL;

	int nextCharacter = (characterIndex + 1) % currNode->state.size();

	if (characterIndex == maxCharacter)
	{
		for (int i = 0; i < operations.size() ; i++)
		{
			nextNode = doOperationEfficient(currNode, i, characterIndex, maxCharacter, heuristic);

			if (nextNode == currNode)
			{
				continue;
			}

			if (*nextNode == *currNode)
			{
				delete nextNode;
				continue;
			}

			nextNode = minimax(nextNode, maxCharacter, nextCharacter, depth - 1, alpha, beta, heuristic);

			if (nextNode == NULL)
				continue;

			alpha = std::max(alpha, nextNode->h);

			if (nextNode->h > alpha)
				alpha = nextNode->h;

			if (alpha >= beta)
				break;

			if (bestNode == NULL || nextNode->h > bestNode->h)
			{
				delete bestNode;
				bestNode = nextNode;
			}
			else
				delete nextNode;
		}
	}
	else
	{
		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = doOperationEfficient(currNode, i, characterIndex, maxCharacter, heuristic);

			if (nextNode == currNode)
			{
				continue;
			}

			if (*nextNode == *currNode)
			{
				delete nextNode;
				continue;
			}

			nextNode = minimax(nextNode, maxCharacter, nextCharacter, depth - 1, alpha, beta, heuristic);

			if (nextNode == NULL)
				continue;

			if (nextNode->h < beta)
				beta = nextNode->h;

			if (alpha >= beta)
				break;

			if (bestNode == NULL || nextNode->h < bestNode->h)
			{
				delete bestNode;
				bestNode = nextNode;
			}
			else
				delete nextNode;
		}
	}

	return bestNode;
}

Node* minimax(Node* currNode, int characterIndex, int depth, int heuristic)
{
	return minimax(currNode, characterIndex, characterIndex, depth, -DBL_MAX, DBL_MAX, heuristic);
}

