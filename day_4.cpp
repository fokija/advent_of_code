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

    int same_range_counter = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        std::string lines_reader = lines[i];
        std::string first_scope_begin;
        std::string first_scope_end;
        std::string second_scope_begin;
        std::string second_scope_end;
        int second_loop_start = 0;
        int third_loop_start = 0;
        int fourth_loop_start = 0;

        for (int i = 0; i < lines_reader.size(); i++)
        {
            if (lines_reader[i] != '-')
            {
                first_scope_begin.push_back(lines_reader[i]);
            }
            else
            {
                i++;
                second_loop_start = i;
                break;
            }
        }
        for (int i = second_loop_start; i < lines_reader.size(); i++)
        {
            if (lines_reader[i] != ',')
            {
                first_scope_end.push_back(lines_reader[i]);
            }
            else
            {
                i++;
                third_loop_start = i;
                break;
            }
        }
        for (int i = third_loop_start; i < lines_reader.size(); i++)
        {
            if (lines_reader[i] != '-')
            {
                second_scope_begin.push_back(lines_reader[i]);
            }
            else
            {
                i++;
                fourth_loop_start = i;
                break;
            }
        }
        for (int i = fourth_loop_start; i < lines_reader.size(); i++)
        {
            second_scope_end.push_back(lines_reader[i]);
        }
        // std::cout << first_scope_begin << " " << first_scope_end 
        // << " " << second_scope_begin << " " << second_scope_end << std::endl;
        
        int first_scope_begin_int = stoi(first_scope_begin);
        int first_scope_end_int = stoi(first_scope_end);
        int second_scope_begin_int = stoi(second_scope_begin);
        int second_scope_end_int = stoi(second_scope_end);

        // std::cout << first_scope_begin_int << " " << first_scope_end_int 
        // << " " << second_scope_begin_int << " " << second_scope_end_int << std::endl;
        if ((first_scope_begin_int <= second_scope_begin_int 
            && first_scope_end_int >= second_scope_end_int) 
            || 
            (second_scope_begin_int <= first_scope_begin_int 
            && second_scope_end_int >= first_scope_end_int))
        {
            same_range_counter++;
        }
    }

std::cout << same_range_counter << std::endl;
return 0;    
}
