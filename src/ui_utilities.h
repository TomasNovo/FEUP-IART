#ifndef _UI_UTILITIES_H
#define _UI_UTILITIES_H

#include <iostream>
#include <string>
#include <chrono>

/**
 * @brief      Class with functions that facilitates both the clearing as well as resizing of the console/terminal.
 */
class ui_utilities{

	unsigned int width = 100;
	unsigned int height = 35;

public:
	
	/**
	 * @brief      Clears the console/terminal.
	 */
	static void ClearScreen();

	/**
	 * @brief      Sets the console/terminal window size.
	 *
	 * @param[in]  width   The width
	 * @param[in]  height  The height
	 *
	 * @return     True if sucessful and False otherwise
	 */
	static bool SetWindow(const int& width, const int& height);

	static void milliSleep(int milliseconds);

};

#endif