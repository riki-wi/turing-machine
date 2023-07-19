#include "turingmachine.h"

TuringMachine::TuringMachine(long long int tapeSize, const TuringProgram &turingProgram) : tapeSize_(tapeSize),
                                                                                           turingProgram_(turingProgram),
                                                                                           currentState_(turingProgram.startState()),
                                                                                           tape_('0', tapeSize_),
                                                                                           currentSymbol_('0'),
                                                                                           cap_(tape_.begin())

{
}

std::string TuringMachine::tapePrint() const
{
    std::string res;
    auto iter = cap_;
    do
    {
        res += *iter;
        ++iter;
    }
    while(iter != cap_);
    return res;
}

void TuringMachine::initialization(const std::string &init)
{
    cap_ = tape_.begin();
    for(int i = 0; init[i] != '\0'; i++)
    {
        *cap_ = init[i];
        ++cap_;
    }
    cap_ = tape_.begin();
    currentSymbol_ = *tape_.begin();
}

std::string TuringMachine::calc(const std::string &init, int max_steps)
{
    initialization(init);
    for(int i = 0; i < max_steps; i++)
    {
        char direction = turingProgram_.mapping(currentState_, currentSymbol_).direction;
        if(direction == '\0')
        {
            return tapePrint();
        }

        char convSymbolSave = turingProgram_.mapping(currentState_, currentSymbol_).conversionSymbol;
        currentState_ = turingProgram_.mapping(currentState_, currentSymbol_).conversionStatus;

        *cap_ = convSymbolSave;
        if(direction == 'R')
        {
            ++cap_;
        }
        if(direction == 'L')
        {
            --cap_;
        }
        currentSymbol_ = *cap_;
    }
    return "Not applicable";
}

long long TuringMachine::tapeSize() const
{
    return tapeSize_;
}

