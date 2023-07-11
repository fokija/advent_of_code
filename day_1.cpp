#include <algorithm>
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
    int counter = 0;
    int temp_counter = 0;
    std::vector<int> all_elves_calories;

    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i] != "")
        {
            int temp_int = stoi(lines[i]);
            //std::cout << temp_int << std::endl;
            temp_counter = temp_int + temp_counter;
        }
        else 
        {
            all_elves_calories.push_back(temp_counter);
            if (temp_counter > counter)
            {
            counter = temp_counter;
            }
            temp_counter = 0;
        }
    };

    std::cout << counter << std::endl;
    std::sort(all_elves_calories.begin(), all_elves_calories.end(), std::greater<int>());
    int sum_of_three = all_elves_calories[0] + all_elves_calories[1] + all_elves_calories[2];
    std::cout << sum_of_three << std::endl;
    return 0;
    
}