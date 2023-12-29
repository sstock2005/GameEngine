#include <iostream> // for std
#include <windows.h> // for sleep
#include <thread> // for thread
#include <chrono> // for std::chrono

static int ky = 5; // Global Player Y
static int kx = 0; // Global Player X
static int ticks = 0; // Ticks
static double fps = 0; // Frames Per Second

std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now(); // start new timer
std::chrono::steady_clock::time_point end_time; // create memory spot for end time
std::chrono::duration<double> elapsed_time; // create memory spot for elapsed time

/* Function to Draw Player (may change) */
void DrawPlayer(int lx, int ly)
{
	system("CLS"); // clear console
	std::string point = "[+]\n"; // create player object
	if (lx > 0) { // as long as local x is greater than 0
		for (int i = 0; i < lx; i++) // move player to the left until it matches with given player x position
		{
			point = " " + point; // move
		}
	}

	int i = 20; // how many blank spaces added in the following line
	std::string default_space = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; // 20 blank spaces to render, will have to change to add objects
	while (i != ly)  // as long as given player y position is above the bottom of the console
	{
		if (i > ly) // if input is less than the 20 blank spaces
		{
			size_t pos = default_space.find("\n"); // find first blank space in default_space
			if (pos != std::string::npos) // find position of first blank space
			{
				default_space[pos] = NULL; // NULL it (delete it)
			}
			point = point + "\n"; // Balance 
			i--; // reflect changes to int i
		}

		if (i < ly) // if input is more than the 20 blank spaces
		{
			default_space = default_space + "\n"; // add blank space
		}
	}

	point = default_space + point; // add spaces to player object
	std::cout << point; // print player to screen
	std::cout << "========================================================================================================================\n"; // print ground
	std::cout << "[DEBUG]\nFPS: " << fps << "\nPlayer X : " << lx << "\nPlayer Y : " << ly << "\n"; // print debug
	std::cout << "\n[CONTROLS]\n[UP] Move Player Up [DOWN] Move Player Down\n"; // print controls
}

/* Function to render to screen */
void Render() {
	while (true) { // forever!

		end_time = std::chrono::steady_clock::now(); // set end time
		elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time); // set elapsed time
		start_time = std::chrono::steady_clock::now(); // restart start time

		ticks++; // add to ticks

		fps = ticks / elapsed_time.count(); // calculate frames per second

		ticks = 0; // reset ticks
		start_time = std::chrono::steady_clock::now(); // restart time again
		DrawPlayer(kx, ky); // draw player

		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Add a small delay to avoid excessive CPU usage
	}
}

/* Function to read player input */
void ReadInput()
{
	while (true)
	{
		// Check for key states only once per iteration
		bool upKeyPressed = GetKeyState(VK_UP) & 0x8000;
		bool downKeyPressed = GetKeyState(VK_DOWN) & 0x8000;
		bool leftKeyPressed = GetKeyState(VK_LEFT) & 0x8000;
		bool rightKeyPressed = GetKeyState(VK_RIGHT) & 0x8000;

		if (upKeyPressed) // if up key
		{
			if (ky > 0) // if global y is greater than 0
			{
				ky = ky - 1; // move player up 1
			}
		}

		if (downKeyPressed) // if down key
		{
			if (ky < 20) // if global y is smaller than 20
			{
				ky = ky + 1; // move player down 1
			}
		}
		if (leftKeyPressed) // if left key
		{
			if (kx > 0) // if global x is greater than 0
			{
				kx = kx - 1; // move to the left
			}
		}
		if (rightKeyPressed) //if right key
		{
			if (kx < 116) // if global x is less than 116
			{
				kx = kx + 1; // move to the right ( I actually don't know how this works in DrawPlayer???)
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Add a small delay to avoid excessive CPU usage
	}
}

/* Main Function */
int main()
{
	system("TITLE Game From Scratch"); // set console title
	std::thread t{ Render }; // create thread object and start it
	ReadInput(); // start reading input
	t.join(); // "wait" for them to join (finish)
	std::cin.get(); // wait for user input to close game (will never happen)
}