
#pragma once

#ifndef FLAG_H
#define FLAG_H

#include "../../../../../../../../sron_headers/_sron_support_.hpp"

#define SRON_DOUBLE_MAX_PRECISION     8
#define SRON_DOUBLE_MIN_PRECISION     1
#define SRON_DOUBLE_DEFAULT_PRECISION 3

enum class SronTypeNum : unsigned short int 
{
    TYPE_VOID      ,
    TYPE_INT       ,
    TYPE_DOUBLE    ,
    TYPE_CHAR      ,
    TYPE_BOOL      ,
    TYPE_STRING    ,
    TYPE_LIST      ,
    TYPE_FILE_READER,
    TYPE_FILE_WRITER,
    TYPE_LITERAL_STR,
    INVALID_TYPE
};

enum class SronExitCodes : int 
{
    EXECUTION_SUCCESS        ,
    BASIC_EXCEPTION          ,
    INVALID_MEMORY_ACCESS    ,
    SYSTEM_OUT_OF_MEMORY     ,
    CPP_STD_EXCEP            ,
    EXCEPTION_THROWN_BY_USER ,
    STACK_OVERFLOW           ,
    SIG_INT                  ,
    SIG_KILL                 ,
    SIG_BREAK                ,
    SIG_TERMINATE            ,
    SIG_ABORT                ,
    SIG_SEG_FAULT            ,
    SIG_UNKNOWN
};

#endif