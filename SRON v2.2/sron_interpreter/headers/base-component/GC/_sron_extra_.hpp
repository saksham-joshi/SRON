#ifndef _EXTRA_H_
#define _EXTRA_H_

#include "_datatypes_overload_.hpp"

namespace SronExtra
{

    inline static bool doesFileExists( AnyBind& );
    inline static const char* TYPENUM_TO_STRING( SronTypeNum ) noexcept;


    /* Implementation starts from here ...*/
    inline static bool doesFileExists( AnyBind& __binder )
    {
        if ( __binder.type() == SronTypeNum::TYPE_STRING )
        {
            return std::filesystem::exists( **stringCast( __binder.ptr()) );
        }

        throw ThrowException("checking if file exists or not. Expected value of type 'String' but found value of type '" + std::string(SronExtra::TYPENUM_TO_STRING( __binder.type()))  + "'", SronException::ArgumentException);
    }

    inline static const char* TYPENUM_TO_STRING( SronTypeNum __type ) noexcept
    {
        switch( __type )
        {
            case SronTypeNum::TYPE_VOID : return "Void";

            case SronTypeNum::TYPE_INT : return "Int";

            case SronTypeNum::TYPE_DOUBLE : return "Double";

            case SronTypeNum::TYPE_CHAR : return "Char";

            case SronTypeNum::TYPE_BOOL : return "Bool";

            case SronTypeNum::TYPE_STRING : return "String";

            case SronTypeNum::TYPE_LIST : return "List";

            default : { }
        }

        return "Invalid-Type";
    }
}
#endif