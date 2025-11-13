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

typedef Any *AnyPtr;
typedef Collective *ColPtr;
typedef Void *VoidPtr;
typedef Int *IntPtr;
typedef Double *DoublePtr;
typedef Char *CharPtr;
typedef Bool *BoolPtr;
typedef String *StringPtr;
typedef List *ListPtr;

class AnyBind;

typedef AnyBind* AnyBindPtr;
typedef AnyBind& AnyBindRef;

class SronOBuffer;

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

    [[gnu::always_inline]] [[gnu::hot]] inline static void addLayer();
    [[gnu::always_inline]] [[gnu::hot]] inline static void destroyLayer();
    [[gnu::always_inline]] [[gnu::hot]] inline static void init();
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr move(AnyBindPtr);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerMemory(AnyPtr);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerMemory(AnyPtr, SronTypeNum);
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr registerAt( GarbageCollector::GcSize_t , AnyPtr , SronTypeNum );
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

        [[gnu::always_inline]] [[gnu::hot]] inline Any& operator*();

        [[gnu::always_inline]] [[gnu::hot]] inline AnyPtr operator->();

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

        [[gnu::always_inline]] [[gnu::hot]] inline SronOBuffer& operator<< ( SronString_t& );

        [[gnu::always_inline]] [[gnu::hot]] inline void flush() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline void clear() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline bool isempty() noexcept;

        [[gnu::always_inline]] [[gnu::hot]] inline SronInt_t size() noexcept;

        inline ~SronOBuffer() noexcept = default;
};

SronOBuffer O_BUFFER;

#endif