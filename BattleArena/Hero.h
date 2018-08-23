#pragma once
using namespace std;

class Hero {
public:
	Hero(int health, string name, string ability, pair<int, int> damage) :
		_health(health), _name(name), _ability(ability), _damage(damage), _maxHealth(health)
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

	void setTeamNumber(string teamnumber) {
		_teamNumber = teamnumber;
	}

private:
	int _health;
	int _maxHealth;
	string _name;
	string _ability;
	pair<int, int> _damage;
	string _teamNumber = "";
};