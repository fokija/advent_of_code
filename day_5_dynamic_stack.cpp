#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <cstring>

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
    delete [] s;
    return res;
}

class Stack_interface
{
public:
    virtual void push(char c) = 0;
    virtual char pop() = 0;
    virtual char get_top_elem() const = 0;
    virtual void print() const = 0;
    virtual ~Stack_interface() {} 
};

constexpr unsigned int SINGLE_ALLOC_SIZE = 5u;

class Dynamic_stack : public Stack_interface
{
// internal data fields
private:
    char* m_data; 
    unsigned int m_allocCounter;
    int m_stackIdx;
public:
    Dynamic_stack()
    {
        m_stackIdx = -1;
        m_allocCounter = 0;
        m_data = new char [SINGLE_ALLOC_SIZE];
        m_allocCounter++;
    }
    ~Dynamic_stack()
    {
        std::cout << "destructor \n";
        delete [] m_data;
    }
    Dynamic_stack(std::vector<char> x) : Dynamic_stack() // konstruktor delegujacy 
    {
        for (int i = 0; i < x.size(); i++)
        {
            push(x[i]);
        }
    }
    Dynamic_stack(const Dynamic_stack& other) // konstruktor kopiujacy
    {
        m_stackIdx = other.m_stackIdx;
        m_allocCounter = other.m_allocCounter;
        m_data = new char [SINGLE_ALLOC_SIZE * m_allocCounter];

        std::memcpy(m_data, other.m_data, SINGLE_ALLOC_SIZE * m_allocCounter * sizeof(char));
    }
    Dynamic_stack& operator=(const Dynamic_stack& other)
    {
        delete [] m_data;
        m_stackIdx = other.m_stackIdx;
        m_allocCounter = other.m_allocCounter;
        m_data = new char [SINGLE_ALLOC_SIZE * m_allocCounter];

        std::memcpy(m_data, other.m_data, SINGLE_ALLOC_SIZE * m_allocCounter * sizeof(char));
        
        return *this;
    }

    
    void push(char c)
    {
        m_stackIdx++;
        if (m_stackIdx < m_allocCounter * SINGLE_ALLOC_SIZE)
        {
            m_data[m_stackIdx] = c;
        }
        else
        {
            char* tmp_data = new char [m_stackIdx];
            for (int i = 0; i < m_stackIdx; i++)
            {
                tmp_data[i] = m_data[i];
            }
            m_allocCounter++;
            delete [] m_data;
            m_data = new char [SINGLE_ALLOC_SIZE * m_allocCounter];
            for (int i = 0; i < m_stackIdx; i++)
            {
                m_data[i] = tmp_data[i];
            }
            delete [] tmp_data;
            m_data[m_stackIdx] = c;
        }
    }
    char pop()
    {
        char last_char = m_data[m_stackIdx];
        m_stackIdx--;
        return last_char;
    }
    char get_top_elem() const
    {
        return m_data[m_stackIdx];
    }
    void print() const
    {
        for (int i = 0; i <= m_stackIdx; i++)
        {
            std::cout << m_data[i] << " ";
        }
        std::cout << std::endl;
    }
};

class My_stack : public Stack_interface
{
    private:
        std::vector<char> m_data;
    public:
        My_stack(std::vector<char> x);
        void push(char c);
        char pop();
        char get_top_elem() const;
        void print() const;
};

class My_stack_2 : public Stack_interface
{
private:
    char m_data[100];
    unsigned int m_last_index = 0;
public:
    My_stack_2(std::vector<char> x)
    {
        for (auto i = 0; i < x.size(); i++)
        {
            m_data[m_last_index] = x[i];
            m_last_index++;
        }
        m_last_index--;
    }
    void push(char c)
    {
        ++m_last_index;
        m_data[m_last_index] = c;
    }
    char pop()
    {
        char last_char = m_data[m_last_index];
        m_last_index--;
        return last_char;
    }
    char get_top_elem() const
    {
        return m_data[m_last_index];
    }
    void print() const
    {
        for (auto c : m_data)
        {
        std::cout << c << " ";
        }
        std::cout << std::endl;
    }
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
    char last_char = this -> get_top_elem();
    m_data.pop_back();
    return last_char;
}
char My_stack::get_top_elem() const
{
    return m_data[m_data.size()-1];
}
void My_stack::print() const
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
    std::vector<Stack_interface*> stack_vec;

    for (int i = 0; i < lines.size(); ++i)
    {
        move_data_vec.push_back(parse_line(lines[i]));
    }
    
    stack_vec.push_back(new Dynamic_stack ({'D','L','J','R','V','G','F'}));
    stack_vec.push_back(new Dynamic_stack ({'T','P','M','B','V','H','J','S'}));
    stack_vec.push_back(new Dynamic_stack ({'V','H','M','F','D','G','P','C'}));
    stack_vec.push_back(new Dynamic_stack ({'M','D','P','N','G','Q'}));
    stack_vec.push_back(new Dynamic_stack ({'J','L','H','N','F'}));
    stack_vec.push_back(new Dynamic_stack ({'N','F','V','Q','D','G','T','Z'}));
    stack_vec.push_back(new Dynamic_stack ({'F','D','B','L'}));
    stack_vec.push_back(new Dynamic_stack ({'M','J','B','S','V','D','N'}));
    stack_vec.push_back(new Dynamic_stack ({'G','L','D'}));

    for (int i = 0; i < stack_vec.size(); i++) //print test
    {
        stack_vec[i]->print();
    }

    for (int i = 0; i < move_data_vec.size(); i++)
    {
        for (int j = 0; j < move_data_vec[i].how_many; j++)
        {
           char temp_char = stack_vec[move_data_vec[i].source-1]->pop();
           stack_vec[move_data_vec[i].destination-1]->push(temp_char); 
        }
    }

    // std::cout << "\n\n\n";
    // for (int i = 0; i < stack_vec.size(); i++)
    // {
    //     stack_vec[i]->print();
    // }

    for (int i = 0; i < stack_vec.size(); i++)
    {
        std::cout << stack_vec[i]->get_top_elem();
    }

    std::cout << std::endl;

    for (auto stack : stack_vec)
    {
        delete stack;
    }

Dynamic_stack stack1({'A','B','C'});
Dynamic_stack stack2(stack1);
Dynamic_stack stack3({'z','z'});
stack1 = stack3;





std::cout << "KONIEC\n";
return 0;    
}
