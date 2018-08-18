#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <memory>
#include <fstream>
#include "display.h"


using namespace std;

class Hero {
public:
	Hero(int health, string name, string ability, pair<int,int> damage) :
		_health(health), _name(name), _ability(ability), _damage(damage)
	{}

	int getHealth() {
		return _health;
	}
	string getName() {
		return _name;
	}
	string getAbility() {
		return _ability;
	}
	int getMinDamage() {
		return _damage.first;
	}
	int getMaxDamage() {
		return _damage.second;
	}

	void setHealth(int attack) {
		_health -= attack;
	}

	string getTeamNumber() {
		return _teamnumber;
	}

	void setTeamNumber(string teamnumber) {
		_teamnumber = teamnumber;
	}

private:
	int _health;
	string _name;
	string _ability;
	pair<int, int> _damage;
	string _teamnumber = "";
};

void display(vector<Hero> team1, vector<Hero> team2) {
	cout << endl;
	cout << "Team " << team1[0].getTeamNumber() << " :  ";
	for (auto i : team1) {
		cout << i.getName() << string(11 - i.getName().size(), ' ') << "    ";
	}
	cout << endl;
	cout << "          ";
	for (auto i : team1) {
		cout << i.getHealth() << string(11 - to_string(i.getHealth()).size(), ' ') << "    ";
	}
	cout << endl;

	cout << "Team " << team2[0].getTeamNumber() << " :  ";
	for (auto i : team2) {
		cout << i.getName() << string(11 - i.getName().size(), ' ') << "    ";
	}
	cout << endl;
	cout << "          ";
	for (auto i : team2) {
		cout << i.getHealth() << string(11 - to_string(i.getHealth()).size(), ' ') <<"    ";
	}
	cout << endl;
}

//TODO add PVP mode and vs AI mode
bool play(vector<int>& index1, vector<int>& index2, vector<Hero>& team1, vector<Hero>& team2) {

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

	cout << team1[player].getName() << " attacks " << team2[target].getName() << " with " << team1[player].getAbility() << " and inflicts " << attack << " damage" << endl;

	team2[target].setHealth(attack);
	if (team2[target].getHealth() <= 0 and index2.size() == 1) {
		cout << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		cout << endl;
		system("CLS");
		cout << "Team " << team1[0].getTeamNumber() <<" wins" << endl;
		return false;
	}
	else if (team2[target].getHealth() <= 0) {
		cout << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		index2.erase(index2.begin() + chosentarget);
		cout << endl;
	}

	return true;
}

int select(vector<Hero> team1) {
	int selected;
	while (true) {
		cin >> selected;
		if (cin.fail()) {
			cout << "Wrong input! Please select again (1-5): ";
			cin.clear();
			cin >> selected;
			continue;
		}
		else if (selected >= team1.size()) {
			cout << "Wrong input! Please select again (1-5): ";
			continue;
		} else if (team1[selected].getHealth() == 0) {
			cout << team1[selected].getName() << " is dead! Please select again (1-5): ";
			continue;
		} else {
			return selected--;
		}
	}
}

//TODO add input error handling
bool pvpplay(vector<int>& index1, vector<int>& index2, vector<Hero>& team1, vector<Hero>& team2) {

	if (team1[0].getTeamNumber() == "1") {
		display(team1, team2);
	}
	else {
		display(team2, team1);
	}

	cout << "Select your character (1-5): ";
	int player = select(team1);

	cout << "Select your target (1-5): ";
	int target = select(team2);
	

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> damage(team1[player].getMinDamage(), team1[player].getMaxDamage()); // define the range
	int attack = damage(eng);

	cout << team1[player].getName() << " attacks " << team2[target].getName() << " with " << team1[player].getAbility() << " and inflicts " << attack << " damage" << endl;

	team2[target].setHealth(attack);

	if (team2[target].getHealth() <= 0 and index2.size() == 1) {
		cout << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		cout << endl;
		
		cout << "Team " << team1[0].getTeamNumber() << " wins" << endl;
		return false;
	}
	else if (team2[target].getHealth() <= 0) {
		cout << team2[target].getName() << " died" << endl;
		team2[target].setHealth(team2[target].getHealth());
		index2.pop_back();
		cout << endl;
	}

	return true;
}

int main()
{
	//Team 1
	vector<Hero> team1;
	Hero mage(0, "Mage", "Fireball", pair<int, int>(4, 6));
	Hero warrior(20, "Warrior", "Mortal Strike", pair<int, int>(3, 9));
	Hero warlock(14, "Warlock", "Chaos Bolt", pair<int, int>(5, 5));
	Hero monk(17, "Monk", "Blackout Kick", pair<int, int>(3, 7));
	Hero rogue(16, "Rogue", "Roll the Dice", pair<int, int>(1, 10));
	team1.push_back(mage);
	team1.push_back(warrior);
	team1.push_back(warlock);
	//team1.push_back(monk);
	//team1.push_back(rogue);

	vector<int> index1;
	for (int i = 0; i < team1.size(); i++) {
		index1.push_back(i);
		team1[i].setTeamNumber("1");
	}



	//Team 2
	vector<Hero> team2;
	Hero deathKnight(18, "DeathKnight", "Death Strike", pair<int, int>(4, 6));
	Hero priest(0, "Priest", "Mind Blast", pair<int, int>(3, 4));
	Hero paladin(18, "Paladin", "Judgement", pair<int, int>(5, 7));
	Hero hunter(14, "Hunter", "Aim Shot", pair<int, int>(3, 5));
	Hero druid(19, "Druid", "Bite", pair<int, int>(4, 7));
	team2.push_back(deathKnight);
	team2.push_back(priest);
	team2.push_back(paladin);
	//team2.push_back(hunter);
	//team2.push_back(druid);

	vector<int> index2;
	for (int i = 0; i < team2.size(); i++) {
		index2.push_back(i);
		team2[i].setTeamNumber("2");
	}


	//TODO gameover screen and win screen
	printscreen("startscreen");
	system("CLS");
	cout << endl;
	cout << endl;

	while(pvpplay(index1,index2,team1,team2) and pvpplay(index2, index1, team2, team1)) {
		
		cout << endl;
		//cin.ignore();
		//system("CLS");
	
	}

	printscreen("endscreen");

}

