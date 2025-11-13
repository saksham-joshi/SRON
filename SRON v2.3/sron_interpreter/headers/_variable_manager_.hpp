

#pragma once

#ifndef VariableManager_H
#define VariableManager_H

#include "base-component/_String_.hpp"

class VariableManager
{

private:
    AnyBindPtr *_vmap;
    BytecodeVariable_t _len;

    inline void INSERT_WITH_STRICT_TYPE_CHECK(const SronTypeNum __expected_type, BytecodeVariable_t __variable_id, AnyBind& __value){

            if(__value.type() == __expected_type)
            {
                this->put( &__value , __variable_id);
                return;
            }
            throw ThrowException("receving arguments value. Expected a argument of type '"+std::string() +"' but found type '"+std::string(__value->type())+"'");
    }

    inline void INSERT_WITH_CONVERTIBLE(const SronTypeNum __expected_type , BytecodeVariable_t __variable_id , AnyBind& __value){

        // if the value is of type same as the expected_type then directly storing the value to the vmap
        if(__value.type() == __expected_type){
            
            this->put( &__value , __variable_id);

            return;
        }

        // program flow will come here when there the expected_type and the value is 
        // not same, then we will try converting the value to as per the expected_type

        switch(__expected_type){

            case SronTypeNum::TYPE_INT : __value->getInt(); break;

            case SronTypeNum::TYPE_DOUBLE : __value->getDouble(); break;

            case SronTypeNum::TYPE_CHAR : __value->getChar(); break;

            case SronTypeNum::TYPE_BOOL : this->put( __value->getBaseBool() ? Bool::__SronTrue : Bool::__SronFalse , __variable_id ); return;

            case SronTypeNum::TYPE_STRING : __value->getString(); break;

            case SronTypeNum::TYPE_LIST : __value->getList(); break;

            default : throw ThrowException("assigning arguments to the function. Found invalid type '"+ std::string ( SronExtra::typenumToString(__expected_type) ) +"'");
        }

        this->put( GarbageCollector::__top->back() , __variable_id);
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
        this->_vmap =  static_cast<AnyBindPtr*>( std::calloc( __total_variables , sizeof( AnyBindPtr ) ) );
        
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

            case BytecodeFlags::Flag_StrictInt     : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_INT     ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictDouble  : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_DOUBLE  ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictChar    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_CHAR    ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictBool    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_BOOL    ,  __variable_id , *__value ); break;

            case BytecodeFlags::Flag_StrictString  : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_STRING  ,  __variable_id , *__value ); break;
            
            case BytecodeFlags::Flag_StrictList    : INSERT_WITH_STRICT_TYPE_CHECK( SronTypeNum::TYPE_LIST    ,  __variable_id , *__value ); break;

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
        std::free(this->_vmap);

        this->_vmap = nullptr;

        this->_len = 0;
    }
};

#endif