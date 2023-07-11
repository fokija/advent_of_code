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

void fill_bacpacks_compartments_vec(const std::vector<std::string> &lines, 
    std::vector<std::string> &first_compartment_vec, 
    std::vector<std::string> &second_compartment_vec)
{
     for (int i = 0; i < lines.size(); i++)
    {
       std::string temp_line = lines[i];
       std::string temp_first_compartment;
       std::string temp_second_compartment;
 
       for (int j = 0; j < temp_line.size(); j++)
       {
        if (j < (temp_line.size() / 2))
        {
            temp_first_compartment.push_back(temp_line[j]);
        }
        else
        {
            temp_second_compartment.push_back(temp_line[j]);
        }
       }
       first_compartment_vec.push_back(temp_first_compartment);
       second_compartment_vec.push_back(temp_second_compartment);
    }
}

std::vector<char> find_common_items_form_compartments(
    const std::vector<std::string> &first_compartment_vec, 
    const std::vector<std::string> &second_compartment_vec)
{
    std::vector<char> same_items;
    for (int i = 0; i < first_compartment_vec.size(); i++)
    {
        std::string temp_first_compartment = first_compartment_vec[i];
        std::string temp_second_compartment = second_compartment_vec[i];
        std::vector<char> temp_first_compartment_char_vec;
        std::vector<char> temp_second_compartment_char_vec;
        
        
        for (int j = 0; j < temp_first_compartment.size(); j++)
        {
            temp_first_compartment_char_vec.push_back(temp_first_compartment[j]);
            temp_second_compartment_char_vec.push_back(temp_second_compartment[j]); 
        }   
        for (int x = 0; x < temp_first_compartment_char_vec.size(); x++)
            {   
                bool is_same_item_found = false;
                for (int y = 0; y < temp_second_compartment_char_vec.size(); y++)
                {
                    if (temp_first_compartment_char_vec[x] == temp_second_compartment_char_vec[y])
                    {
                        same_items.push_back(temp_first_compartment_char_vec[x]);
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
return same_items;
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
    std::vector<std::string> first_compartment_vec;
    std::vector<std::string> second_compartment_vec;
    
    int number_of_points = 0;

   fill_bacpacks_compartments_vec(lines, first_compartment_vec, second_compartment_vec);
   std::vector<char> same_items = find_common_items_form_compartments(first_compartment_vec, 
        second_compartment_vec);

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

    std::cout << number_of_points << "\n";
    return 0;
}