#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Hero {
private:
	int health;
	string name;
	string ability;
	pair<int, int> damage;
};


class Mage : public Hero {
private:
	int health;
	string name;
	string ability;
	pair<int, int> damage;
};

int main()
{

}