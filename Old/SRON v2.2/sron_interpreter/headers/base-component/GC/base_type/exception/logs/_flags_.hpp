
#pragma once

#ifndef FLAG_H
#define FLAG_H

#include "D:\\MY PROJECTS\\SRON_PRIVATE\\sron_headers\\_bytecode_flags_.hpp"

#define SRON_DOUBLE_MAX_PRECISION     8
#define SRON_DOUBLE_MIN_PRECISION     1
#define SRON_DOUBLE_DEFAULT_PRECISION 3

enum SronTypeNum : unsigned short int 
{
    TYPE_VOID      ,
    TYPE_INT       ,
    TYPE_DOUBLE    ,
    TYPE_CHAR      ,
    TYPE_BOOL      ,
    TYPE_STRING    ,
    TYPE_LIST      ,
    INVALID_TYPE
};

enum SronExitCodes : int 
{
    SRON_EXECUTION_SUCCESS        ,
    SRON_BASIC_EXCEPTION          ,
    SRON_INVALID_MEMORY_ACCESS    ,
    SRON_SYSTEM_OUT_OF_MEMORY     ,
    SRON_CPP_STD_EXCEP            ,
    SRON_EXCEPTION_THROWN_BY_USER
};

typedef std::string SronString_t;

#endif