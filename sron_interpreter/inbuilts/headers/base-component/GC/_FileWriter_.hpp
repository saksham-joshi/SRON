#ifndef _SRON_FILE_WRITER_H
#define _SRON_FILE_WRITER_H

#include "_FileReader_.hpp"


inline FileWriter::FileWriter(const std::string_view& __filename, SronBool_t __append_mode)
{
    this->open(__filename, __append_mode);
}

inline AnyPtr FileWriter::copy() const
{
    if( this->_opened) return new FileWriter(this->_filename, true);
    
    throw ThrowException("generating copy of a 'FileWriter'. The file which you are trying to copy doesn't have any file content itself", SronException::FileWriterException);
}

inline void FileWriter::print() const
{
    throw ThrowException("trying to print a value of type 'FileWriter'. If you want to print it's content, then you need to read the file using 'FileReader' and use 'freadFull()' which will give you a value of type 'String' which can be printed further", SronException::FileWriterException);
}

inline void FileWriter::formatPrint() const 
{
    this->print();
}

inline void FileWriter::preMove() { }

inline void FileWriter::fillObuffer(SronOBuffer&) const
{
    printf(WARNING_MESSAGE_ON_OBUFFER_FILE);
}

inline SronTypeNum FileWriter::typeNum() const
{
    return SronTypeNum::TYPE_FILE_WRITER;
}

inline long long int FileWriter::sizeOf() const
{
    return sizeof(class FileWriter);
}

inline bool FileWriter::isCollective() const
{
    return false;
}

inline const char* FileWriter::type() const
{
    return "FileWriter";
}

inline void FileWriter::type(std::string &__str) const
{
    __str.append(this->type());
}

inline SronBool_t FileWriter::__isEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileWriter::__notEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileWriter::__lessThan__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileWriter::__moreThan__(Any &, SronTypeNum) const
{
    return false;
}

inline SronBool_t FileWriter::__lessEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileWriter::__moreEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline void FileWriter::writeChar(SronChar_t __ch)
{
    if ( this->_opened)
    {
        fputc(__ch, this->_file);
    }
}

inline void FileWriter::writeString(const SronLstr_t& __str)
{
    if(this->_opened)
    {
        fwrite(__str.data(), sizeof(SronChar_t), __str.length(), this->_file);
    }
}

inline void FileWriter::writeString(const SronString_t& __str)
{
    if(this->_opened)
    {
        fwrite(__str.c_str(), sizeof(SronChar_t), __str.length(), this->_file);
    }
}

inline SronInt_t FileWriter::tell() const
{
    if( this->_opened) return std::ftell(this->_file);
    
    return -1;
}

inline void FileWriter::setSeek(SronInt_t __pos)
{
    if( this->_opened) std::fseek(this->_file, __pos, SEEK_SET);
}

inline void FileWriter::close()
{
    if(this->_opened)
    {
        std::fclose(this->_file);

        this->_file = nullptr;

        delete[] this->_filename.data();

        this->_filename = std::string_view("", 0);

        this->_opened = false;
    }
}

inline SronBool_t FileWriter::isOpen() const
{
    return this->_opened;
}

inline SronBool_t FileWriter::open(const std::string_view& __filename, SronBool_t __append_mode)
{
    if(this->_opened)
    {
        throw ThrowException("opening a file. You already opened this file before. Use 'fclose()' and then again open this file", SronException::FileWriterException);
    }

    #ifdef _WIN64
        fopen_s(&_file, __filename.data(), __append_mode ? "a" : "w");
    #else
        this->_file = std::fopen(__filename.data(), __append_mode ? "a" : "w");
    #endif

    if(this->_file)
    {
        this->_filename = SronExtra::duplicateString(__filename);

        std::fseek(this->_file, 0, SEEK_END);

        // file load success
        this->_opened = true;
    }
    else
    {
        // file cannot be loaded
        this->_opened = false;
    }

    return this->_opened;
}

inline SronInt_t FileWriter::len() const
{
    if (this->_opened) return std::ftell(this->_file);

    return -1;
}

inline std::string FileWriter::getFileName() const
{
    if(this->_opened) return std::string(this->_filename.data(), this->_filename.length());

    return "";
}

inline FileWriter::~FileWriter() noexcept
{
    this->close();
}

inline FileWriter::Fwriter_t FileWriter::getBaseFwriter()
{
    return this->_file;
}

#endif 