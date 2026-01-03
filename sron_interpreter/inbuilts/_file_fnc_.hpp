#ifndef _FILE_INBUILT_FNC_H
#define _FILE_INBUILT_FNC_H

#include "_type_fnc_.hpp"


inline static AnyBindPtr Sron::fopenRead(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "freader", "String/LiteralString file_name");
        
        AnyBindPtr arg0 = __args.get(0);

        switch(arg0->type())
        {
            case SronTypeNum::TYPE_STRING : return GarbageCollector::registerMemory(new FileReader(stringCast(arg0->ptr())->cStr()), SronTypeNum::TYPE_FILE_READER);

            case SronTypeNum::TYPE_LITERAL_STR : return GarbageCollector::registerMemory(new FileReader(lstrCast(arg0->ptr())->getBaseLstr()), SronTypeNum::TYPE_FILE_READER);
        
            default : { }
        }

        throwArgumentException("freader", "String/LiteralString");

    }

    inline static AnyBindPtr Sron::fopenWrite(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "fwriter", "String/LiteralString file_name, Bool is_append_mode");

        AnyBindPtr arg0 = __args.get(0);
        AnyBindPtr arg1 = __args.get(1);

        if ( arg1->type() == SronTypeNum::TYPE_BOOL)
        {
            SronBool_t is_append_mode = boolCast(arg1->ptr())->getBaseBool();

            if(arg0->type() == SronTypeNum::TYPE_STRING) return GarbageCollector::registerMemory(new FileWriter(stringCast(arg0->ptr())->cStr(), is_append_mode), SronTypeNum::TYPE_FILE_WRITER);

            else if(arg0->type() == SronTypeNum::TYPE_LITERAL_STR) return GarbageCollector::registerMemory(new FileWriter(lstrCast(arg0->ptr())->getBaseLstr(), is_append_mode), SronTypeNum::TYPE_FILE_WRITER);
        }

        throwArgumentException("fwriter", "String/LiteralString, Bool");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::fclose(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "fclose", "FileReader/FileWriter file");

        AnyBindPtr arg_ptr = __args.get(0);

        switch(arg_ptr->type())
        {
            case SronTypeNum::TYPE_FILE_READER : (freaderCast(arg_ptr->ptr()))->close(); break;

            case SronTypeNum::TYPE_FILE_WRITER : (fwriterCast(arg_ptr->ptr()))->close(); break;

            default : throwArgumentException("fclose", "FileReader/FileWriter");
        }

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::fisOpen(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "fisOpen", "FileReader/Filewriter file");
        
        AnyBindPtr arg_ptr = __args.get(0);

        SronBool_t is_opened = false;

        switch(arg_ptr->type())
        {
            case SronTypeNum::TYPE_FILE_READER : is_opened = (freaderCast(arg_ptr->ptr()))->isOpen(); break;

            case SronTypeNum::TYPE_FILE_WRITER : is_opened = (fwriterCast(arg_ptr->ptr()))->isOpen(); break;

            default : throwArgumentException("fisOpen", "FileReader/FileWriter");
        }

        return is_opened ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::fisEnd(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "fisEnd", "FileReader file");

        AnyBindPtr arg_ptr = __args.get(0);

        if( arg_ptr->type() != SronTypeNum::TYPE_FILE_READER)
        {
            throwArgumentException("fisEnd", "FileReader");
        }

        return (freaderCast(arg_ptr->ptr()))->endOfFile() ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::fgetFilename(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "fgetName", "FileReader/FileWriter file");

        AnyBindPtr ptr = __args.get(0);

        StringPtr filename = new String();

        switch(ptr->type())
        {
            case SronTypeNum::TYPE_FILE_READER : filename->append((freaderCast(ptr->ptr()))->getFileName().c_str()); break;

            case SronTypeNum::TYPE_FILE_WRITER : filename->append((fwriterCast(ptr->ptr()))->getFileName().c_str()); break;

            default : throwArgumentException("fgetName", "FileReader/FileWriter" );
        }

        return GarbageCollector::registerMemory(filename, SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr Sron::freset(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "freset", "FileReader file");

        AnyBindPtr ptr = __args.get(0);

        if(ptr->type() != SronTypeNum::TYPE_FILE_READER)
        {
            throwArgumentException("freset", "FileReader");
        }

        freaderCast(ptr->ptr())->reset();

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::fcurPos(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "fcurPos", "FileReader/FileWriter file");

        AnyBindPtr ptr = __args.get(0);

        SronInt_t curpos = 0;

        switch(ptr->type())
        {
            case SronTypeNum::TYPE_FILE_READER : curpos = (freaderCast(ptr->ptr()))->tell(); break;

            case SronTypeNum::TYPE_FILE_WRITER : curpos = (fwriterCast(ptr->ptr()))->tell(); break;

            default : throwArgumentException("fcurPos", "FileReader/FileWriter");
        }

        return GarbageCollector::registerMemory(new Int(curpos), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr Sron::fsetSeek(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "fsetSeek", "FileReader/FileWriter file, Int position");

        AnyBindPtr fileptr = __args.get(0);
        AnyBindPtr setpos = __args.get(1);

        if(setpos->type() != SronTypeNum::TYPE_INT)
        {
            throwArgumentException("fsetSeek", "FileReader/FileWriter, Int");
        }

        SronInt_t set_position = intCast(setpos->ptr())->getBaseInt();

        switch(fileptr->type())
        {
            case SronTypeNum::TYPE_FILE_READER : (freaderCast(fileptr->ptr()))->setSeek(set_position); break;

            case SronTypeNum::TYPE_FILE_WRITER : (fwriterCast(fileptr->ptr()))->setSeek(set_position); break;

            default : throwArgumentException("fsetSeek", "FileReader/FileWriter, Int");
        }

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::freadChar(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "freadChar", "FileReader file");

        AnyBindPtr ptr = __args.get(0);

        if(ptr->type() != SronTypeNum::TYPE_FILE_READER)
        {
            throwArgumentException("freadChar", "FileReader");
        }

        FreadPtr fr = freaderCast(ptr->ptr());

        return GarbageCollector::registerMemory(fr->readChar(), SronTypeNum::TYPE_CHAR);
    }

    inline static AnyBindPtr Sron::freadLine(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "freadLine", "FileReader file");

        AnyBindPtr ptr = __args.get(0);

        if(ptr->type() != SronTypeNum::TYPE_FILE_READER)
        {
            throwArgumentException("freadLine", "FileReader");
        }

        FreadPtr fr = freaderCast(ptr->ptr());

        return GarbageCollector::registerMemory(fr->readLine(), SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr Sron::freadWhole(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "freadWhole", "FileReader file");

        AnyBindPtr ptr = __args.get(0);

        if(ptr->type() != SronTypeNum::TYPE_FILE_READER)
        {
            throwArgumentException("freadWhole", "FileReader");
        }

        FreadPtr fr = freaderCast(ptr->ptr());

        return GarbageCollector::registerMemory(fr->readWhole(), SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr Sron::fwriteChar(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "fwriteChar", "FileWriter file, Char ch");

        AnyBindPtr arg0 = __args.get(0);
        AnyBindPtr arg1 = __args.get(1);

        if(arg0->type() == SronTypeNum::TYPE_FILE_WRITER && arg1->type() == SronTypeNum::TYPE_CHAR)
        {
            fwriterCast(arg0->ptr())->writeChar(arg1->getBaseChar());
        }
        else
        {
            throwArgumentException("fwriteChar", "FileWriter, Char");
        }

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::fwriteString(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "fwriteString", "FileWriter file, String/LiteralString str" );

        AnyBindPtr arg0 = __args.get(0);
        AnyBindPtr arg1 = __args.get(1);

        if(arg0->type() == SronTypeNum::TYPE_FILE_WRITER && arg1->type() == SronTypeNum::TYPE_STRING)
        {
            fwriterCast(arg0->ptr())->writeString(arg1->getBaseStr());
        }
        else if(arg0->type() == SronTypeNum::TYPE_FILE_WRITER && arg1->type() == SronTypeNum::TYPE_LITERAL_STR)
        {
            fwriterCast(arg0->ptr())->writeString(arg1->getBaseLstr());
        }
        else
        {
            throwArgumentException("fwriteString", "FileWriter, String/LiteralString");
        }
        return Void::void_object;
    }
#endif 