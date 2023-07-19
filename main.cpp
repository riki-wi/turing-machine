#include "iostream"
#include "src/turingmachine.h"

void run(int argc, char* argv[])
{
    try
    {
        if(argc != 4)
        {
            throw ArgumentExceptionConsole();
        }

        std::ifstream fin(argv[2], std::ifstream::in);
        std::ofstream fout(argv[3], std::ofstream::out & std::ios_base::trunc);

        if(!fin || !fout)
        {
            throw OpenFileException();
        }

        TuringProgram turingProgram(argv[1]);

        char strInput[255]{'\0'};
        fin.getline(strInput, 255, '\n');
        char **splitStrInput;
        split_string(strInput, ' ', &splitStrInput);

        TuringMachine turingMachine((long long) my_atoi(splitStrInput[0]), turingProgram);
        std::string res = turingMachine.calc(std::string(splitStrInput[2], length_string(splitStrInput[2])),
                                             (int)my_atoi(splitStrInput[1]));

        fout << remove_zero_end(remove_zero_begin(res.c_str()));

        fin.close();
        fout.close();

    } catch (ParserException &e)
    {
        std::ofstream fout(argv[3], std::ofstream::out & std::ios_base::trunc);
        fout << "Error\n";
        fout.close();

    } catch (ArgumentExceptionConsole &e)
    {
        std::cerr << e.what();
    } catch (OpenFileException &e)
    {
        std::cerr << e.what();
    }
}


int main(int argc, char* argv[])
{
    run(argc, argv);
    return 0;
}
