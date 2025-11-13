
#ifndef _SRON_OBUF_H_
#define _SRON_OBUF_H_

#include "base_type/_datatypes_.hpp"

constexpr inline SronOBuffer::SronOBuffer( const unsigned short __pre_allocate ) noexcept
{
    if ( __pre_allocate > SronOBuffer::BUFFER_SIZE )
    {
        this->_dynamic_buffer.reserve( __pre_allocate - SronOBuffer::BUFFER_SIZE );
    }
}

inline void SronOBuffer::append( const char* __str , unsigned long long __length)
{
    if ( this->_on_static_buffer && ( this->_pos + __length < SronOBuffer::BUFFER_SIZE ) )
    {
        SronSupport::copyMemory( this->_static_buffer + this->_pos, __str, __length);
        //std::memcpy( this->_static_buffer + this->_pos , __str , __length );

        this->_pos += __length;

        return;
    }

    // here it is confirmed that _static_buffer is full and
    // we have to start writing content on _dynamic buffer
    this->_on_static_buffer = false;
    
    this->_dynamic_buffer.append( __str , __length);
}

inline SronOBuffer& SronOBuffer::operator<< ( SronInt_t __value )
{
    std::string str = std::to_string( __value );

    this->append( str.c_str() , str.length() );

    return *this;
}

inline SronOBuffer& SronOBuffer::operator<< ( SronDouble_t __value )
{
    std::string str = std::to_string( __value );

    str.erase( str.begin() + str.find('.') + 1 + Double::getPrecision(), str.end()); // managing precision

    this->append( str.c_str() , str.length() );

    return *this;
}

inline SronOBuffer& SronOBuffer::operator<< ( SronChar_t __value )
{
    this->append( &__value , 1);

    return *this;
}

inline SronOBuffer& SronOBuffer::operator<< ( SronBool_t __value )
{
    if ( __value ) this->append( TRUE_STRING_PRINT_FORMAT  , sizeof( TRUE_STRING_PRINT_FORMAT) - 1  );

    else           this->append( FALSE_STRING_PRINT_FORMAT , sizeof( FALSE_STRING_PRINT_FORMAT) - 1 );

    return *this;
}

inline SronOBuffer& SronOBuffer::operator<< ( const char*  __str )
{
    this->append( __str, SronSupport::stringLen( __str));
    
    //this->append( __str , std::strlen( __str ));

    return *this;
}


inline SronOBuffer& SronOBuffer::operator<< ( SronString_t& __str )
{
    this->append( __str.c_str() , __str.length() );

    return *this;
}

inline void SronOBuffer::flush() noexcept
{
    if ( this->_pos ) std::printf( "%.*s", this->_pos , this->_static_buffer);
    
    std::printf( "%s" , this->_dynamic_buffer.c_str() );

    this->clear();
}

inline void SronOBuffer::clear() noexcept
{
    this->_pos = 0;

    this->_on_static_buffer = true;

    this->_dynamic_buffer.clear();
}

inline bool SronOBuffer::isempty() noexcept
{
    return this->_pos == 0;
}

inline SronInt_t SronOBuffer::size() noexcept
{
    return this->_dynamic_buffer.length() + this->_pos;
}


#endif