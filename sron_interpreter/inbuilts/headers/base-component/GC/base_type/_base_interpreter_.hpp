#pragma once 

#ifndef _BASE_INTERPRETER_H_
#define _BASE_INTERPRETER_H_

#include "exception/_exception_.hpp"
#include "exception/_converter_.hpp"

class Any;
class Collective;
class Void;
class Int;
class Double;
class String;
class Char;
class Bool;
class List;
class FileReader;
class FileWriter;
class LiteralString;

typedef Any *AnyPtr;
typedef Collective *ColPtr;
typedef Void *VoidPtr;
typedef Int *IntPtr;
typedef Double *DoublePtr;
typedef Char *CharPtr;
typedef Bool *BoolPtr;
typedef String *StringPtr;
typedef List *ListPtr;
typedef FileReader *FreadPtr;
typedef FileWriter *FwritePtr;
typedef LiteralString *LstrPtr;

class AnyBind;

typedef AnyBind* AnyBindPtr;
typedef AnyBind& AnyBindRef;

class SronOBuffer;

typedef std::string SronString_t;
typedef FILE* Freader_t;
typedef FILE* Fwriter_t;
typedef std::vector<AnyBindPtr> SronList_t;
typedef std::string_view SronLstr_t;

namespace GarbageCollector
{
    typedef unsigned int GcSize_t;

    class MemoryChain final
    {
        private:
            template <typename Tp> class Node final
            {
                public :
                Tp _value;
                Node<Tp> *_next;

                [[gnu::always_inline]] [[gnu::hot]] inline Node(Tp&& __other) noexcept : _value(std::move(__other)) , _next(nullptr)
                { }

                inline Node(Node<Tp> &&__node) : _value(std::move(__node._value)), _next(__node._next) {}

                inline ~Node() noexcept = default;
            };

            MemoryChain::Node<class AnyBind> *_head;
            MemoryChain::Node<class AnyBind> *_tail;
            GarbageCollector::GcSize_t _layer_index;
        
        public :

            [[gnu::always_inline]] [[gnu::hot]] inline MemoryChain(const GarbageCollector::GcSize_t) noexcept;
            [[gnu::always_inline]] [[gnu::hot]] inline MemoryChain(MemoryChain &&) noexcept;
            [[gnu::always_inline]] [[gnu::hot]] inline AnyBindPtr push(AnyPtr);
            [[gnu::always_inline]] [[gnu::hot]] inline AnyBindPtr push(AnyPtr , SronTypeNum );
            [[gnu::always_inline]] [[gnu::hot]] inline AnyBindPtr push(AnyBind &&);
            [[gnu::always_inline]] [[gnu::hot]] inline AnyBindPtr back();
            [[gnu::always_inline]] [[gnu::hot]] inline ~MemoryChain() noexcept;
    };

    typedef GarbageCollector::MemoryChain GcLayer;

    typedef std::vector<GcLayer> GcStack;

    GcStack __garbageStack;

    /* stores the __garbageStack.size() - 1. 
     * Initially set to ULONG_MAX, because
     * When the first layer is added, it is 
     * incremeneted and reaches to zero.
    */
    unsigned int __gcStackTopLoc = UINT32_MAX;

    GcLayer *__top;

    /*
     * Static Memory pool implementation for next version 2.4
    */
    // namespace BigBlockManager
    // {
        
    //     constexpr const static auto SIZE_OF_BLOCK = 98304u; // 98 Kilobytes
        
    //     static char BIG_BLOCK__[BigBlockManager::SIZE_OF_BLOCK];

    //     static const void*const BEGIN   = BigBlockManager::BIG_BLOCK__;
    //     static const void*const END     = BigBlockManager::BIG_BLOCK__ + BigBlockManager::SIZE_OF_BLOCK;
    //     static char*          CURRENT   = (char*)BigBlockManager::BEGIN;
        
    //     // returns nullptr if there is no space left otherwise returns the non-null pointer
    //     [[gnu::always_inline]] [[gnu::hot]] inline static void* registerBlock( size_t __block_size )
    //     {
    //         auto new_end = BigBlockManager::CURRENT + __block_size;

    //         // cannot allocate desired block
    //         if(new_end >= BigBlockManager::END) return nullptr;

    //         auto new_block = BigBlockManager::CURRENT;

    //         BigBlockManager::CURRENT = new_end;

    //         return (void*)new_block;
    //     }

    //     [[gnu::always_inline]] [[gnu::hot]] inline static void freeBlock( void* __ptr, size_t __block_size)
    //     {
    //         if(__ptr >= BigBlockManager::BEGIN && __ptr < BigBlockManager::END)
    //         {
    //             auto end = (char*)__ptr + __block_size;

    //             if(end == BigBlockManager::CURRENT) BigBlockManager::CURRENT = (char*)__ptr;
    //         }
    //     }
    // }

    [[gnu::always_inline]] [[gnu::hot]] inline static void addLayer();
    [[gnu::always_inline]] [[gnu::hot]] inline static void destroyLayer();
    [[gnu::always_inline]] [[gnu::hot]] inline static void init();
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr move(AnyBindPtr);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerMemory(AnyPtr);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerMemory(AnyPtr, SronTypeNum);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerAt( GarbageCollector::GcSize_t , AnyPtr , SronTypeNum );

    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerInt(const SronInt_t);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerDouble(const SronDouble_t);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerChar(const SronChar_t);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerString(const SronString_t&);

    inline static void totalDestruction() noexcept;
}

class AnyBind
{
    AnyPtr _ptr ;
    SronTypeNum _type;
    GarbageCollector::GcSize_t _layer;

    public :
        inline AnyBind(const AnyPtr __ptr = nullptr, const SronTypeNum __type = SronTypeNum::INVALID_TYPE , const GarbageCollector::GcSize_t __layer = GarbageCollector::__gcStackTopLoc) noexcept;

        inline AnyBind(AnyBind&) noexcept;

        inline AnyBind(AnyBind&&) noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void set( AnyPtr , SronTypeNum ) noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void set( AnyPtr ) noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline AnyPtr ptr() const;

        [[gnu::always_inline]] [[gnu::hot]] inline GarbageCollector::GcSize_t layer() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void setLayer( GarbageCollector::GcSize_t ) noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline SronTypeNum type() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline std::string typeStr() const;

        [[gnu::always_inline]] [[gnu::hot]] inline Any& operator*();

        [[gnu::always_inline]] [[gnu::hot]] inline AnyPtr operator->();

        [[gnu::always_inline]] [[gnu::hot]] inline IntPtr getInt();

        [[gnu::always_inline]] [[gnu::hot]] inline DoublePtr getDouble();

        [[gnu::always_inline]] [[gnu::hot]] inline CharPtr getChar();

        [[gnu::always_inline]] [[gnu::hot]] inline BoolPtr getBool();

        [[gnu::always_inline]] [[gnu::hot]] inline StringPtr getStr();

        [[gnu::always_inline]] [[gnu::hot]] inline ListPtr getList();

        [[gnu::always_inline]] [[gnu::hot]] inline FreadPtr getFreader();

        [[gnu::always_inline]] [[gnu::hot]] inline FwritePtr getFwriter();

        [[gnu::always_inline]] [[gnu::hot]] inline LstrPtr getLstr();

        [[gnu::always_inline]] [[gnu::hot]] inline SronInt_t getBaseInt();

        [[gnu::always_inline]] [[gnu::hot]] inline SronDouble_t getBaseDouble();

        [[gnu::always_inline]] [[gnu::hot]] inline SronChar_t getBaseChar();

        [[gnu::always_inline]] [[gnu::hot]] inline SronBool_t getBaseBool();

        [[gnu::always_inline]] [[gnu::hot]] inline SronString_t& getBaseStr();

        [[gnu::always_inline]] [[gnu::hot]] inline SronList_t& getBaseList();

        [[gnu::always_inline]] [[gnu::hot]] inline Freader_t getBaseFreader();

        [[gnu::always_inline]] [[gnu::hot]] inline Fwriter_t getBaseFwriter();

        [[gnu::always_inline]] [[gnu::hot]] inline SronLstr_t& getBaseLstr();

        [[gnu::always_inline]] [[gnu::hot]] inline const char* getCstr();

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeInt() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeDouble() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeChar() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeBool() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeCollective() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool canBeString() const noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline SronInt_t getConvertedInt() const;

        [[gnu::always_inline]] [[gnu::hot]] inline SronDouble_t getConvertedDouble() const;

        [[gnu::always_inline]] [[gnu::hot]] inline SronChar_t getConvertedChar() const;

        [[gnu::always_inline]] [[gnu::hot]] inline SronBool_t getConvertedBool() const;

        [[gnu::always_inline]] [[gnu::hot]] inline ~AnyBind() noexcept;
};

class SronBytecodeReader
{
    private:
        const char* _bytecode;
        const char* _start;
        const char* _end;
        
    public:

        // stores true if code is executing and if set false, code will end
        bool executing__ = true;

        inline                         SronBytecodeReader  ( const char*, const char*                                  ) ;
        inline                         SronBytecodeReader  ( const char *const , unsigned short int , const char*const ) ;

        [[gnu::always_inline]] [[gnu::hot]] inline void                         incrementSeek     ( BytecodePos_t ) noexcept   ;
        [[gnu::always_inline]] [[gnu::hot]] inline void                         decrementSeek     ( BytecodePos_t ) noexcept   ;

        [[gnu::always_inline]] [[gnu::hot]] inline const char*                  getCurrentPos     ( ) const     noexcept       ;

        [[gnu::always_inline]] [[gnu::hot]] inline void                         insertToBuffer    ( SronOBuffer& , BytecodeCount_t );

        [[gnu::always_inline]] [[gnu::hot]] inline void                         print             ( BytecodeCount_t    )       ;

        template <typename Tp> 
        [[gnu::always_inline]] [[gnu::hot]] inline void                         readArray         ( Tp*, BytecodeCount_t )     ;
        template <typename Tp> 
        [[gnu::always_inline]] [[gnu::hot]] inline Tp                           read              () ;
        [[gnu::always_inline]] [[gnu::hot]] inline SronChar_t                   readChar          () ;
        [[gnu::always_inline]] [[gnu::hot]] inline SronDouble_t                 readDouble        () ;
        [[gnu::always_inline]] [[gnu::hot]] inline BytecodeFlags                readFlag          () ;
        [[gnu::always_inline]] [[gnu::hot]] inline Hash_t                       readHash          () ;
        [[gnu::always_inline]] [[gnu::hot]] inline BytecodeVariable_t           readVariable      () ;
        [[gnu::always_inline]] [[gnu::hot]] inline SronInt_t                    readInt           () ;
        [[gnu::always_inline]] [[gnu::hot]] inline BytecodePos_t                readPosition      () ;
        [[gnu::always_inline]] [[gnu::hot]] inline BytecodeCount_t              readCount         () ;

        [[gnu::always_inline]] [[gnu::hot]] inline void                         setSeekToEnd      () noexcept                 ;
        [[gnu::always_inline]] [[gnu::hot]] inline void                         setSeekAt         ( const char* ) noexcept    ;
};

class SronOBuffer final
{
    public :
        constexpr static const unsigned short int BUFFER_SIZE = 512u;

        static_assert( SronOBuffer::BUFFER_SIZE < 8096 , "If value of Buffer size is larger near to max value of unsigned short then numeric overflow can occur at runtime" );

    private :
        alignas(64) char _static_buffer[ SronOBuffer::BUFFER_SIZE ] = { '\0' };

        unsigned short int _pos = 0;

        std::string _dynamic_buffer;

        bool _on_static_buffer = true;

    public :

        constexpr inline SronOBuffer( const unsigned short __pre_allocate = 0 ) noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void         append     ( const char* , unsigned long long );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( SronInt_t    );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( SronDouble_t );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( SronChar_t   );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( SronBool_t   );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( const char*  );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( const SronString_t& );

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< (const SronLstr_t& );

        [[gnu::always_inline]] [[gnu::hot]] inline void flush() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void clear() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool isempty() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline SronInt_t size() noexcept;

        inline ~SronOBuffer() noexcept = default;
};

SronOBuffer O_BUFFER;

#endif