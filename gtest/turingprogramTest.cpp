#pragma once

#include "gtest/gtest.h"
#include "../src/turingprogram.h"

TEST(turingProgram, test_one)
{
    TuringProgram turingProgram("../../tests/1-MT.txt");

    ASSERT_EQ(turingProgram.countRule(), 6);
    ASSERT_STREQ(turingProgram.startState(), "q11");

    ASSERT_EQ(turingProgram.mapping((char *) "q11", '0').direction, 'L');
    ASSERT_EQ(turingProgram.mapping((char *) "q11", '0').conversionSymbol, '0');
    ASSERT_EQ(turingProgram.mapping((char *) "q11", '0').currentSymbol, '0');
    ASSERT_STREQ(turingProgram.mapping((char *) "q11", '0').conversionStatus, "q10");

    ASSERT_EQ(turingProgram.mapping((char *) "q13", '1').direction, 'R');
    ASSERT_EQ(turingProgram.mapping((char *) "q13", '1').conversionSymbol, '0');
    ASSERT_EQ(turingProgram.mapping((char *) "q13", '1').currentSymbol, '1');
    ASSERT_STREQ(turingProgram.mapping((char *) "q13", '1').conversionStatus, "q11");

    ASSERT_EQ(turingProgram.mapping((char *) "q10", '0').direction, '\0');
    ASSERT_EQ(turingProgram.mapping((char *) "q10", '0').conversionSymbol, '\0');
    ASSERT_EQ(turingProgram.mapping((char *) "q10", '0').currentSymbol, '\0');
    ASSERT_STREQ(turingProgram.mapping((char *) "q10", '0').conversionStatus, "\0");
}

TEST(turingProgram, test_two)
{
    TuringProgram turingProgram("../../tests/8-MT.txt");

    ASSERT_EQ(turingProgram.countRule(), 4);
    ASSERT_STREQ(turingProgram.startState(), "q1");

    ASSERT_EQ(turingProgram.mapping((char *) "q1", '0').direction, 'N');
    ASSERT_EQ(turingProgram.mapping((char *) "q1", '0').conversionSymbol, '1');
    ASSERT_EQ(turingProgram.mapping((char *) "q1", '0').currentSymbol, '0');
    ASSERT_STREQ(turingProgram.mapping((char *) "q1", '0').conversionStatus, "q1");

    ASSERT_EQ(turingProgram.mapping((char *) "q1", '1').direction, 'L');
    ASSERT_EQ(turingProgram.mapping((char *) "q1", '1').conversionSymbol, '1');
    ASSERT_EQ(turingProgram.mapping((char *) "q1", '1').currentSymbol, '1');
    ASSERT_STREQ(turingProgram.mapping((char *) "q1", '1').conversionStatus, "q2");

    ASSERT_EQ(turingProgram.mapping((char *) "q2", '0').direction, 'N');
    ASSERT_EQ(turingProgram.mapping((char *) "q2", '0').conversionSymbol, '1');
    ASSERT_EQ(turingProgram.mapping((char *) "q2", '0').currentSymbol, '0');
    ASSERT_STREQ(turingProgram.mapping((char *) "q2", '0').conversionStatus, "q2");

    ASSERT_EQ(turingProgram.mapping((char *) "q2", '1').direction, 'L');
    ASSERT_EQ(turingProgram.mapping((char *) "q2", '1').conversionSymbol, '1');
    ASSERT_EQ(turingProgram.mapping((char *) "q2", '1').currentSymbol, '1');
    ASSERT_STREQ(turingProgram.mapping((char *) "q2", '1').conversionStatus, "q1");
}

TEST(turingProgram, test_three)
{
    ASSERT_THROW(TuringProgram turingProgram("../../tests/error-MT.txt"), ParserException);
}