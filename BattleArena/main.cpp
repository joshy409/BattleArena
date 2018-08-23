#include "display.h"
//#undef max


/*void display(vector<Hero> team1, vector<Hero> team2) {
	cout << endl;
	cout << "\t\tTeam " << team1[0].getTeamNumber() << " :  ";
	for (auto i : team1) {
		cout  << i.getName() << string(11 - i.getName().size(), ' ') << "    ";
	}
	cout << endl;
	cout << "\t\t\t  ";
	for (auto i : team1) {
		cout  << i.getHealth() << string(11 - to_string(i.getHealth()).size(), ' ') << "    ";
	}
	cout << endl;

	cout << "\t\tTeam " << team2[0].getTeamNumber() << " :  ";
	for (auto i : team2) {
		cout << i.getName() << string(11 - i.getName().size(), ' ') << "    ";
	}
	cout << endl;
	cout << "\t\t\t  ";
	for (auto i : team2) {
		cout  << i.getHealth() << string(11 - to_string(i.getHealth()).size(), ' ') <<"    ";
	}
	cout << endl;
}*/


//TODO AI mode
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

/*int select(vector<Hero> team1) {
	int selected;
	while (true) {
		cin >> selected;
		selected--;
		if (cin.fail()) {
			cout << "\t\tWrong input! Please select again (1-5): ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if (selected >= team1.size() or selected == -1) {
			cout << "\t\tWrong input! Please select again (1-5): ";
			continue;
		} 
		else if (team1[selected].getHealth() == 0) {
			cout << "\t\t" << team1[selected].getName() << " is dead! Please select again (1-5): ";
			continue;
		}
		 else {
			return selected;
		}
	}
}
*/

/*bool pvpplay(vector<int>& index1, vector<int>& index2, vector<Hero>& team1, vector<Hero>& team2) {

	if (team1[0].getTeamNumber() == "1") {
		display(team1, team2);
	}
	else {
		display(team2, team1);
	}

	cout << "\t\tSelect your character (1-5): ";
	int player = select(team1);

	cout << "\t\tSelect your target (1-5): ";
	int target = select(team2);
	

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> damage(team1[player].getMinDamage(), team1[player].getMaxDamage()); // define the range
	int attack = damage(eng);

	cout << "\t\t" << team1[player].getName() << " attacks " << team2[target].getName() << " with " << team1[player].getAbility() << " and inflicts " << attack << " damage" << endl;

	team2[target].setHealth(attack);

	if (team2[target].getHealth() <= 0 and index2.size() == 1) {
		cout << "\t\t" << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		cout << endl;
		
		cout << "\t\t" << "Team " << team1[0].getTeamNumber() << " wins" << endl;
		return false;
	}
	else if (team2[target].getHealth() <= 0) {
		cout << "\t\t" << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		index2.pop_back();
		cout << endl;
	}

	return true;
}*/

//TODO ASCII ART gameplay screen

//Game logic. return false if a team wins
bool aiplay(shared_ptr<vector<int>>& index1, shared_ptr<vector<int>>& index2, vector<shared_ptr<Hero>>& team1, vector<shared_ptr<Hero>>& team2) {

	int x = 11;
	int y = 35;
	int len = 58;

	showStat(team1, false);

	//player selection error handling
	int player;
	while (true) {
		player = select(team1.size());
		if (team1[player]->getHealth() == 0) {
			showStat(team1, false);
			clearBox(true, false);
			gotoXY(x + 2, y);
			cout << team1[player]->getName() << " is dead!";
			gotoXY(x + 2, y+1);
			cout << "Please select again";
			continue;
		}
		break;
	}

	showAbility(team1[player]);
	int ablility = select(index1->size());

	//player selection error handling
	showStat(team2, true);
	int target;
	while (true) {
		target = select(team2.size());
		if (team2[target]->getHealth() == 0) {
			showStat(team2, true);
			clearBox(true, false);
			gotoXY(x + 2, y);
			cout << team2[target]->getName() << " is dead!";
			gotoXY(x + 2, y+1);
			cout << "Please select again";
			continue;
		}
		break;
	}

	showAttack(team1[player],team2[target]);

	//infinite loop until Enter key is pressed to give user time to read the text
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
	}
	Sleep(200);
	
	//when a hero dies check if it was the last hero on the team
	if (team2[target]->getHealth() <= 0 and index2->size() == 1) { //when it was the last hero
		
		gotoXY(x + len / 2 + 4, y);
		cout << team2[target]->getName() << " died" << endl;
		team2[target]->setHealth(team2[target]->getHealth());
		cout << endl;

		cout << "\t\t" << "Team " << team1[0]->getTeamNumber() << " wins" << endl;
		return false;

	} else if (team2[target]->getHealth() <= 0) {

		gotoXY(x + len / 2 + 4, y);
		cout << team2[target]->getName() << " died" << endl;
		team2[target]->setHealth(team2[target]->getHealth());
		index2->pop_back();
		cout << endl;
	}
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
	}
	Sleep(200);
	return true;
}

int main()
{
	//Using smart pointers for memory management
	//Team 1
	vector<shared_ptr<Hero>> team1;
	team1.push_back(make_shared<Hero>(1, "Mage", "Fireball", pair<int, int>(4, 6)));
	team1.push_back(make_shared<Hero>(2, "Warrior", "Lightning Bolt", pair<int, int>(3, 9)));
	team1.push_back(make_shared<Hero>(16, "Rogue", "Shuriken", pair<int, int>(1, 10)));
	

	//index vector is used to check how many hero's are alive, used for win condition check
	auto index1 = make_shared<vector<int>>();
	for (int i = 0; i < team1.size(); i++) {
		index1->push_back(i);
		team1[i]->setTeamNumber("1");
	}

	//Team 2
	vector<shared_ptr<Hero>> team2;
	team2.push_back(make_shared<Hero>(18, "Shaman", "Lightning Bolt", pair<int, int>(4, 6)));
	team2.push_back(make_shared<Hero>(14, "Hunter", "Aim Shot", pair<int, int>(3, 5)));
	team2.push_back(make_shared<Hero>(19, "Druid", "Bite", pair<int, int>(4, 7)));

	auto index2 = make_shared<vector<int>>();
	for (int i = 0; i < team2.size(); i++) {
		index2->push_back(i);
		team2[i]->setTeamNumber("2");
	}

	
	//TODO gameover screen and win screen
	startScreen();
	system("CLS");
	cout << endl;
	cout << endl;

	printHero();
	while(aiplay(index1,index2,team1,team2) and aiplay(index2, index1, team2, team1)) {
		
		cout << endl;
		//cin.ignore();
		//system("CLS");
	
	}

	endScreen();

}

