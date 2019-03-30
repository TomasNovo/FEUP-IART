#pragma once

#include <string>

#include "FEUP-IART/src/mapLoader.h"
#include "FEUP-IART/src/node.h"
#include "FEUP-IART/src/algorithms.h"
#include "FEUP-IART/src/ui_utilities.h"

std::string mapFilename;


namespace IART {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for gui
	/// </summary>
	public ref class gui : public System::Windows::Forms::Form
	{
	public:
		gui(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~gui()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button1;


	private: System::Windows::Forms::Panel^  mainPanel;

	private: cli::array<PictureBox^>^ boxes;

	private: Image^ wall;
	private: Image^ floor;
	private: Image^	goal;
	private: Image^ robot;

	private: Node* rootNode;
	private: Node* currNode;
	
	private: System::Windows::Forms::Label^  mapLabel;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;



	protected:

	private:

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>


		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->mapLabel = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(22, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load map";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &gui::button1_Click);
			// 
			// mainPanel
			// 
			this->mainPanel->Location = System::Drawing::Point(150, 0);
			this->mainPanel->Name = L"mainPanel";
			this->mainPanel->Size = System::Drawing::Size(800, 800);
			this->mainPanel->TabIndex = 3;
			// 
			// mapLabel
			// 
			this->mapLabel->AutoSize = true;
			this->mapLabel->Location = System::Drawing::Point(12, 51);
			this->mapLabel->Name = L"mapLabel";
			this->mapLabel->Size = System::Drawing::Size(0, 13);
			this->mapLabel->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(28, 64);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Reset map";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &gui::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Breadth-first search", L"Depth-first search",
					L"Iterative deepening", L"Uniform-cost search", L"Greedy (best-first) search", L"A*"
			});
			this->comboBox1->Location = System::Drawing::Point(11, 146);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 6;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 128);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Agent\'s algorithm";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(28, 182);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Solve";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &gui::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(22, 234);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 9;
			this->textBox1->Text = L"15";
			this->textBox1->Visible = false;
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(950, 801);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->mapLabel);
			this->Controls->Add(this->mainPanel);
			this->Controls->Add(this->button1);
			this->KeyPreview = true;
			this->Name = L"gui";
			this->Text = L"Labyrinth Robots";
			this->Load += gcnew System::EventHandler(this, &gui::gui_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &gui::gui_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void gui_Load(System::Object^  sender, System::EventArgs^  e)
	{
		initializeBoxes();

		comboBox1->SelectedIndex = 5;
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			mapFilename = convertString(openFileDialog1->FileName);

			rootNode = initiateMap(mapFilename);
			currNode = new Node(*rootNode);

			loadMaptoBoxes();

			mapLabel->Text = "Map: " + openFileDialog1->FileName->Substring(openFileDialog1->FileName->LastIndexOf('\\')+1);

			guiFlashingAnimation(currNode);
		}
	}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (map.size() > 0)
			resetMap();
	}

	private: System::Void gui_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		if (!currNode->finished())
		{
			std::vector<char> letters = { 'w', 'd', 's', 'a' };
			Node* nextNode;
			int i, robotIndex = 0, index;
			for (i = 0; i < letters.size(); i++)
			{
				if (letters[i] == e->KeyChar)
				{
					nextNode = operations[i](currNode, robotIndex);

					if (*currNode == *nextNode)
						return;

					nextNode->cost++;
					nextNode->parent = currNode;
					nextNode->operationName = operationNames[i];

					guiWalkingAnimation(currNode, nextNode);

					setNode(currNode, nextNode);

					if (currNode->finished())
					{
						int optimalCost = aStar2(rootNode)->cost;
						MessageBox::Show("You finsihed the map in " + currNode->cost + " moves. The optimal solution is " + optimalCost + ".");
						resetMap();
					}


					break;
				}
			}
		}
	}


	void printAgent()
	{
		std::unordered_set<Node*, hashNode, hashNode> tree;
		tree.insert(currNode);

		Node* result = NULL;

		int algorithm = comboBox1->SelectedIndex + 1;

		int limit = stoi(convertString(textBox1->Text));


		clock_t time = clock();

		if (algorithm == 1) result = breadth(currNode);
		else if (algorithm == 2) result = depth(currNode, 0, limit);
		else if (algorithm == 3) result = iteDeepening(currNode, limit);
		else if (algorithm == 4) result = uniformCost(currNode);
		else if (algorithm == 5) result = greedy(tree, currNode, 0);
		else if (algorithm == 6) result = aStar2(currNode);

		double deltaTime = (double)(clock() - time) / CLOCKS_PER_SEC;


		if (result == NULL)
			MessageBox::Show("Failed to find solution!");
		else
		{
			std::vector<Node*> path;
			Node* node = result;

			for (size_t i = 0; node != NULL; i++)
			{
				path.push_back(node);

				node = node->parent;
			}

			for (size_t i = path.size() - 1; i >= 1; i--)
			{
				guiWalkingAnimation(path[i], path[i - 1]);
			}

			setNode(currNode, path.front());

			guiFlashingAnimation(currNode);
			MessageBox::Show("Agent's solution is " + currNode->cost + " moves.");

			resetMap();
		}
	}

	void guiFlashingAnimation(Node* node)
	{
		int flashTime = 100;

		int index;
		for (int i = 0; i < 16; ++i) // start flashing animation
		{
			if (i % 2 == 0)
			{
				for (size_t j = 0; j < node->state.size(); j++)
				{
					index = coordsToIndex(node->state[j].objective[0], node->state[j].objective[1]);
					
					if (index > 0)
						boxes[index]->Image = nullptr;

					index = coordsToIndex(node->state[j].coords[0], node->state[j].coords[1]);
					boxes[index]->Image = nullptr;
				}
			}
			else
			{
				for (size_t j = 0; j < node->state.size(); j++)
				{
					index = coordsToIndex(node->state[j].objective[0], node->state[j].objective[1]);
				
					if (index > 0)
						boxes[index]->Image = goal;

					index = coordsToIndex(node->state[j].coords[0], node->state[j].coords[1]);
					boxes[index]->Image = robot;
				}
			}

			this->Refresh();
			ui_utilities::milliSleep(flashTime); //sleeps for 100 milliseconds
		}
	}

	void guiWalkingAnimation(Node* node1, Node* node2)
	{
		int walkTime = 200;
		Node* nextNode = new Node(*node1);

		for (int i = 0; i < node1->state.size(); ++i)
		{
			if (node1->state[i].coords[1] != node2->state[i].coords[1])
			{
				int deltaY = node2->state[i].coords[1] - node1->state[i].coords[1];

				for (int j = 0; j < abs(deltaY); ++j)
				{
					nextNode->state[i].coords[1] += deltaY / abs(deltaY);

					setNode(node1, nextNode);

					this->Refresh();
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds
				}
			}
			else if (node1->state[i].coords[0] != node2->state[i].coords[0])
			{
				int deltaX = node2->state[i].coords[0] - node1->state[i].coords[0];

				for (int j = 0; j < abs(deltaX); ++j)
				{
					nextNode->state[i].coords[0] += deltaX / abs(deltaX);
					
					setNode(node1, nextNode);

					this->Refresh();
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds
				}
			}
		}
	}


	private: void initializeBoxes()
	{
		boxes = (gcnew cli::array<PictureBox^>(256));

		PictureBox^ picbox;
		int index;
		for (size_t i = 0; i < 16; i++)
		{
			for (size_t j = 0; j < 16; j++)
			{
				index = coordsToIndex(j, i);

				picbox = gcnew PictureBox();

				picbox->Location = System::Drawing::Point(j * 50, i * 50);
				picbox->Name = L"panelBox" + index;
				picbox->Size = System::Drawing::Size(50, 50);

				mainPanel->Controls->Add(picbox);

				boxes[index] = picbox;
			}
		}

		wall = Image::FromFile("images/wall.png");
		floor = Image::FromFile("images/floor.png");
		goal = Image::FromFile("images/goal.png");
		robot = Image::FromFile("images/robot.png");
	}

	std::string convertString(System::String^ input)
	{
		std::string output;

		for (size_t i = 0; i < input->Length; i++) // copy
		{
			output.push_back((char)input[i]);
		}

		return output;
	}

	void setNode(Node* node1, Node* node2)
	{
		int index;
		for (size_t i = 0; i < node1->state.size(); i++)
		{
			index = coordsToIndex(node1->state[i].coords[0], node1->state[i].coords[1]);
			boxes[index]->Image = nullptr;

			index = coordsToIndex(node2->state[i].coords[0], node2->state[i].coords[1]);
			boxes[index]->Image = robot;
		}

		*node1 = *node2;
	}

	void loadMaptoBoxes()
	{
		Image^ currImage;
		int index;
		for (size_t i = 0; i < map.size(); i++)
		{
			for (size_t j = 0; j < map[i].size(); j++)
			{
				index = coordsToIndex(j, i);
				
				if (map[i][j] == '0')
					currImage = floor;
				else if (map[i][j] == '1')
					currImage = wall;

				boxes[index]->BackgroundImage = currImage;
				boxes[index]->Image = nullptr;
			}
		}

		for (size_t i = 0; i < currNode->state.size(); i++)
		{
			index = coordsToIndex(currNode->state[i].coords[0], currNode->state[i].coords[1]);
			boxes[index]->Image = robot;

			if (currNode->state[i].objective[0] != -1 || currNode->state[i].objective[1] != -1)
			{
				index = coordsToIndex(currNode->state[i].objective[0], currNode->state[i].objective[1]);
				boxes[index]->Image = goal;
			}
		}
	}

	int coordsToIndex(int x, int y)
	{
		return (x + y * 16);
	}

	cli::array<int>^ indexToCoords(int index)
	{
		cli::array<int>^ output = { index % 16, index / 16 };

		return output;
	}

	void resetMap()
	{
		setNode(currNode, rootNode);

		loadMaptoBoxes();
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (comboBox1->SelectedIndex > -1)
		{
			printAgent();
		}
	}

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		textBox1->Visible = (comboBox1->SelectedIndex == 1 || comboBox1->SelectedIndex == 2);
	}
};
}
