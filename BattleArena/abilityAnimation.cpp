// color your text in Windows console mode
// colors are 0=black 1=blue 2=green and so on to 15=white  
// colorattribute = foreground + background * 16
// to get red text on yellow use 4 + 14*16 = 228
// light red on yellow would be 12 + 14*16 = 236
// a Dev-C++ tested console application by  vegaseat  07nov2004

#include "display.h"
enum Abilities {fireball,aimshot,lightningbolt,shuriken};

Abilities stringToenum(string ability);

void animation(shared_ptr<Hero>& hero, shared_ptr<Hero>& target)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	clearBox(false, false, true);
	printHeroByName(hero->getName(),10,14);
	printHeroByName(target->getName(),56,14);

	int k = 0;
	switch (stringToenum(hero->getAbility())) {

		case fireball:{
			string ball[] = { "-o ",
						      "-oo",
						      "-o " };
			int x = 10;
			int y = 16;
			for (int z = 0; z < 20; z++) {
				y = 16;
				for (int b = 0; b < 3; b++) {
					gotoXY(x, y);
					cout << "   ";
					y++;
				}
				y = 16;
				x++;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++) {
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
					x = 24 + z;
				}
				Sleep(100);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}
	
		case aimshot: {
			string arrow= ">>>--->";
			int x = 24;
			int y = 7;
			for (int z = 0; z < 20; z++) {
				x -= 1;
				gotoXY(x, y);
				cout << "       ";
				x += 1;
				gotoXY(x, y);
				SetConsoleTextAttribute(hConsole, 10);
				cout << arrow;
				x += 1;
				
				Sleep(100);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		case lightningbolt: {
			string lightning =  "/\\";

			int x = 24;
			int y = 7;
			for (int z = 0; z < 20; z++) {
				gotoXY(x, y);
				SetConsoleTextAttribute(hConsole, 14);
				cout << lightning;
				x += 2;
				Sleep(50);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		case shuriken: {
			string vert[] = { "o   o",
							  "  o  ",
							  "o   o" };
			string hori[] = { "  o  ",
				              "ooooo",
				              "  o  " };
			int x = 24;
			int y = 7;
			for (int z = 0; z < 20; z++) {
				y = 7;
				for (int b = 0; b < 3; b++) {
					gotoXY(x, y);
					cout << "     ";
					y++;
				}
				y = 7;
				x++;
				if (z%2 == 0) {
					for (int i = 0; i < 3; i++)
					{

						for (int j = 0; j < 5; j++) {
							if (vert[i][j] == ' ') {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 0);
								cout << vert[i][j];
								x++;
							}
							else {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 13);
								cout << vert[i][j];
								x++;
							}
						}
						y++;
						x = 24 + z;
					}
				} else {
					for (int i = 0; i < 3; i++)
					{

						for (int j = 0; j < 5; j++) {
							if (hori[i][j] == ' ') {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 0);
								cout << hori[i][j];
								x++;
							}
							else {
								gotoXY(x, y);
								SetConsoleTextAttribute(hConsole, 13);
								cout << hori[i][j];
								x++;
							}
						}
						y++;
						x = 24 + z;
					}
				}
				Sleep(150);
			}
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}

		default:
			SetConsoleTextAttribute(hConsole, 7);
			break;
	}
	cin.get(); // wait
}

Abilities stringToenum(string ability) {
	if (ability == "Fireball") return fireball;
	if (ability == "Aim Shot") return aimshot;
	if (ability == "Lightning Bolt") return lightningbolt;
	if (ability == "Shuriken") return shuriken;
}