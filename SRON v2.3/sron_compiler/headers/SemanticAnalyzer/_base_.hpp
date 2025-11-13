
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
  inline static void THROW_ERROR_IF_INSIDE_MATH_BLOCK( const SronTokenType ,bool);
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
}

#endif