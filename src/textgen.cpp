// Copyright 2022 UNN-IASR
// #pragma once
#include "textgen.h"

TextGenerator::TextGenerator(std::string in, std::string out, int sPref, int sText) {
    NPREF = sPref;
    MAXGEN = sText;
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

std::string* TextGenerator::selectNewStr() {
    std::map<prefix, std::vector<std::string>>::iterator it = stateTab.find(next);
    if (it != stateTab.end()) {
        std::string* str = new std::string();
        *str = it->second[rand() % (it->second).size()];
        return str;
    }
    else
    {
        return NULL;
    }
}

void TextGenerator::writeToFile() {
    std::ofstream out(fileOut);
    std::vector<std::string> resultOfGeneration = formText();
    for (int i = 0; i < resultOfGeneration.size(); i++) {
        out << resultOfGeneration[i] << " ";
    }
}

std::vector<std::string> TextGenerator::formText() {
    std::vector<std::string> resultOfGeneration;
    for (int i = 0; i < NPREF; i++) {
        resultOfGeneration.push_back(start[i]);
    }
    next = start;
    std::string str;
    srand(time(0));
    for (int i = 0; i < MAXGEN; i++) {
        std::string* nextStr = selectNewStr();
        if (nextStr != NULL) {
            resultOfGeneration.push_back(*nextStr);
            next.pop_front();
            next.push_back(*nextStr);
        }
        else
        {
            break;
        }
    }
    return resultOfGeneration;
}

void TextGenerator::generate() {
    readFromFile();
    writeToFile();
}