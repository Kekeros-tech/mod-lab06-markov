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
    TextGenerator generator = TextGenerator("test2.txt", "", 2, 1000);
    generator.readFromFile();
    prefix expected;
    expected.push_back("Это");
    expected.push_back("второй");
    std::map<prefix, std::vector<std::string>>::iterator result = generator.stateTab.find(expected);
    if (result != generator.stateTab.end()) {
        ASSERT_TRUE(result->second[0] == "тест");
    }
    else
    {
        FAIL();
    }
}