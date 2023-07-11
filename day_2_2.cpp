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
    std::vector<char> oponent;
    std::vector<char> me;
    int counter = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        std::string temp = lines[i];
        oponent.push_back(temp[0]);
        me.push_back(temp[2]);

        //if (me[i] == 'X' && oponent[i] == 'A') {counter += 1}

        if (oponent[i] == 'A' && me[i] == 'X') { counter += 3; }
        else if (oponent[i] == 'A' && me[i] == 'Y') { counter += 4; }
        else if (oponent[i] == 'A' && me[i] == 'Z') { counter += 8; }
        else if (oponent[i] == 'B' && me[i] == 'X') { counter += 1; }
        else if (oponent[i] == 'B' && me[i] == 'Y') { counter += 5; }
        else if (oponent[i] == 'B' && me[i] == 'Z') { counter += 9; }
        else if (oponent[i] == 'C' && me[i] == 'X') { counter += 2; }
        else if (oponent[i] == 'C' && me[i] == 'Y') { counter += 6; }
        else if (oponent[i] == 'C' && me[i] == 'Z') { counter += 7; }

        // switch (me[i])
        // {
        //     case 'X' : 
        //         counter+= 1;
        //         break;
        //     case 'Y' : 
        //         counter+= 2;
        //         break;
        //     case 'Z' : 
        //         counter+= 3;
        //         break;
        // }
    }
    
    std::cout << counter << std::endl;
    return 0;
    
}