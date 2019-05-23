#pragma once

#include <iostream>
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



	private: System::Windows::Forms::Panel^  mainPanel;

	private: Image^ block;
	private: Image^ bar;
	private: array<Image^>^ characters;
	private: array<Image^>^ goals;


	private: Node* rootNode;
	private: Node* currNode;

	private: int selectedCharacter = 0;
	private: int botPlayTime = 500;

	private: bool playing = false;

	private: array<int>^ playerType;


	private: System::Windows::Forms::Label^  mapLabel;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  robotPanel;
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::Label^  label3;







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
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->mapLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->robotPanel = (gcnew System::Windows::Forms::Panel());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->robotPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
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
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(99, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Select Robot Roles";
			// 
			// robotPanel
			// 
			this->robotPanel->Controls->Add(this->comboBox4);
			this->robotPanel->Controls->Add(this->comboBox3);
			this->robotPanel->Controls->Add(this->comboBox2);
			this->robotPanel->Controls->Add(this->comboBox1);
			this->robotPanel->Controls->Add(this->pictureBox4);
			this->robotPanel->Controls->Add(this->pictureBox3);
			this->robotPanel->Controls->Add(this->pictureBox2);
			this->robotPanel->Controls->Add(this->pictureBox1);
			this->robotPanel->Location = System::Drawing::Point(10, 28);
			this->robotPanel->Name = L"robotPanel";
			this->robotPanel->Size = System::Drawing::Size(134, 232);
			this->robotPanel->TabIndex = 12;
			// 
			// comboBox4
			// 
			this->comboBox4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Player", L"Bot", L"Out" });
			this->comboBox4->Location = System::Drawing::Point(70, 192);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(60, 21);
			this->comboBox4->TabIndex = 7;
			this->comboBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::changedRobotPanelComboBoxIndex);
			// 
			// comboBox3
			// 
			this->comboBox3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Player", L"Bot", L"Out" });
			this->comboBox3->Location = System::Drawing::Point(70, 132);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(60, 21);
			this->comboBox3->TabIndex = 6;
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::changedRobotPanelComboBoxIndex);
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Player", L"Bot", L"Out" });
			this->comboBox2->Location = System::Drawing::Point(70, 72);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(60, 21);
			this->comboBox2->TabIndex = 5;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::changedRobotPanelComboBoxIndex);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Player", L"Bot", L"Out" });
			this->comboBox1->Location = System::Drawing::Point(70, 12);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(60, 21);
			this->comboBox1->TabIndex = 4;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &gui::changedRobotPanelComboBoxIndex);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Location = System::Drawing::Point(0, 180);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(50, 50);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(0, 120);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(50, 50);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(0, 60);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(50, 50);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(50, 50);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(38, 349);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Reset";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &gui::button4_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(38, 314);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 16;
			this->button1->Text = L"Play";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &gui::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(41, 388);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 13);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Now playing:";
			// 
			// pictureBox5
			// 
			this->pictureBox5->Location = System::Drawing::Point(50, 414);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(50, 50);
			this->pictureBox5->TabIndex = 18;
			this->pictureBox5->TabStop = false;
			// 
			// comboBox5
			// 
			this->comboBox5->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Easy", L"Medium" });
			this->comboBox5->Location = System::Drawing::Point(30, 281);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(91, 21);
			this->comboBox5->TabIndex = 19;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(50, 264);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 20;
			this->label3->Text = L"Difficulty:";
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(720, 555);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox5);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->robotPanel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->mapLabel);
			this->Controls->Add(this->mainPanel);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->Name = L"gui";
			this->Text = L"Bloqueio";
			this->Load += gcnew System::EventHandler(this, &gui::gui_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &gui::gui_KeyPress);
			this->robotPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void gui_Load(System::Object^  sender, System::EventArgs^  e)
	{
		comboBox1->SelectedIndex = 0;
		comboBox2->SelectedIndex = 1;
		comboBox3->SelectedIndex = 1;
		comboBox4->SelectedIndex = 1;

		comboBox5->SelectedIndex = 1;



		initialize();
	}

	private: void initialize()
	{
		mainPanel->Controls->Clear();

		initializeImages();
		loadRobotsPanel();

		std::vector<char> contructorList;

		for (int i = 0; i < playerType->Length; i++)
		{
			int index = ((ComboBox^)robotPanel->Controls->Find("comboBox" + (i+1), true)[0])->SelectedIndex;

			if (index != 2)
				contructorList.push_back('a' + i);
		}

		rootNode = initiateMap(contructorList);
		currNode = new Node(*rootNode);

		int index = 0, i;
		for (i = 0; i < playerType->Length; i++)
		{
			if (playerType[i] == 0)
			{
				selectedCharacter = index;
				break;
			}
			else if (playerType[i] == 1)
			{
				index++;
			}
		}

		if (i == playerType->Length)
			selectedCharacter = 0;

		pictureBox5->Image = characters[currNode->state[selectedCharacter].id - 'a'];
		pictureBox5->Refresh();

		initializeBoxes();
		loadBoxes();
	}

	private: void initializeImages()
	{
		characters = gcnew array<Image^>(4);
		goals = gcnew array<Image^>(4);

		for (size_t i = 0; i < 4; i++)
		{
			characters[i] = changeColor(Image::FromFile("images/robot.png"), 'a' + i);

			goals[i] = changeColor(Image::FromFile("images/goal.png"), 'a' + i);

			if (i % 2 == 0)
				goals[i] = rotateImage(goals[i]);
		}
	}

	void loadRobotsPanel()
	{
		PictureBox^ picbox;
		RadioButton^ button;

		robotPanel->Controls->Clear();

		for (size_t i = 0; i < 4; i++)
		{
			picbox = gcnew PictureBox();

			picbox->Image = characters[i];
			picbox->Name = "robotSelectorPicture" + i;
			picbox->Location = System::Drawing::Point(0, i * (50 + 10));
			picbox->Size = System::Drawing::Size(50, 50);
			picbox->Click += gcnew System::EventHandler(this, &gui::robotPicturePanelClick);
			robotPanel->Controls->Add(picbox);
		}

		this->robotPanel->Controls->Add(comboBox1);
		this->robotPanel->Controls->Add(comboBox2);
		this->robotPanel->Controls->Add(comboBox3);
		this->robotPanel->Controls->Add(comboBox4);


		playerType = gcnew array<int>(4);
		for (int i = 0; i < 4; i++)
		{
			int selectedIndex = ((ComboBox^)robotPanel->Controls->Find("comboBox" + (i + 1), true)[0])->SelectedIndex;

			playerType[i] = selectedIndex;
		}
	}

	private: void initializeBoxes()
	{
		mainPanel->Size = System::Drawing::Size((MAPWIDTH - 1) * 60 + 50 + 20, (MAPHEIGHT - 1) * 60 + 50 + 20);
		mainPanel->MouseClick += gcnew MouseEventHandler(this, &gui::placeBar);

		PictureBox^ picbox;
		int posX = 0, posY = 0, adder = 0;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				// Box
				picbox = gcnew PictureBox();

				posX = j * 60 + 10;
				posY = i * 60 + 10;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"box" + i + j;
				picbox->Size = System::Drawing::Size(50, 50);

				mainPanel->Controls->Add(picbox);
			}
		}

		for (size_t i = 0; i < currNode->state.size(); i++)
		{
			// Goal
			picbox = gcnew PictureBox();

			int x = currNode->state[i].objective[0];
			int y = currNode->state[i].objective[1];

			posX = 0;
			posY = 0;

			if (x == -1)
			{
				posX += 10;
				posY = y * 60;

				if (y == 8)
					posY += 60;

				picbox->Size = System::Drawing::Size(530, 10);
			}
			else
			{
				posX = x * 60;
				posY += 10;

				if (x == 8)
					posX += 60;

				picbox->Size = System::Drawing::Size(10, 530);
			}

			picbox->Location = System::Drawing::Point(posX, posY);
			picbox->Name = L"goal" + i;
			

			mainPanel->Controls->Add(picbox);
		}
	}

	void loadBoxes()
	{
		block = Image::FromFile("images/wall.png");
		bar = Image::FromFile("images/bar.png");

		Image^ currImage;
		int index;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				getPictureBox("box" + i + j)->BackgroundImage = block;
			}
		}

		for (int i = 0; i < currNode->state.size(); i++)
		{
			getPictureBox("box" + currNode->state[i].coords[1] + currNode->state[i].coords[0])->Image = characters[currNode->state[i].id - 'a'];
			getPictureBox("goal" + i)->Image = goals[currNode->state[i].id - 'a'];
		}

	}


	void placeBar(System::Object^  sender, MouseEventArgs^  e)
	{
		int x = e->X - 10;
		int y = e->Y - 10;

		int j = x / 60;
		int i = y / 60;

		if (playing || x % 60 >= 50 && y % 60 >= 50) // Ambigous position
		{
			return;
		}

		if (x % 60 >= 50) // Vertical line
		{
			if (i == MAPHEIGHT - 1)
				i--;

			if (addBar("barVer", i, j))
			{
				incrementPlayer();
				playCharacter();
			}
		}
		else if (y % 60 >= 50) // Horizontal line
		{
			if (j == MAPWIDTH - 1)
				j--;

			if (addBar("barHor", i, j))
			{
				incrementPlayer();
				playCharacter();
			}
		}
	}

	bool addBar(std::string type, int i, int j)
	{
		if (validBar(currNode, selectedCharacter, type, i, j))
		{
			if (type == "barVer")
			{
				PictureBox^ picbox = gcnew PictureBox();

				int posX = j * 60 + 50 + 10;
				int posY = i * 60 + 10;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"barVer" + i + j;
				picbox->Size = System::Drawing::Size(10, 110);
				picbox->Image = changeColor(bar, currNode->state[selectedCharacter].id);

				mainPanel->Controls->Add(picbox);
				picbox->Refresh();

				if (!currNode->state[selectedCharacter].addWall(type + std::to_string(i) + std::to_string(j)))
					return false;

				return true;
			}
			else if (type == "barHor")
			{
				PictureBox^ picbox = gcnew PictureBox();

				int posX = j * 60 + 10;
				int posY = i * 60 + 50 + 10;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"barHor" + i + j;
				picbox->Size = System::Drawing::Size(110, 10);
				picbox->Image = rotateImage(changeColor(bar, currNode->state[selectedCharacter].id));

				mainPanel->Controls->Add(picbox);
				picbox->Refresh();

				if (!currNode->state[selectedCharacter].addWall(type + std::to_string(i) + std::to_string(j)))
					return false;

				return true;
			}
		}

		return false;
	}


	private: System::Void gui_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		if (currNode != NULL && playing && !currNode->finished() && playerType[currNode->state[selectedCharacter].id - 'a'] == 0)
		{
			std::vector<char> letters = { 'w', 'd', 's', 'a' };
			Node* nextNode;
			int i;
			for (i = 0; i < letters.size(); i++)
			{
				if (letters[i] == e->KeyChar)
				{
					nextNode = doOperation(currNode, i, selectedCharacter);

					if (currNode == nextNode)
					{
						return;
					}

					setNode(&currNode, &nextNode);

					if (checkWin())
						return;

					incrementPlayer();
					playCharacter();

					return;
				}
			}
		}
	}
	

	bool checkWin()
	{
		if (currNode->finished())
		{
			MessageBox::Show("Player " + (selectedCharacter + 1) + " won!");
			return true;
		}

		return false;
	}


	void playCharacter()
	{
		if (playing && playerType[currNode->state[selectedCharacter].id - 'a'] == 1)
		{
			auto begin = std::chrono::high_resolution_clock::now();

			Node* bestMove = minimax(currNode, selectedCharacter, MINIMAXDEPTH, comboBox5->SelectedIndex);
			while (bestMove->parent != currNode)
			{
				bestMove = bestMove->parent;
			}

			int deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() / (double)1e6;
			std::cout << "\nFinished in : " << deltaTime << " milliseconds.\n";

			int remainingTime = botPlayTime - deltaTime;

			if (remainingTime > 0)
				ui_utilities::milliSleep(remainingTime);

			setNode(&currNode, &bestMove);

			if (checkWin())
				return;

			incrementPlayer();
			playCharacter();
		}
	}

	void incrementPlayer()
	{
		selectedCharacter = (selectedCharacter + 1) % currNode->state.size();

		pictureBox5->Image = characters[currNode->state[selectedCharacter].id - 'a'];
		pictureBox5->Refresh();
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

	//System::String^ convertString(std::string input)
	//{
	//	System::String^ output = "";

	//	for (size_t i = 0; i < input.size(); i++) // copy
	//	{
	//		output = output + convertString(std::to_string(input[i]));
	//	}

	//	return output;
	//}

	void setNode(interior_ptr<Node*> node1, interior_ptr<Node*> node2)
	{
		pin_ptr<Node*> ptr1 = node1;
		pin_ptr<Node*> ptr2 = node2;

		setNode2(ptr1, ptr2);
	}

	void setNode2(Node** node1, Node** node2)
	{
		int index = 0;
		for (size_t i = 0; i < (*node2)->state.size(); i++)
		{
			getPictureBox("box" + (*node1)->state[i].coords[1] + (*node1)->state[i].coords[0])->Image = nullptr;
			getPictureBox("box" + (*node1)->state[i].coords[1] + (*node1)->state[i].coords[0])->Refresh();

			getPictureBox("box" + (*node2)->state[i].coords[1] + (*node2)->state[i].coords[0])->Image = characters[(*node2)->state[i].id - 'a'];
			getPictureBox("box" + (*node2)->state[i].coords[1] + (*node2)->state[i].coords[0])->Refresh();

			for (auto wall : (*node2)->state[i].walls)
			{
				String^ wallType = gcnew String(wall.substr(0, 6).c_str());
				int wallI = stoi(wall.substr(6, 1));
				int wallJ = stoi(wall.substr(7, 1));

				PictureBox^ picbox = getPictureBox(wallType + wallI + wallJ);

				if (picbox == nullptr)
					addBar(convertString(wallType), wallI, wallJ);
			}
		}


		*node1 = *node2;
	}


	void resetMap()
	{
		initialize();
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
				Color pixel = bitmap->GetPixel(j, i);

				if (robotId == 'b') // Blue
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(j, i, Color::FromArgb(pixel.A, 0, 0, pixel.R));
					}
				}
				else if (robotId == 'c') // Yellow
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(j, i, Color::FromArgb(pixel.A, pixel.R, pixel.R, 0));
					}
				}
				else if (robotId == 'd') // Green
				{
					if (pixel.R > 0 && pixel.B == 0 && pixel.G == 0)
					{
						((Bitmap^)output)->SetPixel(j, i, Color::FromArgb(pixel.A, 0, pixel.R, 0));
					}
				}
				else
				{
					int a = 0;
					// Error
				}

			}
		}

		return output;
	}

	Image^ rotateImage(Image^ img)
	{
		Bitmap^ bmp = gcnew Bitmap(img);

		Graphics^ gfx = Graphics::FromImage(bmp);
		gfx->Clear(Color::White);
		gfx->DrawImage(img, 0, 0, img->Width, img->Height);

		bmp->RotateFlip(RotateFlipType::Rotate90FlipNone);
		return bmp;
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

	void selectRobotButton(int index)
	{
		selectedCharacter = index;

		((RadioButton^)robotPanel->Controls->Find("robotSelectorButton" + index, true)[0])->Checked = true;
	}


	PictureBox^ getPictureBox(System::String^ name)
	{
		auto findings = mainPanel->Controls->Find(name, true);

		if (findings->Length == 0)
			return nullptr;
		else
			return (PictureBox^)findings[0];
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		playing = true;
		playCharacter();
	}
	
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		resetMap();
	}

	private: System::Void changedRobotPanelComboBoxIndex(System::Object^  sender, System::EventArgs^  e)
	{
		playing = false;
	}
};
}
