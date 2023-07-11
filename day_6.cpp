#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> readLinesFromFile(const std::string& filename)
{
    std::vector<std::string> result;

    std::ifstream file(filename);

    // handle read-error

    std::string str; 
    while (std::getline(file, str))
    {
        result.push_back(str);
    }
    
    return result;
}

int main(int argc, char* argv[]) 
{ 

    // 1. read input file
    if (argc < 2)
    {
        std::cout << "No input files!\n";
        return -1;
    }

    std::string filename { argv[1] };

    std::vector<std::string> lines = readLinesFromFile(filename);
    
    // 2. solve exercise
    
    std::string signal_string = lines[0];
    //std::cout << signal_string << "\n\n";
    int solution = 0;

    for (int i = 0; i < signal_string.size(); i++)
    {
        if (signal_string[i] != signal_string[i+1] && signal_string[i] != signal_string[i+2]
            && signal_string[i] != signal_string[i+3] && signal_string[i+1] != signal_string[i+2]
            && signal_string[i+1] != signal_string[i+3] && signal_string[i+2] != signal_string[i+3])
        {
            solution = i + 4;
            break;
        }
    }

    std::cout << solution << "\n\n";


    return 0;
    
}