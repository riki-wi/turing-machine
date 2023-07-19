#ifndef TASK3_TURING_MACHINE_RIKI_WI_PROGRAM_H
#define TASK3_TURING_MACHINE_RIKI_WI_PROGRAM_H

#pragma once

#include <fstream>
#include <iostream>
#include "errors.h"
#include "../external/SimpleMap.h"
#include "../external/simple-str.h"

#define MAX_STR 255

class TuringProgram
{
private:
    struct RuleOut
    {
        char currentSymbol;
        char *conversionStatus;
        char conversionSymbol;
        char direction;
    };

    struct RuleIn
    {
        char *currentStatus;
        List<RuleOut> listRuleOut;
    };

    static RuleIn parserRule(const char *str);

    void addRule(const RuleIn &rule_in);

    Simple_Map<long long, RuleIn> mapRules_;

    char *startState_;

    long long countRule_;

public:
    explicit TuringProgram(const char *filename);

    RuleOut mapping(char *current_status, char current_symbol) const;

    long long countRule() const;

    char *startState() const;
};

#endif
