#include <fstream>
#include <string>
#include <iostream>
#include <vector>



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
    My_stack stack_1({'Z','N'});
    My_stack stack_2({'M','C','D'});
    My_stack stack_3({'P'});

    stack_1.print();
    stack_2.print();
    stack_3.print();

    char temp_char = stack_2.pop();
    stack_1.push(temp_char);

    for (int i = 0; i < 3; i++)
    {
        char temp_char = stack_1.pop();
        stack_3.push(temp_char);
    }
    for (int i = 0; i < 2; i++)
    {
        char temp_char = stack_2.pop();
        stack_1.push(temp_char);
    }

    temp_char = stack_1.pop();
    stack_2.push(temp_char);

    stack_1.print();
    stack_2.print();
    stack_3.print();

    std::string result = "";

    result = {stack_1.get_top_elem() , stack_2.get_top_elem() , stack_3.get_top_elem()};
    std::cout << result;

return 0;    
}
