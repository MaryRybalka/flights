#include <iostream>
#include "lib.h"
#include <vector>
#include <cstring>
#include <exception>
using namespace std;

int numbersOfRecords(string& line){
    int res = 0;
    int i = 0;
    int size = line.size();
    while (i < size){
        while ((line[i++] != '\n') && (i < size));
        res++;
    }
    return res;
}

void records(string line, Roads *part, int numb){
    int i = 0;

    for(int j = 0; j<numb; j++){
        size_t check = line.find('\n');
        size_t found = line.find(' ');
        if((check < found) || (check == found+1) || ((check > line.length()) && (found > line.length()))){
            throw out_of_range("Name of arrival place and value of distance are missed.");
        } else {
            string sub = line.substr(0, found);
            part[j].from = new char [found];
            strcpy(part[j].from,sub.c_str());

            line.erase(0,found+1);
            found = line.find(' ');
            check = line.find('\n');
            if((check > line.length()) && (found > line.length())){
                throw out_of_range("Value of distance is missed.");
            } else {
                sub = line.substr(0, found);
                part[j].to = new char [found];
                strcpy(part[j].to,sub.c_str());

                line.erase(0,found+1);
                found = line.find('\n');
                sub = line.substr(0, found);
                part[j].dist = atoi(sub.c_str());
                if((found == 0) || (part[j].dist == 0)){
                    throw out_of_range("Error in value of distance.");
                } else {
                    line.erase(0,found+1);
                }
            }
        }
    }
}

int searchLess(Roads *way, string& from, string& to, int numb){
    int foundWay = MAX;
    if(numb == 1){
        foundWay = way[0].dist;
    } else {
        int min[numb-1];
        for (int i = 0; i < numb-1; i++) min[i] = 0;

        int j = 0;
        for (int i = 0; i<numb; i++){
            if(way[i].from == from){
                min[j] = way[i].dist;
                if(way[i].to == to) j++;
                else {
                    for (int m = 0; m<numb; m++){
                        if(strcmp(way[m].from, way[i].to) == 0) {
                            if (way[m].to == to) {
                                min[j+1] = min[j];
                                min[j] += way[m].dist;
                                j++;
                            } else {
                                min[j] += way[m].dist;
                                for (int l = 0; l<numb; l++){
                                    if(strcmp(way[l].from, way[m].to) == 0) {
                                        if (way[l].to == to) {
                                            min[j+1] = min[j];
                                            min[j] += way[l].dist;
                                            j++;
                                        }
                                    }
                                }
                                min[j] -= way[m].dist;
                            }
                        }
                    }
                    min[j] -= way[i].dist;
                }
            }
        }

        for (int i = 0; i < numb-1; i++){
            if ((min[i] < foundWay)&&(min[i] != 0)) foundWay = min[i];
        }
    }
    return foundWay;
}

int findMinWay(const string& FilePath, string& departure, string& arrival){
    int res = MAX;
    ifstream f;
    f.open(FilePath);
    if(!f.is_open()){
        throw bad_alloc();
    } else {
        string check((istreambuf_iterator<char>(f)),
                     istreambuf_iterator<char>());
        f >> check;
        f.close();

        int number = numbersOfRecords(check);
        auto *map = new Roads[number];
        records(check, map, number);

        bool chck = false;
        int i = 0;
        string s;
        while ((i < number)&&(!chck)) {
            s = map[i++].from;
            chck = (s == departure);
        }
        if (chck){
            res = searchLess(map,departure, arrival, number);
        }
        delete [] (map);
    }
    return res;
}