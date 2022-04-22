// #pragma once
#include "textgen.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>


TextGenerator::TextGenerator(std::string in, std::string out, int sizeOfPrefix, int sizeOfOutText) {
    NPREF = sizeOfPrefix;
    MAXGEN = sizeOfOutText;
    fileIn = in;
    fileOut = out;
}

void TextGenerator::readFromFile() {
    std::ifstream in(fileIn);
    std::string str;
    for (int i = 0; i < NPREF; i++) {
        in >> str;
        next.push_back(str);
    }
    start = next;
    while (in >> str) {
        stateTab[next].push_back(str);
        next.pop_front();
        next.push_back(str);
    }
    in.close();
}

void TextGenerator::writeToFile() {
    std::ofstream out(fileOut);
    for (int i = 0; i < NPREF; i++) {
        out << start[i] << " ";
    }
    std::map<prefix, std::vector<std::string>>::iterator it;
    next = start;
    std::string str;
    srand(time(0));
    for (int i = 0; i < MAXGEN; i++) {
        it = stateTab.find(next);
        if (it != stateTab.end()) {
            str = it->second[rand() % (it->second).size()];
            out << str << " ";
            next.pop_front();
            next.push_back(str);
        }
        else
        {
            break;
        }
    }
}

void TextGenerator::generate() {
    readFromFile();
    writeToFile();
}