

#include "_garbage_collector_.hpp"

inline AnyBind::AnyBind( const AnyPtr __ptr , const SronTypeNum __type , const GarbageCollector::GcSize_t __layer )
noexcept : _ptr( __ptr ) , _type( __type ) , _layer( __layer ) { }

inline AnyBind::AnyBind(AnyBind &__binder) noexcept
{

    if (this != &__binder) [[likely]]
    {

        this->_ptr = __binder._ptr;
        this->_layer = __binder._layer;
        this->_type = __binder._type;

        __binder._ptr = nullptr;
    }
}

inline AnyBind::AnyBind(AnyBind &&__rhs) noexcept
{

    if (this != &__rhs) [[likely]]
    {
        this->_ptr = __rhs._ptr;
        this->_layer = __rhs._layer;
        this->_type = __rhs._type;

        __rhs._ptr = nullptr;
    }
}

inline void AnyBind::set( AnyPtr __ptr , SronTypeNum __type ) noexcept
{
    this->_ptr = __ptr;

    this->_type = __type;
}

inline void AnyBind::set( AnyPtr __ptr ) noexcept
{
    this->_ptr = __ptr;

    if ( this->_ptr ) this->_type = __ptr->TYPE_NUMBER();

    else this->_type = SronTypeNum::INVALID_TYPE;
}

inline AnyPtr AnyBind::ptr() const 
{
    if ( this->_ptr ) [[likely]] return this->_ptr;

    throw SronException::NullPointerException();
}

inline GarbageCollector::GcSize_t AnyBind::layer() const noexcept 
{
    return this->_layer;
}

inline void AnyBind::setLayer( GarbageCollector::GcSize_t __layer ) noexcept
{
    this->_layer = __layer;
}

inline SronTypeNum AnyBind::type() const noexcept
{
    return this->_type;
}

inline Any &AnyBind::operator*()
{
    return *(this->ptr());
}

inline AnyPtr AnyBind::operator->() 
{
    return this->ptr();
}

inline AnyBind::~AnyBind() noexcept { delete this->_ptr; }



struct ExceptionThrowByUser {

    private :
        StringPtr ptr;

    public :
        inline ExceptionThrowByUser(StringPtr __ptr) : ptr(__ptr) { }

        inline void DISPLAY_EXCEPTION() const
        {
            ptr->PRINT();

            printf_s(" caught:\n    ");

            SronException::LOAD_FILE_AND_PRINT((**ptr).c_str());
        }

};
