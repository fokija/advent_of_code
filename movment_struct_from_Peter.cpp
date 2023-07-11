#include <iostream>

#include <string.h>
#include <stdlib.h>

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
        std::cout << substr << "*";
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

int main()
{
    
    std::string str = "move 1 from 2 to 3";
    
    movement_data data = parse_line(str);
    
    std::cout << "\n\n";
    
    std::cout << data.how_many << " " << data.source << " " << data.destination << "\n";
}