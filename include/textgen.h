// Copyright 2022 UNN-IASR
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>

typedef std::deque<std::string> prefix;

class TextGenerator {
public:
    int NPREF;
    int MAXGEN;
    prefix start;
    std::map<prefix, std::vector<std::string>> stateTab;
    std::string fileIn;
    std::string fileOut;
    TextGenerator(std::string, std::string, int, int);
    void generate();
    void readFromFile();
    void writeToFile();
    std::string selectNewStr(prefix);
    std::vector<std::string> formText();
};
