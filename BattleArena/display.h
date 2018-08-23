#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <windows.h>
#include "Hero.h"


std::string getFileContentsReverse(std::ifstream & File);
void startScreen();
void printHero();
void endScreen();
int select(int size);
void showStat(vector<shared_ptr<Hero>>& team, bool target);
void showAttack(shared_ptr<Hero>& hero, shared_ptr<Hero>& target);
void showAbility(shared_ptr<Hero>& hero);
void animation(string ability);
void border();
void clearBox(bool left, bool right);
void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
std::string getFileContents(std::ifstream& File);