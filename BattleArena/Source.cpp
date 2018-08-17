#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <memory>
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

protected:
	int _health;
	string _name;
	string _ability;
	pair<int, int> _damage;
};

void play(vector<Hero>& team1, vector<Hero>& team2) {

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> hero(0, team2.size()-1); // define the range
	std::uniform_int_distribution<> hero1(0, team1.size() - 1); // define the range
	int target = hero(eng);
	int player = hero1(eng);
	std::uniform_int_distribution<> damage(team1[player].getMinDamage(), team1[player].getMaxDamage()); // define the range
	int attack = damage(eng);
	team2[target].setHealth(attack);
	if (team2[target].getHealth() <= 0) {
		cout << team2[target].getName() << " is removed" << endl;
		team2.erase(team2.begin()+target);
		cout << endl;
	}
	cout << team1[player].getName() << " attacks " << team2[target].getName() << " with " << team1[player].getAbility() << " and inflicts " << attack << " damage" << endl;
	
	std::uniform_int_distribution<> hero3(0, team1.size()-1); // define the range
	std::uniform_int_distribution<> hero4(0, team2.size() - 1); // define the range
	target = hero3(eng);
	player = hero4(eng);
	std::uniform_int_distribution<> damage1(team2[player].getMinDamage(), team2[player].getMaxDamage()); // define the range
	attack = damage1(eng);
	team1[target].setHealth(attack);
	cout << team2[player].getName() << " attacks " << team1[target].getName() << " with " << team2[player].getAbility() << " and inflicts " << attack << " damage" << endl;
	cout << endl;
	if (team1[target].getHealth() <= 0) {
		cout << team1[target].getName() << " is removed" << endl;
		cout << endl;
		team1.erase(team1.begin() + target);
	}
	
}


int main()
{
	//Team 1
	vector<Hero> team1;
	Hero mage(15, "Mage", "Fireball", pair<int, int>(4, 6));
	Hero warrior(20, "Warrior", "Mortal Strike", pair<int, int>(2, 8));
	Hero warlock(14, "Warlock", "Chaos Bolt", pair<int, int>(5, 5));
	Hero monk(17, "Monk", "Blackout Kick", pair<int, int>(2, 7));
	Hero rogue(16, "Rogue", "Roll the Dice", pair<int, int>(1, 10));
	team1.push_back(mage);
	team1.push_back(warrior);
	team1.push_back(warlock);
	team1.push_back(monk);
	team1.push_back(rogue);

	//Team 2
	vector<Hero> team2;
	Hero deathKnight(19, "DeathKnight", "Death Strike", pair<int, int>(4, 6));
	Hero priest(15, "Priest", "Mind Blast", pair<int, int>(3, 4));
	Hero paladin(18, "Paladin", "Judgement", pair<int, int>(5, 7));
	Hero hunter(14, "Hunter", "Aim Shot", pair<int, int>(3, 5));
	Hero druid(20, "Druid", "Bite", pair<int, int>(4, 7));
	team2.push_back(deathKnight);
	team2.push_back(priest);
	team2.push_back(paladin);
	team2.push_back(hunter);
	team2.push_back(druid);


	for (int i = 0; i < 15; i++) {
		play(team1, team2);

		for (int i = 0; i < team1.size(); i++) {
			cout << team1[i].getName() << " has " << team1[i].getHealth() << " hp" << endl;
		}
		for (int i = 0; i < team2.size(); i++) {
			cout << team2[i].getName() << " has " << team2[i].getHealth() << " hp" << endl;
		}
		cout << endl;
	}

}