#include "display.h"

std::string getFileContents(std::ifstream&);            //Gets file contents
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


// console width 80
// console height 25
void printscreen(string filename)
{

	std::ifstream Reader(filename + ".txt");             //Open file
	std::string Art = getFileContents(Reader);       //Get file
	std::cout << Art << std::endl;               //Print it to the screen
	Reader.close();                           //Close file


	string Plane[] = { "Press Enter to start                      " };

	char holder = ' ';
	int len, x, y;
	len = Plane[0].length();

	bool exit = true;
	while (exit) {
		if (GetAsyncKeyState(VK_RETURN))
		{
			exit = false;
		}
		for (y = 0; y<1; y++)
		{
			gotoXY(20, 18, Plane[y]);
		}

		for (y = 0; y<1; y++)
		{
			holder = Plane[y][len];
			for (x = len; x>0; x--)
			{

				Plane[y][x] = Plane[y][x - 1];
			}
			Plane[y][0] = holder;
		}

		Sleep(100);
	} 
}

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}




void gotoXY(int x, int y, string text)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << text;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
}