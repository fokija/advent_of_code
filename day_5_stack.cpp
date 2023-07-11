#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

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

struct movement_data
{
    int how_many;
    int source;
    int destination;
};

movement_data parse_line(const std::string& str)
{    
    char* s = new char[str.size()+1]; 
    strcpy(s, str.c_str());
    
    movement_data res;
    
    char* substr;
    substr = strtok(s, " ");
    
    int cnt = 0;
    while (NULL != substr)
    {
        //std::cout << substr << "*";
        substr = strtok(NULL, " ");
        
        if (NULL == substr) break;
        
        int converted_val = atoi(substr);
        
        if (converted_val > 0)
        {
            switch (cnt)
            {
                case 0:
                    res.how_many = converted_val;
                    break;
                case 1:
                    res.source = converted_val;
                    break;
                case 2:
                    res.destination = converted_val;
                    break;
                default:
                    break;
            }
            cnt++;
        }
    }
    return res;
}

std::stack<char> create_stack(const std::vector<char>& v)
{
    std::stack<char> my_stack;
    for (auto a : v)
    {
        my_stack.push(a);
    }
    return my_stack;
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

    std::vector<movement_data> move_data_vec;
    std::vector<std::stack<char>> stack_vec;

    for (int i = 0; i < lines.size(); ++i)
    {
        move_data_vec.push_back(parse_line(lines[i]));
    }

    stack_vec.push_back(create_stack({'D','L','J','R','V','G','F'}));
    stack_vec.push_back(create_stack({'T','P','M','B','V','H','J','S'}));
    stack_vec.push_back(create_stack({'V','H','M','F','D','G','P','C'}));
    stack_vec.push_back(create_stack({'M','D','P','N','G','Q'}));
    stack_vec.push_back(create_stack({'J','L','H','N','F'}));
    stack_vec.push_back(create_stack({'N','F','V','Q','D','G','T','Z'}));
    stack_vec.push_back(create_stack({'F','D','B','L'}));
    stack_vec.push_back(create_stack({'M','J','B','S','V','D','N'}));
    stack_vec.push_back(create_stack({'G','L','D'}));

    for (int i = 0; i < move_data_vec.size(); i++)
    {
        for (int j = 0; j < move_data_vec[i].how_many; j++)
        {
           char temp_char = stack_vec[move_data_vec[i].source-1].top();
           stack_vec[move_data_vec[i].source-1].pop();
           stack_vec[move_data_vec[i].destination-1].push(temp_char); 
        }
    }

    for (int i = 0; i < stack_vec.size(); i++)
    {
        std::cout << stack_vec[i].top();
    }

    std::cout << std::endl;

return 0;    
}
