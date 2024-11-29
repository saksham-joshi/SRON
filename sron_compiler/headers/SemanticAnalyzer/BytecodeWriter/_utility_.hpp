
#include "_base_writer_.hpp"

/*
 * Saves the current file position and then move the file seek to the position specified in seek_tracker's last element.
 * Writes the file position which was saved before and then moves the file seek to the same position.
*/
inline static void ByteCodeWriter::WRITE_CLOSING_INDEX()
{

    auto cur_position = std::ftell(ByteCodeWriter::__ByteCodeFile__);

    auto& getBackPos = ByteCodeWriter::seek_tracker.back();

    std::fseek(ByteCodeWriter::__ByteCodeFile__, getBackPos._position, SEEK_SET);

    ByteCodeWriter::SAVE_LONG_TO_FILE(cur_position);

    std::fseek(ByteCodeWriter::__ByteCodeFile__ , cur_position , SEEK_SET);

    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Closing index At : " << getBackPos._position << "     ----> Flag : "<< Support::FLAG_TO_STRING(getBackPos._flag) ;
    #endif

    ByteCodeWriter::seek_tracker.pop_back();

}