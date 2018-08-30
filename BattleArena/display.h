#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <string>
#include <windows.h>
#include "Hero.h"



void startScreen();
void printHero(vector<shared_ptr<Hero>>& team1);
void printHeroByName(shared_ptr<Hero>& hero, int x, int y);
void endScreen(string winningTeam);
int select(int size);
void showStat(vector<shared_ptr<Hero>>& team, bool target);
void showAttack(shared_ptr<Hero>& hero, shared_ptr<Hero>& target);
void showAbility(shared_ptr<Hero>& hero);
void animation(shared_ptr<Hero>& hero, shared_ptr<Hero>& target);
void clearBox(bool left, bool right, bool up);
void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
void grave(string name, string teamNumber, int x, int y);

