#pragma once 

#ifndef _BYTECODE_READER_H
#define _BYTECODE_READER_H

#include "base-component/_sron_obuffer_.hpp"

namespace BytecodeManager
{
    class BytecodeBinder
    {
        private :
            const char* _content;  // pointer from where the bytecode starts. Should not be freed
            const char* _end;      // pointer to the end of the file . Should not be freed
            const char* _start;    // absolute start of the file. Must be freed

            #ifdef _WIN64
                HANDLE _hfile;
                HANDLE _hmapping;
            #elif defined(__linux__)
                int _file_descriptor = -1;
                size_t _size = 0;
            #endif
        
        public :

            struct BytecodeContent 
            {
                const char* _content;
                const char* _end;
            };

            inline BytecodeBinder( const char*const __filename , const char*const __fnc_name_exclude_dir_path )
            {
                #ifdef _WIN64
                    this->_hfile = CreateFileA(
                        __filename,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_SEQUENTIAL_SCAN ,
                        NULL
                    );

                    if (this->_hfile == INVALID_HANDLE_VALUE) throw ThrowException("searching for bytecode file '" + std::string( __filename) + "'", SronException::BytecodeNotFoundException);

                    this->_hmapping = CreateFileMappingA(
                        this->_hfile,
                        NULL,
                        PAGE_READONLY,
                        0,
                        0,
                        NULL
                    );

                    if (!this->_hmapping) throw ThrowException("creating mapping of bytecode's file. File load is OK but cannot create file map");
                
                    this->_content = (const char*)MapViewOfFile(
                        this->_hmapping,
                        FILE_MAP_READ,
                        0,
                        0,
                        0
                    );
                
                    if (! (this->_content)) throw ThrowException("extracting content of bytecode file '"+ std::string(__filename) +"'. OS is not allowing to read file's content");

                    
                    DWORD fileSize = GetFileSize(this->_hfile, NULL);
                    if (fileSize == INVALID_FILE_SIZE || fileSize == 0)
                    {
                        CloseHandle(this->_hfile);
                        
                        throw ThrowException("getting the size of bytecode file '" + std::string( __filename ) + "' . Either the bytecode file is empty or OS is not allowing to get its meta");
                    }

                    this->_end = this->_content + fileSize;
                    
                #elif defined(__linux__)
                    this->_file_descriptor = ::open(__filename, O_RDONLY);

                    if ( this->_file_descriptor < 0) throw ThrowException("searching for bytecode file '" + std::string( __filename) + "'", SronException::BytecodeNotFoundException);
                    

                    struct stat filestat;

                    if (::fstat( this->_file_descriptor, &filestat) < 0)
                    {
                        ::close( this->_file_descriptor );

                        throw ThrowException("getting the size of bytecode file '" + std::string( __filename ) + "' . Either the bytecode file is empty or OS is not allowing to get its meta");
                    }

                    this->_size = static_cast<size_t>( filestat.st_size );

                    if ( this->_size == 0 )
                    {
                        ::close( this->_file_descriptor );
                        
                        throw ThrowException("getting the size of bytecode file '" + std::string( __filename ) + "' . Either the bytecode file is empty or OS is not allowing to get its meta");throw ThrowException("getting the size of bytecode file '" + std::string( __filename ) + "' . The bytecode file is empty");
                    }

                    void* map = ::mmap(nullptr, this->_size, PROT_READ, MAP_PRIVATE, this->_file_descriptor, 0);
                    
                    if (map == MAP_FAILED)
                    {
                        ::close( this->_file_descriptor );

                        throw ThrowException("creating mapping of bytecode's file '"+ std::string(__filename) +"'. File load is OK but cannot create file map");
                    }

                    this->_content = static_cast<const char*>(map);

                    this->_end = this->_content + this->_size;
                #endif

                this->_start = this->_content;

                // verifying the metadata of the value
                SronBytecodeMeta meta;

                SronSupport::copyMemory(&meta, this->_content, sizeof(meta));
                //std::memcpy(&meta, this->_content, sizeof(meta));

                if ( ! meta.matchMeta( { SRON_VERSION , SronHasher(__fnc_name_exclude_dir_path).GET() } ) )
                {
                    #ifdef SRON_DEVELOPMENT_PHASE
                        std::printf("\n |__| Version= %lf \t MetaHash= %llu \t FileName= %s \t Expected FileHash= %llu \n", meta._version , meta._safety_hash , __filename, SronHasher(__filename).GET());
                    #endif
                    throw ThrowException("loading the bytecode. The bytecode's meta is invalid", SronException::InvalidByteCodeException);
                }

                this->_content += sizeof(meta);
            }

            inline BytecodeBinder( BytecodeBinder&& __rhs) noexcept  
            {
                this->_content     = __rhs._content;
                this->_end         = __rhs._end;
                this->_start       = __rhs._start;

                #ifdef _WIN64
                    this->_hfile       = __rhs._hfile;
                    this->_hmapping    = __rhs._hmapping;

                    __rhs._hfile = __rhs._hmapping = nullptr;
                #elif defined(__linux__)
                    this->_size = __rhs._size;
                    this->_file_descriptor = __rhs._file_descriptor;

                    __rhs._file_descriptor = -1;
                    __rhs._size = 0;
                #endif

                __rhs._content = __rhs._end = __rhs._start = nullptr;
            }

            inline BytecodeBinder::BytecodeContent getContent() noexcept 
            {
                return { this->_content , this->_end };
            }

            inline const char* getStart() const noexcept 
            {
                return this->_content;
            }

            inline const char* getEnd() const noexcept 
            {
                return this->_end;
            }

            inline ~BytecodeBinder() noexcept
            {
                #ifdef _WIN64
                    if ( this->_hfile && this->_hmapping)
                    {
                        CloseHandle( this->_hfile );

                        CloseHandle( this->_hmapping );

                        this->_hfile = this->_hmapping = nullptr;
                    }
                #elif defined(__linux__)
                    if ( this->_content ) ::munmap(const_cast<char*>(this->_start), this->_size);
        
                    if ( this->_file_descriptor >= 0) ::close( this->_file_descriptor );
                #endif
            }
    };

    static std::unordered_map <std::string_view , BytecodeManager::BytecodeBinder> __UserDefinedFncMap__;

    [[gnu::hot]] [[gnu::always_inline]] inline static BytecodeBinder::BytecodeContent getBytecode ( const std::string_view& __filename , const char*const __file_name_exclude_dir_path )
    {
        using BytecodeManager::__UserDefinedFncMap__;

        auto it = __UserDefinedFncMap__.find( __filename );

        if ( it == __UserDefinedFncMap__.end()) return __UserDefinedFncMap__.insert({__filename , BytecodeBinder(__filename.data() , __file_name_exclude_dir_path)}).first->second.getContent();
        
        return it->second.getContent();
    }

    inline static bool isBytecodeCached( AnyBind& __fnc_name )
    {
        if( __fnc_name.type() == SronTypeNum::TYPE_STRING )
        {
            auto& bytecode_name = stringCast(__fnc_name.ptr())->getBaseString();

            return BytecodeManager::__UserDefinedFncMap__.find( bytecode_name ) != BytecodeManager::__UserDefinedFncMap__.end();
        }
        else if(__fnc_name.type() == SronTypeNum::TYPE_LITERAL_STR)
        {
            auto& bytecode_name = lstrCast(__fnc_name.ptr())->getBaseLstr();

            return BytecodeManager::__UserDefinedFncMap__.find(bytecode_name) != BytecodeManager::__UserDefinedFncMap__.end();
        }

        throw ThrowException("finding if the bytecode is cached or not. Expected an argument of type 'String' or 'LiteralString' but found value of type '" + __fnc_name.typeStr() + "'" , SronException::ArgumentException);
    }

}

#endif