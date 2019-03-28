#include "ui_utilities.h"

#ifdef _WIN32

#include <windows.h>

void ui_utilities::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

	/* Move the cursor home */
			SetConsoleCursorPosition(hStdOut, homeCoords);
	}

	bool ui_utilities::SetWindow(const int& Width, const int& Height)
	{
		_COORD coord;
		coord.X = Width;
		coord.Y = Height;

		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = Height - 1;
		Rect.Right = Width - 1;

		// Get handle of the standard output 
		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Handle == NULL)
		{
			std::cout << "Failure in getting the handle\n" << GetLastError();
			return FALSE;
		}

		// Set screen buffer size to that specified in coord 
		if (!SetConsoleScreenBufferSize(Handle, coord))
		{
			std::cout << "Failure in setting buffer size\n" << GetLastError();
			return FALSE;
		}

		// Set the window size to that specified in Rect 
		if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
		{
			std::cout << "Failure in setting window size\n" << GetLastError();
			return FALSE;
		}
		
		return TRUE;
	}

	void ui_utilities::milliSleep(int milliseconds)
	{
		Sleep(milliseconds);
	}

#else

	#include <unistd.h>

	void ui_utilities::ClearScreen()
	{
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
	}

	bool ui_utilities::SetWindow(const int& width, const int& height)
	{
		string res = "\e[8;";
		res += to_string(height);
		res += ";";
		res += to_string(width);
		res += "t";
		cout << res;

		return true;
	}

	void ui_utilities::milliSleep(int milliseconds)
	{
		usleep(milliseconds*1000);
	}


#endif
