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

	private: cli::array<cli::array<PictureBox^>^>^ boxes;
	private: cli::array<PictureBox^>^ bars;

	private: Image^ block;
	private: Image^ bar;
	private: array<Image^>^ characters;

	private: Node* rootNode;
	private: Node* currNode;

	private: int selectedCharacter = 0;

	private: bool playing = false;

	private: System::Windows::Forms::Label^  mapLabel;
	private: System::Windows::Forms::Button^  button1;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  robotPanel;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;









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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->robotPanel = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
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
			// button1
			// 
			this->button1->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->button1->Location = System::Drawing::Point(33, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Minimax";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &gui::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(35, 188);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Current Robot";
			// 
			// robotPanel
			// 
			this->robotPanel->Location = System::Drawing::Point(12, 215);
			this->robotPanel->Name = L"robotPanel";
			this->robotPanel->Size = System::Drawing::Size(117, 205);
			this->robotPanel->TabIndex = 12;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(33, 63);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 13;
			this->button2->Text = L"NodeH";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &gui::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(33, 106);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 14;
			this->button3->Text = L"CharacterH";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &gui::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(33, 151);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 15;
			this->button4->Text = L"Reset";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &gui::button4_Click);
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(693, 540);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->robotPanel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->mapLabel);
			this->Controls->Add(this->mainPanel);
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
		mainPanel->Size = System::Drawing::Size((MAPWIDTH - 1) * 60 + 50, (MAPHEIGHT - 1) * 60 + 50);
		mainPanel->MouseClick += gcnew MouseEventHandler(this, &gui::placeBar);

		PictureBox^ picbox;
		int posX = 0, posY = 0, adder = 0;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				// Box
				picbox = gcnew PictureBox();

				posX = j * 60;
				posY = i * 60;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"box" + i + j;
				picbox->Size = System::Drawing::Size(50, 50);

				mainPanel->Controls->Add(picbox);
			}
		}
	}

	void loadBoxes()
	{
		block = Image::FromFile("images/wall.png");
		bar = Image::FromFile("images/bar.png");
		characters = gcnew array<Image^>(currNode->state.size());

		Image^ currImage;
		int index;
		for (size_t i = 0; i < MAPHEIGHT; i++)
		{
			for (size_t j = 0; j < MAPWIDTH; j++)
			{
				getPictureBox("box" + i + j)->BackgroundImage = block;
			}
		}

		for (size_t i = 0; i < currNode->state.size(); i++)
		{
			characters[i] = changeColor(Image::FromFile("images/robot.png"), currNode->state[i].id);
			getPictureBox("box" + currNode->state[i].coords[1] + currNode->state[i].coords[0])->Image = characters[i];
		}
	}

	void placeBar(System::Object^  sender, MouseEventArgs^  e)
	{
		if (e->X % 60 >= 50 && e->Y % 60 >= 50) // Ambigous position
		{
			return;
		}

		if (e->X % 60 >= 50) // Vertical line
		{
			int j = e->X / 60;
			int i = e->Y / 60;

			if (i == MAPWIDTH - 1)
				i--;

			addBar("barVer", i, j);

			//incrementPlayer();
			//playBots();
		}
		else if (e->Y % 60 >= 50) // Horizontal line
		{
			int j = e->X / 60;
			int i = e->Y / 60;

			if (j == MAPWIDTH - 1)
				j--;

			addBar("barHor", i, j);

			//incrementPlayer();
			//playBots();
		}
	}

	bool addBar(std::string type, int i, int j)
	{
		if (validBar(currNode, selectedCharacter, type, i, j))
		{
			if (type == "barVer")
			{
				PictureBox^ picbox = gcnew PictureBox();

				int posX = j * 60 + 50;
				int posY = i * 60;

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

				int posX = j * 60;
				int posY = i * 60 + 50;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"barHor" + i + j;
				picbox->Size = System::Drawing::Size(110, 10);
				picbox->Image = RotateImage(changeColor(bar, currNode->state[selectedCharacter].id));

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
		if (currNode != NULL && !playing && !currNode->finished())
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
					
					playBots();

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

	void playBots()
	{
		playing = true;
		for (size_t i = 1; i < currNode->state.size(); i++)
		{
			//ui_utilities::milliSleep(250);

			auto begin = std::chrono::high_resolution_clock::now();
			
			playCharacter();

			double deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() / (double)1e9;
			std::cout << "\nFinished in : " << deltaTime << " seconds.\n";

			if (checkWin())
				return;

			incrementPlayer();
		}

		playing = false;
	}

	void playCharacter()
	{
		Node* bestMove = minimax(currNode, selectedCharacter, 1);

		while (bestMove->parent != currNode)
		{
			bestMove = bestMove->parent;
		}

		setNode(&currNode, &bestMove);
	}

	void incrementPlayer()
	{
		selectedCharacter = (selectedCharacter + 1) % currNode->state.size();
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

			getPictureBox("box" + (*node2)->state[i].coords[1] + (*node2)->state[i].coords[0])->Image = characters[i];
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
		mainPanel->Controls->Clear();

		initializeBoxes();

		setNode(&currNode, &rootNode);

		loadBoxes();
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

	Image^ RotateImage(Image^ img)
	{
		Bitmap^ bmp = gcnew Bitmap(img);

		Graphics^ gfx = Graphics::FromImage(bmp);
		gfx->Clear(Color::White);
		gfx->DrawImage(img, 0, 0, img->Width, img->Height);

		bmp->RotateFlip(RotateFlipType::Rotate90FlipNone);
		return bmp;
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		playCharacter();
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		MessageBox::Show("Heuristic is " + currNode->h);
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		MessageBox::Show("Heuristic is " + currNode->getDistance(0));
	}

	
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		resetMap();
	}
};
}
