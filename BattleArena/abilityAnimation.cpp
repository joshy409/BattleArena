// color your text in Windows console mode
// colors are 0=black 1=blue 2=green and so on to 15=white  
// colorattribute = foreground + background * 16
// to get red text on yellow use 4 + 14*16 = 228
// light red on yellow would be 12 + 14*16 = 236
// a Dev-C++ tested console application by  vegaseat  07nov2004

#include "display.h"
enum Abilities {fireball,aimshot,lightningbolt,shuriken,mortalstrike,bite};

Abilities stringToenum(string ability);

void animation(shared_ptr<Hero>& hero, shared_ptr<Hero>& target)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	clearBox(false, false, true);

	//print team 1 hero on the left
	if (hero->getTeamNumber() == "1") {
		printHeroByName(hero, 10, 12);
	}
	else {
		printHeroByName(target, 10, 12);
	}
	
	//print team 2 hero on the right
	if (hero->getTeamNumber() == "2") {
		printHeroByName(hero, 70-hero->getWidth(), 12);
	}
	else {
		printHeroByName(target, 70-target->getWidth(), 12);
	}

	switch (stringToenum(hero->getAbility())) {

		case fireball: {
			vector <string> ball = { "-o ",
						      "-oo",
						      "-o " };
			int x = hero->getWidth() + 10;
			int y = 13;
			for (int z = 0; z < 70 - target->getWidth() - hero->getWidth() - 10 + 2; z++) {
				y = 13;
				for (int b = 0; b < ball.size(); b++) {
					gotoXY(x, y, "   ");
					y++;
				}
				y = 13;
				x++;
				for (int i = 0; i < ball.size(); i++)
				{
					for (int j = 0; j < ball[0].length(); j++) {
						if (ball[i][j] == ' ') {
							gotoXY(x, y);
							SetConsoleTextAttribute(hConsole, 0);
							cout << ball[i][j];
							x++;
						}
						else {
							gotoXY(x, y);
							SetConsoleTextAttribute(hConsole, 12);
							cout << ball[i][j];
							x++;
						}
					}
					y++;
					x = hero->getWidth() + 10 + z;
				}
				Sleep(65);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}
	
		case aimshot: {
			string arrow = "<---<<<";
			int x = 70-hero->getWidth()-arrow.length()-1;
			int y = 14;
			for (int z = 0; z < 70 - target->getWidth() - hero->getWidth() - 10; z++) {
				x++;;
				gotoXY(x, y, "       ");
				x --;
				SetConsoleTextAttribute(hConsole, 10);
				gotoXY(x, y, arrow);
				x --;
				
				Sleep(60);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		case lightningbolt: {
			string lightning =  "/\\";

			int x = 70-hero->getWidth()-1;
			int y = 14;
			for (int z = 0; z < (70 - target->getWidth() - hero->getWidth() - 10)/2+4; z++) {
				SetConsoleTextAttribute(hConsole, 14);
				gotoXY(x, y, lightning);
				x -= 2;
				Sleep(50);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		case shuriken: {
			vector<string> vert = { "o   o",
							  "  o  ",
							  "o   o" };
			vector<string> hori = { "  o  ",
				              "ooooo",
				              "  o  " };
			int x = 70 - hero->getWidth() - vert[0].length() - 1;
			int y = 12;
			for (int z = 0; z < 70 - target->getWidth() - hero->getWidth() - 10 + 3; z++) {
				y = 12;
				for (int b = 0; b < vert.size(); b++) {
					gotoXY(x, y, "     ");
					y++;
				}
				y = 12;
				x--;
				if (z%2 == 0) {
					for (int i = 0; i < vert.size(); i++)
					{

						for (int j = 0; j < vert[0].length(); j++) {
							if (vert[i][j] == ' ') {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 0);
								cout << vert[i][j];
								x--;
							}
							else {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 13);
								cout << vert[i][j];
								x--;
							}
						}
						y++;
						x = 70 - hero->getWidth() - vert[0].length() - 1 - z;
					}
				} else {
					for (int i = 0; i < hori.size(); i++)
					{

						for (int j = 0; j < hori[0].length(); j++) {
							if (hori[i][j] == ' ') {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 0);
								cout << hori[i][j];
								x--;
							}
							else {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 13);
								cout << hori[i][j];
								x--;
							}
						}
						y++;
						x = 70 - hero->getWidth() - vert[0].length() - 1 - z;
					}
				}
				Sleep(65);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		case mortalstrike: {
			int x = 10;
			int y = 12;
			for (int z = 0; z < 70 - target->getWidth() - hero->getWidth() - 10 + 5; z++) {

				for (int b = 0; b < hero->getAscii().size(); b++) {
					gotoXY(x, y, string(hero->getAscii()[b].length(),' '));
					y++;
				}
				y = 12;
				x++;
				for (auto i: hero->getAscii())
				{
					gotoXY(x, y, i);
					y++;
				}
				x = 10 + z;
				y = 12;
				
				Sleep(40);
			}
			break; 
		}

		case bite: {
			int x = 10;
			int y = 12;
			for (int z = 0; z < 70 - target->getWidth() - hero->getWidth() - 10 + 3; z++) {

				for (int b = 0; b < hero->getAscii().size(); b++) {
					gotoXY(x, y, string(hero->getAscii()[b].length(), ' '));
					y++;
				}
				y = 12;
				x++;
				for (auto i : hero->getAscii())
				{
					gotoXY(x, y, i);
					y++;
				}
				x = 10 + z;
				y = 12;

				Sleep(40);
			}
			break; 
		}

		default:
			SetConsoleTextAttribute(hConsole, 7);
			break;
	}
}

Abilities stringToenum(string ability) {
	if (ability == "Fireball") return fireball;
	if (ability == "Aim Shot") return aimshot;
	if (ability == "Lightning Bolt") return lightningbolt;
	if (ability == "Shuriken") return shuriken;
	if (ability == "Mortal Strike") return mortalstrike;
	if (ability == "Bite") return bite;
}