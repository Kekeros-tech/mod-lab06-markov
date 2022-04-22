// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "textgen.h"


TEST(test1, prefixSize) {
    TextGenerator generator = TextGenerator("test1.txt", "", 3, 1000);
    generator.readFromFile();
    ASSERT_TRUE(generator.start.size() == 3);
}

TEST(test2, recordFormation) {
    TextGenerator g = TextGenerator("test2.txt", "", 2, 1000);
    g.readFromFile();
    prefix expected;
    expected.push_back("���");
    expected.push_back("������");
    std::map<prefix, std::vector<std::string>>::iterator r=g.stateTab.find(expected);
    if (r != g.stateTab.end()) {
        ASSERT_TRUE(r->second[0] == "����");
    } else {
        FAIL();
    }
}

TEST(test3, wordChoice) {
    TextGenerator generator = TextGenerator("test3.txt", "", 2, 1000);
    generator.readFromFile();
    prefix expected;
    expected.push_back("�");
    expected.push_back("�������");
    std::string* nextStr = generator.selectNewStr(expected);
    ASSERT_EQ(*nextStr, "����������������");
}

TEST(test4, multipleChoice) {
    TextGenerator generator = TextGenerator("test4.txt", "", 2, 1000);
    generator.readFromFile();
    prefix expected;
    expected.push_back("�");
    expected.push_back("����");
    std::string* nextStr = generator.selectNewStr(expected);
    ASSERT_TRUE((*nextStr == "�����������") || (*nextStr == "c"));
}

TEST(test5, dimensionalCheck) {
    TextGenerator generator = TextGenerator("test5.txt", "resultTest5.txt", 2, 1000);
    generator.generate();
    std::ifstream in("resultTest5.txt");
    std::string str;
    int count = 0;
    if (in.is_open()) {
        while (in >> str) {
            count++;
        }
    } else {
        FAIL();
    }
    in.close();
    ASSERT_EQ(count, 79);
}
