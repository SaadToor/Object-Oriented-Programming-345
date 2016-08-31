#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void csvdump(string filename, char seperator, vector<vector<string>>& csvData);
void trimSpace(string& f);
void csvprint(vector<vector<string>>& csvData);