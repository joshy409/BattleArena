#pragma once
using namespace std;

class Hero {
public:
	Hero(int health, string name, string ability, pair<int, int> damage, string teamNumber, vector<string> ascii) :
		_health(health), _name(name), _ability(ability), _damage(damage), _maxHealth(health), _teamNumber(teamNumber), _ascii(ascii)
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

	int getMaxHealth() {
		return _maxHealth;
	}
	string getTeamNumber() {
		return _teamNumber;
	}

	int getWidth() {
		return _ascii[0].size();
	}

	int getHeight() {
		return _ascii.size();
	}

	vector<string> getAscii() {
		return _ascii;
	}

private:
	int _health;
	int _maxHealth;
	string _name;
	string _ability;
	pair<int, int> _damage;
	string _teamNumber = "";
	vector<string> _ascii;
};