#pragma once
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

using std::ifstream;
using std::ofstream;
using std::cerr;

string read_file(string file_name);

// time_t str_to_time_t(const string& ATime, const string& AFormat);

time_t str_to_time_t(std::string str);

void Stringsplit(const string& str, const char split, std::vector<string>& res);

void Stringsplit(const string& str, const string& splits, std::vector<string>& res);

string& replace_all(string& src, const string& old_value, const string& new_value);
