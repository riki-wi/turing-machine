#pragma once

#include "gtest/gtest.h"
#include "../src/turingmachine.h"

TEST(turingMachine, test_one)
{
    ASSERT_THROW(TuringMachine(2, TuringProgram("../../tests/error-MT.txt")), ParserException);
}

TEST(turingMachine, test_two)
{
    for(int i = 3; i < 13; i++)
    {
        std::string pathInput = "../../tests/" + std::to_string(i) + "-input.txt";
        std::string pathOutput = "../../tests/" + std::to_string(i) + "-output.txt";
        std::string pathMT = "../../tests/" + std::to_string(i) + "-MT.txt";

        std::ifstream finInput(pathInput, std::ifstream::in);
        std::ifstream finOutput(pathOutput, std::ifstream::in);
        std::ifstream finMT(pathInput, std::ifstream::in);

        char strInput[255]{'\0'};
        char strOutput[255]{'\0'};
        finInput.getline(strInput, 255, '\n');
        finOutput.getline(strOutput, 255, '\n');

        char **splitStrInput;
        split_string(strInput, ' ', &splitStrInput);

        TuringProgram turingProgram(pathMT.c_str());
        TuringMachine turingMachine((long long) my_atoi(splitStrInput[0]), turingProgram);

        std::string res = turingMachine.calc(std::string(splitStrInput[2], length_string(splitStrInput[2])),
                                             (int) my_atoi(splitStrInput[1]));

        ASSERT_STREQ(remove_zero_end(remove_zero_begin(res.c_str())), strOutput);

        finInput.close();
        finOutput.close();
        finMT.close();
    }
}