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

	private: System::Windows::Forms::Label^  mapLabel;
	private: System::Windows::Forms::Button^  button1;






	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  robotPanel;
	private: System::Windows::Forms::Button^  button2;
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
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->mapLabel = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->robotPanel = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
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
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(693, 540);
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
			//boxes[i] = (gcnew cli::array<PictureBox^>(MAPWIDTH));

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
		}
		else if (e->Y % 60 >= 50) // Horizontal line
		{
			int j = e->X / 60;
			int i = e->Y / 60;

			if (j == MAPWIDTH - 1)
				j--;

			addBar("barHor", i, j);
		}
	}

	void addBar(String^ type, int i, int j)
	{
		if (validBar(currNode, selectedCharacter, convertString(type), i, j))
		{
			if (type == "barVer")
			{
				PictureBox^ picbox = gcnew PictureBox();

				int posX = j * 60 + 50;
				int posY = i * 60;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"barVer" + i + j;
				picbox->Size = System::Drawing::Size(10, 110);
				picbox->Image = bar;

				mainPanel->Controls->Add(picbox);
			}
			else if (type == "barHor")
			{
				PictureBox^ picbox = gcnew PictureBox();

				int posX = j * 60;
				int posY = i * 60 + 50;

				picbox->Location = System::Drawing::Point(posX, posY);
				picbox->Name = L"barHor" + i + j;
				picbox->Size = System::Drawing::Size(110, 10);
				picbox->Image = RotateImage(bar);

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

	private: System::Void gui_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		if (currNode != NULL && !currNode->finished())
		{
			std::vector<char> letters = { 'w', 'd', 's', 'a' };
			Node* nextNode;
			int i;
			for (i = 0; i < letters.size(); i++)
			{
				if (letters[i] == e->KeyChar)
				{
					nextNode = doOperation(currNode, i, selectedCharacter);

					if (*currNode == *nextNode)
					{
						delete nextNode;
						return;
					}

					nextNode->cost++;
					nextNode->parent = currNode;
					nextNode->operationName = operationNames[i];

					setNode(currNode, nextNode);

					if (currNode->finished())
					{
						int optimalCost = aStar2(rootNode, 0)->cost;
						MessageBox::Show("You finsihed the map in " + currNode->cost + " moves. The optimal solution is " + optimalCost + ".");
						resetMap();
						break;
					}

					incrementPlayer();
					playBots();

					break;
				}
			}
		}
	}


	void playBots()
	{
		for (size_t i = 1; i < currNode->state.size(); i++)
		{
			playCharacter();
			incrementPlayer();

			ui_utilities::milliSleep(1000);
		}
	}

	void playCharacter()
	{
		Node* bestMove = minimax(currNode, selectedCharacter, 2);

		while (bestMove->parent != currNode)
		{
			bestMove = bestMove->parent;
		}

		setNode(currNode, bestMove);
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

	System::String^ convertString(std::string input)
	{
		System::String^ output = "";

		for (size_t i = 0; i < input.size(); i++) // copy
		{
			output->Concat((char)input[i]);
		}

		return output;
	}

	void setNode(Node* node1, Node* node2)
	{
		int index;
		for (size_t i = 0; i < node2->state.size(); i++)
		{
			getPictureBox("box" + node1->state[i].coords[1] + node1->state[i].coords[0])->Image = nullptr;
			getPictureBox("box" + node1->state[i].coords[1] + node1->state[i].coords[0])->Refresh();

			getPictureBox("box" + node2->state[i].coords[1] + node2->state[i].coords[0])->Image = characters[i];
			getPictureBox("box" + node2->state[i].coords[1] + node2->state[i].coords[0])->Refresh();

			for (auto wall : node2->state[i].walls)
			{
				String^ wallType = convertString(wall.substr(0, 6));
				int wallI = stoi(wall.substr(6, 1));
				int wallJ = stoi(wall.substr(7, 1));

				PictureBox^ picbox = getPictureBox(wallType + wallI + wallJ);

				if (picbox == nullptr)
					addBar(wallType, wallI, wallJ);
			}
		}


		*node1 = *node2;
		delete node2;
	}


	void resetMap()
	{
		setNode(currNode, rootNode);

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

	
};
}
