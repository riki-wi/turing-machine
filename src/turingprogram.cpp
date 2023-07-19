#include "turingprogram.h"

TuringProgram::TuringProgram(const char *filename) : startState_(nullptr), countRule_(0)
{
    std::ifstream fin(filename, std::ifstream::in);

    if(!fin)
    {
        throw OpenFileException();
    }

    char str[MAX_STR]{'\0'};
    while(fin.getline(str, MAX_STR, '\n'))
    {
        RuleIn ruleIn = parserRule(str);
        addRule(ruleIn);
    }
    fin.close();
}

void TuringProgram::addRule(const RuleIn &ruleIn)
{
    long long key = polynomial_hash(ruleIn.currentStatus);
    bool ruleIs = mapRules_.find_by_key(key);
    if(ruleIs)
    {
        RuleIn placeOfAdding = mapRules_.get_by_key(key);
        placeOfAdding.listRuleOut.push_front(ruleIn.listRuleOut.front());
        mapRules_.change_by_key(key, placeOfAdding);

    } else
    {
        mapRules_.add(key, ruleIn);
    }

    if(mapRules_.size() == 1)
    {
        startState_ = ruleIn.currentStatus;
    }
    countRule_++;
}

TuringProgram::RuleIn TuringProgram::parserRule(const char *str)
{
    char **splitStrSpace;
    RuleIn ruleIn{};
    RuleOut ruleOut{};
    split_string(str, ' ', &splitStrSpace);

    if(splitStrSpace[0] == nullptr || splitStrSpace[1] == nullptr || splitStrSpace[2] == nullptr
       || splitStrSpace[3] == nullptr || splitStrSpace[4] == nullptr || splitStrSpace[5] == nullptr)
    {
        throw ParserException();
    }

    if(splitStrSpace[0][0] == 'q')
    {
        ruleIn.currentStatus = splitStrSpace[0];
    } else
    {
        throw ParserException();
    }

    if(splitStrSpace[1][0] == '0' || splitStrSpace[1][0] == '1')
    {
        ruleOut.currentSymbol = splitStrSpace[1][0];
    } else
    {
        throw ParserException();
    }

    if(splitStrSpace[3][0] == 'q')
    {
        ruleOut.conversionStatus = splitStrSpace[3];
    } else
    {
        throw ParserException();
    }

    if(splitStrSpace[4][0] == '0' || splitStrSpace[4][0] == '1')
    {
        ruleOut.conversionSymbol = splitStrSpace[4][0];
    } else
    {
        throw ParserException();
    }

    if(splitStrSpace[5][0] == 'L' || splitStrSpace[5][0] == 'R' || splitStrSpace[5][0] == 'N')
    {
        ruleOut.direction = splitStrSpace[5][0];
    } else
    {
        throw ParserException();
    }
    ruleIn.listRuleOut.push_front(ruleOut);
    return ruleIn;
}

TuringProgram::RuleOut TuringProgram::mapping(char *currentStatus, char currentSymbol) const
{
    long long key = polynomial_hash(currentStatus);
    bool ruleIs = mapRules_.find_by_key(key);

    if(ruleIs)
    {
        RuleIn list_out = mapRules_.get_by_key(key);
        for(auto iter = list_out.listRuleOut.begin(); iter != list_out.listRuleOut.end(); ++iter)
        {
            if(iter.operator*().currentSymbol == currentSymbol)
            {
                return iter.operator*();
            }
        }
    }
    return RuleOut{'\0', (char *) "\0", '\0', '\0'};
}

long long TuringProgram::countRule() const
{
    return countRule_;
}

char *TuringProgram::startState() const
{
    return startState_;
}