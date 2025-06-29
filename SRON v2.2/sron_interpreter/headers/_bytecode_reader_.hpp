#ifndef _BYTECODE_FILE_MNG_H_
#define _BYTECODE_FILE_MNG_H_

#include "_input_.hpp"

inline SronBytecodeReader::SronBytecodeReader ( const char* __start , const char* __end )
{
    this->_bytecode = this->_start = __start;
    
    this->_end = __end;
}

inline SronBytecodeReader::SronBytecodeReader(const char *const __filename, unsigned short int __length_of_filename , const char*const __filename_exclude_dir_path)
{

    auto file = BytecodeManager::getBytecode( std::string_view(__filename , __length_of_filename - 1) , __filename_exclude_dir_path  );

    this->_bytecode = this->_start = file._content;
    
    this->_end = file._end;
}

inline void SronBytecodeReader::incrementSeek( BytecodePos_t __jump ) noexcept 
{
    this->_bytecode += __jump;
}

inline void SronBytecodeReader::decrementSeek(BytecodePos_t __jump) noexcept
{
    this->_bytecode -= __jump;
}


inline const char* SronBytecodeReader::getCurrentPos() const noexcept
{
    return this->_bytecode;
}

inline void SronBytecodeReader::insertToBuffer( SronOBuffer& __buffer , BytecodeCount_t __count )
{
    const auto jump_to = this->_bytecode + __count ;

    if ( this->_bytecode < this->_start || jump_to > this->_end) [[unlikely]]
    {
        throw ThrowException("preparing to print the values. The seek of bytecode got out of bound", SronException::InvalidByteCodeException);
    }

    __buffer.append( this->_bytecode , __count - 1 ); // -1 for excluding the last'\0'

    this->_bytecode = jump_to;
}

inline void SronBytecodeReader::print( BytecodeCount_t __count)
{
    const auto jump_to = this->_bytecode + __count ;

    if ( this->_bytecode < this->_start || jump_to > this->_end) [[unlikely]]
    {
        throw ThrowException("preparing to print the values. The seek of bytecode got out of bound", SronException::InvalidByteCodeException);
    }
 
    printf_s("%s", this->_bytecode);

    this->_bytecode = jump_to;
}

template <typename Tp> inline Tp SronBytecodeReader::read()
{
    const auto jump_to = this->_bytecode + sizeof(Tp);

    if ( this->_bytecode < this->_start || jump_to > this->_end ) [[unlikely]]
    {
        throw ThrowException("preparing to print the values. The seek of bytecode got out of bound", SronException::InvalidByteCodeException);
    }

    Tp value;

    std::memcpy(&value , this->_bytecode , sizeof(Tp));

    this->_bytecode = jump_to;

    return value;
}

template <typename Tp> inline void SronBytecodeReader::readArray ( Tp* __array , const BytecodeCount_t __len )
{
    const auto count = __len * sizeof(Tp);

    const auto jump_to = this->_bytecode + count;
    
    if ( this->_bytecode < this->_start || jump_to > this->_end ) [[unlikely]]
    {
        throw ThrowException("preparing to print the values. The seek of bytecode got out of bound", SronException::InvalidByteCodeException);
    }

    std::memcpy(__array, this->_bytecode, count);

    this->_bytecode = jump_to;
}


inline SronInt_t SronBytecodeReader::readInt ( )
{
    return this->read<SronInt_t> ( );
}
inline SronChar_t SronBytecodeReader::readChar()
{
    return this->read<SronChar_t> ( );
}

inline SronDouble_t SronBytecodeReader::readDouble()
{
    return this->read<SronDouble_t> ( );
}

inline BytecodeCount_t SronBytecodeReader::readCount ( )
{
     return this->read <BytecodeCount_t> ( );
}

inline Flag_t SronBytecodeReader::readFlag()
{
    return this->read<Flag_t> ( );
}

inline BytecodeVariable_t SronBytecodeReader::readVariable()
{
    return this->read<BytecodeVariable_t> ( );
}


inline BytecodePos_t SronBytecodeReader::readPosition ()
{
    return this->read<BytecodePos_t> ( );
}


inline Hash_t SronBytecodeReader::readHash()
{
    return this->read<Hash_t> ( );
}

inline void SronBytecodeReader::setSeekToEnd() noexcept
{
    this->executing__ = false;
}

inline void SronBytecodeReader::setSeekAt (const char* __position) noexcept
{
    this->_bytecode = __position;
}

#endif