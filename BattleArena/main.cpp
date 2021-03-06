﻿#include "display.h"
//#undef max

bool myfunction(shared_ptr<Hero> first, shared_ptr<Hero> second);

//TODO: vs comp mode computer randomly selects
/*bool play(vector<int>& index1, vector<int>& index2, vector<Hero>& team1, vector<Hero>& team2) {

	if (team1[0].getTeamNumber() == "1") {
		display(team1, team2);
	}
	else {
		display(team2, team1);
	}
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> chosseplayer(0, index1.size() - 1); // define the range
	std::uniform_int_distribution<> choosetarget(0, index2.size() - 1); // define the range
	int chosenplayer = chosseplayer(eng);
	int chosentarget = choosetarget(eng);
	int player = index1[chosenplayer];
	int target = index2[chosentarget];
	
	std::uniform_int_distribution<> damage(team1[player].getMinDamage(), team1[player].getMaxDamage()); // define the range
	int attack = damage(eng);

	cout << "\t\t" << team1[player].getName() << " attacks " << team2[target].getName() << " with " << team1[player].getAbility() << " and inflicts " << attack << " damage" << endl;

	team2[target].setHealth(attack);
	if (team2[target].getHealth() <= 0 and index2.size() == 1) {
		cout << "\t\t" << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		cout << endl;
		system("CLS");
		cout << "\t\t" << "Team " << team1[0].getTeamNumber() <<" wins" << endl;
		return false;
	}
	else if (team2[target].getHealth() <= 0) {
		cout << "\t\t" << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		index2.erase(index2.begin() + chosentarget);
		cout << endl;
	}

	return true;
}*/

//Game logic. returns false if a team wins
bool aiplay(shared_ptr<vector<int>>& index1, shared_ptr<vector<int>>& index2, vector<shared_ptr<Hero>>& team1, vector<shared_ptr<Hero>>& team2) {

	int x = 11;
	int y = 33;
	int len = 58;

	clearBox(false, false, true);

	//print every hero
	printHero(team1);
	printHero(team2);

	showStat(team1, false);

	//player selection error handling
	int player;
	while (true) {
		player = select(team1.size());
		if (team1[player]->getHealth() == 0) {
			showStat(team1, false);
			clearBox(true, false,false);
			gotoXY(x + 2, y, team1[player]->getName() + " is dead!");
			gotoXY(x + 2, y+1, "Please select again");
			continue;
		}
		break;
	}

	showAbility(team1[player]);
	int ablility = select(1);

	//player selection error handling
	showStat(team2, true);
	int target;
	while (true) {
		target = select(team2.size());
		if (team2[target]->getHealth() == 0) {
			showStat(team2, true);
			clearBox(true, false,false);
			gotoXY(x + 2, y, team2[target]->getName() + " is dead!");
			gotoXY(x + 2, y+1, "Please select again");
			continue;
		}
		break;
	}

	showAttack(team1[player],team2[target]);

	//when a hero dies check if it was the last hero on the team
	if (team2[target]->getHealth() <= 0 and index2->size() == 1) { //when it was the last hero
		clearBox(false, true, false);
		gotoXY(x + len / 2 + 3, y, team2[target]->getName() + " died");
		
		team2[target]->setHealth(team2[target]->getHealth()); //sets health to 0
		
		//wait for enter key press
		while (true) {
			gotoXY(66, 37, "^");
			if (GetAsyncKeyState(VK_RETURN)) {
				while (true) {
					if (!GetAsyncKeyState(VK_RETURN)) {
						break;
					}
				}
				break;
			}
		}

		clearBox(true, true, true);
		//print every hero
		printHero(team1);
		printHero(team2);

		gotoXY(x + 2, y, "All the characters in ");
		gotoXY(x + 2, y+1, "Team " + team2[0]->getTeamNumber() + " is dead!");
		//wait for enter key press
		while (true) {
			gotoXY(66, 37, "^");
			if (GetAsyncKeyState(VK_RETURN)) {
				while (true) {
					if (!GetAsyncKeyState(VK_RETURN)) {
						break;
					}
				}
				break;
			}
		}

		endScreen(team1[0]->getTeamNumber());
		return false;

	} else if (team2[target]->getHealth() <= 0) {
		clearBox(false, true, false);
		gotoXY(x + len / 2 + 3, y, team2[target]->getName() + " died");
		
		//wait for enter key press
		while (true) {
			gotoXY(66, 37, "^");
			if (GetAsyncKeyState(VK_RETURN)) {
				while (true) {
					if (!GetAsyncKeyState(VK_RETURN)) {
						break;
					}
				}
				break;
			}
		}
		team2[target]->setHealth(team2[target]->getHealth()); //sets health to 0 
		index2->pop_back();
		cout << endl;
	}
	//sort each team in ascending order based on health
	sort(team1.begin(), team1.end(), myfunction);
	sort(team2.begin(), team2.end(), myfunction);
	return true;
}

// custom function for sorting algorithm
bool myfunction(shared_ptr<Hero> first, shared_ptr<Hero> second) {
	return (first->getHealth() < second->getHealth());
}

//TODO: add comments, implement menu screen to chosse pvp, vscomp and pve
//TODO: boss design 
int main()
{
	//set console size
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 100, 100, 800, 500,true);

	vector<string> mage =
	{ "   __\\/__     "
		,"   //''\\\\  _ ."
		,"   \\_||_/-) (-"
		,"   /_)(_\\ .'. "
		,"   / . |   |  "
		,"  /  . |   |  "
		,".'_____\, .'. " };

	vector<string> warrior =
	{ "  v__         /|"
		,"__|==)_      / )"
		,"|_\\`+'_/)   -/|/"
		," \\ )!/( | _/~/  "
		," |\\\\._//_/~/    "
		," (#`(_)7~       "
		," \\#|  \#|       "
		," |#b  (>b       " };

	vector<string> hunter =
	{ " /|    "
		,"/_|_{) "
		,"| |__\\"
		,"\\ |  ( "
		," \\|  ) "
		,"    /| "
		,"    \\ \\"
		,"    ~ ~" };

	vector<string> shaman =
	{ "     __/\\__   "
		,". _  \\\\''//   "
		,"-( )-/_||_\\   "
		," .'. \\_()_/   "
		,"  |   | . \\   "
		,"  |   | .  \\  "
		," .'. ,\\_____'." };

	vector<string> ninja =
	{   "          ",
	    "          ",
		"    _v_  /",
		" ~(/`U`)/ ",
		" /    c=) ",
		"(_/>   i  ",
		" /(_/ ^ U " };

	vector<string> druid =
	{   
		"                       ",
		 " ..------~~~--.__     "
		,"  /               c~\\ "
		,"  /             \\__ `\\"
		,"  |  /~~--__/  /'\ ~~'"
		," /'/'\\ |    | |`\\ \\_  "
		,"`-))  `-))  `-)) `-)) " };

	//Using smart pointers for memory management
	//Team 1
	vector<shared_ptr<Hero>> team1;
	team1.push_back(make_shared<Hero>(10, "Mage", "Fireball", pair<int, int>(4, 7),"1", mage));
	team1.push_back(make_shared<Hero>(14, "Warrior", "Mortal Strike", pair<int, int>(2, 5),"1", warrior));
	team1.push_back(make_shared<Hero>(12, "Druid", "Bite", pair<int, int>(3, 4), "1", druid));
	
	

	//index vector is used to check how many hero's are alive, used for win condition check
	auto index1 = make_shared<vector<int>>();
	for (int i = 0; i < team1.size(); i++) {
		index1->push_back(i);
	}

	//Team 2
	vector<shared_ptr<Hero>> team2;
	team2.push_back(make_shared<Hero>(11, "Hunter", "Aim Shot", pair<int, int>(4, 6),"2",hunter));
	team2.push_back(make_shared<Hero>(10, "Shaman", "Lightning Bolt", pair<int, int>(5, 7),"2",shaman));
	team2.push_back(make_shared<Hero>(9, "Ninja", "Shuriken", pair<int, int>(5, 10), "2",ninja));

	auto index2 = make_shared<vector<int>>();
	for (int i = 0; i < team2.size(); i++) {
		index2->push_back(i);
	}

	startScreen();
	
	while(aiplay(index1,index2,team1,team2) and aiplay(index2, index1, team2, team1)) {}

	//wait for enter key press
	while (true) {
		gotoXY(66, 37, "^");
		if (GetAsyncKeyState(VK_RETURN)) {
			while (true) {
				if (!GetAsyncKeyState(VK_RETURN)) {
					break;
				}
			}
			break;
		}
	}

}

