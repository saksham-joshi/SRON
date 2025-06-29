#pragma once

#ifndef _IMPRT_H
#define _IMPRT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <filesystem>


#include "_flags_.hpp"
#include "../../../../../../../sron_headers/_sron_hasher_.hpp"

#ifdef _WIN64
    #include<windows.h>
#else
    #error "THIS SOURCE CODE IS ONLY COMPATIBLE WITH WINDOWS"
#endif

#pragma GCC poison printf
#pragma GCC poison scanf

#endif