
#include "_specific_writers_.hpp"


// starts generating the bytecode .............!!
inline static void ByteCodeWriter::GENERATE(TokenVector &__tokenVector)
{
    using ByteCodeWriter::iterator;

    using ByteCodeWriter::tokenVectorEnd;

    using ByteCodeWriter::__ByteCodeFile__;

    try
    {
        // initializing the file....
        fopen_s(&ByteCodeWriter::__ByteCodeFile__, ((Logs::directory_path + (ByteCodeWriter::fnc_name->GET())) + ".srb").c_str(), "wb");

        if (!__ByteCodeFile__)
        {
            throw ThrowException("generating the bytecode. Cannot generate bytecode file '" + (Logs::directory_path + fnc_name->GET()) + "'");
        }


        // the first and last values are '{' and  '}' respectively
        // which is not required to in bytecode generation.
        iterator = __tokenVector.begin() + 1;
        tokenVectorEnd = __tokenVector.end() - 1;

        for (; iterator < tokenVectorEnd; ++iterator)
        {

            ByteCodeWriter::TYPE_MAPPER();
        }

        ByteCodeWriter::SAVE_FLAG_TO_FILE(Flag_CodeCompleted);

        std::cout << "\n =| Successfully saved bytecode in '" << Logs::directory_path << *ByteCodeWriter::fnc_name << ".srb'.";

        ByteCodeWriter::RESET();
    }
    catch (const ThrowException &__excep)
    {
        ByteCodeWriter::RESET();

        throw __excep;
    }
    catch (const std::exception &__excep)
    {
        ByteCodeWriter::RESET();

        throw __excep;
    }
}



inline static void ByteCodeWriter::RESET() noexcept
{
    std::fclose(ByteCodeWriter::__ByteCodeFile__);

    ByteCodeWriter::__ByteCodeFile__ = nullptr;

    ByteCodeWriter::fnc_name = nullptr;

    ByteCodeWriter::__returnTypeFlag__ = Flag_Any;
}

// this function is called when Flag_FunctionScopeEnd found ...
inline static void ByteCodeWriter::HANDLE_SCOPES()
{ 
    using ByteCodeWriter::iterator;
    using ByteCodeWriter::seek_tracker;

    if(seek_tracker.empty())
    {
        throw ThrowException("generating the bytecode. Something goes wrong with the scope handling in source code");
    }

    ByteCodeWriter::SAVE_FLAG_TO_FILE(seek_tracker.back()._flag);
    
    ByteCodeWriter::WRITE_CLOSING_INDEX();
}



inline static void ByteCodeWriter::TYPE_MAPPER()
{

    using ByteCodeWriter::iterator;

    using ByteCodeWriter::tokenVectorEnd;

    switch (iterator->_type)
    {
        case TYPE_MATH_BLOCK:
            ByteCodeWriter::MATH_BLOCK_WRITER();
            break;

        case TYPE_INT:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(Flag_Int_Value);
            ByteCodeWriter::SAVE_INT64_TO_FILE(Converter::TO_INT(iterator->_token.GET()));
            break;

        case TYPE_DOUBLE:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(Flag_Double_Value);
            ByteCodeWriter::SAVE_DOUBLE_TO_FILE(Converter::TO_DOUBLE(iterator->_token.GET()));
            break;

        case TYPE_CHAR:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(Flag_Char_Value);
            ByteCodeWriter::SAVE_CHAR_TO_FILE(iterator->_token.GET()[1]);
            break;

        case TYPE_BOOL:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(iterator->_flag);
            break;

        case TYPE_STRING:
            ByteCodeWriter::SAVE_STRING_TO_FILE(iterator->_token);
            break;

        case TYPE_VOID:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(iterator->_flag);
            break;

        case TYPE_LIST_OPEN: 
            ByteCodeWriter::LIST_WRITER();
            break;

        case TYPE_DATATYPE:
        case TYPE_STRICT_TYPE :
            ByteCodeWriter::DATATYPE_WRITER();
            break;

        case TYPE_IDENTIFIER:
            ByteCodeWriter::IDENTIFIER_WRITER();
            break;

        case TYPE_ATTRIBUTE:
            ByteCodeWriter::ATTRIBUTE_MAPPER();
            break;

        case TYPE_FUNCTION_CALL:
            ByteCodeWriter::FUNCTION_CALL_WRITER();
            break;

        case TYPE_KEYWORD:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(iterator->_flag);
            break;

        case TYPE_OPERATOR:
            ByteCodeWriter::SAVE_FLAG_TO_FILE((Support::IS_UNARY_OPERATOR(iterator->_flag)) ? Flag_UnaryOperator : Flag_Operator);
            ByteCodeWriter::SAVE_FLAG_TO_FILE(iterator->_flag);
            break;

        case TYPE_FUNCTION_SCOPE_CLOSE: 
            ByteCodeWriter::HANDLE_SCOPES();
            break;

        case TYPE_CLOSING_BRACKETS:
            ByteCodeWriter::SAVE_FLAG_TO_FILE(seek_tracker.back()._flag);
            ByteCodeWriter::seek_tracker.pop_back();
            break;

        case TYPE_NEWLINE:
        case TYPE_COLON:
        case TYPE_COMMA:
            break;
        default: throw ThrowException("generating the bytecode. Cannot map type '" + std::string(Support::TYPE_TO_STRING(iterator->_type)) + "' to bytecode method", iterator->_file_index);
        
    }
}
