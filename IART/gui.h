#pragma once

#include <string>

#include "FEUP-IART/src/mapLoader.h"
#include "FEUP-IART/src/node.h"

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

	private: System::String^ mapFilename;

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
			this->button2->Click += gcnew System::EventHandler(this, &gui::button2_Click_1);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Breadth-first search", L"Depth-first search",
					L"Iterative deepening", L"Uniform-cost search", L"Greedy (best-first) search", L"A*"
			});
			this->comboBox1->Location = System::Drawing::Point(12, 146);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 6;
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
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(987, 801);
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

	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			mapFilename = openFileDialog1->FileName;

			initializeBoxes();

			std::string filename = convertString(mapFilename);

			currNode = initiateMap(filename);

			loadMaptoBoxes();

			mapLabel->Text = "Map: " + mapFilename->Substring(mapFilename->LastIndexOf('\\')+1);

			//this->Focus();
		}
	}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{

	}

	private: System::Void gui_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		//MessageBox::Show(e->KeyChar.ToString());

		std::vector<char> letters = { 'w', 'd', 's', 'a' };
		Node* nextNode;
		int i, robotIndex = 0, index;
		for (i = 0; i < letters.size(); i++)
		{
			if (letters[i] == e->KeyChar)
			{
				nextNode = operations[i](currNode, robotIndex);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];

				index = coordsToIndex(currNode->state[robotIndex].coords[0], currNode->state[robotIndex].coords[1]);
				boxes[index]->Image = nullptr;

				index = coordsToIndex(nextNode->state[robotIndex].coords[0], nextNode->state[robotIndex].coords[1]);
				boxes[index]->Image = robot;

				currNode = nextNode;

				break;
			}
		}


		// walkingAnimation(currNode, nextNode);
	
	}


	private: System::Void initializeBoxes()
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

	System::Void loadMaptoBoxes()
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


	private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e)
	{
		currNode = new Node(*rootNode);
	}
};
}
