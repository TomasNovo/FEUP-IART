#pragma once

#include <string>

#include "mapLoader.h"
#include "node.h"
#include "algorithms.h"
#include "ui_utilities.h"
#include "macros.h"

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

	private: cli::array<cli::array<PictureBox^>^>^ boxes;
	private: cli::array<PictureBox^>^ bars;

	private: Image^ wall;
	private: Image^ floor;
	private: array<Image^>^ characters;

	private: Node* rootNode;
	private: Node* currNode;

	private: int selectedRobot = 0;
	
	private: System::Windows::Forms::Label^  mapLabel;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  robotPanel;
	private: System::Windows::Forms::ComboBox^  comboBox2;








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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(gui::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->mapLabel = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->robotPanel = (gcnew System::Windows::Forms::Panel());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
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
			this->mapLabel->Location = System::Drawing::Point(30, 51);
			this->mapLabel->Name = L"mapLabel";
			this->mapLabel->Size = System::Drawing::Size(0, 13);
			this->mapLabel->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(28, 72);
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
			this->comboBox1->Location = System::Drawing::Point(11, 134);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 6;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 113);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Agent\'s algorithm:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(33, 228);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Solve";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &gui::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(22, 168);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 9;
			this->textBox1->Text = L"15";
			this->textBox1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(37, 283);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Current Robot";
			// 
			// robotPanel
			// 
			this->robotPanel->Location = System::Drawing::Point(17, 312);
			this->robotPanel->Name = L"robotPanel";
			this->robotPanel->Size = System::Drawing::Size(117, 421);
			this->robotPanel->TabIndex = 12;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Manhattan distance", L"Euclidean distance" });
			this->comboBox2->Location = System::Drawing::Point(13, 197);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 13;
			this->comboBox2->Visible = false;
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(700, 600);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->robotPanel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->mapLabel);
			this->Controls->Add(this->mainPanel);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->KeyPreview = true;
			this->MaximizeBox = false;
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

		rootNode = initiateMap();
		currNode = new Node(*rootNode);

		loadBoxes();
	}

	private: void initializeBoxes()
	{
		boxes = (gcnew cli::array<cli::array<PictureBox^>^>(MAPHEIGHT));
		bars = (gcnew cli::array<PictureBox^>(MAPHEIGHT*2 - 1));

		PictureBox^ picbox;
		int index, posX = 0, posY = 0, adder = 0;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			boxes[i] = (gcnew cli::array<PictureBox^>(MAPWIDTH));

			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				index = coordsToIndex(j, i);

				// Box
				picbox = gcnew PictureBox();

				posX = j * 60;
				posY = i * 60;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"box" + index;
				picbox->Size = System::Drawing::Size(50, 50);

				mainPanel->Controls->Add(picbox);

				boxes[i][j] = picbox;

				picbox->MouseUp += gcnew MouseEventHandler(this, &gui::dragDrop);
				


				//if (j < MAPWIDTH-1)
				//{
				//	// Bar
				//	picbox = gcnew PictureBox();

				//	posX = j * 60 + 50;
				//	posY = i * 60;

				//	picbox->Location = System::Drawing::Point(posX, posY);
				//	picbox->Name = L"bar" + index;
				//	picbox->Size = System::Drawing::Size(10, 50);

				//	mainPanel->Controls->Add(picbox);

				//	//bars[index] = picbox;
				//}

				//if (i < MAPHEIGHT - 1)
				//{
				//	// Bar
				//	picbox = gcnew PictureBox();

				//	posX = j * 60;
				//	posY = i * 60 + 50;

				//	picbox->Location = System::Drawing::Point(posX, posY);
				//	picbox->Name = L"bar" + index;
				//	picbox->Size = System::Drawing::Size(50, 10);

				//	mainPanel->Controls->Add(picbox);

				//	//bars[index] = picbox;
				//}
			}
		}
	}

	void dragDrop(System::Object^  sender, MouseEventArgs^  e)
	{

	}

	void loadBoxes()
	{
		wall = Image::FromFile("images/wall.png");
		floor = Image::FromFile("images/floor.png");
		characters = gcnew array<Image^>(currNode->state.size());

		Image^ currImage;
		int index;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				boxes[i][j]->BackgroundImage = wall;
			}
		}

		for (size_t i = 0; i < currNode->state.size(); i++)
		{
			characters[i] = changeColor(Image::FromFile("images/robot.png"), currNode->state[i].id);
			boxes[currNode->state[i].coords[1]][currNode->state[i].coords[0]]->Image = characters[i];
		}
	}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (map.size() > 0)
			resetMap();
	}

	private: System::Void gui_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		if (currNode != NULL && !currNode->finished() && map.size() > 0)
		{
			std::vector<char> letters = { 'w', 'd', 's', 'a' };
			Node* nextNode;
			int i;
			for (i = 0; i < letters.size(); i++)
			{
				if (letters[i] == e->KeyChar)
				{
					nextNode = operations[i](currNode, selectedRobot);

					if (*currNode == *nextNode)
						return;

					nextNode->cost++;
					nextNode->parent = currNode;
					nextNode->operationName = operationNames[i];

					setNode(currNode, nextNode);

					if (currNode->finished())
					{
						int optimalCost = aStar2(rootNode, 0)->cost;
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
		Node* newCurrNode = new Node(*currNode);
		newCurrNode->parent = NULL;

		std::unordered_set<Node*, hashNode, hashNode> tree;
		tree.insert(newCurrNode);

		Node* result = NULL;

		int algorithm = comboBox1->SelectedIndex + 1;

		int limit = stoi(convertString(textBox1->Text));

		int heuristic = comboBox2->SelectedIndex;

		clock_t time = clock();

		if (algorithm == 1) result = breadth(newCurrNode);
		else if (algorithm == 2) result = depth(newCurrNode, 0, limit);
		else if (algorithm == 3) result = iteDeepening(newCurrNode, limit);
		else if (algorithm == 4) result = uniformCost(newCurrNode);
		else if (algorithm == 5) result = greedy(tree, newCurrNode, 0, limit, heuristic);
		else if (algorithm == 6) result = aStar2(newCurrNode, heuristic);

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

			int stopTime = 150;

			for (size_t i = path.size() - 1; i >= 1; i--)
			{
				ui_utilities::milliSleep(stopTime);
			}
			

			setNode(currNode, result);

			MessageBox::Show("Agent's solution is " + currNode->cost + " moves." + "Finished in " + deltaTime + " seconds.");

			resetMap();
		}
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
		/*int index;
		for (size_t i = 0; i < node1->state.size(); i++)
		{
			index = coordsToIndex(node1->state[i].coords[0], node1->state[i].coords[1]);
			
			bool flag = false;
			for (size_t j = 0; j < node1->state.size(); j++)
			{
				if (node1->state[j].objective == node1->state[i].coords)
				{
					boxes[index]->Image = goals[j];
					flag = true;
					break;
				}
			}

			if (!flag)
			{
				boxes[index]->Image = nullptr;
			}

			boxes[index]->Refresh();

			index = coordsToIndex(node2->state[i].coords[0], node2->state[i].coords[1]);
			boxes[index]->Image = robots[i];
			boxes[index]->Refresh();
		}*/

		*node1 = *node2;
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

		loadBoxes();
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (comboBox1->SelectedIndex > -1 && map.size() > 0)
		{
			printAgent();
		}
	}

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		textBox1->Visible = (comboBox1->SelectedIndex == 1 || comboBox1->SelectedIndex == 2 || comboBox1->SelectedIndex == 4);

		comboBox2->Visible = (comboBox1->SelectedIndex == 4 || comboBox1->SelectedIndex == 5);
	}


	Image^ changeColor(Image^ image, char robotId)
	{
		if (robotId == 'a') // Red
			return image;

		Bitmap^ bitmap = (Bitmap^)image;
		Image^ output = (gcnew Bitmap(bitmap));

		for (size_t i = 0; i < image->Height; i++)
		{
			for (size_t j = 0; j < image->Width; j++)
			{
				Color pixel = bitmap->GetPixel(i, j);

				if (robotId == 'b') // Blue
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(i, j, Color::FromArgb(pixel.A, 0, 0, pixel.R));
					}
				}
				else if (robotId == 'c') // Yellow
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(i, j, Color::FromArgb(pixel.A, pixel.R, pixel.R, 0));
					}
				}
				else if (robotId == 'd') // Green
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(i, j, Color::FromArgb(pixel.A, 0, pixel.R, 0));
					}
				} 
				
			}
		}

		return output;
	}

	void robotPicturePanelClick(System::Object^  sender, System::EventArgs^  e)
	{
		PictureBox^ box = (PictureBox^)sender;
		selectRobotButton(box->Name[box->Name->Length - 1] - '0');
	}

	void robotPanelButtonClick(System::Object^  sender, System::EventArgs^  e)
	{
		RadioButton^ button = (RadioButton^)sender;
		selectRobotButton(button->Name[button->Name->Length - 1] - '0');
	}

	void loadRobotsPanel()
	{
		/*PictureBox^ picbox;
		RadioButton^ button;
		robotPanel->Controls->Clear();

		for (size_t i = 0; i < currNode->state.size(); i++)
		{
			picbox = gcnew PictureBox();

			picbox->Image = robots[i];
			picbox->Name = "robotSelectorPicture" + i;
			picbox->Location = System::Drawing::Point(0, i * (50+10));
			picbox->Size = System::Drawing::Size(50, 50);
			picbox->Click += gcnew System::EventHandler(this, &gui::robotPicturePanelClick);
			robotPanel->Controls->Add(picbox);

			button = gcnew RadioButton();

			button->Name = "robotSelectorButton" + i;
			button->Location = System::Drawing::Point(90, i * (50 + 10) + 12);
			button->Click += gcnew System::EventHandler(this, &gui::robotPanelButtonClick);
			robotPanel->Controls->Add(button);
		}

		selectRobotButton(0);*/
	}

	void selectRobotButton(int index)
	{
		selectedRobot = index;
	
		((RadioButton^)robotPanel->Controls->Find("robotSelectorButton" + index, true)[0])->Checked = true;
	}
	
	
};
}
