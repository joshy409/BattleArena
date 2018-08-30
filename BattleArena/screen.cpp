#include "display.h"
// console width 80
// console height 40


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//displays start screen
void startScreen()
{
	int x = 18;
	int y = 11;
	
	vector<string> logo = 
	  { "    ____        __  __  __                     ",
		"   / __ )____ _/ /_/ /_/ /__                   ",
		"  / __  / __ `/ __/ __/ / _ \\                  ",
		" / /_/ / /_/ / /_/ /_/ /  __/                  ",
		"/_____/\\__,_/\\__/\\____/\\___/                   ",
		"                  /   |  ________  ____  ____ _",
		"                 / /| | / ___/ _ \\/ __ \\/ __ `/",
		"                / ___ |/ /  /  __/ / / / /_/ / ",
		"               /_/  |_/_/   \\___/_/ /_/\\__,_/  " };

	for (auto i : logo) {
		gotoXY(x, y, i);
		y++;
	}


	string startprompt = { "Press Enter to start                      " };

	char holder = ' ';
	int len = startprompt.length();

	// string startprompt rotates until Enter key is pressed
	
	while (true) {
		gotoXY(20, 23, startprompt);
		holder = startprompt[len];
		for (int i = len; i>0; i--)
		{
			startprompt[i] = startprompt[i - 1];
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


	//creat a textbox to display text for the game
	x = 10;
	y = 31;
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

//displays win screen
void endScreen(string winningTeam)
{
	clearBox(true, true, true);
	int x = 22;
	int y = 13;
	if (winningTeam == "1") {
		vector<string> team1win = {
			"  ______                        ___",
			" /_  __/__  ____ _____ ___     <  /",
			"  / / / _ \\/ __ `/ __ `__ \\    / /  ",
			" / / /  __/ /_/ / / / / / /   / /  ",
			"/_/  \\___/\\__,____ /_/ /_/   /_/   ",
			"      | |     / (_)___  _____      ",
			"      | | /| / / / __ \\/ ___/      ",
			"      | |/ |/ / / / / (__  )       ",
			"      |__/|__/_/_/ /_/____/        " };

		for (auto i : team1win) {
			gotoXY(x, y, i);
			y++;
		}
	}
	else {
		vector<string> team2win = {
			"  ______                        ___ ",
			" /_  __/__  ____ _____ ___     |__ \\",
			"  / / / _ \\/ __ `/ __ `__ \\    __/ /",
			" / / /  __/ /_/ / / / / / /   / __/ ",
			"/_/  \\___/\\__,____ /_/ /_/   /____/ ",
			"      | |     / (_)___  _____      ",
			"      | | /| / / / __ \\/ ___/      ",
			"      | |/ |/ / / / / (__  )       ",
			"      |__/|__/_/_/ /_/____/        " };

		for (auto i : team2win) {
			gotoXY(x, y, i);
			y++;
		}
	}
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
		gotoXY(x, y, i);
		y++;
	}

}

void grave(string name, string teamNumber, int x, int y) {
	
	if (teamNumber == "1") {
		vector<string> team1grave = { 
			 "     _|_     "
			,"   ___|___   "
			," /~/~     ~\\ "
			,"| |         |"
			,"| |" + string((9 - name.size()) - (9 - name.size()) / 2,' ') + name + string((9 - name.size()) / 2,' ') + "|"
			,"| |         |"
			,"| |         |"
			,"|_|_ _ _ __ |" };

		for (auto i : team1grave) {
			gotoXY(x, y, i);
			y++;
		}
	}
	else {
		vector<string> team2grave = { 
			 "     _|_     "
			,"   ___|___   "
			," /~     ~\\~\\ "
			,"|         | |"
			,"|" + string((9 - name.size()) / 2,' ') + name + string((9 - name.size()) - (9 - name.size()) / 2,' ') + "| |"
			,"|         | |"
			,"|         | |"
			,"|_ _ _ __ |_|" };

		for (auto i : team2grave) {
			gotoXY(x-i.size(), y, i);
			y++;
		}
	}
}

//returns index of the hero user selected
int select(int size) {
	int len = 58;
	int x = 11 + len / 2 + 2;
	int y = 33;

	//keeps track of cursor's y position when UP or DOWN arrow key is pressed
	//infinite loop until Enter key is pressed
	while (true) {
		if (y < 33) {
			y = 33 + size - 1;
		}
		else if (y > 33 + size - 1) {
			y = 33;
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
		//wait for enter key press
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
	return y % 33;
}

//displays team number, member of the team and their current and max health
void showStat(vector<shared_ptr<Hero>>& team, bool target)
{
	//clears textbox
	clearBox(true, true, false);

	int x = 11;
	int y = 32;
	int len = 58;
	gotoXY(x + len / 2 + 4, y, "Team " + team[0]->getTeamNumber() + string(9, ' ') + "HP");
	y++;
	gotoXY(x + len / 2 + 4, y);
	for (auto i : team) {
		cout << i->getName() << string(11 - i->getName().size(), ' ') << "    " << i->getHealth() << "/" << i->getMaxHealth();
		y++;
		gotoXY(x + len / 2 + 4, y);
	}

	x = 11;
	y = 33;

	//shows different prompt if the function was called for defending team
	if (!target) {
		gotoXY(x + 3, y, "Select Character");
	}
	else {
		gotoXY(x + 3, y, "Select Target");
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
	int y = 33;
	int len = 58;
	gotoXY(x + 2, y, hero->getName() + " attacks " + target->getName());
	gotoXY(x + 2, y+1, "with " + hero->getAbility());

	animation(hero,target);

	gotoXY(x + len / 2 + 3, y, hero->getAbility() + " did ");
	gotoXY(x + len / 2 + 3, y+1,  to_string(attack) + " damage");

	while (true) {
		gotoXY(66,37, "^");
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
	int y = 32;
	int len = 58;
	gotoXY(x + len / 2 + 4, y, hero->getName() + "'s Abilities");
	gotoXY(x + len / 2 + 4, y+1, hero->getAbility());

	x = 11;
	y = 33;
	gotoXY(x + 3, y, "What will " + hero->getName() + " do?");
	
}

//clears contents 
void clearBox(bool left, bool right, bool up) {
	int len, x, y;
	x = 11;
	len = 58;

	if (up) {
		y = 2;
		for (int i = 0; i < 28; i++) {
			gotoXY(x - 1, y, string(60, ' '));
			y++;
		}
	}

	if (left) {
		y = 32;
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y, string(len / 2, ' '));
			y++;
		}
	}

	if (right) {
		y = 32;
		x = x + len / 2 + 1;
		for (int i = 0; i < 6; i++) {
			gotoXY(x, y, string(len / 2 - 1, ' '));
			y++;
		}
	}

	
}

//cursor changer and prints out the text
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