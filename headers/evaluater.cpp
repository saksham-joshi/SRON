#include "_argument_list_.hpp"
#include <queue>
#include <stack>

#ifndef EVALUATER_H
#define EVALUATER_H


class Evaluater
{
    

    // because the function Executor::EVALUATER only allows 
    // strings that are either a valid operator or a number
    // so all the values passed here are either number or operator
    // if the value is of type Char then it must be the operator else a number. 
    inline static bool is_operator(Any* value){
        return (value->TYPE() == "Char");
    }

    inline static bool is_number(Any* value){
        return (value->TYPE() == "Int" || value->TYPE() == "Double");
    }

    inline static char extract_char(Any* value){
        if(value->GET_CHAR() != nullptr){
            return value->GET_CHAR()->GET();
        }
        return ' ';
    }

    inline static unsigned short int precedence(char ch)
    {
        switch (ch)
        {

        case '(':
        case ')':
            return 4;

        case '^':
            return 3;

        case '/':
        case '%':
        case '*':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            DISPLAY_EXCEPTION("evaluating expression. This Exception caused because an invalid operator was found", NoException);
        }
        return 0;
    }

public:
    inline Double* EVALUATE(Argument_List *arglist)
    {
        try{

            std::queue<Any *> exp = postfix(arglist);
            std::stack<long double> stk;
            int len = exp.size();

            for (int i = 0; i < len; i++)
            {
                Any* temp = exp.front();
                exp.pop();
                if (is_number(temp))
                {
                    stk.push(temp->GET_DOUBLE()->GET());
                }
                else if (is_operator(temp))
                {
                    long double d2 = stk.top();
                    stk.pop();
                    long double d1 = stk.top();
                    stk.pop();
                    char op = temp->GET_CHAR()->GET();
                    if ( op == '+')
                    {
                        stk.push(d1 + d2);
                    }
                    else if (op == '-')
                    {
                        stk.push(d1 - d2);
                    }
                    else if (op == '*')
                    {
                        stk.push(d1 * d2);
                    }
                    else if (op == '^')
                    {
                        stk.push(std::pow(d1, d2));
                    }
                    else
                    {
                        if(d2 != 0){
                            if(op == '/'){
                                stk.push(d1/d2);
                            }
                            else if(op == '%'){
                                stk.push((long long int)d1%(long long int)d2 );
                            }
                        }
                        else{
                            DISPLAY_EXCEPTION("evaluating mathematical expression.",DivisionByZeroException);
                        }
                    }
                }
            }
            return Double::MAKE(stk.top());
        }
        catch (const std::exception&)
        {
            DISPLAY_EXCEPTION("evaluting expressions",MathEvaluationException);
        }
        return nullptr;
    }

private:
    std::queue<Any *> postfix(Argument_List *arglist)
    {
        std::stack<char> stk;
        std::queue<Any *> exp;
        for (unsigned short int i = 0; i < arglist->LEN(); ++i)
        {
            auto val = arglist->operator[](i);
            if (Evaluater::is_number(val))
            {
                exp.push(val);
                continue;
            }
            char ch = extract_char(val);
            if(val->GET_CHAR()->GET() == '('){
                stk.push(ch);
            }
            else if (Evaluater::is_operator(val))
            {

                while (!stk.empty() && precedence(ch) <= precedence(stk.top()))
                {
                    exp.push(Char::MAKE(stk.top()) );
                    stk.pop();
                }
                stk.push(ch);
            }
            else if (ch == ')')
            {
                while (!stk.empty() && stk.top() != '(')
                {
                    exp.push(Char::MAKE(stk.top()));
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
            exp.push(Char::MAKE(stk.top()));
            stk.pop();
        }
        return exp;
    }
};

int main()
{

    Evaluater e1;
    std::string str;
    Argument_List* argslist = new Argument_List();
    argslist->PUT(Int::MAKE(2));
    argslist->PUT(Char::MAKE('*'));
    argslist->PUT(Int::MAKE(2));
    argslist->PUT(Char::MAKE('+'));
    argslist->PUT(Int::MAKE(2));
    for(unsigned short int i = 0 ; i< argslist->LEN() ; ++i){
        if((*argslist)[i]->TYPE() == "Int"){
            printf("%lld",(*argslist)[i]->GET_INT()->GET());
        }
        else{
            printf("%c",(*argslist)[i]->GET_CHAR()->GET());
        }
    }
    printf("%s", e1.EVALUATE(argslist)->GET_DOUBLE()->GET());
}

#endif
