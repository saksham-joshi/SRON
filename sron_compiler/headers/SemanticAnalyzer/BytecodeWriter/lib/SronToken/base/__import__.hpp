#pragma once

#ifndef _IMPRT_H
#define _IMPRT_H

#include<iostream>
#include<string>
#include<cstring>
#include<unordered_map>
#include<set>
#include<stack>
#include<vector>
#include<fstream>
#include<ctime>
#include<exception>
#include<list>
#include<filesystem>

#include "_flags_.hpp"
#include "../../../../../../../sron_headers/_sron_hasher_.hpp"
#include "../../../../../../../sron_headers/_sron_support_.hpp"
#include "../../../../../../../sron_headers/_cli_colors_.hpp"

#ifdef _WIN64
    #include<Windows.h>
#elif defined(__linux__)
    #include<unistd.h>
    #include<climits>
#else
    #error This codebase is only written for Windows and linux
#endif
 
#endif