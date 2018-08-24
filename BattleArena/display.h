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



void startScreen();
void printHero();
void printHeroByName(string name, int x, int y);
void endScreen();
int select(int size);
void showStat(vector<shared_ptr<Hero>>& team, bool target);
void showAttack(shared_ptr<Hero>& hero, shared_ptr<Hero>& target);
void showAbility(shared_ptr<Hero>& hero);
void animation(shared_ptr<Hero>& hero, shared_ptr<Hero>& target);
void border();
void clearBox(bool left, bool right, bool up);
void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
std::string getFileContents(std::ifstream& File,int x, int y);
std::string getFileContentsReverse(std::ifstream & File, int x, int y);