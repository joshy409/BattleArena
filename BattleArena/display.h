#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

void printscreen(string filename);
void gotoXY(int x, int y, string text);
void gotoXY(int x, int y);
std::string getFileContents(std::ifstream& File);