#ifndef _SRON_FILE_READER_H
#define _SRON_FILE_READER_H

#include "_String_.hpp"

inline FileReader::FileReader(const std::string_view& __str)
{
    this->open(__str);
}

inline AnyPtr FileReader::copy() const
{
    if( this->_opened) return new FileReader(this->_filename);
    
    throw ThrowException("generating copy of a 'FileReader'. The file which you are trying to copy doesn't have any file content itself");
}

inline void FileReader::print() const
{
    throw ThrowException("trying to print a value of type 'FileReader'. If you want to print it's content, then you need to read the file which will give you a value of type 'String' which can be printed further");
}

inline void FileReader::formatPrint() const 
{
    this->print();
}

inline void FileReader::preMove() { }

inline void FileReader::fillObuffer(SronOBuffer&) const
{
    printf(WARNING_MESSAGE_ON_OBUFFER_FILE);
}

inline SronTypeNum FileReader::typeNum() const
{
    return SronTypeNum::TYPE_FILE_READER;
}

inline long long int FileReader::sizeOf() const
{
    return sizeof(class FileReader);
}

inline bool FileReader::isCollective() const
{
    return false;
}

inline const char* FileReader::type() const
{
    return "FileReader";
}

inline void FileReader::type(std::string &__str) const
{
    __str.append(this->type());
}

inline SronBool_t FileReader::__isEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileReader::__notEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileReader::__lessThan__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileReader::__moreThan__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileReader::__lessEqual__(Any &, SronTypeNum) const 
{
    return false;
}

inline SronBool_t FileReader::__moreEqual__(Any &, SronTypeNum) const 
{
    return false;
}

[[using gnu: malloc, hot, returns_nonnull]] [[nodiscard]] inline StringPtr FileReader::readLine()
{
    if ( this->_opened)
    {
        StringPtr str = new String();

        while(!std::feof(this->_file))
        {
            char ch = fgetc(this->_file);

            if(ch == '\n') break;

            str->push(ch);
        }

        return str;
    }

    return new String();
}

[[using gnu: malloc, hot, returns_nonnull]] [[nodiscard]] inline CharPtr FileReader::readChar()
{
    if(this->_opened)
    {
        char ch = fgetc(this->_file);

        return new Char( ch == EOF ? '\0' : ch);
    }

    return new Char();
}

[[using gnu: malloc, hot, returns_nonnull]] [[nodiscard]] inline StringPtr FileReader::readWhole()
{
    if(this->_opened)
    {
        char ch;

        StringPtr str = new String();

        while( (ch = fgetc(this->_file)) != EOF)
        {
            str->push(ch);
        }

        return str;
    }

    return new String();
}

inline SronInt_t FileReader::tell() const
{
    if( this->_opened) return std::ftell(this->_file);
    
    return -1;
}

inline SronBool_t FileReader::endOfFile() const
{
    if (this->_opened) return std::feof(this->_file);

    return true;
}

inline void FileReader::setSeek(SronInt_t __pos)
{
    if( this->_opened) std::fseek(this->_file, __pos, SEEK_SET);
}

inline void FileReader::close()
{
    if(this->_opened)
    {
        std::fclose(this->_file);

        this->_file = nullptr;

        delete[] this->_filename.data();

        this->_filename = std::string_view("", 0);

        this->_len = 0;

        this->_opened = false;
    }
}

inline bool FileReader::isOpen() const
{
    return this->_opened;
}

inline bool FileReader::open(const std::string_view& __filename)
{
    if(this->_opened)
    {
        throw ThrowException("opening a file. You already opened this file before. Use 'fclose()' and then again open this file", SronException::FileWriterException);
    }

    #ifdef _WIN64
        fopen_s(&_file, __filename.data(), "r");
    #else
        this->_file = std::fopen(__filename.data(), "r");
    #endif

    if(this->_file)
    {
        std::fseek(this->_file, 0, SEEK_END);

        this->_len = std::ftell(this->_file);

        std::fseek(this->_file, 0, SEEK_SET);

        this->_filename = SronExtra::duplicateString(__filename);

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

inline SronInt_t FileReader::len() const
{
    return this->_len;
}

inline std::string FileReader::getFileName() const
{
    if(this->_opened) return std::string(this->_filename.data(), this->_filename.length());

    return "";
}

inline FileReader::~FileReader() noexcept
{
    this->close();
}

inline void FileReader::reset()
{
    if( this->_opened)
    {
        std::fseek(this->_file, 0, SEEK_SET);
    }
}

inline FileReader::Freader_t FileReader::getBaseFreader()
{
    return this->_file;
}

#endif 