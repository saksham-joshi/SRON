#include "_general_.hpp"

inline static AnyBindPtr ExecutionEngine::EVALUATE(SronFncPtr __top)
{

    constexpr static auto match_operator = [](std::vector<AnyBindPtr> *__stk, Any &__val1, Any &__val2, flag_t __flag)
    {
        
    };

    flag_t flag__ = __top->_codefile.READ_FLAG();

    while (flag__ != Flag_EvalEnd)
    {

        if (flag__ == Flag_Operator)
        {
            AnyBindPtr val2 = stk__.back();

            stk__.pop_back();

            AnyBindPtr val1 = stk__.back();

            stk__.pop_back();

            auto operator_flag = __top->_codefile.READ_FLAG();

            match_operator(&stk__, **val1, **val2, operator_flag);
        }
        else if (flag__ == Flag_UnaryOperator)
        {
            Any &val = **stk__.back();
            stk__.pop_back();

            // Some part of this scope is not open sourced for security reasons...
        }
        else
        {
            stk__.push_back(ExecutionEngine::FLAG_TO_FUNCTION_MAP(flag__, __top));
        }

        flag__ = __top->_codefile.READ_FLAG();
        
    }

    AnyBindPtr res = stk__.back();
    
    stk__.pop_back();

    return res;
}

inline static AnyBindPtr ExecutionEngine::ADD_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__ADD_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}
inline static AnyBindPtr ExecutionEngine::MIN_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__MIN_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}
inline static AnyBindPtr ExecutionEngine::MULT_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__MULT_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}
inline static AnyBindPtr ExecutionEngine::DIV_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__DIV_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}
inline static AnyBindPtr ExecutionEngine::MOD_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__MOD_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}
inline static AnyBindPtr ExecutionEngine::POW_AND_ASSIGN(SronFncPtr __top)
{
    auto it = __top->_Vmanager.GET_ITERATOR(__top->_codefile.READ_UNSIGNED_INT64());

    it->second->ptr_->__POW_AND_ASSIGN__(**ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top));

    return it->second;
}