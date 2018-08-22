// Plane Billboard.cpp : Defines the entry point for the console application.

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
int main(int)
{
	string Plane[] =
	{ "                    _                                      "
		,"                  -=\\`\\                                    "
		,"              |\\ ____\\_\\__                                 "
		,"            -=\\c`\"\"\"\"\"\"\" \"`)                               "
		,"               `~~~~~/ /~~`                                "
		,"                 -==/ /                                    "
		,"                   '-'                                     " };

	string cloud[] =
	{ "                  _  _                                     "
		,"                 ( `   )_                                  "
		,"                (    )    `)                               "
		,"              (_   (_ .  _) _)                             " };


	char holder = ' ';

	int len, x, y;

	len = Plane[0].length();
	string border(len, '\xCD');
	string shadow(len + 2, '\xB2');
	cout << "\t  \xC9" << border << "\xBB" << endl;
	for (x = 0; x<11; x++)
		cout << "\t  \xBA                                                           \xBA" << endl;
	cout << "\t  \xBA                                             _             \xBA" << endl;
	cout << "\t  \xBA                                           (   )           \xBA" << endl;
	cout << "\t  \xBA             _ .                         ( `  ) . )        \xBA" << endl;
	cout << "\t  \xBA           (  _ )_                      (_, _(  ,_)_)      \xBA" << endl;
	cout << "\t  \xBA         (_  _(_ ,)                                        \xBA" << endl;

	cout << "\t  \xC8" << border << "\xBC" << endl;

	vector<Hero> team1;
	Hero mage(1, "Mage", "Fireball", pair<int, int>(4, 6));
	Hero warrior(2, "Warrior", "Mortal Strike", pair<int, int>(3, 9));
	Hero warlock(4, "Warlock", "Chaos Bolt", pair<int, int>(5, 5));
	Hero monk(17, "Monk", "Blackout Kick", pair<int, int>(3, 7));
	Hero rogue(16, "Rogue", "Roll the Dice", pair<int, int>(1, 10));
	team1.push_back(mage);
	team1.push_back(warrior);
	team1.push_back(warlock);
	do {
		for (y = 0; y<7; y++)
		{
			gotoXY(11, 1 + y, Plane[y]);
		}

		for (x = 0; x<4; x++)
		{
			gotoXY(11, 8 + x, cloud[x]);
		}

		for (y = 0; y<7; y++)
		{
			holder = Plane[y][len];
			for (x = len; x>0; x--)
			{
				Plane[y][x] = Plane[y][x - 1];
			}
			Plane[y][0] = holder;
		}

		for (y = 0; y<4; y++)
		{
			holder = cloud[y][0];
			for (x = 0; x<len; x++)
			{
				cloud[y][x] = cloud[y][x + 1];
			}
			cloud[y][len] = holder;
		}
		Sleep(60);
	} while (true);
	return 0;
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
}