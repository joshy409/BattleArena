#include "display.h"
// console width 80
// console height 25


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//read the file and print line by line
string getFileContents(std::ifstream& File, int x, int y)
{
	string Lines = "";        //All lines
	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			string TempLine;                  //Temp line
			getline(File, TempLine);        //Get temp line
			gotoXY(x, y, TempLine);			//print Templine at given x,y cursor position
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
	getFileContents(Reader, 18, 10);       //Get file
	Reader.close();                           //Close file


	string startprompt = { "Press Enter to start                      " };

	char holder = ' ';
	int len, x;
	len = startprompt.length();

	// string startprompt rotates until Enter key is pressed
	
	while (true) {
		gotoXY(20, 22, startprompt);
		holder = startprompt[len];
		for (x = len; x>0; x--)
		{
			startprompt[x] = startprompt[x - 1];
		}
		startprompt[0] = holder;
		Sleep(100);

		if (GetAsyncKeyState(VK_RETURN)) {
			while (true) {
				if (!GetAsyncKeyState(VK_RETURN)) {
					break;
				}
			}
			break;
		}
	} 
	//clear the screen
	system("CLS");
	

	//creat a textbox to display text for the game
	x = 10;
	int y = 30;
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


void printHero(vector<shared_ptr<Hero>>& team) {
	int x;
	int y = 2;

	if (team[0]->getTeamNumber() == "1") {
		x = 10;
		for (auto i : team) {
			if (i->getHealth() == 0) {
				grave(i->getName(), "1", x, y);
				y += 10;
			}
			else {
				printHeroByName(i, x, y);
				y += 10;
			}
		}
	} else {
		x = 70;
		for (auto i : team) {
			if (i->getHealth() == 0) {
				grave(i->getName(), "2",x,y);
				y += 10;
			}
			else {
				printHeroByName(i, x - i->getWidth(), y);
				y += 10;
			}
		}
	}
    
}

void printHeroByName(shared_ptr<Hero>& hero, int x, int y)
{
	for (auto i : hero->getAscii()) {
		gotoXY(x, y);
		cout << i;
		y++;
	}

}

void grave(string name, string teamNumber, int x, int y) {
	//int len = (9 - name.size()) / 2;
	//int len2 = (9 - name.size()) - (9 - name.size()) / 2;

	if (teamNumber == "1") {
		vector<string> team1grave = { "     _|_     "
			,"   ___|___   "
			," /~/~     ~\\ "
			,"| |         |"
			,"| |" + string((9 - name.size()) - (9 - name.size()) / 2,' ') + name + string((9 - name.size()) / 2,' ') + "|"
			,"| |         |"
			,"| |         |"
			,"|_|_ _ _ __ |" };

		for (auto i : team1grave) {
			gotoXY(x, y);
			cout << i;
			y++;
		}
	}
	else {
		vector<string> team2grave = { "     _|_     "
			,"   ___|___   "
			," /~     ~\\~\\ "
			,"|         | |"
			,"|" + string((9 - name.size()) / 2,' ') + name + string((9 - name.size()) - (9 - name.size()) / 2,' ') + "| |"
			,"|         | |"
			,"|         | |"
			,"|_ _ _ __ |_|" };

		for (auto i : team2grave) {
			gotoXY(x, y);
			cout << i;
			y++;
		}
	}
}

void endScreen(string winningTeam)
{
	int x = 22;
	int y = 12;
	system("CLS");
	if (winningTeam == "1") {
		std::ifstream Reader("Team1win.txt");             //Open file
		getFileContents(Reader, x, y);       //Get file
		Reader.close();                           //Close file
	}
	else {
		std::ifstream Reader("Team2win.txt");             //Open file
		getFileContents(Reader, x, y);       //Get file
		Reader.close();                           //Close file
	}
}

//returns index of the hero user selected
int select(int size) {
	int len = 58;
	int x = 11 + len / 2 + 2;
	int y = 32;

	//keeps track of cursor's y position when UP or DOWN arrow key is pressed
	//infinite loop until Enter key is pressed
	while (true) {
		if (y < 32) {
			y = 32 + size - 1;
		}
		else if (y > 32 + size - 1) {
			y = 32;
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
			while (true) {
				if (!GetAsyncKeyState(VK_RETURN)) {
					break;
				}
			}
			break;
		}
		Sleep(200);
	}
	return y % 32;
}

//displays team number, member of the team and their current and max health
void showStat(vector<shared_ptr<Hero>>& team, bool target)
{
	//clears textbox
	clearBox(true, true, false);

	int x = 11;
	int y = 31;
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
	y = 32;

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

	clearBox(true, true, false);
	int x = 11;
	int y = 32;
	int len = 58;
	gotoXY(x + 2, y);
	cout << hero->getName() << " attacks " << target->getName(); 
	gotoXY(x + 2, y+1);
	cout << "with " << hero->getAbility(); 
	
	animation(hero,target);

	gotoXY(x + len / 2 + 3, y);
	cout << hero->getAbility() << " did "; 
	gotoXY(x + len / 2 + 3, y+1);
	cout << attack << " damage" << endl;

	while (true) {
		gotoXY(66,36, "^");
		if (GetAsyncKeyState(VK_RETURN)) {
			while (true) {
				if (!GetAsyncKeyState(VK_RETURN)) {
					break;
				}
			}
			break;
		}
	}


	//subtract damage from HP
	target->setHealth(attack);
}

//TODO implement multiple ablility hero/choice
//displays abilitis of the chosen hero
void showAbility(shared_ptr<Hero>& hero)
{
	clearBox(true, true, false);
	int x = 11;
	int y = 31;
	int len = 58;
	gotoXY(x + len / 2 + 4, y);
	cout << hero->getName() << "'s Abilities";
	y++;
	gotoXY(x + len / 2 + 4, y);
	
	cout << hero->getAbility();
	y++;
	gotoXY(x + len / 2 + 4, y);


	x = 11;
	y = 32;
	gotoXY(x + 3, y);
	cout << "What will " << hero->getName() << " do?";
	
}

//clears contents only if the left or the right or both
void clearBox(bool left, bool right, bool up) {
	int len, x, y;
	x = 11;
	
	len = 58;
	
	if (left) {
		y = 31;
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y);
			cout << string(len / 2, ' ');
			y++;
		}
	}

	if (right) {
		y = 31;
		x = x + len / 2 + 1;
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y);
			cout << string(len / 2-1, ' ');
			y++;
		}
	}

	if (up) {
		y = 2;
		for (int i = 0; i < 28; i++) {
			gotoXY(x-1, y);
			cout << string(60, ' ');
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