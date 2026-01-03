#ifndef USER_FNC_H
#define USER_FNC_H

#include "headers/_input_.hpp"
#include "headers/_math_.hpp"
#include "headers/_random_.hpp"
#include "headers/_function_.hpp"

namespace Sron
{
    
    inline static AnyBindPtr ascii(ArgumentList &);

    inline static AnyBindPtr beep(ArgumentList &);
    inline static AnyBindPtr copy(ArgumentList &);

    [[noreturn]] inline static AnyBindPtr exit(ArgumentList &);
    inline static AnyBindPtr getExecTime(ArgumentList &);

    // USER INPUT FUNCTIONS
    inline static AnyBindPtr inputInt(ArgumentList &);
    inline static AnyBindPtr inputDouble(ArgumentList &);
    inline static AnyBindPtr inputChar(ArgumentList &);
    inline static AnyBindPtr inputString(ArgumentList &);

    // CHAR MANIPUALTION FUNCTIONS
    inline static AnyBindPtr isAlphabet(ArgumentList &);
    inline static AnyBindPtr isConsonant(ArgumentList &);
    inline static AnyBindPtr isDigit(ArgumentList &);
    inline static AnyBindPtr isVowel(ArgumentList &);
    inline static AnyBindPtr isLowerCase(ArgumentList &);
    inline static AnyBindPtr isUpperCase(ArgumentList &);
    inline static AnyBindPtr isAlphaNum(ArgumentList &);

    // type check functions ...
    inline static AnyBindPtr isVoid(ArgumentList &);
    inline static AnyBindPtr isInt(ArgumentList &);
    inline static AnyBindPtr isDouble(ArgumentList &);
    inline static AnyBindPtr isChar(ArgumentList &);
    inline static AnyBindPtr isBool(ArgumentList &);
    inline static AnyBindPtr isCollective(ArgumentList &);
    inline static AnyBindPtr isString(ArgumentList &);
    inline static AnyBindPtr isList(ArgumentList &);
    inline static AnyBindPtr isFileReader(ArgumentList &);
    inline static AnyBindPtr isFileWriter(ArgumentList &);
    inline static AnyBindPtr isLiteralString(ArgumentList &);

    // COMMON LIST AND STRING MANIPULATION FUNCTIONS
    inline static AnyBindPtr at(ArgumentList &);
    inline static AnyBindPtr clear(ArgumentList &);
    inline static AnyBindPtr count(ArgumentList &);
    inline static AnyBindPtr drop(ArgumentList &);
    inline static AnyBindPtr index(ArgumentList &);
    inline static AnyBindPtr insert(ArgumentList &);
    inline static AnyBindPtr len(ArgumentList &);
    inline static AnyBindPtr push(ArgumentList &);
    inline static AnyBindPtr POP(ArgumentList &);
    inline static AnyBindPtr replace(ArgumentList &);
    inline static AnyBindPtr reverse(ArgumentList &);
    inline static AnyBindPtr rIndex(ArgumentList &);
    inline static AnyBindPtr sort(ArgumentList &);
    inline static AnyBindPtr reverseSort(ArgumentList &);
    inline static AnyBindPtr subPart(ArgumentList &);
    inline static AnyBindPtr update(ArgumentList &);

    [[gnu::hot]] inline static AnyBindPtr print(ArgumentList &);
    [[gnu::hot]] inline static AnyBindPtr println(ArgumentList &);

    // generating random numbers...
    inline static AnyBindPtr randInt(ArgumentList &);
    inline static AnyBindPtr randRange(ArgumentList &);
    inline static AnyBindPtr randDouble(ArgumentList &);

    inline static AnyBindPtr sizeOf(ArgumentList &);

    // type conversion function
    inline static AnyBindPtr toBool(ArgumentList &);
    inline static AnyBindPtr toDouble(ArgumentList &);
    inline static AnyBindPtr toInt(ArgumentList &);
    inline static AnyBindPtr toString(ArgumentList &);

    // COMMON STRING AND CHAR FUNCTIONS...
    inline static AnyBindPtr toLowercase(ArgumentList &);
    inline static AnyBindPtr toUppercase(ArgumentList &);

    // mathematical functions
    inline static AnyBindPtr abs(ArgumentList &);
    inline static AnyBindPtr cbrt(ArgumentList &);
    inline static AnyBindPtr ceil(ArgumentList &);
    inline static AnyBindPtr cos(ArgumentList &);
    inline static AnyBindPtr floor(ArgumentList &);
    inline static AnyBindPtr log(ArgumentList &);
    inline static AnyBindPtr log2(ArgumentList &);
    inline static AnyBindPtr log10(ArgumentList &);
    inline static AnyBindPtr maxValue(ArgumentList &);
    inline static AnyBindPtr minValue(ArgumentList &);
    inline static AnyBindPtr sqrt(ArgumentList &);
    inline static AnyBindPtr sin(ArgumentList &);
    inline static AnyBindPtr tan(ArgumentList &);

    // string manipulation functions...
    inline static AnyBindPtr split(ArgumentList &);
    inline static AnyBindPtr trim(ArgumentList &);

    inline static AnyBindPtr setPrecision(ArgumentList &);
    inline static AnyBindPtr sleep(ArgumentList& args);
    inline static AnyBindPtr sronCmd( ArgumentList&);
    inline static AnyBindPtr sysCmd(ArgumentList &);
    inline static AnyBindPtr throwException(ArgumentList &);

    inline static AnyBindPtr typeOf(ArgumentList &);

    // returns the version of the function ...;
    inline static AnyBindPtr version(ArgumentList &);


    inline static AnyBindPtr fopenRead(ArgumentList &);
    inline static AnyBindPtr fopenWrite(ArgumentList &);
    inline static AnyBindPtr fclose(ArgumentList &);
    inline static AnyBindPtr fisOpen(ArgumentList &);
    inline static AnyBindPtr fisEnd(ArgumentList &);
    inline static AnyBindPtr fgetFilename(ArgumentList &);
    inline static AnyBindPtr freset(ArgumentList &);
    inline static AnyBindPtr fcurPos(ArgumentList &);
    inline static AnyBindPtr fsetSeek(ArgumentList &);

    inline static AnyBindPtr freadChar(ArgumentList &);
    inline static AnyBindPtr freadLine(ArgumentList &);
    inline static AnyBindPtr freadWhole(ArgumentList &);
    inline static AnyBindPtr fwriteChar(ArgumentList &);
    inline static AnyBindPtr fwriteString(ArgumentList &);

    inline static AnyBindPtr cliTextColor(ArgumentList &);
    inline static AnyBindPtr cliBgColor(ArgumentList &);
    

    typedef AnyBindPtr (*SronInBuiltFnc) (ArgumentList&);

    struct SronInBuiltFncBinder
    {
        const char* _fnc_name;
        SronInBuiltFnc _fnc;
    };

    constexpr static struct SronInBuiltFncBinder Fmap[] = {

        // user input functions...
        {"inputChar", Sron::inputChar},
        {"inputDouble", Sron::inputDouble},
        {"inputInt", Sron::inputInt},
        {"inputString", Sron::inputString},

        // character functions
        {"isAlphabet", Sron::isAlphabet},
        {"isConsonant", Sron::isConsonant},
        {"isDigit", Sron::isDigit},
        {"isVowel", Sron::isVowel},
        {"isLower", Sron::isLowerCase},
        {"isUpper", Sron::isUpperCase},
        {"isAlphaNum", Sron::isAlphaNum},

        // type checking functions
        {"isVoid", Sron::isVoid},
        {"isInt", Sron::isInt},
        {"isDouble", Sron::isDouble},
        {"isChar", Sron::isChar},
        {"isBool", Sron::isBool},
        {"isCollective", Sron::isCollective},
        {"isString", Sron::isString},
        {"isList", Sron::isList},
        {"isFileReader", Sron::isFileReader},
        {"isFileWriter", Sron::isFileWriter},
        {"isLiteralString", Sron::isLiteralString},

        // List and string manipulation functions
        {"at", Sron::at},
        {"clear", Sron::clear},
        {"count", Sron::count},
        {"delete", Sron::drop},
        {"index", Sron::index},
        {"insert", Sron::insert},
        {"len", Sron::len},
        {"push", Sron::push},
        {"pop", Sron::POP},
        {"replace", Sron::replace},
        {"reverse", Sron::reverse},
        {"rindex", Sron::rIndex},
        {"sort", Sron::sort},
        {"reverseSort", Sron::reverseSort},
        {"subPart", Sron::subPart},
        {"update", Sron::update},

        {"println", Sron::println},
        {"print", Sron::print},

        // generating random numbers...
        {"randInt", Sron::randInt},
        {"randRange", Sron::randRange},
        {"randDouble", Sron::randDouble},

        // type conversion functions...
        {"toBool", Sron::toBool},
        {"toDouble", Sron::toDouble},
        {"toInt", Sron::toInt},
        {"toString", Sron::toString},

        // String manipulation methods
        {"split", Sron::split},
        {"trim", Sron::trim},
        {"toLower", Sron::toLowercase},
        {"toUpper", Sron::toUppercase},

        // math functions
        {"abs", Sron::abs},
        {"max", Sron::maxValue},
        {"min", Sron::minValue},
        {"sqrt", Sron::sqrt},
        {"cbrt", Sron::cbrt},
        {"log", Sron::log},
        {"log2", Sron::log2},
        {"log10", Sron::log10},
        {"sin", Sron::sin},
        {"cos", Sron::cos},
        {"tan", Sron::tan},
        {"ceil", Sron::ceil},
        {"floor", Sron::floor},

        // File Manipulation functions
        {"freader", Sron::fopenRead},
        {"fwriter", Sron::fopenWrite},
        {"fclose", Sron::fclose},
        {"fisOpen", Sron::fisOpen},
        {"fisEnd", Sron::fisEnd},
        {"fgetName", Sron::fgetFilename},
        {"freset", Sron::freset},
        {"fcurPos", Sron::fcurPos},
        {"fsetSeek", Sron::fsetSeek},
        {"freadChar", Sron::freadChar},
        {"freadLine", Sron::freadLine},
        {"freadWhole", Sron::freadWhole},
        {"fwriteChar", Sron::fwriteChar},
        {"fwriteString", Sron::fwriteString},

        // miscelleaneous functions
        {"ascii" , Sron::ascii},
        {"beep", Sron::beep},
        {"copy", Sron::copy},
        {"exit", Sron::exit},
        {"getExecTime", Sron::getExecTime},
        {"sleep", Sron::sleep},
        {"sronCmd", Sron::sronCmd},
        {"sysCmd", Sron::sysCmd},
        {"throwException", Sron::throwException},
        {"typeof", Sron::typeOf},
        {"version", Sron::version},
        {"setPrecision", Sron::setPrecision},
        {"sizeof", Sron::sizeOf},
        {"cliTextColor", Sron::cliTextColor},
        {"cliBgColor", Sron::cliBgColor}
    };

    inline static SronInBuiltFnc getSronFunction( const SronInBuiltFncIndex_t __fnc_index )
    {
        if ( __fnc_index < sizeof(Fmap)/sizeof(Fmap[0])) [[likely]] return Fmap[__fnc_index]._fnc;

        throw ThrowException("searching for an in-built function", SronException::FunctionNotFoundException);
    }

    #define CHECK_ARGS_COUNT(__count__, __fnc_name__, __format__) if( __args.len() != __count__)throwArgumentException(__fnc_name__, __format__)


    // function to print data on the command line...
    inline static AnyBindPtr print(ArgumentList &__args)
    {
        SronOBuffer buffer;

        const ArgListLen_t length_of_arglist = __args.len();

        for (ArgListLen_t i = 0; i < length_of_arglist; ++i)
        {
            auto value = __args.unsafeGet(i);

            switch( value->type() )
            {
                case SronTypeNum::TYPE_VOID:    voidCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_INT:     intCast( value->ptr() )->fillObuffer ( buffer ); break;

                case SronTypeNum::TYPE_DOUBLE:  doubleCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_CHAR :   charCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_BOOL :   boolCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_STRING : stringCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_LIST :   listCast( value->ptr() )->fillObuffer( buffer ); break;
                
                case SronTypeNum::TYPE_LITERAL_STR : lstrCast(value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_FILE_READER : 

                case SronTypeNum::TYPE_FILE_WRITER : printf(WARNING_MESSAGE_ON_PRINT_FILE); break;

                default: value->ptr()->fillObuffer( buffer ); 
            }
        }

        buffer.flush();

        return Void::void_object;
    }

    // function to print data on the command line with a newline in the end....
    inline static AnyBindPtr println(ArgumentList &__args)
    {
        Sron::print(__args);

        putchar('\n');

        return Void::void_object;
    }

    // function to convert a Char or String type value to lowercase ....
    inline static AnyBindPtr toLowercase(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toLower", "String/Char/LiteralString value");

        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_STRING: return stringCast(value->ptr())->toLowerCase();

            case SronTypeNum::TYPE_CHAR: return charCast(value->ptr())->toLowerCase();

            case SronTypeNum::TYPE_LITERAL_STR : return lstrCast(value->ptr())->toLowerCase();

            default : throwArgumentException("toLower", "String/Char/LiteralString");
        }
        
        return Void::void_object;
    }

    // function to convert a Char or String type value to uppercase ....
    inline static AnyBindPtr toUppercase(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toUpper", "String/Char/LiteralString value");

        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_STRING: return stringCast(value->ptr())->toUpperCase();

            case SronTypeNum::TYPE_CHAR: return charCast(value->ptr())->toUpperCase();

            case SronTypeNum::TYPE_LITERAL_STR : return lstrCast(value->ptr())->toUpperCase();
            
            default : throwArgumentException("toUpper", "String/Char/LiteralString");
        }
        

        return Void::void_object;
    }

    // function to trim a string...
    inline static AnyBindPtr trim(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "trim", "String value");

        auto value = __args.get(0);

        if(value->type() == SronTypeNum::TYPE_STRING)
        {
            stringCast( value->ptr() )->trim();
            
            return Void::void_object;
        }
        
        throwArgumentException("trim", "String");

        return Void::void_object;
    }

    // function to split a string .....
    inline static AnyBindPtr split(ArgumentList &__args)
    {
        if(__args.len() == 1 && __args.get(0)->type() == SronTypeNum::TYPE_STRING)
        {
            ListPtr lst = new List();

            for(const auto& ch : stringCast(__args.unsafeGet(0)->ptr())->getBaseString())
            {
                lst->pushWithoutCopy(new Char(ch), SronTypeNum::TYPE_CHAR);
            }

            return GarbageCollector::registerMemory(lst, SronTypeNum::TYPE_LIST);
        }
        else if(__args.len() == 1 && __args.get(0)->type() == SronTypeNum::TYPE_LITERAL_STR)
        {
            ListPtr lst = new List();

            for(const auto ch : lstrCast(__args.unsafeGet(0)->ptr())->getBaseLstr())
            {
                lst->pushWithoutCopy(new Char(ch), SronTypeNum::TYPE_CHAR);
            }

            return GarbageCollector::registerMemory(lst, SronTypeNum::TYPE_LIST);
        }

        CHECK_ARGS_COUNT(2, "split", "String str, Char delimiter");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);


        if(arg0->type() == SronTypeNum::TYPE_STRING && arg1->type() == SronTypeNum::TYPE_CHAR)
        {
            return GarbageCollector::registerMemory(stringCast(arg0->ptr())->split(*charCast(arg1->ptr())) , SronTypeNum::TYPE_LIST);
        }

        else if(arg0->type() == SronTypeNum::TYPE_LITERAL_STR && arg1->type() == SronTypeNum::TYPE_CHAR)
        {
            return lstrCast(arg0->ptr())->split(arg1->getBaseChar());
        }

        else throwArgumentException("split", "String/LiteralString, Char");

        return Void::void_object;
    }

    inline static AnyBindPtr cliTextColor(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "cliTextColor", "Int r, Int g, Int b");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->type() == SronTypeNum::TYPE_INT && arg1->type() == SronTypeNum::TYPE_INT && arg2->type() == SronTypeNum::TYPE_INT)
        {
            // preparing the rbg terminal color
            std::string color = "\033[38;2;";
            color += arg0->ptr()->toString();
            color += ';';

            color += arg1->ptr()->toString();
            color += ';';

            color += arg2->ptr()->toString();
            color += 'm';

            return GarbageCollector::registerMemory(new String(std::move(color)), SronTypeNum::TYPE_STRING);
        }

        throwArgumentException("cliTextColor", "Int r, Int g, Int b");

        return Void::void_object;
    }

    inline static AnyBindPtr cliBgColor(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "cliBgColor", "Int r, Int g, Int b");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->type() == SronTypeNum::TYPE_INT && arg1->type() == SronTypeNum::TYPE_INT && arg2->type() == SronTypeNum::TYPE_INT)
        {
            // preparing the rgb terminal color
            std::string color = "\033[48;2;";
            color += arg0->ptr()->toString();
            color += ';';

            color += arg1->ptr()->toString();
            color += ';';

            color += arg2->ptr()->toString();
            color += 'm';

            return GarbageCollector::registerMemory(new String(std::move(color)), SronTypeNum::TYPE_STRING);
        }

        throwArgumentException("cliBgColor", "Int r, Int g, Int b");

        return Void::void_object;
    }
}

#endif