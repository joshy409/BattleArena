#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
class Hero {
public:
	Hero(int health, string name, string ability, pair<int, int> damage) :
		_health(health), _name(name), _ability(ability), _damage(damage), _maxhealth(health)
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
		return _maxhealth;
	}
	string getTeamNumber() {
		return _teamnumber;
	}

	void setTeamNumber(string teamnumber) {
		_teamnumber = teamnumber;
	}

private:
	int _health;
	int _maxhealth;
	string _name;
	string _ability;
	pair<int, int> _damage;
	string _teamnumber = "";
};

void textbox(vector<Hero> team) {
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
	for (int i = 0; i < team.size()+1; i++) {
		cout << "\xBA" << string(len / 2, ' ') << "|" << string(len / 2, ' ') << "\b\xBA" << endl;
		gotoXY(x, y);
		y++;
	}
	cout << "\xC8" << border << "\xBC" << endl;

	x = 11;
	y = 19;
	gotoXY(x + len / 2 + 4, y);
	cout << "Team " << team[0].getTeamNumber() << string(9,' ') << "HP";
	y++;
	gotoXY(x + len / 2 + 4, y);
	for (auto i : team) {
		cout << i.getName() << string(11 - i.getName().size(), ' ') << "    " << i.getHealth() << "/" << i.getMaxHealth();
		y++;
		gotoXY(x + len / 2 + 4, y);	
	}
}


int select(vector<Hero> team1) {
	int len = 58;
	int x = 11 + len / 2 + 2;
	int y = 20;

	while (true) {
		if (y < 20) {
			y = 20;
		}
		else if (y > 20 + team1.size()-1) {
			y = 20 + team1.size();
		}
		gotoXY(x, y, ">");
		if (GetAsyncKeyState(VK_DOWN))
		{
			gotoXY(x, y, " ");
			y--;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			gotoXY(x, y, " ");
			y++;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		Sleep(100);
	}
	return 0;
}

int main(int)
{
	vector<Hero> team1;
	Hero mage(1, "Mage", "Fireball", pair<int, int>(4, 6));
	Hero warrior(2, "Warrior", "Mortal Strike", pair<int, int>(3, 9));
	Hero warlock(4, "Warlock", "Chaos Bolt", pair<int, int>(5, 5));
	Hero monk(17, "Monk", "Blackout Kick", pair<int, int>(3, 7));
	Hero rogue(16, "Rogue", "Roll the Dice", pair<int, int>(1, 10));
	team1.push_back(mage);
	team1.push_back(warrior);
	team1.push_back(warlock);
	team1.push_back(monk);
	team1.push_back(rogue);

	for (int i = 0; i < team1.size(); i++) {
		team1[i].setTeamNumber("1");
	}

	textbox(team1);

	int i = select(team1);


	vector<Hero> team2;
	Hero deathKnight(18, "DeathKnight", "Death Strike", pair<int, int>(4, 6));
	Hero priest(1, "Priest", "Mind Blast", pair<int, int>(3, 4));
	Hero paladin(18, "Paladin", "Judgement", pair<int, int>(5, 7));
	Hero hunter(14, "Hunter", "Aim Shot", pair<int, int>(3, 5));
	Hero druid(19, "Druid", "Bite", pair<int, int>(4, 7));
	team2.push_back(deathKnight);
	team2.push_back(priest);
	team2.push_back(paladin);

	for (int i = 0; i < team2.size(); i++) {
		team2[i].setTeamNumber("2");
	}
	textbox(team2);
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