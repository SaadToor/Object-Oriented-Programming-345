#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string& trim(std::string& s, char trimChar = ' ');

void csvprint(std::vector<std::vector<std::string>>& csvData);

void csvReader(std::string& filename, char delim, std::vector< std::vector<std::string> > &csv);