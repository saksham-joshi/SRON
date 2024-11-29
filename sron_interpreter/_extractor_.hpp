#include "_base_engine_.hpp"

inline static AnyBindPtr ExecutionEngine::EXTRACT_INT(SronFncPtr __top)
{
    return GarbageCollector::REGISTER_MEMORY(new Int(__top->_codefile.READ_INT64()));
}

inline static AnyBindPtr ExecutionEngine::EXTRACT_DOUBLE(SronFncPtr __top)
{

    return GarbageCollector::REGISTER_MEMORY(new Double(__top->_codefile.READ_DOUBLE()));
}

inline static AnyBindPtr ExecutionEngine::EXTRACT_CHAR(SronFncPtr __top)
{
    return GarbageCollector::REGISTER_MEMORY(new Char(__top->_codefile.READ_CHAR()));
}

inline static AnyBindPtr ExecutionEngine::EXTRACT_STRING(SronFncPtr __top)
{
    String *str = new String();

    __top->_codefile.READ_STRING(**str);

    return GarbageCollector::REGISTER_MEMORY(str);
}

inline static AnyBindPtr ExecutionEngine::EXTRACT_LIST(SronFncPtr __top)
{
    List *lst = new List();

    flag_t flag = __top->_codefile.READ_FLAG();

    // Some part of this function is not open sourced for security reasons

    return GarbageCollector::REGISTER_MEMORY(lst);
}

inline static AnyBindPtr ExecutionEngine::EXTRACT_IDENTIFIER(SronFncPtr __top)
{
    // This code is not open sourced for security reasons
}

inline static void ExecutionEngine::EXTRACT_ARGUMENTS(SronFncPtr __top, ArgListPtr __args)
{

    // This code is not open sourced for security reasons
}

inline static AnyBindPtr ExecutionEngine::REFINE_TO_INT(SronFncPtr __top)
{

    // This code is not open sourced for security reasons
}
inline static AnyBindPtr  ExecutionEngine::REFINE_TO_DOUBLE(SronFncPtr __top)
{
    // This code is not open sourced for security reasons
}
inline static AnyBindPtr  ExecutionEngine::REFINE_TO_CHAR(SronFncPtr __top)
{
    // This code is not open sourced for security reasons
}
inline static AnyBindPtr  ExecutionEngine::REFINE_TO_BOOL(SronFncPtr __top)
{
    // if you try to call Any::GET_BOOL(), it will either return
    // Bool::__SronTrue or Bool::__SronFalse 's const casted objects
    // so there is no need to register the memory to register on
    // Garbage Collector, if it cannot be parsed to Bool type value, 
    // then exception will be thrown by GET_BOOL() method, so no loophole

    return ((ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top)->ptr_->GET_BOOL_ABS())? Bool::__SronTrue : Bool::__SronFalse);
}
inline static AnyBindPtr  ExecutionEngine::REFINE_TO_STRING(SronFncPtr __top)
{
    // This code is not open sourced for security reasons
}
inline static AnyBindPtr  ExecutionEngine::REFINE_TO_LIST(SronFncPtr __top)
{
    // This code is not open sourced for security reasons
}