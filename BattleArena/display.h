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

using namespace std;
void startscreen();
void endscreen();
void textbox(vector<Hero> team);
void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
std::string getFileContents(std::ifstream& File);