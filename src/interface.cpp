#include "interface.h"

#include "mapLoader.h"

#include <sstream> 
#include <algorithm>
#include <random>

void info()
{
	ui_utilities::ClearScreen();

	cout << "Game devoloped based on play store game Labyrinth Robots." << endl << endl;
	cout << "Developed by :" << endl << endl;
	cout << "-Joana Silva  - up201208979" << endl;
	cout << "-Joao Franco  - up201604828" << endl;
	cout << "-Tomas Novo   - up201604503" << endl << endl;
	
	std::cin.get();

	menu();

}

int algorithm_menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << "------------------------------" << endl;
	cout << "|    Choose an algorithm:    |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 1 -      Breadth           |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 2 -       Depth            |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 3 - Iterative Deepening    |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 4 -    Uniform cost        |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 5 -       Greedy           |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 6 -         A*             |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 0 -       Exit             |" << endl;
	cout << "------------------------------" << endl;

	cin >> input;
	while (cin.fail() || input > 6 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Option number: ";
			cin >> input;
		}

	return input;
}


void agent(string map)
{
	Node* rootNode = initiateMap(map);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;
	
	int algorithm = algorithm_menu();

	int limit = 18;

	int heuristic = 0;

	if (algorithm == 2 || algorithm == 3 || algorithm == 5)
	{
		cout << "Insert a limit for the algorithm:";
		cin >> limit;
	}

	if (algorithm == 5 || algorithm == 6)
	{
		cout << "Choose between manhattan distance(0) or euclidean distance(1):";
		cin >> heuristic;

		if (heuristic != 0 && heuristic != 1)
			heuristic = 0;
	}

	clock_t time = clock();

	if (algorithm == 1) result = breadth(rootNode);
	else if (algorithm == 2) result = depth(rootNode, 0, limit);
	else if (algorithm == 3) result = iteDeepening(rootNode, limit);
	else if (algorithm == 4) result = uniformCost(rootNode);
	else if (algorithm == 5) result =  greedy(tree, rootNode, 0, limit, heuristic);
	else if (algorithm == 6) result =  aStar2(rootNode, heuristic);
	else if (algorithm == 0) return;

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";

	if (result == NULL)
		cout << "Failed to find solution!";
	else
	{
		printPath3(result);
		cout << "Agent's solution: " << result->cost << " moves.\n";
	}


	printf("\nFinished in %f seconds.\n", deltaTime);

	ui_utilities::milliSleep(4000);

	options();
}

void options()
{
	ui_utilities::ClearScreen();

	cout << "---------------------------" << endl;
	cout << "|    Choose an option:    |" << endl;
	cout << "---------------------------" << endl;
	cout << "| 1 - Return to map menu  |" << endl;
	cout << "--------------------------" << endl;
	cout << "| 2 - Return to main menu |" << endl;
	cout << "--------------------------" << endl;
	cout << "| 0 - Exit                |" << endl;
	cout << "--------------------------" << endl;
	

	int input;

	cout << "Option: " ;
	cin >> input;
	while (cin.fail() || input > 2 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}

	if (input == 0) return;
	else if (input == 1) agent_menu();
	else if (input == 2) menu();
}

void agent_menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << endl << "------------------------------------" << endl;
	cout << "|                                  |" << endl;
	cout << "|  L A B Y R I N T H   R O B O T S |" << endl;
	cout << "|                                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << "|      Choose the map to play  !   |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 1 - MAP 1                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 2 - MAP 2                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 3 - MAP 3                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 4 - MAP 4                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 5 - MAP 5                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 6 - MAP 6                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 7 - MAP 7                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Option: ";

	string m = "map";

	cin >> input;
	while (cin.fail() || input > 7 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}


	if (input != 1)
		m += std::to_string(input);

	m += ".txt";
	
	agent(m);
}


void play_menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << endl << "------------------------------------" << endl;
	cout << "|                                  |" << endl;
	cout << "|  L A B Y R I N T H   R O B O T S |" << endl;
	cout << "|                                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << "|      Choose the map to play  !   |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 1 - MAP 1                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 2 - MAP 2                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 3 - MAP 3                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 4 - MAP 4                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 5 - MAP 5                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 6 - MAP 6                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 7 - MAP 7                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 8 - MAP 8                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 9 - MAP 9                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 10 - MAP 10                      |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 11 - Random Map                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Option: ";

	string m = "map";

	cin >> input;
	while (cin.fail() || input > 11 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}

	if (input == 11)
	{
		srand(time(NULL));
		int randNum = rand()%(10-1 + 1) + 1;

		m += std::to_string(randNum);
	}
	else 
	{
		m += std::to_string(input);
	}
	
	m += ".txt";
	play(m);
	m = "map";
	
}


Node* play_loop(Node* rootNode)
{
	Node* currNode = new Node(*rootNode);
	Node* nextNode = new Node();

	ui_utilities::ClearScreen();
	flashingAnimation(currNode);

	while (!currNode->finished())
	{
		ui_utilities::ClearScreen();
		printMap(currNode);

		int robotIndex = 0;
		if (currNode->state.size() > 1)
		{
			cout << endl << "Robot numbers: " << endl;
			
			vector<string> robots;
			
			for (int i = 0; i < currNode->state.size(); i++)
			{
				char c = currNode->state[i].id;			
				string s;
				s.push_back(c);
				robots.push_back(s);
			}


			for (int i = 0; i < currNode->state.size(); i++)
			{
				string tmp = robots[i];
				
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
				
				cout << "Robot " << tmp <<  " number -> " << i <<  endl;
			}

			cout << "\nSelect robot: ";
			cin >> robotIndex;

			while(robotIndex >= robots.size() || robotIndex < 0)
			{
				cout << "Please input a valid option !" << endl << endl;
				cout << "Select robot: ";
				cin >> robotIndex;
			}
		}

		char input;
		cout << "\nSelect direction: ";
		cin >> input;

		if (input == 'w' || input == 'a' || input == 's' || input == 'd')
		{
			vector<char> letters = {'w', 'd', 's', 'a'};
			int i;
			for (i = 0; i < letters.size(); i++)
			{
				if (letters[i] == input)
				{
					nextNode = operations[i](currNode, robotIndex);
					nextNode->cost++;
					nextNode->parent = currNode;
					nextNode->operationName = operationNames[i];

					break;
				}
			}

			walkingAnimation(currNode, nextNode);

			currNode = nextNode;
		}
		else 
		{
			cout << "Please input a valid option !" << endl << endl;
			cout << "Select direction: ";
			cin >> input;
		}
	}

	flashingAnimation(currNode);

	cout << "You completed the map in " << currNode->cost << " moves.\n";
	cout << "The best solution is " << aStar2(rootNode, 0)->cost << " moves.\n";

	return currNode;
}

int play(string map)
{
	ui_utilities::ClearScreen();

	cout << " How to play :" << endl << endl;
	cout << "- Input the letter of the robot that you want to move (A-Z)" << endl;
	cout << "- Input u,d,l,r to go up, down, left and right, respectively " << endl;
 	cout << "- By pressing one of these keys, your robot will move in that direction " << "and it will only stop if an obstacle is in its way" << endl;

	// ui_utilities::milliSleep(6000); 
	ui_utilities::ClearScreen();

	// srand(time(NULL));
	// int randNum = rand()%(10-1 + 1) + 1;

	// string map = "map";

	// map += std::to_string(randNum);
	// map += ".txt";
	Node* rootNode = initiateMap(map);

	play_loop(rootNode);

	cout << "\n";

	ui_utilities::milliSleep(4000);
	ui_utilities::ClearScreen();

	options();

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
	cout << "| 0 - Exit                         |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Input: ";

	cin >> input;
	while (cin.fail() || input > 4 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Option number: ";
			cin >> input;
		}
	if (input == 1) play_menu();
	else if (input == 2) agent_menu();
	else if (input == 3) info();
	else if (input == 0)
	{
		cout << endl << "Bye, have a good time !" << endl;
		ui_utilities::milliSleep(4000);
		ui_utilities::ClearScreen();
		return 0;
	}

	return input;
}


void flashingAnimation(Node* node)
{
	int flashTime = 100;

	vector<Robot> stateSave = node->state;

	for (int i = 0; i < 16; ++i) // start flashing animation
	{
		if (i % 2 == 0)
		{
			node->state.resize(0);
		}
		else
		{
			node->state = stateSave;
		}

		ui_utilities::ClearScreen();
		printMap(node);
		cout << "\n\n";
		ui_utilities::milliSleep(flashTime); //sleeps for 100 milliseconds
	}
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

	int stopTime = 500;
	Node *currNode = new Node(*nodes.back()), *nextNode;

	flashingAnimation(currNode);

	ui_utilities::ClearScreen();
	printMap(currNode);
	cout << "\n\n";
	ui_utilities::milliSleep(stopTime*2); //sleeps for 1 second


	for (int i = path.size()-1; i >= 1; i--) // walking animation
	{
		currNode = new Node(*nodes[i]);
		nextNode = nodes[i-1];

		walkingAnimation(currNode, nextNode);

		if (i >= 2)
			ui_utilities::milliSleep(stopTime); //sleeps for 500 milliseconds
	}


	flashingAnimation(currNode);

	// cout << "Path size: " << path.size()-1 << "\n\n";
}

