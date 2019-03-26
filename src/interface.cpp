#include "interface.h"

#include "mapLoader.h"


Node* play_loop(Node* currNode)
{
	
	Node* nextNode = new Node();

	while (!currNode->finished())
	{
		ui_utilities::ClearScreen();
		printMap(currNode);

		int robotIndex = 0;
		if (currNode->state.size() > 1)
		{
			cout << "\nSelect robot:";
			cin >> robotIndex;
		}

		char input;
		cout << "\nSelect direction: ";
		cin >> input;

		int i;
		for (i = 0; i < operationNames.size(); i++)
		{
			if (operationNames[i][0] == input)
			{
				nextNode = operations[i](currNode, robotIndex);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];

				break;
			}
		}

		if (i == operationNames.size())
		{
			cout << "Wrong input!";
			continue;
		}

		walkingAnimation(currNode, nextNode);

		float progress = 0.0;
		while (progress < 1.0) {
			int barWidth = 70;

			std::cout << "[";
			int pos = barWidth * progress;
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			std::cout << "] " << int(progress * 100.0) << " %\r";
			std::cout.flush();

			progress += 0.1; // for demonstration only
		}
		std::cout << std::endl;

	}

	return currNode;
}

int play()
{
	ui_utilities::ClearScreen();

	cout << " How to play :" << endl << endl;
	cout << "- Input the letter of the robot that you want to move (A-Z)" << endl;
	cout << "- Use W,S,A,D to go up, down, left and right, respectively " << endl;
 	cout << "- By pressing one of these keys, your robot will move in that direction " << "and it will only stop if an obstacle is in its way" << endl;

	// ui_utilities::milliSleep(6000); //sleeps for 1 second
	ui_utilities::ClearScreen();

	Node* rootNode = initiateMap("map3.txt");

	play_loop(rootNode);

	cout << "\n";

	return 0;
}


int menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << endl << "------------------------------------" << endl;
	cout << "|                                  |" << endl;
	cout << "|  L A B Y R I N T H   R O B O T S |" << endl;
	cout << "|                                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 1 - Play                         |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 2 - Watch an agent play          |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 3 - Info                         |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Input: ";

	cin >> input;
	while (cin.fail() || input > 3 || input < 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}


	return input;
}

void walkingAnimation(Node* node1, Node* node2)
{
	int walkTime = 200;

	for (int i = 0; i < node1->state.size(); ++i)
	{
		if (node1->state[i].coords[1] != node2->state[i].coords[1])
		{
			int deltaY = node2->state[i].coords[1] - node1->state[i].coords[1];

			for (int j = 0; j < abs(deltaY); ++j)
			{
				node1->state[i].coords[1] += deltaY/abs(deltaY);
				ui_utilities::ClearScreen();
				printMap(node1);
				cout << "\n\n";
				ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

			}
		}
		else if (node1->state[i].coords[0] != node2->state[i].coords[0])
		{
			int deltaX = node2->state[i].coords[0] - node1->state[i].coords[0];

			for (int j = 0; j < abs(deltaX); ++j)
			{
				node1->state[i].coords[0] += deltaX/abs(deltaX);
				ui_utilities::ClearScreen();
				printMap(node1);
				cout << "\n\n";
				ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

			}
		}	
	}
}



void printPath(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node->parent != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	cout << "Path:\n";
	cout << printState(node->state);
	cout << "\n\n";

	for (int i = path.size()-1; i >= 0; i--)
	{
		cout << path[i] << "\n";
		
		if (DEBUG)
			cout << *nodes[i];
		else
			cout << printState(nodes[i]->state);
		
		cout << "\n\n";
	}

	cout << "Path size: " << path.size() << "\n";

}


void printMap(Node* node)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			int k;
			if (node != NULL)
			{
				for (k = 0; k < node->state.size(); ++k)
				{
					if (i == node->state[k].coords[1] && j == node->state[k].coords[0]) // robot's position
					{
						cout << (char)(node->state[k].id + ('A' - 'a'));
						break;
					}

					else if (i == node->state[k].objective[1] && j == node->state[k].objective[0]) // robot's position
					{
						cout << (char)node->state[k].id;
						break;
					}
				}
			}
			
			if (node == NULL || k == node->state.size())
			{
				if (map[i][j] == '2' || map[i][j] == '0')
				cout << " ";

				else if (map[i][j] == '1')
					cout << 0;

				else
					cout << map[i][j];
			}

			cout << " ";
		}

		cout << "\n";
	}
}

void printPath2(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	for (int i = path.size()-1; i >= 0; i--)
	{
		ui_utilities::ClearScreen();
		printMap(nodes[i]);
		cout << "\n\n";

		ui_utilities::milliSleep(2000); //sleeps for 1 second
	}
}


void printPath3(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	int flashTime = 100, walkTime = 200, stopTime = 500;
	Node *currNode = new Node(*nodes.back()), *nextNode;
	vector<Robot> stateSave = currNode->state;

	for (int i = 0; i < 15; ++i) // start flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state.resize(0);
		}
		else
		{
			currNode->state = stateSave;
		}

		ui_utilities::ClearScreen();
		printMap(currNode);
		cout << "\n\n";
		ui_utilities::milliSleep(flashTime); //sleeps for 100 milliseconds
	}
	currNode->state = stateSave;

	ui_utilities::ClearScreen();
	printMap(currNode);
	cout << "\n\n";
	ui_utilities::milliSleep(stopTime*2); //sleeps for 1 second


	for (int i = path.size()-1; i >= 1; i--) // walking animation
	{
		currNode = new Node(*nodes[i]);
		nextNode = nodes[i-1];

		for (int j = 0; j < currNode->state.size(); ++j)
		{
			if (currNode->state[j].coords[1] != nextNode->state[j].coords[1])
			{
				int deltaY = nextNode->state[j].coords[1] - currNode->state[j].coords[1];

				for (int k = 0; k < abs(deltaY); ++k)
				{
					currNode->state[j].coords[1] += deltaY/abs(deltaY);
					ui_utilities::ClearScreen();
					printMap(currNode);
					cout << "\n\n";
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

				}
			}
			else if (currNode->state[j].coords[0] != nextNode->state[j].coords[0])
			{
				int deltaX = nextNode->state[j].coords[0] - currNode->state[j].coords[0];

				for (int k = 0; k < abs(deltaX); ++k)
				{
					currNode->state[j].coords[0] += deltaX/abs(deltaX);
					ui_utilities::ClearScreen();
					printMap(currNode);
					cout << "\n\n";
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

				}
			}	
		}

		if (i >= 2)
			ui_utilities::milliSleep(stopTime); //sleeps for 500 milliseconds
	}


	stateSave = currNode->state;
	for (int i = 0; i < 16; ++i) // end flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state.resize(0);
		}
		else
		{
			currNode->state = stateSave;
		}

		ui_utilities::ClearScreen();
		printMap(currNode);
		cout << "\n\n";
		ui_utilities::milliSleep(flashTime); //sleeps for 500 milliseconds
	}

	cout << "Path size: " << path.size()-1 << "\n\n";
}

