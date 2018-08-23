#include "display.h"

std::string getFileContents(std::ifstream&);            //Gets file contents
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


// console width 80
// console height 25
void startscreen()
{

	std::ifstream Reader("startscreen.txt");             //Open file
	getFileContents(Reader);       //Get file
	Reader.close();                           //Close file


	string startprompt = { "Press Enter to start                      " };

	char holder = ' ';
	int len, x;
	len = startprompt.length();

	bool exit = true;
	while (exit) {
		if (GetAsyncKeyState(VK_RETURN))
		{
			exit = false;
		}
		gotoXY(20, 18, startprompt);
		holder = startprompt[len];
		for (x = len; x>0; x--)
		{
			startprompt[x] = startprompt[x - 1];
		}
		startprompt[0] = holder;
		Sleep(100);
	} 
}
int select(vector<Hero> team1) {
	int len = 58;
	int x = x + len / 2 + 2;
	int y = 19;

	while (true) {
		if (y < 19 or y > team1.size() - 1 + y) {
			y = 19;
		}
		gotoXY(x, y, ">");
		if (GetAsyncKeyState(VK_DOWN))
		{
			y--;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			y++;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		Sleep(100);
	}
	return 0;
}
void endscreen()
{
}

void textbox(vector<Hero> team)
{
	int len, x, y;
	x = 10;
	y = 18;
	len = 58;
	string border(len, '\xCD');
	gotoXY(x, y);
	cout << "\xC9" << border << "\xBB" << endl;
	y++;
	gotoXY(x, y);
	y++;
	for (int i = 0; i < team.size() + 1; i++) {
		cout << "\xBA" << string(len / 2, ' ') << "|" << string(len / 2, ' ') << "\b\xBA" << endl;
		gotoXY(x, y);
		y++;
	}
	cout << "\xC8" << border << "\xBC" << endl;

	x = 11;
	y = 19;
	gotoXY(x + len / 2 + 4, y);
	cout << "Team " << team[0].getTeamNumber() << string(9, ' ') << "HP";
	y++;
	gotoXY(x + len / 2 + 4, y);
	for (auto i : team) {
		cout << i.getName() << string(11 - i.getName().size(), ' ') << "    " << i.getHealth() << "/" << i.getMaxHealth();
		y++;
		gotoXY(x + len / 2 + 4, y);
	}
}

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines
	if (File)                      //Check if everything is good
	{
		int x = 20;
		int y = 5;
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			gotoXY(x, y, TempLine);
			cout<< endl;
			y++;
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
	SetConsoleCursorPosition(console, CursorPosition);
}