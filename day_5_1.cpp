#include <fstream>
#include <string>
#include <iostream>
#include <vector>
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

class My_stack
{
    private:
        std::vector<char> m_data;
    public:
        My_stack(std::vector<char> x);
        void push(char c);
        char pop();
        char get_top_elem();
        void print();
};

My_stack::My_stack(std::vector<char> x)
{
    for (auto i = 0; i < x.size(); i++)
    {
        m_data.push_back(x[i]);
    }
}
void My_stack::push(char c)
{
    m_data.push_back(c);
}
char My_stack::pop()
{
    char last_char = this->get_top_elem();
    m_data.pop_back();
    return last_char;
}
char My_stack::get_top_elem()
{
    return m_data[m_data.size()-1];
}
void My_stack::print()
{
    for (auto c : m_data)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
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
    std::vector<My_stack> stack_vec;

    for (int i = 0; i < lines.size(); ++i)
    {
        move_data_vec.push_back(parse_line(lines[i]));
    }

    stack_vec.push_back(My_stack ({'D','L','J','R','V','G','F'}));
    stack_vec.push_back(My_stack ({'T','P','M','B','V','H','J','S'}));
    stack_vec.push_back(My_stack ({'V','H','M','F','D','G','P','C'}));
    stack_vec.push_back(My_stack ({'M','D','P','N','G','Q'}));
    stack_vec.push_back(My_stack ({'J','L','H','N','F'}));
    stack_vec.push_back(My_stack ({'N','F','V','Q','D','G','T','Z'}));
    stack_vec.push_back(My_stack ({'F','D','B','L'}));
    stack_vec.push_back(My_stack ({'M','J','B','S','V','D','N'}));
    stack_vec.push_back(My_stack ({'G','L','D'}));

    for (int i = 0; i < move_data_vec.size(); i++)
    {
        My_stack temp_stack({});

        for (int j = 0; j < move_data_vec[i].how_many; j++)
        {
           char temp_char = stack_vec[move_data_vec[i].source-1].pop();
           temp_stack.push(temp_char);
        }
        for (int k = 0; k < move_data_vec[i].how_many; k++)
        {
            char temp_char = temp_stack.pop();
            stack_vec[move_data_vec[i].destination-1].push(temp_char); 
        }
    }

    for (int i = 0; i < stack_vec.size(); i++)
    {
        std::cout << stack_vec[i].get_top_elem();
    }

    std::cout << std::endl;

return 0;    
}
