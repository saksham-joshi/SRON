#include "_argument_list_.hpp"
#include <queue>
#include <stack>

#ifndef POSTFIX_H
#define POSTFIX_H

class PostFix
{
    inline static int precedence(char &ch)
    {
        switch (ch)
        {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        }
        return 0;
    }

    inline static bool is_number(const std::string &str)
    {
        char ch = str[0];
        if ((ch >= '0' && ch <= '9'))
        {
            return true;
        }
        else if ((ch == '.' || ch == '-') && str.length() > 1 && ((str[1] >= '0' && str[1] <= '9') || str[1] == '.'))
        {
            return true;
        }
        return false;
    }
    inline static bool is_operator(char ch)
    {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(';
    }

    inline static bool is_operator(const std::string &ch)
    {
        return ch.length() == 1 && is_operator(ch[0]);
    }

public:
    inline static std::queue<std::string>* POSTFIX(const std::vector<std::string> &vec)
    {
        std::stack<char> stk;
        std::queue<std::string> exp;
        for (auto it = vec.begin(); it < vec.end(); ++it)
        {
            if (PostFix::is_number(*it)) 
            {
                exp.push(*it);
            }
            else if (*it == "(")
            {
                stk.push((*it)[0]);
            }
            else if (PostFix::is_operator((*it)[0]))
            {
                char ch = (*it)[0];
                while (!stk.empty() && PostFix::precedence(ch) <= PostFix::precedence(stk.top()))
                {
                    exp.push(std::string(*it));
                    stk.pop();
                }
                stk.push((*it)[0]);
            }
            else if (*it == ")")
            {
                while (!stk.empty() && stk.top() != '(')
                {
                    exp.push(std::string(1, stk.top()));
                    stk.pop();
                }
                if (!stk.empty())
                {
                    stk.pop();
                }
            }
        }
        while (!stk.empty())
        {
            exp.push(std::string(1, stk.top()));
            stk.pop();
        }
        return &exp;
    }
};

#endif