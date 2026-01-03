

#pragma once

#ifndef VariableManager_H
#define VariableManager_H

#include "base-component/_sron_obuffer_.hpp"

class VariableManager
{

private:
    AnyBindPtr *_vmap;
    BytecodeVariable_t _len;

    inline void INSERT_WITH_STRICT_TYPE_CHECK(const SronTypeNum __expected_type, BytecodeVariable_t __variable_id, AnyBind& __value){

        if(__value.type() == __expected_type) this->put( &__value , __variable_id);      
        
        else throw ThrowException("receving arguments value. Expected a argument of type '"+std::string(SronExtra::typenumToString(__expected_type)) +"' but found type '"+__value.typeStr()+"'", SronException::ArgumentException);
    }

    inline void INSERT_WITH_CONVERTIBLE(const SronTypeNum __expected_type , BytecodeVariable_t __variable_id , AnyBind& __value){

        // if the value is of type same as the expected_type then directly storing the value to the vmap
        if(__value.type() == __expected_type) this->put( &__value , __variable_id);
        
        else if( __expected_type == SronTypeNum::TYPE_INT && __value.canBeInt()) this->put(GarbageCollector::registerInt(__value.getConvertedInt()), __variable_id);

        else if( __expected_type == SronTypeNum::TYPE_DOUBLE && __value.canBeDouble()) this->put(GarbageCollector::registerDouble(__value.getConvertedDouble()), __variable_id);

        else if( __expected_type == SronTypeNum::TYPE_CHAR &&__value.canBeChar()) this->put(GarbageCollector::registerChar(__value.getConvertedChar()), __variable_id);

        else if( __expected_type == SronTypeNum::TYPE_BOOL &&__value.canBeBool()) this->put(__value.getConvertedBool() ? Bool::__SronTrue : Bool::__SronFalse, __variable_id);

        else if( __expected_type == SronTypeNum::TYPE_STRING && __value.type() == SronTypeNum::TYPE_LITERAL_STR)
        {
            auto l_str = lstrCast(__value.ptr())->getBaseLstr();

            this->put(GarbageCollector::registerMemory(new String(l_str.data(), l_str.length()) ,SronTypeNum::TYPE_STRING), __variable_id);
        }
        
        else throw ThrowException("assigning arguments to the function. Expected argument of type '"+std::string(SronExtra::typenumToString(__expected_type))+"' but found value of type '"+ __value.typeStr() +"'", SronException::ArgumentException);
    }

public:

    inline VariableManager() : _vmap(nullptr) , _len(0) { }

    inline VariableManager( VariableManager&& __other ) : _vmap( __other._vmap ) , _len( __other._len )
    {
        __other._vmap = nullptr;
        __other._len = 0;
    }

    inline void allocate( BytecodeVariable_t __total_variables )
    {
        this->_vmap = new AnyBindPtr[__total_variables];

        this->_len = __total_variables;
    }

    [[gnu::always_inline]] [[gnu::hot]] [[gnu::leaf]] inline AnyBindPtr put( AnyBindPtr __value, const BytecodeVariable_t __index )
    {
        if ( __index >= this->_len ) [[unlikely]] throw ThrowException("saving new variables. [Compiler/Interpreter-Issue] Cannot put value at 0x00000000+"+ std::to_string( __index ), SronException::InvalidByteCodeException);
        
        return (this->_vmap[ __index ] = __value);
    }

    inline void unsafePut( AnyBindPtr __value, const BytecodeVariable_t __index ) noexcept
    {
        this->_vmap[ __index] = __value;
    }

    [[gnu::always_inline]] [[gnu::hot]] [[gnu::leaf]] inline AnyBindPtr get( const BytecodeVariable_t __index )
    {
        if ( __index >= this->_len ) [[unlikely]] throw ThrowException("getting a variable. Cannot get value from 0x00000000+"+ std::to_string( __index ) , SronException::InvalidByteCodeException);
        
        auto value = this->_vmap[__index];

        if ( value ) return value;

        throw SronException::NullPointerException();
    }

    inline AnyBindPtr unsafeGet(const BytecodeVariable_t __index ) const noexcept
    {
        return (this->_vmap[ __index ]);
    }

    /* 
     * Called when variables are declared but not assigned
        Int a
        Double b
        Char c,
        FileReader d
        ... and so on
    */
    inline void insert(const BytecodeFlags __type, const BytecodeVariable_t __variable_index )
    {
        AnyPtr value = nullptr;

        SronTypeNum type_of_variable = SronTypeNum::TYPE_VOID;

        switch (__type)
        {
            case BytecodeFlags::Flag_Any     : this->put( Void::void_object , __variable_index); return;

            case BytecodeFlags::Flag_Int     : value = new Int(); type_of_variable = SronTypeNum::TYPE_INT; break;

            case BytecodeFlags::Flag_Double  : value = new Double(); type_of_variable = SronTypeNum::TYPE_DOUBLE; break;

            case BytecodeFlags::Flag_Char    : value = new Char(); type_of_variable = SronTypeNum::TYPE_CHAR; break;

            case BytecodeFlags::Flag_Bool    : value = new Bool(); type_of_variable = SronTypeNum::TYPE_BOOL; break;

            case BytecodeFlags::Flag_String  : value = new String(); type_of_variable = SronTypeNum::TYPE_STRING; break;

            case BytecodeFlags::Flag_List   : value = new List(); type_of_variable = SronTypeNum::TYPE_LIST; break;

            case BytecodeFlags::Flag_FileReader : value = new FileReader(); type_of_variable = SronTypeNum::TYPE_FILE_READER; break;

            case BytecodeFlags::Flag_FileWriter : value = new FileWriter(); type_of_variable = SronTypeNum::TYPE_FILE_WRITER; break;

            case BytecodeFlags::Flag_Lstr : this->put(LiteralString::__EmptyStr, __variable_index); return;

            default : throw ThrowException("declaring and allocating memory space for variables. Found invalid type '" + std::string( SronSupport::flagToString(__type) ) + "'" , SronException::InvalidTypeException);
        }

        this->put( GarbageCollector::registerMemory( value , type_of_variable ), __variable_index );
    }

    [[gnu::hot]] inline void insert(const BytecodeFlags __flag, const BytecodeVariable_t __variable_id, AnyBindPtr __value)
    {
        switch (__flag)
        {
            case BytecodeFlags::Flag_Any           : this->put( __value , __variable_id ) ; break;

            case BytecodeFlags::Flag_Int           : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_INT    , __variable_id, *__value); break;

            case BytecodeFlags::Flag_Double        : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_DOUBLE , __variable_id, *__value); break;

            case BytecodeFlags::Flag_Char          : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_CHAR   , __variable_id, *__value); break;

            case BytecodeFlags::Flag_Bool          : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_BOOL   , __variable_id, *__value); break;

            case BytecodeFlags::Flag_String        : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_STRING , __variable_id, *__value); break;

            case BytecodeFlags::Flag_List          : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_LIST   , __variable_id, *__value); break;

            case BytecodeFlags::Flag_FileReader    : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_FILE_READER, __variable_id, *__value); break;
            
            case BytecodeFlags::Flag_FileWriter    : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_FILE_WRITER, __variable_id, *__value); break;

            case BytecodeFlags::Flag_Lstr          : INSERT_WITH_CONVERTIBLE( SronTypeNum::TYPE_LITERAL_STR, __variable_id, *__value); break;

            case BytecodeFlags::Flag_StrictInt     : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_INT     ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictDouble  : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_DOUBLE  ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictChar    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_CHAR    ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictBool    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_BOOL    ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictString  : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_STRING  ,  __variable_id , *__value ); break;
            
            case BytecodeFlags::Flag_StrictList    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_LIST    ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictFreader : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_FILE_READER, __variable_id, *__value); break;

            case BytecodeFlags::Flag_StrictFwriter : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_FILE_WRITER, __variable_id, *__value); break;

            case BytecodeFlags::Flag_StrictLstr    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_LITERAL_STR, __variable_id, *__value); break;

            default : throw ThrowException("assigning arguments to the function. Found flag '"+std::string(SronSupport::flagToString(__flag)) +"'", SronException::InvalidFlagException);
        
        }
    }

    inline AnyBindPtr* getDirectRef(const BytecodeVariable_t __variable_id)
    {
        if ( __variable_id >= this->_len ) [[unlikely]] throw ThrowException("getting the reference variable but it is referencing either NULL or beyond bounds '" + std::to_string( __variable_id ) + "' [Compiler/Interpreter-Issue]", SronException::InvalidByteCodeException);

        return this->_vmap + __variable_id;
    }

    [[gnu::hot]] inline ~VariableManager() noexcept  
    {
        delete[] this->_vmap;

        this->_vmap = nullptr;

        this->_len = 0;
    }
};

#endif