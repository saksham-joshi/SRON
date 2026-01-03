
#pragma once

#ifndef _SEMNTC_ANLZR_H
#define _SEMNTC_ANLZR_H

#include "BytecodeWriter/_bytecode_writer_.hpp"

namespace SemanticAnalyzer
{

  // this variable will tell what values will be returned from the function
  // it will be used to check if the 'type' attribute is used more than once
  // or the returned values are same as the mentioned type
  BytecodeFlags fncReturnType = BytecodeFlags::Flag_bydefault;

  // used by some methods of Semantic Analyzer to set expected type values that can never met true...
  constexpr const SronTokenType SRON_NO_TYPE = SronTokenType::NO_TYPE;

  // used to keep track of scopes for handling break and continue keyword analysis...
  constexpr const char SRON_LOOP        = 'L';
  constexpr const char SRON_IF          = 'I';
  constexpr const char SRON_FNC_SCOPE   = '{';
  constexpr const char SRON_OS_SCOPE    = 'O';

  // stores the names of variable defined in a function
  VariableIndexer variableSet;

  // stores the names of in built functions ....
  std::set<IndexAndHash> inbuiltFncSet;

  // stores the user defined function of the current file loaded...
  std::set<SronHasher> userDefinedFncSet;

  TokenVector::const_iterator tokenVectorBegin;
  TokenVector::iterator iterator;
  TokenVector::const_iterator tokenVectorEnd;

  // used to keep track of scopes...
  std::stack<char> scope_stack;

  unsigned short int __loop_count = 0;

  /*
    Found functions which are called when a particular type is found.
  */
  inline static void FOUND_TYPE_INT();
  inline static void FOUND_TYPE_DOUBLE();
  inline static void FOUND_TYPE_ATTRIBUTE();
  inline static void FOUND_TYPE_ASSIGN();
  inline static void FOUND_TYPE_IDENTIFIER();
  inline static void FOUND_TYPE_DATATYPE();
  inline static void FOUND_TYPE_FUNCTION_CALL();
  inline static void FOUND_TYPE_KEYWORD();
  inline static void FOUND_TYPE_MATH_BLOCK();
  inline static void FOUND_TYPE_LIST_OPEN();

  // Analyzer functions for specific attributes...
  inline static void FOUND_ARGS_ATTRIBUTE();
  inline static void FOUND_MAIN_ARGS_ATTRIBUTE();
  inline static void FOUND_NAME_ATTRIBUTE();
  inline static void FOUND_ROTATE_ATTRIBUTE();
  inline static void FOUND_CONDITION_ATTRIBUTE();
  inline static void FOUND_RANGE_ATTRIBUTE();
  inline static void FOUND_CONSOLE_ATTRIBUTE();
  inline static void FOUND_RETURN_ATTRIBUTE();
  inline static void FOUND_LOOP_ATTRIBUTE();
  inline static void FOUND_IF_ELIF_ELSE_ATTRIBUTE();
  inline static void FOUND_ATTRIBUTE_TYPE();
  inline static void FOUND_FOREACH_ON_ATTRIBUTE();
  inline static void FOUND_OS_ATTRIBUTE();

  /*
   * Function which just check a particular condition and return true or false...
   */
  inline static bool CHECK_IF_IN_BUILT_FUNCTION_EXISTS(const SronToken::TokenElement_t &) noexcept;
  inline static bool CHECK_IF_USER_DEFINED_FUNCTION_EXISTS(const SronToken::TokenElement_t &) noexcept;
  inline static bool IS_A_DECLARED_VARIABLE(const std::string &) noexcept;

  /*
   * Functions which throw exception on some conditions!!
   */
  inline static void THROW_ERROR_IF_IN_BUILT_FUNCTION_EXISTS(SronToken &);
  inline static void THROW_ERROR_IF_USER_DEFINED_FUNCTION_NOT_EXISTS(SronToken::TokenElement_t&);
  inline static void THROW_ERROR_IF_INVALID_VARIABLE_NAME(bool, const std::string&);
  inline static void THROW_ERROR_IF_NOT_ATTRIBUTE(SronToken &);
  inline static void THROW_ERROR_IF_INSIDE_MATH_BLOCK( const SronTokenType ,short);
  inline static void THROW_ERROR_IF_NUMBER_OVERFLOWS(bool, std::string&);
  inline static void THROW_ERROR_IF_INT_OVERFLOW (std::string&);
  inline static void THROW_ERROR_IF_DOUBLE_OVERFLOW (std::string&);
  inline static void THROW_ERROR_IF_DIVISION_BY_ZERO_FOUND (std::string&, FilePos_t);
  inline static void THROW_ERROR_IF_ITERATOR_NOT_WITHIN_BOUND();
  inline static void THROW_ERROR_IF_VALID_BYTECODE_FILE_NOT_EXISTS(const char*);

  /*
   * Functions which display warnings only!
   */
  inline static size_t SHOW_WARNING_IF_VARIABLE_ALREADY_DECLARED(const char*);

  // Performs the analysis on the passed TokenVector, it calls the other methods of SemanticAnalyzer namespace to check for syntax errors
  inline static void ANALYZE(TokenVector &);

  // this function resets everything to default
  inline static void RESET() noexcept;

  // check if a value type is found...
  inline static void VALUE_TYPE_CHECK();

  inline static unsigned short int VERIFY_BYTECODE_FILE( const char* ) noexcept;

  class MathBlockAnalyzer
  {
    std::vector<BytecodeFlags> _mathStack;
    short _valueCount;

    inline void pushOperator();
    inline void popOperator();
    constexpr inline static unsigned short getPrecedence(const BytecodeFlags);

    public :

      inline MathBlockAnalyzer() : _valueCount(0) { }

      inline void startAnalysis();
  };


  namespace ImplicitConversion
  {
        /*

         type : Void

         return : Void
        */
        constexpr inline static bool VOID_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_Void );
        }

        /*

         type : Int

         return : Int/Double/true/false/Char
        */
        constexpr inline static bool INT_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_Int_Value || __value == BytecodeFlags::Flag_Double_Value || __value == BytecodeFlags::Flag_Char_Value || __value == BytecodeFlags::Flag_True || __value == BytecodeFlags::Flag_False );
        }
        
        /*

         type : Double

         return : Double/Int
        */
        constexpr inline static bool DOUBLE_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_Double_Value || __value == BytecodeFlags::Flag_Int_Value);
        }

        /*

         type : Char

         return : Char/Int
        */
        constexpr inline  static bool CHAR_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_Char_Value || __value == BytecodeFlags::Flag_Int_Value);
        }

        /*

         type : Bool

         return : Int/true/false
        */
        constexpr inline static bool BOOL_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_Int_Value || __value == BytecodeFlags::Flag_True || __value == BytecodeFlags::Flag_False);
        }

        /*

         type : String

         return : "String"
        */
        constexpr inline static bool STRING_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_String_Value );
        }

        /*

         type : List

         return : [List]
        */
        constexpr inline static bool LIST_WITH( BytecodeFlags __value )
        {
            return ( __value == BytecodeFlags::Flag_ListStart );
        }

        /*

         type : LiteralString

         return : "String"
        */
        constexpr inline static bool LITERAL_STR_WITH( BytecodeFlags __value)
        {
            return (__value == BytecodeFlags::Flag_String_Value );
        }

        constexpr inline static bool matchImplicitConversion ( BytecodeFlags __expected_return_type, BytecodeFlags __return_value )
        {
            switch ( __expected_return_type )
            {
                case BytecodeFlags::Flag_Void    :    return ImplicitConversion::VOID_WITH     ( __return_value );

                case BytecodeFlags::Flag_Int     :    return ImplicitConversion::INT_WITH      ( __return_value );

                case BytecodeFlags::Flag_Double  :    return ImplicitConversion::DOUBLE_WITH   ( __return_value );

                case BytecodeFlags::Flag_Char    :    return ImplicitConversion::CHAR_WITH     ( __return_value ); 

                case BytecodeFlags::Flag_Bool    :    return ImplicitConversion::BOOL_WITH     ( __return_value ); 

                case BytecodeFlags::Flag_String  :    return ImplicitConversion::STRING_WITH   ( __return_value ); 

                case BytecodeFlags::Flag_List    :    return ImplicitConversion::LIST_WITH     ( __return_value );

                case BytecodeFlags::Flag_Lstr :       return ImplicitConversion::LITERAL_STR_WITH(__return_value);

                case BytecodeFlags::Flag_FileReader:

                case BytecodeFlags::Flag_FileWriter:  return true;

                default : { }
            }

            throw ThrowException("analyzing the code. [Compiler-Issue] The 'SemanticAnalyzer::fncReturnType' has a invalid datatype flag '" + std::string( SronSupport::flagToString(__expected_return_type) ) + "'");
        }

        inline static void THROW_EXCEPTION_IF_RETURNED_VALUE_DOESNOT_MATCH_WITH_RETURN_TYPE ( )
        {
            using SemanticAnalyzer::iterator;
            /*
            Checking if the
             * Returned value is a type of value whose type cannot be find during compile time
             *
             * Return type is not set yet
             *
             * Return type is set as 'Any'
            */
            if(iterator->isIndefiniteValueType() || SemanticAnalyzer::fncReturnType == BytecodeFlags::Flag_bydefault || SemanticAnalyzer::fncReturnType == BytecodeFlags::Flag_Any) return;

            else if( !SemanticAnalyzer::ImplicitConversion::matchImplicitConversion(SemanticAnalyzer::fncReturnType, iterator->_flag) )
            {
                throw ThrowException( "analyzing the code. The returned value which is of type '" + std::string( SronSupport::flagToString( iterator->_flag ) ) +"' which doesn't matches with the return type '" + std::string( SronSupport::flagToString( SemanticAnalyzer::fncReturnType) ) +"' or cannot be implicitly converted" , iterator->_file_index );
            }
        }
    }
}

#endif