#pragma once
#include <fstream>
using namespace std;

const int MAX = 10000;

struct Roads{
    char *from = nullptr;
    char *to = nullptr;
    int dist = 0;
};
int numbersOfRecords(string &file);
void records(string line, Roads *part, int numb);
int findMinWay(const string& FilePath, string& departure, string& arrival);
int searchLess(Roads *way, string& from, string& to, int numb);