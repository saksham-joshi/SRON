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

    if ( this->_ptr ) this->_type = __ptr->typeNum();

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

inline std::string AnyBind::typeStr() const
{
    return SronExtra::typenumToString(this->_type);
}

inline Any &AnyBind::operator*()
{
    return *(this->ptr());
}

inline AnyPtr AnyBind::operator->() 
{
    return this->ptr();
}

inline IntPtr AnyBind::getInt()
{
    if(this->_type == SronTypeNum::TYPE_INT) return intCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'Int'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline DoublePtr AnyBind::getDouble()
{
    if(this->_type == SronTypeNum::TYPE_DOUBLE) return doubleCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'Double'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline CharPtr AnyBind::getChar()
{
    if(this->_type == SronTypeNum::TYPE_CHAR) return charCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'Char'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline BoolPtr AnyBind::getBool()
{
    if(this->_type == SronTypeNum::TYPE_BOOL) return boolCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'Bool'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline StringPtr AnyBind::getStr()
{
    if(this->_type == SronTypeNum::TYPE_STRING) return stringCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'String'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline ListPtr AnyBind::getList()
{
    if(this->_type == SronTypeNum::TYPE_LIST) return listCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'List'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline FreadPtr AnyBind::getFreader()
{
    if(this->_type == SronTypeNum::TYPE_FILE_READER) return freaderCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'FileReader'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline FwritePtr AnyBind::getFwriter()
{
    if(this->_type == SronTypeNum::TYPE_FILE_WRITER) return fwriterCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'FileWriter'. [[ISSUE OF SRON's COMPILER AND INTERPRETER]]");
}

inline LstrPtr AnyBind::getLstr()
{
    if(this->_type == SronTypeNum::TYPE_LITERAL_STR) return lstrCast(this->_ptr);

    throw ThrowException("converting value of type '" + this->typeStr() + "' to type 'LiteralString'");
}

inline SronInt_t AnyBind::getBaseInt()
{
    return this->getInt()->getBaseInt();
}

inline SronDouble_t AnyBind::getBaseDouble()
{
    return this->getDouble()->getBaseDouble();
}

inline SronChar_t AnyBind::getBaseChar()
{
    return this->getChar()->getBaseChar();
}

inline SronBool_t AnyBind::getBaseBool()
{
    return this->getBool()->getBaseBool();
}

inline SronString_t& AnyBind::getBaseStr()
{
    return this->getStr()->getBaseString();
}

inline List::SronList_t& AnyBind::getBaseList()
{
    return this->getList()->getBaseList();
}

inline FileReader::Freader_t AnyBind::getBaseFreader()
{
    return this->getFreader()->getBaseFreader();
}

inline FileWriter::Fwriter_t AnyBind::getBaseFwriter()
{
    return this->getFwriter()->getBaseFwriter();
}

inline LiteralString::SronLstr_t& AnyBind::getBaseLstr()
{
    return this->getLstr()->getBaseLstr();
}

inline const char* AnyBind::getCstr()
{
    switch(this->_type)
    {
        case SronTypeNum::TYPE_STRING : return stringCast(this->_ptr)->cStr();

        case SronTypeNum::TYPE_LITERAL_STR : return lstrCast(this->_ptr)->getBaseLstr().data();

        default : { }
    }

    throw ThrowException("extracting a 'LiteralString' from a value of type '" + std::string(this->_ptr->type()) + "' which is not possible");
}

inline bool AnyBind::canBeInt() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_INT || this->_type == SronTypeNum::TYPE_DOUBLE || this->_type == SronTypeNum::TYPE_CHAR || this->_type == SronTypeNum::TYPE_BOOL);
}

inline bool AnyBind::canBeDouble() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_INT || this->_type == SronTypeNum::TYPE_DOUBLE);
}

inline bool AnyBind::canBeChar() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_INT || this->_type == SronTypeNum::TYPE_CHAR);
}

inline bool AnyBind::canBeBool() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_INT || this->_type == SronTypeNum::TYPE_BOOL);
}

inline bool AnyBind::canBeCollective() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_STRING || this->_type == SronTypeNum::TYPE_LIST);
}

inline bool AnyBind::canBeString() const noexcept
{
    return (this->_type == SronTypeNum::TYPE_STRING || this->_type == SronTypeNum::TYPE_LITERAL_STR);
}

inline SronInt_t AnyBind::getConvertedInt() const
{
    switch(this->_type)
    {
        case SronTypeNum::TYPE_INT : return intCast(this->_ptr)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE : return (SronInt_t)doubleCast(this->_ptr)->getBaseDouble();

        case SronTypeNum::TYPE_CHAR : return (SronChar_t)charCast(this->_ptr)->getBaseChar();

        case SronTypeNum::TYPE_BOOL : return (SronBool_t)boolCast(this->_ptr)->getBaseBool();

        default : { }
    }

    throw ThrowException("converting value to type '"+this->typeStr() + "' to 'Int' type", SronException::TypeConversionException);
}

inline SronDouble_t AnyBind::getConvertedDouble() const
{
    switch(this->_type)
    {
        case SronTypeNum::TYPE_DOUBLE : return doubleCast(this->_ptr)->getBaseDouble();

        case SronTypeNum::TYPE_INT : return (SronDouble_t)intCast(this->_ptr)->getBaseInt();

        default : { }
    }

    throw ThrowException("converting value to type '"+this->typeStr() + "' to 'Double' type", SronException::TypeConversionException);
}

inline SronChar_t AnyBind::getConvertedChar() const 
{
    switch(this->_type)
    {
        case SronTypeNum::TYPE_CHAR : return charCast(this->_ptr)->getBaseChar();

        case SronTypeNum::TYPE_INT : return (SronChar_t)intCast(this->_ptr)->getBaseInt();

        default : { }
    }

    throw ThrowException("converting value to type '"+this->typeStr() + "' to 'Char' type", SronException::TypeConversionException);
}

inline SronBool_t AnyBind::getConvertedBool() const 
{
    switch(this->_type)
    {
        case SronTypeNum::TYPE_BOOL : return boolCast(this->_ptr)->getBaseBool();

        case SronTypeNum::TYPE_INT : return (SronBool_t)intCast(this->_ptr)->getBaseInt();

        default : { }
    }

    throw ThrowException("converting value to type '"+this->typeStr() + "' to 'Bool' type", SronException::TypeConversionException);
}

inline AnyBind::~AnyBind() noexcept 
{ 
    delete this->_ptr;
    this->_ptr = nullptr;
    this->_type = SronTypeNum::INVALID_TYPE;
}