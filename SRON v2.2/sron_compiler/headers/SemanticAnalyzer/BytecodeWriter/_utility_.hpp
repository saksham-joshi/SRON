
#include "_base_writer_.hpp"

/*
 * Saves the current file position and then move the file seek to the position specified in seek_tracker's last element.
 * Writes the file position which was saved before and then moves the file seek to the same position.
*/
inline static void ByteCodeWriter::WRITE_CLOSING_INDEX()
{

    auto cur_position = std::ftell(ByteCodeWriter::__ByteCodeFile__);

    ByteCodeWriter::THROW_ERROR_IF_SEEK_TRACKER_IS_EMPTY();

    auto& getBackPos = ByteCodeWriter::seek_tracker.back();

    std::fseek(ByteCodeWriter::__ByteCodeFile__, getBackPos._position, SEEK_SET);

    ByteCodeWriter::SAVE_DATA<BytecodePos_t>(cur_position - getBackPos._position);

    std::fseek(ByteCodeWriter::__ByteCodeFile__ , cur_position , SEEK_SET);

    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>> Closing index At : %ld \t ----> Flag : %s", getBackPos._position , Support::FLAG_TO_STRING(getBackPos._flag));
    #endif

    ByteCodeWriter::seek_tracker.pop_back();

}

inline static void ByteCodeWriter::REMOVE_DEAD_CODE()
{
    using ByteCodeWriter::iterator;

    int open_curly_brace_count = 1;

    for(; iterator < ByteCodeWriter::tokenVectorEnd; ++iterator){

        open_curly_brace_count += (iterator->_type == TYPE_FUNCTION_SCOPE_START ? 1 : 0);

        open_curly_brace_count -= (iterator->_type == TYPE_FUNCTION_SCOPE_CLOSE ? 1 : 0);

        if(open_curly_brace_count <= 0 && (iterator->_type == TYPE_FUNCTION_SCOPE_CLOSE)){
            break;
        }
    }

    if(iterator < ByteCodeWriter::tokenVectorEnd) ByteCodeWriter::HANDLE_SCOPES();

    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s ("\n Deadcode removed! Moved iterator:");
        if(iterator < ByteCodeWriter::tokenVectorEnd){
            printf_s(" '%s' ", iterator->_token.c_str());
        }
        else{
            printf_s("End of the function");
        }
    #endif
}

inline static void ByteCodeWriter::THROW_ERROR_IF_SEEK_TRACKER_IS_EMPTY()
{
    if ( ByteCodeWriter::seek_tracker.empty() ) throw ThrowException("generating the bytecode. Something goes wrong while handling scopes [Compiler-Issue]", SronError::ScopeBasedError);
}