#include "display.h"
// console width 80
// console height 25

std::string getFileContents(std::ifstream&);            //Gets file contents
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//read the file and print line by line
std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines
	if (File)                      //Check if everything is good
	{
		int x = 18;
		int y = 10;
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			gotoXY(x, y, TempLine);
			cout << endl;
			y++;
		}
		return Lines;

	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}

std::string getFileContentsReverse(std::ifstream& File)
{
	std::string Lines = "";        //All lines
	if (File)                      //Check if everything is good
	{
		int x = 10;
		int y = 5;
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			reverse(TempLine.begin(),TempLine.end());
			gotoXY(x, y, TempLine);
			cout << endl;
			y++;
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}

void startScreen()
{

	std::ifstream Reader("startscreen.txt");             //Open file
	getFileContents(Reader);       //Get file
	Reader.close();                           //Close file


	string startprompt = { "Press Enter to start                      " };

	char holder = ' ';
	int len, x;
	len = startprompt.length();

	// string startprompt rotates until Enter key is pressed
	bool exit = true;
	while (exit) {
		if (GetAsyncKeyState(VK_RETURN))
		{
			exit = false;
		}
		gotoXY(20, 22, startprompt);
		holder = startprompt[len];
		for (x = len; x>0; x--)
		{
			startprompt[x] = startprompt[x - 1];
		}
		startprompt[0] = holder;
		Sleep(100);
	} 
}

void printHero() {
	std::ifstream Reader("mage.txt");             //Open file
	getFileContentsReverse(Reader);       //Get file
	Reader.close();                           //Close file
}

void endScreen()
{
}

//returns index of the hero user selected
int select(int size) {
	int len = 58;
	int x = 11 + len / 2 + 2;
	int y = 35;

	//keeps track of cursor's y position when UP or DOWN arrow key is pressed
	//infinite loop until Enter key is pressed
	while (true) {
		if (y < 35) {
			y = 35 + size - 1;
		}
		else if (y > 35 + size - 1) {
			y = 35;
		}
		gotoXY(x, y, ">");
		if (GetAsyncKeyState(VK_DOWN))
		{
			gotoXY(x, y, " ");
			y++;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			gotoXY(x, y, " ");
			y--;
		}
		Sleep(100);
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		Sleep(200);
	}
	return y % 35;
}

//displays team number, member of the team and their current and max health
void showStat(vector<shared_ptr<Hero>>& team, bool target)
{
	//clears textbox
	border();

	int x = 11;
	int y = 34;
	int len = 58;
	gotoXY(x + len / 2 + 4, y);
	cout << "Team " << team[0]->getTeamNumber() << string(9, ' ') << "HP";
	y++;
	gotoXY(x + len / 2 + 4, y);
	for (auto i : team) {
		cout << i->getName() << string(11 - i->getName().size(), ' ') << "    " << i->getHealth() << "/" << i->getMaxHealth();
		y++;
		gotoXY(x + len / 2 + 4, y);
	}

	x = 11;
	y = 35;

	//shows different prompt if the function was called for defending team
	if (!target) {
		gotoXY(x + 3, y);
		cout << "Select Character";
	}
	else {
		gotoXY(x + 3, y);
		cout << "Select Target";
	}
}

//randomly select damage from min/max value and displays results
void showAttack(shared_ptr<Hero>& hero, shared_ptr<Hero>& target)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> damage(hero->getMinDamage(), hero->getMaxDamage()); // define the range
	int attack = damage(eng);

	border();
	int x = 11;
	int y = 35;

	gotoXY(x + 2, y);
	cout << hero->getName() << " attacks " << target->getName(); 
	gotoXY(x + 2, y+1);
	cout << "with " << hero->getAbility(); 
	gotoXY(x + 2, y+2);
	cout << "and inflicts " << attack << " damage" << endl;
	
	animation(hero->getAbility());

	//subtract damage from HP
	target->setHealth(attack);
}

//TODO implement multiple ablility hero/choice
//displays abilitis of the chosen hero
void showAbility(shared_ptr<Hero>& hero)
{
	border();
	int x = 11;
	int y = 34;
	int len = 58;
	gotoXY(x + len / 2 + 4, y);
	cout << hero->getName() << "'s Abilities";
	y++;
	gotoXY(x + len / 2 + 4, y);
	
	cout << hero->getAbility();
	y++;
	gotoXY(x + len / 2 + 4, y);


	x = 11;
	y = 35;
	gotoXY(x + 3, y);
	cout << "What will " << hero->getName() << " do?";
	
}

//creates a textbox to show text displays
//entirely clears the contents of the textbox
void border()
{
	int len, x, y;
	x = 10;
	y = 33;
	len = 58;
	string border(len, '\xCD');
	gotoXY(x, y);
	cout << "\xC9" << border << "\xBB" << endl;
	y++;
	gotoXY(x, y);
	y++;
	for (int i = 0; i < 6; i++) {
		cout << "\xBA" << string(len / 2, ' ') << "|" << string(len / 2, ' ') << "\b\xBA" << endl;
		gotoXY(x, y);
		y++;
	}
	cout << "\xC8" << border << "\xBC" << endl;
}

//clears contents only if the left or the right or both
void clearBox(bool left, bool right) {
	int len, x, y;
	x = 11;
	y = 19;
	len = 58;
	
	if (left) {
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y);
			cout << string(len / 2, ' ');
			y++;
		}
	}

	if (right) {
		x = x + len / 2 + 3;
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y);
			cout << string(len / 2, ' ');
			y++;
		}
	}

}

//cursor changer
void gotoXY(int x, int y, string text)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << text;
}

//cursor changer
void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}