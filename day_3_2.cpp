#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector<char> same_items;
    int number_of_points = 0;

    for (int i = 0; i < lines.size(); i += 3)
    {
        std::string first_backpack = lines[i];
        std::string second_backapack = lines[i+1];
        std::string third_backpack = lines[i+2];
        std::string same_items_from_two_backpacks;
        
        // std::cout << first_backpack << std::endl << second_backapack << std::endl
        //     << third_backpack << std::endl << std::endl;

        for (int x = 0; x < first_backpack.size(); x++)
        {
            for (int y = 0; y < second_backapack.size(); y++)
            {
                if (first_backpack[x] == second_backapack[y])
                {
                    same_items_from_two_backpacks.push_back(first_backpack[x]);
                }
            }
        }
        //std::cout << same_items_from_two_backpacks << std::endl;
        for (int x = 0; x < same_items_from_two_backpacks.size(); x++)
        {
            bool is_same_item_found = false;
            for (int y = 0; y < third_backpack.size(); y++)
            {
                if (same_items_from_two_backpacks[x] == third_backpack[y])
                {
                    same_items.push_back(same_items_from_two_backpacks[x]);
                    is_same_item_found = true;
                    break;
                }
            }
            if (is_same_item_found == true)
            {
                break;
            }
        }
    }

    for (int i = 0; i < same_items.size(); i++)
    {
        std::cout << same_items[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < same_items.size(); i++)
    {
        int temp_int = same_items[i];

        if (temp_int < 91)
        {
            number_of_points += temp_int - 38;
        }
        else
        {
            number_of_points += temp_int - 96;
        }
    }

    std::cout << number_of_points << std::endl;
    return 0;
}
