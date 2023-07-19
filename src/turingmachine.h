#ifndef TASK3_TURING_MACHINE_RIKI_WI_TURINGMACHINE_H
#define TASK3_TURING_MACHINE_RIKI_WI_TURINGMACHINE_H

#include <string>
#include "turingprogram.h"
#include "../external/CirculCoubleList.h"

class TuringMachine
{
private:
    TuringProgram turingProgram_;

    long long tapeSize_;

    Circle_Double_List<char> tape_;

    char *currentState_;

    Circle_Double_List<char>::Iterator cap_;

    char currentSymbol_;

public:
    TuringMachine(long long tapeSize, const TuringProgram &turingProgram);

    TuringMachine(const TuringMachine &other) = default;

    TuringMachine(TuringMachine &&other) noexcept = default;

    ~TuringMachine() = default;

    TuringMachine &operator=(const TuringMachine &other) = default;

    TuringMachine &operator=(TuringMachine &&other) noexcept = default;

    std::string tapePrint() const;

    void initialization(std::string const &init);

    std::string calc(std::string const &init, int maxSteps);

    long long tapeSize() const;
};

#endif
